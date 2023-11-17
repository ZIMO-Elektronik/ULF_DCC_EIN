#include <ulf/dcc_ein.hpp>

auto packet2senddcc_str() {
  // Create a DCC advanced operations speed packet
  dcc::Packet packet{dcc::make_advanced_operations_speed_packet(3u, 1, 10u)};

  // Create senddcc string from packet
  auto senddcc_str{ulf::dcc_ein::packet2senddcc_str(packet)};

  // Alternatively use a preallocated buffer
  std::array<char, 64uz> senddcc_str_buf;
  auto last{ulf::dcc_ein::packet2senddcc_str(packet, data(senddcc_str_buf))};
  auto senddcc_str_buf_len{last - cbegin(senddcc_str_buf)};

  return senddcc_str;
}

void senddcc_str2packet(auto&& senddcc_str) {
  // Create DCC packet from senddcc string
  auto maybe_packet{ulf::dcc_ein::senddcc_str2packet(senddcc_str)};

  // Could be DCC packet
  if (maybe_packet) {
    // Already complete?
    if (*maybe_packet) {
      // Complete DCC packet
      auto packet{**maybe_packet};
    }
    // No, still missing characters
    else {}
  }
  // Error, not DCC packet
  else {}
}

auto addressed_datagram2sendbidi_str() {
  // Create sendbidi string from address and datagram
  ulf::dcc_ein::AddressedDatagram addressed_datagram{
    .addr = {.value = 3u, .type = dcc::Address::Short},
    .datagram = {0xA3u, 0xACu, 0x55u, 0xB1u, 0xD2u, 0x5Au, 0xACu, 0x9Au}};
  auto sendbidi_str{
    ulf::dcc_ein::addressed_datagram2sendbidi_str(addressed_datagram)};

  return sendbidi_str;
}

void sendbidi_str2addressed_datagram(auto&& sendbidi_str) {
  // Create pair of address and datagram from sendbidi string
  auto addr_datagram{ulf::dcc_ein::sendbidi_str2addressed_datagram(
    {cbegin(sendbidi_str), cend(sendbidi_str)})};
  auto [addr_from_str, datagram_from_str]{**addr_datagram};
}

int main() {
  auto senddcc_str{packet2senddcc_str()};
  senddcc_str2packet(senddcc_str);
  auto sendbidi_str{addressed_datagram2sendbidi_str()};
  sendbidi_str2addressed_datagram(sendbidi_str);
}