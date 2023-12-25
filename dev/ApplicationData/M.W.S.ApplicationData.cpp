// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.ApplicationData.h"
#include "Microsoft.Windows.Storage.ApplicationData.g.cpp"

#include "M.W.S.ApplicationDataContainer.h"

#include <winrt/Windows.Management.Core.h>

#include "ApplicationDataTelemetry.h"

static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Local));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::LocalCache) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::LocalCache));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Roaming) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Roaming));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Temporary) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Temporary));

namespace winrt::Microsoft::Windows::Storage::implementation
{
    ApplicationData::ApplicationData(winrt::Windows::Storage::ApplicationData const& value, hstring const& packageFamilyName) :
        m_applicationData(value),
        m_packageFamilyName(packageFamilyName)
    {
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetDefault()
    {
        const auto packageFamilyName{ ::AppModel::Identity::GetCurrentPackageFamilyName<winrt::hstring>() };
        auto applicationData{ winrt::Windows::Storage::ApplicationData::Current() };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(applicationData, packageFamilyName);
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForUser(winrt::Windows::System::User user)
    {
        const auto packageFamilyName{ ::AppModel::Identity::GetCurrentPackageFamilyName<winrt::hstring>() };
        auto applicationData{ winrt::Windows::Storage::ApplicationData::GetForUserAsync(user).get() };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(applicationData, packageFamilyName);
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForPackageFamily(hstring const& packageFamilyName)
    {
        auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(applicationData, packageFamilyName);
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForUnpackaged(hstring const& publisher, hstring const& name)
    {
        // TODO implement GetForUnpackaged
        throw hresult_not_implemented();
    }
    bool ApplicationData::IsMachinePathSupported()
    {
#if defined(TODO_FrameworkUdk__ApplicationData_MachinePathIsSupported)
        bool isSupported{};
        THROW_IF_FAILED(ApplicationData_IsMachinePathSupported(m_packageFamilyName.c_str(), isSupported));
#endif
        return false;
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
        wil::unique_cotaskmem_string programData;
        THROW_IF_FAILED(::SHGetKnownFolderPath(FOLDERID_ProgramData, 0, nullptr, wil::out_param(programData)));
        std::filesystem::path path{ programData.get() };
        path /= m_packageFamilyName.c_str();
        return hstring{ path.c_str() };
    }
    hstring ApplicationData::RoamingPath()
    {
        return m_applicationData.RoamingFolder().Path();
    }
    hstring ApplicationData::SharedLocalPath()
    {
        return m_applicationData.SharedLocalFolder().Path();
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
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(MachinePath()).get();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::RoamingFolder()
    {
        return m_applicationData.RoamingFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::SharedLocalFolder()
    {
        return m_applicationData.SharedLocalFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::TemporaryFolder()
    {
        return m_applicationData.TemporaryFolder();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer ApplicationData::LocalSettings()
    {
        auto applicationDataContainer{ m_applicationData.LocalSettings() };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(applicationDataContainer);
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer ApplicationData::RoamingSettings()
    {
        auto applicationDataContainer{ m_applicationData.RoamingSettings() };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(applicationDataContainer);
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
        return m_applicationData.ClearPublisherCacheFolderAsync(folderName);
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearMachineFolderAsync()
    {
        const auto path{ MachinePath() };

        auto logTelemetry{ ApplicationDataTelemetry::ClearMachineFolderAsync::Start(path) };

        auto strong{ get_strong() };

        logTelemetry.IgnoreCurrentThread();
        co_await winrt::resume_background();
        auto logTelemetryContinuation{ logTelemetry.ContinueOnCurrentThread() };

        const auto options{ wil::RemoveDirectoryOptions::KeepRootDirectory | wil::RemoveDirectoryOptions::RemoveReadOnly };
        wil::RemoveDirectoryRecursive(path.c_str(), options);

        logTelemetry.Stop();
    }
    void ApplicationData::Close()
    {
        m_applicationData.Close();
    }
    hstring ApplicationData::GetPublisherCachePath(hstring const& folderName)
    {
        return m_applicationData.GetPublisherCacheFolder(folderName).Path();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::GetPublisherCacheFolder(hstring const& folderName)
    {
        return m_applicationData.GetPublisherCacheFolder(folderName);
    }
}
