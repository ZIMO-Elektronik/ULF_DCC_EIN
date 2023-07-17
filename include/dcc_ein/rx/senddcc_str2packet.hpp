// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert senddcc string to packet
///
/// \file   dcc_ein/rx/senddcc_str2packet.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include <charconv>
#include <dcc/dcc.hpp>
#include <optional>
#include <string_view>
#include "../senddcc.hpp"

namespace dcc_ein::rx {

/// Convert senddcc string to packet
///
/// String should have the pattern 'senddcc( [0-9a-fA-F]{2}){3,}\r'. If the
/// string contains multiple packets only the first one is returned.
///
/// \param  str senddcc string
/// \return dcc::Packet for valid strings
/// \return std::nullopt for invalid strings
inline std::optional<dcc::Packet> senddcc_str2packet(std::string_view str) {
  // String must be of certain length and starting with "senddcc "
  if (size(str) < 17uz || !str.starts_with(senddcc_prefix)) return std::nullopt;

  // Find \r
  auto const last{std::ranges::find(str, '\r')};
  if (last == cend(str)) return std::nullopt;

  // Data length must be multiple of 3
  auto const str_len{static_cast<size_t>(last - cbegin(str))};
  auto const data_len{str_len + 1uz - size(senddcc_prefix)};
  if (data_len % 3uz) return std::nullopt;

  // Hex string to binary
  dcc::Packet packet;
  packet.resize(static_cast<dcc::Packet::size_type>(data_len / 3uz));
  for (dcc::Packet::size_type i{}; i < size(packet); ++i) {
    auto const first{&str[size(senddcc_prefix) + 3uz * i]};
    if (std::from_chars(first, first + 2, packet[i], 16).ec != std::errc{})
      return std::nullopt;
  }
  return packet;
}

}  // namespace dcc_ein::rx