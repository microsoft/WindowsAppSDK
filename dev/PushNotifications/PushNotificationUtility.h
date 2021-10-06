// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"
#include "../Common/Microsoft.Utf8.h"
#include  "NotificationsLongRunningProcess_h.h"

namespace winrt::Microsoft::Windows::PushNotifications::Helpers
{
    inline wil::unique_cotaskmem_string GetAppUserModelId()
    {
        wchar_t appId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appIdSize{ ARRAYSIZE(appId) };

        THROW_IF_FAILED(::GetCurrentApplicationUserModelId(&appIdSize, appId));

        return wil::make_unique_string<wil::unique_cotaskmem_string>(appId);
    }

    inline HRESULT ProtocolLaunchHelper(std::wstring processName, _In_ byte* payload) noexcept try
    {
        // Command line format: ----WindowsAppRuntimePushServer:-Payload:"<payloadAsEscapedUriFormat>"
        std::wstring commandLine = L"----WindowsAppRuntimePushServer:-Payload:\"";

        // Escape special characters to follow command line standards for any app activation type in AppLifecycle
        // (See AppInstance.cpp and Serialize() from other activation types)
        auto payloadAsWideString{ ::Microsoft::Utf8::ToUtf16<std::wstring>(reinterpret_cast<PCSTR>(payload)) };
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

    inline wil::com_ptr<INotificationsLongRunningPlatform> GetNotificationPlatform()
    {
        return wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER);
    }
}
