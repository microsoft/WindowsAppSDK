// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "DataStore.h"

#include "DynamicDependencyDataStore_h.h"

#include <wil/winrt.h>

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
}

MddCore::PackageDependency MddCore::DataStore::Load(PCWSTR packageDependencyId)
{
    //TODO
    return MddCore::PackageDependency();
}

void MddCore::DataStore::Save(const MddCore::PackageDependency& packageDependency)
{
    auto dataStore = GetDataStore();
    auto persisted = dataStore.LocalSettings().CreateContainer(winrt::hstring(packageDependency.Id()), winrt::Windows::Storage::ApplicationDataCreateDisposition::Always);
    auto values = persisted.Values();

    auto userSid = packageDependency.User();
    const BYTE* userSidAsBytes = static_cast<const BYTE*>(userSid);
    if (userSid)
    {
        winrt::array_view<uint8_t const> user{ userSidAsBytes, userSidAsBytes + GetLengthSid(userSid) };
        //TODO: values.Insert(winrt::hstring(L"User"), winrt::box_value(user));
    }
    values.Insert(winrt::hstring(L"PackageFamilyName"), winrt::box_value(packageDependency.PackageFamilyName()));
    values.Insert(winrt::hstring(L"MinVersion"), winrt::box_value(packageDependency.MinVersion().Version));
    values.Insert(winrt::hstring(L"ProcessorArchitectures"), winrt::box_value(static_cast<int32_t>(packageDependency.Architectures())));
    values.Insert(winrt::hstring(L"LifetimeKind"), winrt::box_value(static_cast<int32_t>(packageDependency.LifetimeKind())));
    values.Insert(winrt::hstring(L"LifetimeArtifact"), winrt::box_value(packageDependency.LifetimeArtifact()));
    values.Insert(winrt::hstring(L"Options"), winrt::box_value(static_cast<int32_t>(packageDependency.Options())));
}

void MddCore::DataStore::Delete(PCWSTR packageDependencyId)
{
    //TODO
}
