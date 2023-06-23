// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert sendbidi string to pair of address and datagram
///
/// \file   dcc_ein/tx/sendbidi_str2datagram.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include <charconv>
#include <optional>
#include <string_view>
#include "../senddcc.hpp"

namespace dcc_ein::tx {

/// Convert sendbidi string to pair of address and datagram
///
/// \param  str sendbidi string
/// \return Pair of address and datagram for valid strings
/// \return std::nullopt for invalid strings
inline std::optional<std::pair<dcc::Address, dcc::bidi::BundledChannels>>
sendbidi_str2datagram(std::string_view str) {
  if (size(str) < sendbidi_str_size || !str.starts_with(sendbidi_prefix))
    return std::nullopt;

  dcc::Address addr;

  // Address type identifier
  switch (str[size(sendbidi_prefix)]) {
    case 'u': addr.type = dcc::Address::UnknownService; break;
    case 'b': addr.type = dcc::Address::Broadcast; break;
    case 's': addr.type = dcc::Address::Short; break;
    case 'a': addr.type = dcc::Address::Accessory; break;
    case 'l': addr.type = dcc::Address::Long; break;
    case 'r': addr.type = dcc::Address::Reserved; break;
    case 't': addr.type = dcc::Address::TipOffSearch; break;  // May change
    case 'e': addr.type = dcc::Address::ExtendedPacket; break;
    case 'i': addr.type = dcc::Address::IdleSystem; break;
    default: return std::nullopt;
  }

  // Address
  if (std::from_chars(&str[size(sendbidi_prefix) + 1uz],
                      &str[size(sendbidi_prefix) + 1uz + 4uz],
                      addr.value,
                      16)
        .ec != std::errc{})
    return std::nullopt;

  // Datagram
  dcc::bidi::BundledChannels datagram;
  for (auto i{0uz}; i < dcc::bidi::bundled_channels_size; ++i) {
    auto const first{&str[size(sendbidi_prefix) + 1uz + 4uz + 1uz + 3uz * i]};
    if (std::from_chars(first, first + 2, datagram[i], 16).ec != std::errc{})
      return std::nullopt;
  }

  return std::pair{addr, datagram};
}

}  // namespace dcc_ein::tx