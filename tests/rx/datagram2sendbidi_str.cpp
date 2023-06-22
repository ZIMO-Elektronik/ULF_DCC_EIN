#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <dcc_ein/dcc_ein.hpp>

using namespace std::literals;

TEST(datagram2sendbidi_str, datagram_too_short) {
  dcc::Address addr{.value = 3u, .type = dcc::Address::Short};
  std::array<uint8_t, dcc::bidi::channel1_size - 1uz> datagram;
  EXPECT_FALSE(dcc_ein::rx::datagram2sendbidi_str(addr, datagram));
}

TEST(datagram2sendbidi_str, datagram_too_long) {
  dcc::Address addr{.value = 3u, .type = dcc::Address::Short};
  std::array<uint8_t, dcc::bidi::bundled_channels_size + 1uz> datagram;
  EXPECT_FALSE(dcc_ein::rx::datagram2sendbidi_str(addr, datagram));
}

TEST(datagram2sendbidi_str, short_address) {
  dcc::Address addr{.value = 3u, .type = dcc::Address::Short};
  dcc::bidi::BundledChannels datagram{
    0xF4u, 0x58u, 0x81u, 0x3Bu, 0xC4u, 0x79u, 0xF5u, 0xDFu};
  EXPECT_TRUE(
    std::ranges::equal(*dcc_ein::rx::datagram2sendbidi_str(addr, datagram),
                       "sendbidi s0003 f4 58 81 3b c4 79 f5 df\r"sv));

  addr = {.value = 42u, .type = dcc::Address::Short};
  EXPECT_TRUE(
    std::ranges::equal(*dcc_ein::rx::datagram2sendbidi_str(addr, datagram),
                       "sendbidi s002a f4 58 81 3b c4 79 f5 df\r"sv));
}

TEST(datagram2sendbidi_str, long_address) {
  dcc::Address addr{.value = 4217u, .type = dcc::Address::Long};
  dcc::bidi::Channel2 datagram{0xF4u, 0x58u, 0x81u, 0x3Bu, 0xC4u, 0x79u};
  EXPECT_TRUE(
    std::ranges::equal(*dcc_ein::rx::datagram2sendbidi_str(addr, datagram),
                       "sendbidi l1079 f4 58 81 3b c4 79 00 00\r"sv));
}

TEST(datagram2sendbidi_str, accessory_address) {
  dcc::Address addr{.value = 271u, .type = dcc::Address::Accessory};
  dcc::bidi::Channel1 datagram{0xF4u, 0x58u};
  EXPECT_TRUE(
    std::ranges::equal(*dcc_ein::rx::datagram2sendbidi_str(addr, datagram),
                       "sendbidi a010f f4 58 00 00 00 00 00 00\r"sv));
}
