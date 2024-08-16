// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert senddcc string to packet
///
/// \file   ulf/dcc_ein/senddcc_str2packet.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <charconv>
#include <dcc/dcc.hpp>
#include <expected>
#include <optional>
#include <string_view>
#include <system_error>
#include "senddcc.hpp"

namespace ulf::dcc_ein {

/// Convert senddcc string to packet
///
/// String should have the pattern 'senddcc( [0-9a-fA-F]{2}){3,}\r'. If the
/// string contains multiple packets only the first one is returned.
///
/// \param  str                             senddcc string
/// \return dcc::Packet                     dcc::Packet created from string
/// \retval std::nullopt                    Not enough characters
/// \retval std::errc::invalid_argument     Invalid senddcc string
/// \retval std::errc::result_out_of_range  Datagram out of range
constexpr std::expected<std::optional<dcc::Packet>, std::errc>
senddcc_str2packet(std::string_view str) {
  auto const count{size(str)};

  // String must start width "senddcc "
  if (!str.starts_with(senddcc_prefix.substr(0uz, count)))
    return std::unexpected(std::errc::invalid_argument);

  // String must be of certain length
  if (count < 17uz) return std::nullopt;

  // Find \r
  auto const last{std::ranges::find(str, '\r')};
  if (last == cend(str)) return std::nullopt;

  // Data length must be multiple of 3
  auto const str_len{static_cast<size_t>(last - cbegin(str))};
  auto const data_len{str_len + 1uz - size(senddcc_prefix)};
  if (data_len % 3uz) return std::unexpected(std::errc::invalid_argument);

  // Hex string to binary
  dcc::Packet packet;
  packet.resize(static_cast<dcc::Packet::size_type>(data_len / 3uz));
  for (dcc::Packet::size_type i{}; i < size(packet); ++i) {
    auto const first{&str[size(senddcc_prefix) + 3uz * i]};
    if (auto const [ptr, ec]{std::from_chars(first, first + 2, packet[i], 16)};
        ec != std::errc{})
      return std::unexpected(ec);
  }
  return packet;
}

}  // namespace ulf::dcc_ein