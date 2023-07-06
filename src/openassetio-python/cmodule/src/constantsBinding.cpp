// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 The Foundry Visionmongers Ltd
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include <openassetio/constants.hpp>

#include "_openassetio.hpp"

void registerConstants(const py::module_ &mod) {
  mod.attr("kInfoKey_Icon") = openassetio::constants::kInfoKey_Icon;
  mod.attr("kInfoKey_SmallIcon") = openassetio::constants::kInfoKey_SmallIcon;
  mod.attr("kInfoKey_EntityReferencesMatchPrefix") =
      openassetio::constants::kInfoKey_EntityReferencesMatchPrefix;
  // TODO(DF): @deprecated
  mod.attr("kField_Icon") = openassetio::constants::kInfoKey_Icon;
  mod.attr("kField_SmallIcon") = openassetio::constants::kInfoKey_SmallIcon;
  mod.attr("kField_EntityReferencesMatchPrefix") =
      openassetio::constants::kInfoKey_EntityReferencesMatchPrefix;
}
