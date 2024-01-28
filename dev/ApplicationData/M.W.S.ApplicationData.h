// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Storage.ApplicationData.g.h"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    struct ApplicationData : ApplicationDataT<ApplicationData>
    {
        ApplicationData() = default;
        ApplicationData(winrt::Windows::Storage::ApplicationData const& value, hstring const& packageFamilyName);

        static winrt::Microsoft::Windows::Storage::ApplicationData GetDefault();
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForUser(winrt::Windows::System::User user);
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForPackageFamily(hstring const& packageFamilyName);
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForUnpackaged(hstring const& publisher, hstring const& product);
        bool IsMachinePathSupported();
        hstring LocalCachePath();
        hstring LocalPath();
        hstring MachinePath();
        hstring SharedLocalPath();
        hstring TemporaryPath();
        winrt::Windows::Storage::StorageFolder LocalCacheFolder();
        winrt::Windows::Storage::StorageFolder LocalFolder();
        winrt::Windows::Storage::StorageFolder MachineFolder();
        winrt::Windows::Storage::StorageFolder SharedLocalFolder();
        winrt::Windows::Storage::StorageFolder TemporaryFolder();
        winrt::Microsoft::Windows::Storage::ApplicationDataContainer LocalSettings();
        winrt::Windows::Foundation::IAsyncAction ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality);
        winrt::Windows::Foundation::IAsyncAction ClearPublisherCacheFolderAsync(hstring folderName);
        void Close();
        hstring GetPublisherCachePath(hstring const& folderName);
        winrt::Windows::Storage::StorageFolder GetPublisherCacheFolder(hstring const& folderName);

    private:
        winrt::Windows::Foundation::IAsyncAction ClearMachineFolderAsync();
        static std::filesystem::path _MachinePath(hstring const& packageFamilyName);
        static bool _PathExists(std::filesystem::path const& path);
        static hstring StorageFolderToPath(winrt::Windows::Storage::StorageFolder storageFolder);

    private:
        winrt::Windows::Storage::ApplicationData m_applicationData;
        winrt::hstring m_packageFamilyName;
    };
}
namespace winrt::Microsoft::Windows::Storage::factory_implementation
{
    struct ApplicationData : ApplicationDataT<ApplicationData, implementation::ApplicationData>
    {
    };
}
