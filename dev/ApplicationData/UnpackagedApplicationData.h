// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Storage.ApplicationData.g.h"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    struct UnpackagedApplicationData : ApplicationDataT<UnpackagedApplicationData>
    {
        UnpackagedApplicationData() = default;
        UnpackagedApplicationData(winrt::hstring const& publisher, winrt::hstring const& product);

        static winrt::Microsoft::Windows::Storage::ApplicationData GetDefault();
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForUser(winrt::Windows::System::User user);
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForPackageFamily(winrt::hstring const& packageFamilyName);
        static winrt::Microsoft::Windows::Storage::ApplicationData GetForUnpackaged(winrt::hstring const& publisher, winrt::hstring const& product);
        bool IsMachinePathSupported();
        winrt::hstring LocalCachePath();
        winrt::hstring LocalPath();
        winrt::hstring MachinePath();
        winrt::hstring SharedLocalPath();
        winrt::hstring TemporaryPath();
        winrt::Windows::Storage::StorageFolder LocalCacheFolder();
        winrt::Windows::Storage::StorageFolder LocalFolder();
        winrt::Windows::Storage::StorageFolder MachineFolder();
        winrt::Windows::Storage::StorageFolder SharedLocalFolder();
        winrt::Windows::Storage::StorageFolder TemporaryFolder();
        winrt::Microsoft::Windows::Storage::ApplicationDataContainer LocalSettings();
        winrt::Windows::Foundation::IAsyncAction ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality);
        winrt::Windows::Foundation::IAsyncAction ClearPublisherCacheFolderAsync(winrt::hstring folderName);
        void Close();
        winrt::hstring GetPublisherCachePath(winrt::hstring const& folderName);
        winrt::Windows::Storage::StorageFolder GetPublisherCacheFolder(winrt::hstring const& folderName);

    private:
        void _VerifyNotClosed();
        static std::filesystem::path _MachinePath(winrt::hstring const& publisher, winrt::hstring const& product);
        static bool _PathExists(std::filesystem::path const& path);

    private:
        winrt::hstring m_publisher;
        winrt::hstring m_product;
        winrt::hstring m_localPath;
        winrt::hstring m_temporaryPath;
    };
}
