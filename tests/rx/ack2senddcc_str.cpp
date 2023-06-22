#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <dcc_ein/dcc_ein.hpp>

using namespace std::literals;

TEST(ack2senddcc_str, current_buffer_level_in_bytes) {
  EXPECT_TRUE(std::ranges::equal(dcc_ein::rx::ack2senddcc_str('b', 0xAAu),
                                 "senddcc baa\r"sv));
  EXPECT_TRUE(std::ranges::equal(dcc_ein::rx::ack2senddcc_str('b', 0x07u),
                                 "senddcc b07\r"sv));
}
