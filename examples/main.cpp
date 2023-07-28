#include <dcc_ein/dcc_ein.hpp>

int main() {
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
}