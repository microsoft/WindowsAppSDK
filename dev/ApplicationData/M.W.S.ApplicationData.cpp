// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.ApplicationData.h"
#include "Microsoft.Windows.Storage.ApplicationData.g.cpp"

#include "M.W.S.ApplicationDataContainer.h"

#include <shlobj_core.h>

#include <winrt/Windows.Management.Core.h>

#include "ApplicationDataTelemetry.h"

static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Local));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::LocalCache) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::LocalCache));
static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::SharedLocal) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::SharedLocal));
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
        winrt::Windows::Storage::ApplicationData applicationData{ nullptr };
        if (wil::get_token_is_app_container())
        {
            applicationData = winrt::Windows::Storage::ApplicationData::Current();
        }
        else
        {
            applicationData = winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName);
        }
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(applicationData, packageFamilyName);
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForUser(winrt::Windows::System::User user)
    {
        if (!user)
        {
            return GetDefault();
        }
        const auto packageFamilyName{ ::AppModel::Identity::GetCurrentPackageFamilyName<winrt::hstring>() };
        auto applicationData{ winrt::Windows::Storage::ApplicationData::GetForUserAsync(user).get() };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(applicationData, packageFamilyName);
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForPackageFamily(hstring const& packageFamilyName)
    {
        if (wil::get_token_is_app_container())
        {
            // ApplicationDataManager.CreateForPackageFamily requires the caller is not in an AppContainer
            // But if you ask for your own package family name it's equivalent to GetDefault()
            const auto currentPackageFamilyName{ ::AppModel::Identity::GetCurrentPackageFamilyName<winrt::hstring>() };
            if (CompareStringOrdinal(packageFamilyName.c_str(), -1, currentPackageFamilyName.c_str(), -1, TRUE) == CSTR_EQUAL)
            {
                return GetDefault();
            }

            // Let's fall through and let CreateForPackageFamily()'s error handling report the problem
        }

        try
        {
            auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
            return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(applicationData, packageFamilyName);
        }
        catch (winrt::hresult_error& e)
        {
            // CreateForPackageFamily() fails for Framework packages with HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)
            // But we succeed (the return object is just limited in function)
            if (e.code() == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                UINT32 count{};
                UINT32 bufferLength{};
                UINT32 packageProperties{};
                const auto rc{ ::FindPackagesByPackageFamily(packageFamilyName.c_str(), PACKAGE_FILTER_DIRECT, &count, nullptr, &bufferLength, nullptr, &packageProperties) };
                if ((rc == ERROR_INSUFFICIENT_BUFFER) && (count > 0))
                {
                    // The package family has package(s) registered for the user with at least 1 Framework package
                    // (and a package family can't have Framework and not-Framework packages in the same package family)
                    return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationData>(nullptr, packageFamilyName);
                }
            }

            // Nope! Not a framework. We have an actual error
            throw;
        }
    }
    winrt::Microsoft::Windows::Storage::ApplicationData ApplicationData::GetForUnpackaged(hstring const& /*publisher*/, hstring const& /*product*/)
    {
        // TODO implement GetForUnpackaged
        throw hresult_not_implemented();
    }
    bool ApplicationData::IsMachinePathSupported()
    {
        const auto path{ _MachinePath(m_packageFamilyName) };
        return !path.empty();
    }
    hstring ApplicationData::LocalCachePath()
    {
        if (!m_applicationData)
        {
            return winrt::hstring{};
        }
        return StorageFolderToPath(m_applicationData.LocalCacheFolder());
    }
    hstring ApplicationData::LocalPath()
    {
        if (!m_applicationData)
        {
            return winrt::hstring{};
        }
        return StorageFolderToPath(m_applicationData.LocalFolder());
    }
    hstring ApplicationData::MachinePath()
    {
        const auto path{ _MachinePath(m_packageFamilyName) };
        return winrt::hstring{ path.c_str() };
    }
    hstring ApplicationData::SharedLocalPath()
    {
        if (!m_applicationData)
        {
            return winrt::hstring{};
        }

        // SharedLocalFolder is only available if the device has the appropriate group policy.  If the group policy
        // is not enabled, the device administrator must enable it. From Local Group Policy Editor, navigate to
        // Computer Configuration\Administrative Templates\Windows Components\App Package Deployment,
        // then change the setting "Allow a Windows app to share application data between users" to "Enabled."
        //
        // After the group policy is enabled, SharedLocalFolder can be accessed.
        //
        // @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.sharedlocalfolder

        return StorageFolderToPath(m_applicationData.SharedLocalFolder());
    }
    hstring ApplicationData::TemporaryPath()
    {
        if (!m_applicationData)
        {
            return winrt::hstring{};
        }
        return StorageFolderToPath(m_applicationData.TemporaryFolder());
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::LocalCacheFolder()
    {
        if (!m_applicationData)
        {
            return nullptr;
        }
        return m_applicationData.LocalCacheFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::LocalFolder()
    {
        if (!m_applicationData)
        {
            return nullptr;
        }
        return m_applicationData.LocalFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::MachineFolder()
    {
        const auto path{ MachinePath() };
        if (path.empty())
        {
            return nullptr;
        }
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::SharedLocalFolder()
    {
        if (!m_applicationData)
        {
            return nullptr;
        }
        return m_applicationData.SharedLocalFolder();
    }
    winrt::Windows::Storage::StorageFolder ApplicationData::TemporaryFolder()
    {
        if (!m_applicationData)
        {
            return nullptr;
        }
        return m_applicationData.TemporaryFolder();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer ApplicationData::LocalSettings()
    {
        if (!m_applicationData)
        {
            return nullptr;
        }
        auto applicationDataContainer{ m_applicationData.LocalSettings() };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(applicationDataContainer);
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality)
    {
        if (!m_applicationData)
        {
            co_return;
        }
        if (locality == winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Machine)
        {
            co_await ClearMachineFolderAsync();
        }
        else
        {
            co_await m_applicationData.ClearAsync(static_cast<winrt::Windows::Storage::ApplicationDataLocality>(locality));
        }
    }
    winrt::Windows::Foundation::IAsyncAction ApplicationData::ClearPublisherCacheFolderAsync(hstring folderName)
    {
        if (!m_applicationData)
        {
            co_return;
        }
        co_await m_applicationData.ClearPublisherCacheFolderAsync(folderName);
    }
    void ApplicationData::Close()
    {
        if (m_applicationData)
        {
            m_applicationData.Close();
        }
    }
    hstring ApplicationData::GetPublisherCachePath(hstring const& folderName)
    {
        auto folder{ GetPublisherCacheFolder(folderName) };
        winrt::hstring path;
        if (folder)
        {
            path = folder.Path();
        }
        return path;
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
    winrt::Windows::Storage::StorageFolder ApplicationData::GetPublisherCacheFolder(hstring const& folderName)
    {
        if (!m_applicationData)
        {
            return nullptr;
        }

        try
        {
            return m_applicationData.GetPublisherCacheFolder(folderName);
        }
        catch (winrt::hresult_error& e)
        {
            // GetPublisherCacheFolder() throws HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) when it doesn't exist
            if (e.code() == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                return nullptr;
            }

            // Nope! We have an actual error
            throw;
        }
    }
    std::filesystem::path ApplicationData::_MachinePath(hstring const& packageFamilyName)
    {
        // Path = HKLM\...apprepository...\Families\ApplicationData\...pkgfamilyname...\Machine
        // This is typically %ProgramData%\Microsoft\Windows\AppRepository\Families\ApplicationData\...pkgfamilyname...\Machine
        PCWSTR c_path{ L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Appx" };
        PCWSTR c_valueName{ L"PackageRepositoryRoot" };
        std::filesystem::path appRepository{ wil::reg::get_value_string(HKEY_LOCAL_MACHINE, c_path, c_valueName) };
        auto path{ appRepository / L"Families\\ApplicationData" };
        path /= packageFamilyName.c_str();
        path /= "Machine";

        // Does it exist?
        if (_PathExists(path))
        {
            return path;
        }
        return std::filesystem::path{};
    }

    bool ApplicationData::_PathExists(std::filesystem::path const& path)
    {
        const std::filesystem::directory_entry directoryEntry{ path };
        return directoryEntry.is_directory();
    }
    winrt::hstring ApplicationData::StorageFolderToPath(winrt::Windows::Storage::StorageFolder storageFolder)
    {
        winrt::hstring path;
        if (storageFolder)
        {
            path = storageFolder.Path();
        }
        return path;
    }
}
