// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "DataStore.h"

#include "DynamicDependencyDataStore_h.h"

#include <wil/winrt.h>

#include <fstream>

namespace MddCore::DataStore
{
    winrt::Windows::Storage::ApplicationData GetDataStore()
    {
        wil::com_ptr<IUnknown> dataStore_iunknown{ wil::CoCreateInstance<DynamicDependencyDataStore, IDynamicDependencyDataStore>(CLSCTX_LOCAL_SERVER) };
        auto dataStore{ dataStore_iunknown.query<IDynamicDependencyDataStore>() };

        wil::com_ptr<IUnknown> applicationData_iunknown;
        THROW_IF_FAILED(dataStore->GetApplicationData(applicationData_iunknown.addressof()));

        return winrt::Windows::Storage::ApplicationData{ applicationData_iunknown.detach(), winrt::take_ownership_from_abi };
    }

    std::filesystem::path GetDataStorePath()
    {
        auto dataStore{ GetDataStore() };
        return std::filesystem::path(dataStore.LocalFolder().Path().c_str());
    }
}

MddCore::PackageDependency MddCore::DataStore::Load(PCWSTR packageDependencyId)
{
    auto path{ GetDataStorePath() };
    path /= L"DynamicDependency";
    auto filename{ path / (std::wstring(packageDependencyId) + L".ddpd") };

    const auto c_bufferSize = 32 * 1024;    // Way more than we need
    auto buffer{ wil::make_process_heap_string(nullptr, c_bufferSize) };
    memset(buffer.get(), 0, c_bufferSize * sizeof(*buffer.get()));
    {
        std::wifstream file(filename);
        file.read(buffer.get(), c_bufferSize);
        file.close();
    }

    return MddCore::PackageDependency::FromJSON(winrt::hstring(buffer.get()));
}

void MddCore::DataStore::Save(const MddCore::PackageDependency& packageDependency)
{
    auto json = packageDependency.ToJSON();

    auto path{ GetDataStorePath() };
    path /= L"DynamicDependency";
    std::filesystem::create_directory(path);

    auto filename = path / (packageDependency.Id() + L".ddpd");
    {
        std::wofstream file(filename, std::wofstream::trunc);
        file.write(json.c_str(), json.length());
        file.close();
    }
}

void MddCore::DataStore::Delete(PCWSTR packageDependencyId)
{
    auto path = GetDataStorePath();
    path /= packageDependencyId;

    THROW_IF_WIN32_BOOL_FALSE_MSG(DeleteFileW(path.c_str()), "Error deleting file %ls", path.c_str());
}
