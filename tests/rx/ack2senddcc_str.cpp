#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <dcc_ein/dcc_ein.hpp>

using namespace std::literals;

TEST(ack2senddcc_str, bla) {
  EXPECT_TRUE(
    std::ranges::equal(dcc_ein::rx::ack2senddcc_str(0xAAu), "senddcc aa\r"sv));
}
