// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert senddcc string to packet
///
/// \file   dcc_ein/rx/str2packet.hpp
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
/// \return dcc::Packet for valid strings
/// \return std::nullopt for invalid strings
constexpr std::optional<dcc::Packet> str2packet(std::string_view str) {
  // String must be of certain length and starting with "senddcc "
  if (size(str) < 17uz || !str.starts_with(senddcc)) return std::nullopt;

  // Find \r
  auto const last{std::ranges::find(str, '\r')};
  if (last == cend(str)) return std::nullopt;

  // Data length must be multiple of 3
  auto const str_len{static_cast<size_t>(last - cbegin(str))};
  auto const data_len{str_len + 1uz - size(senddcc)};
  if (data_len % 3uz) return std::nullopt;

  // Convert string to packet
  dcc::Packet packet{
    .size = static_cast<decltype(dcc::Packet::size)>(data_len / 3uz)};
  for (auto i{0uz}; i < packet.size; ++i) {
    auto const first{&str[8uz + 3uz * i]};
    [[maybe_unused]] auto const [ptr, ec]{
      std::from_chars(first, first + 2, packet.data[i], 16)};
    if (ec != std::errc{}) return std::nullopt;
  }
  return packet;
}

}  // namespace dcc_ein::rx