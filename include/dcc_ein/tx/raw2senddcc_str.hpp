// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

///
///
/// \file   dcc_ein/tx/raw2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include <charconv>
#include <optional>
#include <span>
#include "../senddcc.hpp"

namespace dcc_ein::tx {

///
constexpr void raw2senddcc_str(std::span<uint8_t const> chunk) {
  // rettype?
}

}  // namespace dcc_ein::tx