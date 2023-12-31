#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ulf/dcc_ein.hpp>

TEST(packet2senddcc_str, std_string_and_buffer_versions_are_equal) {
  dcc::Packet packet{0x0Au, 0x12u, 0x49u, 0xFCu};

  // std::string version
  auto std_str{ulf::dcc_ein::packet2senddcc_str(packet)};
  EXPECT_EQ(std_str, "senddcc 0a 12 49 fc\r");

  // preallocated buffer version
  std::array<char, 64uz> buf_str;
  auto last{ulf::dcc_ein::packet2senddcc_str(packet, data(buf_str))};
  EXPECT_TRUE(std::equal(cbegin(std_str), cend(std_str), data(buf_str)));
  EXPECT_EQ(size(std_str), last - data(buf_str));
}
