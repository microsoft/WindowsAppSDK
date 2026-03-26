// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <shlobj_core.h>

#include <winrt/Windows.Management.Core.h>

#include "UnpackagedApplicationData.h"
#include "UnpackagedApplicationDataContainer.h"

#include "ApplicationDataTelemetry.h"

namespace Microsoft::Windows::Storage
{
    UnpackagedApplicationData::UnpackagedApplicationData(winrt::hstring const& publisher, winrt::hstring const& product) :
        m_publisher(publisher),
        m_product(product),
        m_localPath()
    {
    }
    bool UnpackagedApplicationData::IsMachinePathSupported()
    {
        _VerifyNotClosed();

        const auto path{ _MachinePath(m_publisher, m_product) };
        return !path.empty();
    }
    winrt::hstring UnpackagedApplicationData::LocalCachePath()
    {
        _VerifyNotClosed();

        // ApplicationData.LocalCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    winrt::hstring UnpackagedApplicationData::LocalPath()
    {
        _VerifyNotClosed();

        if (m_localPath.empty())
        {
            // Caller is LocalSystem    : %PROGRAMDATA%\...publisher...\...product...
            // Caller is <MediumIL (Low): %USERPROFILE%\AppData\LocalLow\...publisher...\...product...
            // Caller is >=MediumIL     : %USERPROFILE%\AppData\Local\...publisher...\...product...
            auto folderId{ FOLDERID_LocalAppData };
            if (::Security::User::IsLocalSystem())
            {
                folderId = FOLDERID_ProgramData;
            }
            else if (::Security::IntegrityLevel::GetIntegrityLevel() < SECURITY_MANDATORY_MEDIUM_RID)
            {
                folderId = FOLDERID_LocalAppDataLow;
            }
            wil::unique_cotaskmem_string rootPath;
            THROW_IF_FAILED(SHGetKnownFolderPath(folderId, KF_FLAG_DEFAULT/*TODO KF_FLAG_CREATE | KF_FLAG_DONT_VERIFY*/, nullptr, wil::out_param(rootPath)));
            std::filesystem::path path{ rootPath.get() };
            path /= m_publisher.c_str();
            path /= m_product.c_str();
            m_localPath = path.c_str();
        }
        return m_localPath;
    }
    winrt::hstring UnpackagedApplicationData::MachinePath()
    {
        _VerifyNotClosed();

        const auto path{ _MachinePath(m_publisher, m_product) };
        return winrt::hstring{ path.c_str() };
    }
    winrt::hstring UnpackagedApplicationData::SharedLocalPath()
    {
        _VerifyNotClosed();

        // ApplicationData.SharedLocalFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    winrt::hstring UnpackagedApplicationData::TemporaryPath()
    {
        _VerifyNotClosed();

        if (m_temporaryPath.empty())
        {
            // GetTempPath[2]() + \...publisher...\...product...
            auto path{ ::Microsoft::FileSystem::Path::GetTempDirectory() };
            path /= m_publisher.c_str();
            path /= m_product.c_str();
            m_temporaryPath = path.c_str();
        }
        return m_temporaryPath;
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::LocalCacheFolder()
    {
        _VerifyNotClosed();

        const auto path{ LocalCachePath() };
        if (path.empty())
        {
            return nullptr;
        }
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::LocalFolder()
    {
        _VerifyNotClosed();

        const auto path{ LocalPath() };
        if (path.empty())
        {
            return nullptr;
        }
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::MachineFolder()
    {
        _VerifyNotClosed();

        const auto path{ MachinePath() };
        if (path.empty())
        {
            return nullptr;
        }
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::SharedLocalFolder()
    {
        _VerifyNotClosed();

        const auto path{ SharedLocalPath() };
        if (path.empty())
        {
            return nullptr;
        }
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::TemporaryFolder()
    {
        _VerifyNotClosed();

        const auto path{ TemporaryPath() };
        if (path.empty())
        {
            return nullptr;
        }
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer UnpackagedApplicationData::LocalSettings()
    {
        _VerifyNotClosed();

        wil::unique_hkey currentUserKey;
        THROW_IF_WIN32_ERROR(::RegOpenCurrentUser(KEY_READ | KEY_WRITE, currentUserKey.put()));
        auto subKey{ std::format(L"SOFTWARE\\{}\\{}", m_publisher, m_product) };
        auto key{ wil::reg::create_shared_key(currentUserKey.get(), subKey.c_str(), wil::reg::key_access::readwrite) };
        auto container{ std::make_shared<UnpackagedApplicationDataContainer>(
            std::move(key), winrt::hstring{}, winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local) };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(container);
    }
    winrt::Windows::Foundation::IAsyncAction UnpackagedApplicationData::ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality)
    {
        _VerifyNotClosed();

        const winrt::hstring publisher{ m_publisher };
        const winrt::hstring product{ m_product };
        winrt::hstring localityPath;
        switch (locality)
        {
        case winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local:
        {
            localityPath = LocalPath();
            break;
        }
        case winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Temporary:
        {
            localityPath = TemporaryPath();
            break;
        }
        case winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Machine:
        {
            localityPath = MachinePath();
            break;
        }
        default:
            THROW_HR_MSG(E_NOTIMPL, "%d", static_cast<int>(locality));
        }

        auto logTelemetry{ ApplicationDataTelemetry::UnpackagedClearAsync::Start(locality, publisher, product) };

        logTelemetry.IgnoreCurrentThread();
        co_await winrt::resume_background();
        auto logTelemetryContinuation{ logTelemetry.ContinueOnCurrentThread() };

        // Clear the path
        if (!localityPath.empty())
        {
            std::filesystem::path path{ localityPath.c_str() };
            if (_PathExists(path))
            {
                const auto options{ wil::RemoveDirectoryOptions::KeepRootDirectory | wil::RemoveDirectoryOptions::RemoveReadOnly };
                THROW_IF_FAILED(wil::RemoveDirectoryRecursiveNoThrow(path.c_str(), options));
            }
        }

        // Clear the settings (if necessary)
        if (locality == winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local)
        {
            wil::unique_hkey currentUserKey;
            THROW_IF_WIN32_ERROR(::RegOpenCurrentUser(KEY_READ | KEY_WRITE, currentUserKey.put()));
            auto subKey{ std::format(L"SOFTWARE\\{}\\{}", publisher, product) };
            const auto hr{ HRESULT_FROM_WIN32(::RegDeleteTreeW(currentUserKey.get(), subKey.c_str())) };
            if (hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) && hr != HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND))
            {
                THROW_IF_FAILED(hr);
            }
        }

        logTelemetry.Stop();

        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction UnpackagedApplicationData::ClearPublisherCacheFolderAsync(winrt::hstring folderName)
    {
        _VerifyNotClosed();

        // ApplicationData.PublisherCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    void UnpackagedApplicationData::Close()
    {
        m_publisher.clear();
        m_product.clear();
        m_localPath.clear();
        m_machinePath.clear();
    }
    winrt::hstring UnpackagedApplicationData::GetPublisherCachePath(winrt::hstring const& folderName)
    {
        _VerifyNotClosed();

        // ApplicationData.PublisherCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::GetPublisherCacheFolder(winrt::hstring const& folderName)
    {
        _VerifyNotClosed();

        // ApplicationData.PublisherCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    void UnpackagedApplicationData::_VerifyNotClosed()
    {
        THROW_HR_IF(RO_E_CLOSED, m_publisher.empty());
    }
    std::filesystem::path UnpackagedApplicationData::_MachinePath(winrt::hstring const& publisher, winrt::hstring const& product)
    {
        wil::unique_cotaskmem_string rootPath;
        THROW_IF_FAILED(SHGetKnownFolderPath(FOLDERID_ProgramData, KF_FLAG_DEFAULT/*TODO KF_FLAG_CREATE | KF_FLAG_DONT_VERIFY*/, nullptr, wil::out_param(rootPath)));
        std::filesystem::path path{ rootPath.get() };
        path /= publisher.c_str();
        path /= product.c_str();

        // Does it exist?
        if (_PathExists(path))
        {
            return path;
        }
        return std::filesystem::path{};
    }

    bool UnpackagedApplicationData::_PathExists(std::filesystem::path const& path)
    {
        const std::filesystem::directory_entry directoryEntry{ path };
        return directoryEntry.is_directory();
    }
}
