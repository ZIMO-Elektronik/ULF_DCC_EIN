// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// sendbidi prefix and size
///
/// \file   dcc_ein/sendbidi.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include <string_view>

namespace dcc_ein {

using namespace std::literals;

inline constexpr std::string_view sendbidi_prefix{"sendbidi "};
inline constexpr auto sendbidi_str_size{size(sendbidi_prefix) +
                                        size("s0000 "sv) +
                                        size("00 00 00 00 00 00 00 00\r"sv)};

}  // namespace dcc_ein