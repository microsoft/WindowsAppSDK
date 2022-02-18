// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"
#include  "NotificationsLongRunningProcess_h.h"
#include <winrt/Windows.Foundation.Metadata.h>
#include "../Common/AppModel.Identity.h"
#include "wil/stl.h"
#include "wil/win32_helpers.h"
#include "PushBackgroundTaskInstance.h"

namespace winrt
{
    using namespace Windows::Foundation;
}
namespace winrt::Microsoft::Windows::PushNotifications::Helpers
{
    const std::wstring c_serverIdCommandString = L"ServerId";
    const std::wstring c_argumentCommandString = L"Arguments";
    const std::wstring c_executableCommandString = L"Executable";

    inline std::string WideStringToUtf8String(_In_ std::wstring const& utf16string)
    {
        int size = WideCharToMultiByte(
            CP_UTF8,
            0,
            utf16string.data(),
            static_cast<int>(utf16string.length()),
            nullptr,
            0,
            nullptr,
            nullptr);

        THROW_LAST_ERROR_IF(size == 0);

        std::string utf8string;
        utf8string.resize(size);

        size = WideCharToMultiByte(
            CP_UTF8,
            0,
            utf16string.data(),
            static_cast<int>(utf16string.length()),
            &utf8string[0],
            size,
            nullptr,
            nullptr);

        THROW_LAST_ERROR_IF(size == 0);

        return utf8string;
    }

    inline std::wstring Utf8BytesToWideString(unsigned int payloadLength, _In_reads_(payloadLength) byte* payload)
    {
        int size = MultiByteToWideChar(
            CP_UTF8,
            0,
            reinterpret_cast<PCSTR>(payload),
            payloadLength,
            nullptr,
            0);
        THROW_LAST_ERROR_IF(size == 0);

        std::wstring payloadAsWideString(size, 0);
        size = MultiByteToWideChar(
            CP_UTF8,
            0,
            reinterpret_cast<PCSTR>(payload),
            payloadLength,
            &payloadAsWideString[0],
            size);
        THROW_LAST_ERROR_IF(size == 0);

        return payloadAsWideString;
    }

    inline wil::unique_cotaskmem_string GetAppUserModelId()
    {
        wchar_t appId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appIdSize{ ARRAYSIZE(appId) };

        THROW_IF_FAILED(::GetCurrentApplicationUserModelId(&appIdSize, appId));

        return wil::make_unique_string<wil::unique_cotaskmem_string>(appId);
    }

