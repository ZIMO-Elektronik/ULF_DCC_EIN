// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Addressed datagram
///
/// \file   ulf/dcc_ein/addressed_datagram.hpp
/// \author Vincent Hamp
/// \date   17/11/2023

#pragma once

#include <dcc/dcc.hpp>

namespace ulf::dcc_ein {

struct AddressedDatagram {
  dcc::Address addr{};
  dcc::bidi::Datagram<> datagram{};
};

}  // namespace ulf::dcc_ein