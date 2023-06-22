// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert acknowledge to senddcc string
///
/// \file   dcc_ein/rx/ack2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include <charconv>
#include <dcc/dcc.hpp>
#include <string_view>
#include "../senddcc.hpp"

namespace dcc_ein::rx {

/// Convert acknowledge to senddcc string
///
/// The returned string will have the pattern 'senddcc [a-z]([0-9a-f]{2})\r'.
/// This string is sent as acknowledge to received senddcc strings. Depending on
/// the transferred ID, the response byte has different meanings.
///
/// \param  id    'b' response byte indicates current buffer level in bytes
///               'p' response byte indicates current buffer level in packets
/// \param  byte  Response byte
/// \return senddcc string for acknowledge
constexpr std::array<char, size(senddcc) + 4uz> ack2senddcc_str(char id,
                                                                uint8_t byte) {
  // Copy prefix
  std::array<char, size(senddcc) + 4uz> str{};
  auto first{std::copy(cbegin(senddcc), cend(senddcc), data(str))};

  // Add ID
  *first++ = id;

  // Add byte
  if (byte <= 0xFu) *first++ = '0';
  first = std::to_chars(first, end(str), byte, 16).ptr;

  *first = '\r';

  return str;
}

}  // namespace dcc_ein::rx