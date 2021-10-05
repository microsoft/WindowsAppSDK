// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "externs.h"
#include "PushNotificationUtility.h"

wil::unique_cotaskmem_string GetAppUserModelId()
{
    wchar_t appId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
    UINT32 appIdSize{ ARRAYSIZE(appId) };

    THROW_IF_FAILED(::GetCurrentApplicationUserModelId(&appIdSize, appId));

    return wil::make_unique_string<wil::unique_cotaskmem_string>(appId);
}

std::wstring Utf8BytesToWideString(unsigned int payloadLength, _In_reads_(payloadLength) byte* payload)
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

void ProtocolLaunchHelper(unsigned int payloadLength, _In_reads_(payloadLength) byte* payload)
{
    // Command line format: ----WindowsAppRuntimePushServer:-Payload:"<payloadAsEscapedUriFormat>"
    std::wstring commandLine = L"----WindowsAppRuntimePushServer:-Payload:\"";

    // Escape special characters to follow command line standards for any app activation type in AppLifecycle
    // (See AppInstance.cpp and Serialize() from other activation types)
    std::wstring payloadAsWideString = Utf8BytesToWideString(payloadLength, payload);
    auto payloadAsEscapedUriFormat = winrt::Windows::Foundation::Uri::EscapeComponent(payloadAsWideString.c_str());

    commandLine.append(payloadAsEscapedUriFormat);
    commandLine.append(L"\"");

    wil::unique_cotaskmem_string processName;
    THROW_IF_FAILED(GetCurrentProcessPath(processName));

    SHELLEXECUTEINFO shellExecuteInfo{};
    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
    shellExecuteInfo.lpFile = processName.get();
    shellExecuteInfo.lpParameters = commandLine.c_str();

    shellExecuteInfo.nShow = SW_NORMAL;

    if (!ShellExecuteEx(&shellExecuteInfo))
    {
        THROW_IF_WIN32_ERROR(GetLastError());
    }
}
