// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "PackageDependency.h"

namespace MddCore::DataStore
{
MddCore::PackageDependency Load(PCWSTR packageDependencyId);

void Save(const MddCore::PackageDependency& packageDependency);

void Delete(PCWSTR packageDependencyId);
}