    inline HRESULT ProtocolLaunchHelper(std::wstring processName, unsigned int payloadLength, _In_reads_(payloadLength) byte* payload) noexcept try
    {
        // Command line format: ----WindowsAppRuntimePushServer:-Payload:"<payloadAsEscapedUriFormat>"
        std::wstring commandLine = L"----WindowsAppRuntimePushServer:-Payload:\"";

        // Escape special characters to follow command line standards for any app activation type in AppLifecycle
        // (See AppInstance.cpp and Serialize() from other activation types)
        auto payloadAsWideString{ Utf8BytesToWideString(payloadLength, payload) };
        auto payloadAsEscapedUriFormat = winrt::Windows::Foundation::Uri::EscapeComponent(payloadAsWideString.c_str());

        commandLine.append(payloadAsEscapedUriFormat);
        commandLine.append(L"\"");

        SHELLEXECUTEINFO shellExecuteInfo{};
        shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
        shellExecuteInfo.lpFile = processName.c_str();
        shellExecuteInfo.lpParameters = commandLine.c_str();

        shellExecuteInfo.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&shellExecuteInfo))
        {
            THROW_IF_WIN32_ERROR(GetLastError());
        }
        return S_OK;
    }
    CATCH_RETURN()

    inline HRESULT PackagedAppLauncherByClsid(winrt::guid const& comServerClsid, unsigned int payloadLength, _In_reads_(payloadLength) byte* payload) noexcept try
    {
        auto payloadAsWideString{ Utf8BytesToWideString(payloadLength, payload) };
        auto pushBackgroundTaskInstance{ winrt::make_self<PushBackgroundTaskInstance>(payloadAsWideString) };

        auto localBackgroundTask = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(comServerClsid, CLSCTX_ALL);
        localBackgroundTask.Run(*pushBackgroundTaskInstance);
        return S_OK;
    }
    CATCH_RETURN()

    inline wil::com_ptr<INotificationsLongRunningPlatform> GetNotificationPlatform()
    {
        return wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER);
    }

    inline bool IsBackgroundTaskBuilderAvailable()
    {
        static bool hasSetTaskEntrypoint{ winrt::Metadata::ApiInformation::IsMethodPresent(L"Windows.ApplicationModel.Background.BackgroundTaskBuilder", L"SetTaskEntryPointClsid") };
        return hasSetTaskEntrypoint;
    }

    inline bool IsPackagedAppScenario()
    {
        return AppModel::Identity::IsPackagedProcess() && IsBackgroundTaskBuilderAvailable();
    }

    inline HRESULT GetPackageFullName(wil::unique_cotaskmem_string& packagedFullName) noexcept try
    {
        WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 packageFullNameLength{ ARRAYSIZE(packageFullName) };
        THROW_IF_FAILED(GetCurrentPackageFullName(&packageFullNameLength, packageFullName));

        packagedFullName = wil::make_cotaskmem_string(packageFullName);
        THROW_IF_NULL_ALLOC(packagedFullName);

        return S_OK;
    }
    CATCH_RETURN()

    inline std::wstring GetExeNameFromPath(std::wstring const& exePath)
    {
        size_t pos{ exePath.rfind(L"\\") };
        THROW_HR_IF(E_UNEXPECTED, pos == std::wstring::npos);
        return exePath.substr(pos + 1); // One after the delimiter
    }

    inline HRESULT GetComRegistrationFromRegistry(const std::wstring argumentToCheck, winrt::guid& comServerClsid) noexcept try
    {
        wil::unique_cotaskmem_string packagedFullName;
        THROW_IF_FAILED(GetPackageFullName(packagedFullName));

        wil::unique_hkey hKey;
        // Path where packaged apps' ComActivators are in the registry:
        // HKLM\SOFTWARE\Classes\PackagedCom\Package\{PackageFullName}\Class
        std::wstring packagedRegistryPath{ LR"(SOFTWARE\Classes\PackagedCom\Package\)" + std::wstring(packagedFullName.get()) };
        std::wstring clsidPath{ packagedRegistryPath + LR"(\Class)"};
        THROW_IF_FAILED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, clsidPath.c_str(), 0, KEY_READ, &hKey));

        DWORD comServerGuidCount{};
        DWORD maxSubKeyLength;
        THROW_IF_FAILED(::RegQueryInfoKey(
            hKey.get(),
            nullptr,    // No user-defined class
            nullptr,    // No user-defined class size
            nullptr,    // Reserved
            &comServerGuidCount,
            &maxSubKeyLength,
            nullptr,    // No subkey class length
            nullptr, // No values we want to get
            nullptr,
            nullptr,    // No max value length
            nullptr,    // No security descriptor
            nullptr     // No last write time
        ));

        THROW_HR_IF_MSG(E_FAIL, comServerGuidCount < 1, "No COM servers are registered for this app");

        maxSubKeyLength++; // Account for the null character

        // Loop through registered ComServerGuids, grab the ServerId and check the registered Arguments/Executable
        bool found = false;
        for (DWORD i = 0; i < comServerGuidCount; i++)
        {
            std::vector<wchar_t> comServerGuid;
            comServerGuid.resize(maxSubKeyLength);
            DWORD cbName{ maxSubKeyLength };
            THROW_IF_FAILED(RegEnumKeyExW(hKey.get(), i, comServerGuid.data(), &cbName, nullptr, nullptr, nullptr, nullptr));
            // Path: HKLM\SOFTWARE\Classes\PackagedCom\Package\{PackageFullName}\Class\{comServerGuid}
            std::wstring clsidPathWithKey{ clsidPath + L"\\" + comServerGuid.data() };

            // Get the ServerId for the ComActivatorGuid
            DWORD serverId = 0;
            DWORD serverIdSize = sizeof(serverId);
            THROW_IF_FAILED(RegGetValueW(
                HKEY_LOCAL_MACHINE,
                clsidPathWithKey.c_str(),
                c_serverIdCommandString.c_str(),
                RRF_RT_REG_DWORD,
                nullptr /* pdwType */,
                &serverId,
                &serverIdSize));

            // Path: HKLM\SOFTWARE\Classes\PackagedCom\Package\{PackageFullName}\Server\{serverId}
            std::wstring serverPath{ packagedRegistryPath + LR"(\Server\)" + std::to_wstring(serverId) };
            WCHAR argumentsBuffer[MAX_PATH];
            DWORD argumentsBufferLength = sizeof(argumentsBuffer);
            THROW_IF_FAILED(RegGetValueW(
                HKEY_LOCAL_MACHINE,
                serverPath.c_str(),
                c_argumentCommandString.c_str(),
                RRF_RT_REG_SZ,
                nullptr /* pdwType */,
                &argumentsBuffer,
                &argumentsBufferLength));

            std::wstring argumentString{ argumentsBuffer };

            if (argumentString == argumentToCheck)
            {
                WCHAR exeBuffer[MAX_PATH];
                DWORD exeBufferLength = sizeof(exeBuffer);
                THROW_IF_FAILED(RegGetValueW(
                    HKEY_LOCAL_MACHINE,
                    serverPath.c_str(),
                    c_executableCommandString.c_str(),
                    RRF_RT_REG_SZ,
                    nullptr /* pdwType */,
                    &exeBuffer,
                    &exeBufferLength));

                std::wstring exeString{ GetExeNameFromPath(exeBuffer) };

                wil::unique_cotaskmem_string exePath;
                THROW_IF_FAILED(wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, exePath));

                std::wstring exeToCheck{ GetExeNameFromPath(exePath.get()) };

                THROW_HR_IF_MSG(E_FAIL, exeString != exeToCheck, "Caller RegistrationProcess is not the same as manifest defined COM Server!");

                std::wstring storedComActivatorString{ comServerGuid.data() };
                comServerClsid = winrt::guid(storedComActivatorString.substr(1, storedComActivatorString.size() - 2));

                found = true;
                break;
            }
        }
        THROW_HR_IF(E_NOT_SET, !found);

        return S_OK;
    }
    CATCH_RETURN();
}
