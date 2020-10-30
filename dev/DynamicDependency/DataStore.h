// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "PackageDependency.h"

namespace MddCore
{
    class DataStore
    {
    public:
        DataStore() = delete;
        ~DataStore() = delete;

    public:
        static constexpr PCWSTR fileExtension{ L".mdd" };

        static MddCore::PackageDependency Load(PCWSTR packageDependencyId);

        static void Save(const MddCore::PackageDependency& packageDependency);

        static void Delete(PCWSTR packageDependencyId);

    private:
        static void DeleteFileIfExists(PCWSTR filename);

        static std::filesystem::path GetDataStorePath();
    };
}
