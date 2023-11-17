// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert bytes to senddcc string
///
/// \file   ulf/dcc_ein/bytes2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <charconv>
#include <optional>
#include <span>
#include <string>
#include "senddcc.hpp"

namespace ulf::dcc_ein {

/// Convert bytes to senddcc string into provided buffer
///
/// \param  bytes Bytes
/// \param  out   Pointer to the destination buffer
/// \return One-past-the-end pointer of the characters written
inline char* bytes2senddcc_str(std::span<uint8_t const> bytes, char* out) {
  // Prefix
  out = std::copy(cbegin(senddcc_prefix), cend(senddcc_prefix) - 1, out);

  // Chunk
  for (auto const byte : bytes) {
    *out++ = ' ';
    if (byte <= 0xFu) *out++ = '0';
    out = std::to_chars(out, out + 2, byte, 16).ptr;
  }

  *out++ = '\r';

  return out;
}

/// Convert bytes to senddcc string
///
/// \param  bytes Bytes
/// \return senddcc string
inline std::string bytes2senddcc_str(std::span<uint8_t const> bytes) {
  std::string str(size(senddcc_prefix) + 3uz * size(bytes), '\0');
  bytes2senddcc_str(bytes, data(str));
  return str;
}

}  // namespace ulf::dcc_ein