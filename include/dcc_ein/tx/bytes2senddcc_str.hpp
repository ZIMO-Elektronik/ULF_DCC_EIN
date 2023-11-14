// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert raw data to senddcc string
///
/// \file   dcc_ein/tx/bytes2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   14/11/2023

#pragma once

#include <charconv>
#include <optional>
#include <span>
#include <string>
#include "../senddcc.hpp"

namespace dcc_ein::tx {

/// Convert bytes to senddcc string into provided buffer
///
/// \param  bytes Bytes
/// \param  out   Pointer to the destination buffer
/// \return One-past-the-end pointer of the characters written
inline char* bytes2senddcc_str(std::span<uint8_t const> chunk, char* out) {
  // Prefix
  out = std::copy(cbegin(senddcc_prefix), cend(senddcc_prefix) - 1, out);

  // Chunk
  for (auto const byte : chunk) {
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
inline std::string bytes2senddcc_str(std::span<uint8_t const> chunk) {
  std::string str(size(senddcc_prefix) + 3uz * size(chunk), '\0');
  bytes2senddcc_str(chunk, data(str));
  return str;
}

}  // namespace dcc_ein::tx