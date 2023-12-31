#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ulf/dcc_ein.hpp>

using namespace std::literals;

TEST(senddcc_str2packet, string_empty) {
  auto p{ulf::dcc_ein::senddcc_str2packet("")};
  EXPECT_TRUE(p);
  EXPECT_FALSE(*p);
}

TEST(senddcc_str2packet, string_too_short) {
  // Too short
  {
    auto p{ulf::dcc_ein::senddcc_str2packet("senddcc 00")};
    EXPECT_TRUE(p);
    EXPECT_FALSE(*p);
  }

  // Still too short
  {
    auto p{ulf::dcc_ein::senddcc_str2packet("senddcc 00 01\r")};
    EXPECT_TRUE(p);
    EXPECT_FALSE(*p);
  }
}

TEST(senddcc_str2packet, string_does_not_start_with_senddcc) {
  auto p{ulf::dcc_ein::senddcc_str2packet("00 01 02 03 04 05 06\r")};
  EXPECT_FALSE(p);
  EXPECT_EQ(p, std::unexpected(std::errc::invalid_argument));
}

TEST(senddcc_str2packet, string_does_not_contain_carriage_return) {
  EXPECT_FALSE(ulf::dcc_ein::senddcc_str2packet("00 01 02 03 04 05 06 07"));
}

TEST(senddcc_str2packet, string_contains_unexpected_chars) {
  auto p{ulf::dcc_ein::senddcc_str2packet("senddcc 00 01 0w2 03 04 05 06\r")};
  EXPECT_FALSE(p);
  EXPECT_EQ(p, std::unexpected(std::errc::invalid_argument));
}

TEST(senddcc_str2packet, string_valid) {
  EXPECT_EQ(
    ulf::dcc_ein::senddcc_str2packet("senddcc 3F 8E 96 5D 38 45 F8 47\r"),
    (dcc::Packet{0x3Fu, 0x8Eu, 0x96u, 0x5Du, 0x38u, 0x45u, 0xF8u, 0x47u}));
}

TEST(senddcc_str2packet, hex_data_is_case_insensitive) {
  EXPECT_EQ(
    ulf::dcc_ein::senddcc_str2packet("senddcc 3f 8E 96 5d 38 45 f8 47\r"),
    (dcc::Packet{0x3Fu, 0x8Eu, 0x96u, 0x5Du, 0x38u, 0x45u, 0xF8u, 0x47u}));
}

TEST(senddcc_str2packet, string_data_not_multiple_of_three_chars) {
  auto p{ulf::dcc_ein::senddcc_str2packet("senddcc 3F 8E  96 5D\r")};
  EXPECT_FALSE(p);
  EXPECT_EQ(p, std::unexpected(std::errc::invalid_argument));
}

TEST(senddcc_str2packet, string_can_be_longer) {
  EXPECT_EQ(
    ulf::dcc_ein::senddcc_str2packet("senddcc A0 57 AC 02 9B\r senddcc 0"),
    (dcc::Packet{0xA0u, 0x57u, 0xACu, 0x02u, 0x9Bu}));
}