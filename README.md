# ULF_DCC_EIN

[![build](https://github.com/ZIMO-Elektronik/ULF_DCC_EIN/actions/workflows/build.yml/badge.svg)](https://github.com/ZIMO-Elektronik/ULF_DCC_EIN/actions/workflows/build.yml) [![tests](https://github.com/ZIMO-Elektronik/ULF_DCC_EIN/actions/workflows/tests.yml/badge.svg)](https://github.com/ZIMO-Elektronik/ULF_DCC_EIN/actions/workflows/tests.yml)

<img src="data/images/logo.svg" width="20%" align="right">

ULF_DCC_EIN is a ASCII protocol used by the [ZIMO Sound Programmer](http://www.zimo.at/web2010/products/zsp_zimo-sound-programmer.htm). This C++ library of the same name contains code to either encode binary data into an ASCII string or vice versa to encode an ASCII string back into binary data. The protocol is currently supported by the following products:
- Command stations
  - [ZIMO MXULF](http://www.zimo.at/web2010/products/InfMXULF_EN.htm)

<details>
  <summary>Table of contents</summary>
  <ol>
    <li><a href="#protocol">Protocol</a></li>
      <ul>
        <li><a href="#senddcc">senddcc</a></li>
        <li><a href="#sendbidi">sendbidi</a></li>
      </ul>
    <li><a href="#getting-started">Getting started</a></li>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#build">Build</a></li>
      </ul>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>

## Protocol
The protocol consists of only two commands, both of which send raw data encoded as hex ASCII. A `senddcc` command to send DCC and a `sendbidi` command to receive BiDi feedback. Both command strings are terminated with a carriage return.

![](data/images/protocol.png)

### senddcc
The string of the `senddcc` command follows the pattern `senddcc( [0-9a-fA-F]{2}){3,}\r`. The hex ASCII coded bytes contained in the string correspond to the data bytes of the DCC command including the checksum.

The command can optionally be answered with a string of the pattern `senddcc [a-fA-F]([0-9a-fA-F]{2})\r`. The response contains an identifier and a hex ASCII encoded data byte whose meaning depends on the identifier.
| Response byte preceding character | Response byte type                                      |
| --------------------------------- | ------------------------------------------------------- |
| b                                 | Response byte indicates current buffer level in bytes   |
| p                                 | response byte indicates current buffer level in packets |

### sendbidi
The string of the `sendbidi` command follows the pattern `sendbidi [ubsalrtei][0-9a-fA-F]{4}( [0-9a-fA-F]{2}){8}\r`. In addition to the hex ASCII coded datagram, the command also contains the address belonging to the datagram. Since DCC addresses are not unique, an associated identifier that determines the address type must also be included.

| Address preceding character | DCC address type   |
| --------------------------- | ------------------ |
| u                           | Unknown or service |
| b                           | Broadcast          |
| s                           | Short              |
| a                           | Accessory          |
| l                           | Long               |
| r                           | Reserved           |
| t                           | Data transfer      |
| e                           | Automatic logon    |
| i                           | Idle or system     |

## Getting started
### Prerequisites
- C++23 compatible compiler
- [CMake](https://cmake.org/) ( >= 3.25 )

### Installation
This library is meant to be consumed with CMake.

```cmake
# Either by including it with CPM
cpmaddpackage("gh:ZIMO-Elektronik/DCC_EIN@0.0.1")

# or the FetchContent module
FetchContent_Declare(
  DCC
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/DCC_EIN
  GIT_TAG v0.0.1)

target_link_libraries(YourTarget INTERFACE DCC_EIN::DCC_EIN)
```

### Build
If the build is running as a top-level CMake project then tests and a small example will be generated.
```sh
cmake -Bbuild
cmake --build build --target DCC_EINExamples
```

## Usage
```cpp
// Create a DCC advanced operations speed packet
dcc::Packet packet{dcc::make_advanced_operations_speed_packet(3u, -1, 10u)};

// Create senddcc string from packet
auto senddcc_str{dcc_ein::tx::packet2senddcc_str(packet)};

// Alternatively use a preallocated buffer
std::array<char, 64uz> senddcc_str_buf;
auto last{dcc_ein::tx::packet2senddcc_str(packet, data(senddcc_str_buf))};
auto senddcc_str_buf_len{last - cbegin(senddcc_str_buf)};

// Create DCC packet from senddcc string
auto packet_from_str{dcc_ein::rx::senddcc_str2packet(senddcc_str)};

// Create sendbidi string from address and datagram
dcc_ein::AddressedDatagram addressed_datagram{
  .addr = {.value = 3u, .type = dcc::Address::Short},
  .datagram = {0xA3u, 0xACu, 0x55u, 0xB1u, 0xD2u, 0x5Au, 0xACu, 0x9Au}};
auto sendbidi_str{
  dcc_ein::rx::addressed_datagram2sendbidi_str(addressed_datagram)};

// Create pair of address and datagram from sendbidi string
auto addr_datagram{dcc_ein::tx::sendbidi_str2addressed_datagram(
  {cbegin(*sendbidi_str), cend(*sendbidi_str)})};
auto [addr_from_str, datagram_from_str]{*addr_datagram};
```