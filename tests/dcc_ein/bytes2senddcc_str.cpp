#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ulf/dcc_ein.hpp>

TEST(bytes2senddcc_str, std_string_and_buffer_versions_are_equal) {
  std::array<uint8_t, 4uz> chunk{0x0Au, 0x12u, 0x49u, 0xFCu};

  // std::string version
  auto std_str{ulf::dcc_ein::bytes2senddcc_str(chunk)};
  EXPECT_EQ(std_str, "senddcc 0a 12 49 fc\r");

  // preallocated buffer version
  std::array<char, 64uz> buf_str;
  auto last{ulf::dcc_ein::bytes2senddcc_str(chunk, data(buf_str))};
  EXPECT_TRUE(std::equal(cbegin(std_str), cend(std_str), data(buf_str)));
  EXPECT_EQ(size(std_str), last - data(buf_str));
}
