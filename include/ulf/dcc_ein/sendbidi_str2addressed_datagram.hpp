// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert sendbidi string to addressed datagram
///
/// \file   ulf/dcc_ein/sendbidi_str2addressed_datagram.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <charconv>
#include <expected>
#include <optional>
#include <string_view>
#include <system_error>
#include "addressed_datagram.hpp"
#include "senddcc.hpp"

namespace ulf::dcc_ein {

/// Convert sendbidi string to addressed datagram
///
/// \param  str sendbidi string
/// \return Addressed datagram
/// \return std::nullopt for invalid strings
inline std::expected<std::optional<AddressedDatagram>, std::errc>
sendbidi_str2addressed_datagram(std::string_view str) {
  auto const count{size(str)};

  // String must start width "sendbidi "
  if (!str.starts_with(sendbidi_prefix.substr(0uz, count)))
    return std::unexpected(std::errc::invalid_argument);

  // String must be of certain length
  if (size(str) < sendbidi_str_size) return std::nullopt;

  dcc::Address addr;

  // Address type identifier
  switch (str[size(sendbidi_prefix)]) {
    case 'u': addr.type = dcc::Address::UnknownService; break;
    case 'b': addr.type = dcc::Address::Broadcast; break;
    case 's': addr.type = dcc::Address::Short; break;
    case 'a': addr.type = dcc::Address::Accessory; break;
    case 'l': addr.type = dcc::Address::Long; break;
    case 'r': addr.type = dcc::Address::Reserved; break;
    case 't': addr.type = dcc::Address::DataTransfer; break;
    case 'e': addr.type = dcc::Address::AutomaticLogon; break;
    case 'i': addr.type = dcc::Address::IdleSystem; break;
    default: return std::unexpected(std::errc::invalid_argument);
  }

  // Address
  if (auto const [ptr,
                  ec]{std::from_chars(&str[size(sendbidi_prefix) + 1uz],
                                      &str[size(sendbidi_prefix) + 1uz + 4uz],
                                      addr.value,
                                      16)};
      ec != std::errc{})
    return std::unexpected(ec);

  // Datagram
  dcc::bidi::Datagram datagram;
  for (auto i{0uz}; i < size(datagram); ++i) {
    auto const first{&str[size(sendbidi_prefix) + 1uz + 4uz + 1uz + 3uz * i]};
    if (auto const [ptr,
                    ec]{std::from_chars(first, first + 2, datagram[i], 16)};
        ec != std::errc{})
      return std::unexpected(ec);
  }

  return AddressedDatagram{.addr = addr, .datagram = datagram};
}

}  // namespace ulf::dcc_ein