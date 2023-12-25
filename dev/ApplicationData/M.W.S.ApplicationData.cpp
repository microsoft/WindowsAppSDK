// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.ApplicationData.h"
#include "Microsoft.Windows.Storage.ApplicationData.g.cpp"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetDefault()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForPackageFamily(hstring const& packageFamilyName)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForUnpackaged(hstring const& publisher, hstring const& name)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::ApplicationData> ApplicationData::GetForUser(winrt::Windows::System::User user)
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::LocalCachePath()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::LocalPath()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::MachinePath()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::RoamingPath()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::SharedLocalPath()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::TemporaryPath()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::LocalCacheFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::LocalFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::MachineFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::RoamingFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::SharedLocalFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::TemporaryFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer ApplicationData::LocalSettings()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer ApplicationData::RoamingSettings()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearAllAsync()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearPublisherCacheFolderAsync(hstring folderName)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearMachineFolderAsync()
    {
        throw hresult_not_implemented();
    }
    void ApplicationData::Close()
    {
        throw hresult_not_implemented();
    }
    void ApplicationData::Dispose()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::GetPublisherCachePath(hstring const& folderName)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::GetPublisherCacheFolder(hstring const& folderName)
    {
        throw hresult_not_implemented();
    }
}
