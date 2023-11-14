// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Convert packet to senddcc string
///
/// \file   dcc_ein/tx/packet2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include "bytes2senddcc_str.hpp"

namespace dcc_ein::tx {

/// Convert packet to senddcc string into provided buffer
///
/// \param  packet  DCC packet
/// \param  out     Pointer to the destination buffer
/// \return One-past-the-end pointer of the characters written
inline char* packet2senddcc_str(dcc::Packet const& packet, char* out) {
  return bytes2senddcc_str({cbegin(packet), size(packet)}, out);
}

/// Convert packet to senddcc string
///
/// \param  packet  DCC packet
/// \return senddcc string
inline auto packet2senddcc_str(dcc::Packet const& packet) {
  return bytes2senddcc_str({cbegin(packet), size(packet)});
}

}  // namespace dcc_ein::tx