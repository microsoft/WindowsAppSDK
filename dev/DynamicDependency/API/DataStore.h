// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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

        static void Save(
                const MddCore::PackageDependency& packageDependency,
                const MddCreatePackageDependencyOptions options);

        static void Delete(PCWSTR packageDependencyId);

    private:
        static bool DeleteFileIfExists(PCWSTR filename);

        static HANDLE OpenFileIfExists(PCWSTR filename);

        static std::filesystem::path GetDataStorePath(const MddCreatePackageDependencyOptions options);

        static std::filesystem::path GetDataStorePathForSystem();

        static std::filesystem::path GetDataStorePathForUser();
        static std::filesystem::path GetDataStorePathForUserViaCOMDataStore();
        static std::filesystem::path GetDataStorePathForUserViaApplicationDataManager();

        static std::wstring GetWindowsAppRuntimeMainPackageFamilyName();
    };
}
