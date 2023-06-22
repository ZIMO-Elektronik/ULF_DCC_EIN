// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

///
///
/// \file   dcc_ein/tx/packet2senddcc_str.hpp
/// \author Vincent Hamp
/// \date   22/06/2023

#pragma once

#include "raw2senddcc_str.hpp"

namespace dcc_ein::tx {

///
constexpr auto packet2senddcc_str(dcc::Packet const& packet) {
  return raw2senddcc_str({cbegin(packet.data), packet.size});
}

}  // namespace dcc_ein::tx