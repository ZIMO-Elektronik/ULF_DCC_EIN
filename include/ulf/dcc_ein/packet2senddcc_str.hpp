// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert packet to senddcc string
///
/// \file   ulf/dcc_ein/packet2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include "bytes2senddcc_str.hpp"

namespace ulf::dcc_ein {

/// Convert packet to senddcc string into provided buffer
///
/// \param  packet  DCC packet
/// \param  out     Pointer to the destination buffer
/// \return One-past-the-end pointer of the characters written
constexpr char* packet2senddcc_str(dcc::Packet const& packet, char* out) {
  return bytes2senddcc_str({cbegin(packet), size(packet)}, out);
}

/// Convert packet to senddcc string
///
/// \param  packet  DCC packet
/// \return senddcc string
constexpr auto packet2senddcc_str(dcc::Packet const& packet) {
  return bytes2senddcc_str({cbegin(packet), size(packet)});
}

}  // namespace ulf::dcc_ein