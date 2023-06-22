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
#include <optional>
#include <string_view>
#include "../senddcc.hpp"

namespace dcc_ein::rx {

///
/// \return
constexpr std::array<char, size(senddcc) + 3uz> ack2senddcc_str(uint8_t code) {
  // Copy prefix
  std::array<char, size(senddcc) + 3uz> str{};
  auto first{std::copy(cbegin(senddcc), cend(senddcc), data(str))};

  // Add code
  if (code <= 0xFu) *first++ = '0';
  first = std::to_chars(first, end(str), code, 16).ptr;

  *first = '\r';

  return str;
}

}  // namespace dcc_ein::rx