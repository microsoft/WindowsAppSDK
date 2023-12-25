// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.ApplicationData.h"
#include "Microsoft.Windows.Storage.ApplicationData.g.cpp"

static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Local));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::LocalCache) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::LocalCache));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Roaming) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Roaming));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Temporary) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Temporary));

namespace winrt::Microsoft::Windows::Storage::implementation
{
    ApplicationData::ApplicationData(winrt::Windows::Storage::ApplicationData const& value) :
        m_applicationData(value)
    {
    }
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
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForUser(winrt::Windows::System::User user)
    {
        auto applicationData{ winrt::Windows::Storage::ApplicationData::GetForUserAsync(user).get() };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(applicationData);
    }
    hstring ApplicationData::LocalCachePath()
    {
        return m_applicationData.LocalCacheFolder().Path();
    }
    hstring ApplicationData::LocalPath()
    {
        return m_applicationData.LocalFolder().Path();
    }
    hstring ApplicationData::MachinePath()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::RoamingPath()
    {
        return m_applicationData.RoamingFolder().Path();
    }
    hstring ApplicationData::SharedLocalPath()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationData::TemporaryPath()
    {
        return m_applicationData.TemporaryFolder().Path();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::LocalCacheFolder()
    {
        return m_applicationData.LocalCacheFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::LocalFolder()
    {
        return m_applicationData.LocalFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::MachineFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::RoamingFolder()
    {
        return m_applicationData.RoamingFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::SharedLocalFolder()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::TemporaryFolder()
    {
        return m_applicationData.TemporaryFolder();
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
        return m_applicationData.ClearAsync();
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality)
    {
        return m_applicationData.ClearAsync(static_cast<winrt::Windows::Storage::ApplicationDataLocality>(locality));
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
