#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ulf/dcc_ein.hpp>

using namespace std::literals;

TEST(sendbidi_str2addressed_datagram, string_empty) {
  auto d{ulf::dcc_ein::sendbidi_str2addressed_datagram("")};
  EXPECT_TRUE(d);
  EXPECT_FALSE(*d);
}

TEST(sendbidi_str2addressed_datagram, string_too_short) {
  auto d{ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendbidi s002a f4 58 81 3b c4 79 df\r")};
  EXPECT_TRUE(d);
  EXPECT_FALSE(*d);
}

TEST(sendbidi_str2addressed_datagram, string_does_not_start_with_sendbidi) {
  auto d{ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendXXXX s002a f4 58 81 3b c4 79 f5 df\r")};
  EXPECT_FALSE(d);
  EXPECT_EQ(d, std::unexpected(std::errc::invalid_argument));
}

TEST(sendbidi_str2addressed_datagram, address_identifier_wrong) {
  auto d{ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendbidi x002a f4 58 81 3b c4 79 f5 df\r")};
  EXPECT_FALSE(d);
  EXPECT_EQ(d, std::unexpected(std::errc::invalid_argument));
}

TEST(sendbidi_str2addressed_datagram, string_valid) {
  auto d{ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendbidi s002a f4 58 81 3b c4 79 f5 df\r")};
  EXPECT_TRUE(d);
  EXPECT_TRUE(*d);
  auto [addr, datagram]{**d};
  EXPECT_EQ(addr, (dcc::Address{.value = 0x2Au, .type = dcc::Address::Short}));
}
