// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Storage.ApplicationData.g.h"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    struct ApplicationData : ApplicationDataT<ApplicationData>
    {
        ApplicationData() = default;
        ApplicationData(winrt::Windows::Storage::ApplicationData const& value);

        static winrt::Microsoft::Windows::Storage::ApplicationData GetDefault();
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForPackageFamily(hstring const& packageFamilyName);
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForUnpackaged(hstring const& publisher, hstring const& name);
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForUser(winrt::Windows::System::User user);
        hstring LocalCachePath();
        hstring LocalPath();
        hstring MachinePath();
        hstring RoamingPath();
        hstring SharedLocalPath();
        hstring TemporaryPath();
        winrt::Windows::Storage::StorageFolder LocalCacheFolder();
        winrt::Windows::Storage::StorageFolder LocalFolder();
        winrt::Windows::Storage::StorageFolder MachineFolder();
        winrt::Windows::Storage::StorageFolder RoamingFolder();
        winrt::Windows::Storage::StorageFolder SharedLocalFolder();
        winrt::Windows::Storage::StorageFolder TemporaryFolder();
        winrt::Microsoft::Windows::Storage::ApplicationDataContainer LocalSettings();
        winrt::Microsoft::Windows::Storage::ApplicationDataContainer RoamingSettings();
        winrt::Windows::Foundation::IAsyncAction ClearAllAsync();
        winrt::Windows::Foundation::IAsyncAction ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality);
        winrt::Windows::Foundation::IAsyncAction ClearPublisherCacheFolderAsync(hstring folderName);
        winrt::Windows::Foundation::IAsyncAction ClearMachineFolderAsync();
        void Close();
        void Dispose();
        hstring GetPublisherCachePath(hstring const& folderName);
        winrt::Windows::Storage::StorageFolder GetPublisherCacheFolder(hstring const& folderName);

    private:
        winrt::Windows::Storage::ApplicationData m_applicationData;
    };
}
namespace winrt::Microsoft::Windows::Storage::factory_implementation
{
    struct ApplicationData : ApplicationDataT<ApplicationData, implementation::ApplicationData>
    {
    };
}
