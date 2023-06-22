// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

///
///
/// \file   dcc_ein/tx/sendbidi_str2datagram.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include <charconv>
#include <optional>
#include <span>
#include "../senddcc.hpp"

namespace dcc_ein::tx {

///
constexpr std::optional<std::array<uint8_t, 8uz>>
sendbidi_str2datagram(std::span<uint8_t const> chunk) {
  // rettype?
  return {};
}

}  // namespace dcc_ein::tx