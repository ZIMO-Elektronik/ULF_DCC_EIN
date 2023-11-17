#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ulf/dcc_ein.hpp>

using namespace std::literals;

TEST(sendbidi_str2addressed_datagram, string_too_short) {
  EXPECT_FALSE(ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendbidi s002a f4 58 81 3b c4 79 df\r"sv));
}

TEST(sendbidi_str2addressed_datagram, string_does_not_start_with_sendbidi) {
  EXPECT_FALSE(ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendXXXX s002a f4 58 81 3b c4 79 f5 df\r"sv));
}

TEST(sendbidi_str2addressed_datagram, address_identifier_wrong) {
  EXPECT_FALSE(ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendbidi x002a f4 58 81 3b c4 79 f5 df\r"sv));
}

TEST(sendbidi_str2addressed_datagram, BLA_BLA) {
  auto retval{ulf::dcc_ein::sendbidi_str2addressed_datagram(
    "sendbidi s002a f4 58 81 3b c4 79 f5 df\r"sv)};
  EXPECT_TRUE(retval);
  auto [addr, datagram]{*retval};
  EXPECT_EQ(addr, (dcc::Address{.value = 0x2Au, .type = dcc::Address::Short}));
}
