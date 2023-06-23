// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert datagram to sendbidi string
///
/// \file   dcc_ein/rx/datagram2sendbidi_str.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include <algorithm>
#include <charconv>
#include <dcc/dcc.hpp>
#include <optional>
#include <string_view>
#include "../sendbidi.hpp"

namespace dcc_ein::rx {

/// Convert datagram to sendbidi string
///
/// The returned string will have the pattern
/// 'sendbidi [ubsalrtei][0-9a-f]{4}( [0-9a-f]{2}){8}\r'. This string is sent
/// when a BiDi datagram has been received.
///
/// \param  addr      Address
/// \param  datagram  Datagram
/// \return sendbidi string for valid datagrams
/// \return std::nullopt for invalid datagrams
inline std::optional<std::array<char, sendbidi_str_size>>
datagram2sendbidi_str(dcc::Address addr, std::span<uint8_t const> datagram) {
  // Datagram can't be smaller than channel1 or bundled size
  if (size(datagram) < dcc::bidi::channel1_size ||
      size(datagram) > dcc::bidi::bundled_channels_size)
    return std::nullopt;

  // Prefix
  std::array<char, sendbidi_str_size> str{};
  auto first{
    std::copy(cbegin(sendbidi_prefix), cend(sendbidi_prefix), data(str))};

  // Address type identifier
  switch (addr.type) {
    case dcc::Address::UnknownService: *first++ = 'u'; break;
    case dcc::Address::Broadcast: *first++ = 'b'; break;
    case dcc::Address::Short: *first++ = 's'; break;
    case dcc::Address::Accessory: *first++ = 'a'; break;
    case dcc::Address::Long: *first++ = 'l'; break;
    case dcc::Address::Reserved: *first++ = 'r'; break;
    case dcc::Address::TipOffSearch: *first++ = 't'; break;  // May change
    case dcc::Address::ExtendedPacket: *first++ = 'e'; break;
    case dcc::Address::IdleSystem: *first++ = 'i'; break;
  }

  // Address
  if (addr <= 0xFFFu) {
    *first++ = '0';
    if (addr <= 0xFFu) {
      *first++ = '0';
      if (addr <= 0xFu) *first++ = '0';
    }
  }
  first = std::to_chars(first, end(str), addr, 16).ptr;

  // Datagram
  for (auto i{0uz}; i < dcc::bidi::bundled_channels_size; ++i) {
    *first++ = ' ';
    auto const byte{i < size(datagram) ? datagram[i] : 0u};
    if (byte <= 0xFu) *first++ = '0';
    first = std::to_chars(first, end(str), byte, 16).ptr;
  }

  *first = '\r';

  return str;
}

}  // namespace dcc_ein::rx