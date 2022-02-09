// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"
#include  "NotificationsLongRunningProcess_h.h"
#include <winrt/Windows.Foundation.Metadata.h>
#include "../Common/AppModel.Identity.h"
#include "PushBackgroundTaskInstance.h"

namespace winrt
{
    using namespace Windows::Foundation;
}
namespace winrt::Microsoft::Windows::PushNotifications::Helpers
{
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
}
