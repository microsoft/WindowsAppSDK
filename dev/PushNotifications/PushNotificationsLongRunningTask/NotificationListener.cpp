#include "pch.h"
#include "NotificationListener.h"

NotificationListener::NotificationListener(std::wstring appId)
{
    m_appId = appId;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationListener::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING correlationVector) noexcept try
{
    auto lock = m_lock.lock_shared();

    // Look for foreground handler. If not, then do protocol activation

    std::wstring processPath = L"";

    STARTUPINFO startupInfo = { 0 };
    wil::unique_process_information processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    BOOL wasProcessCreated = CreateProcess(
        processPath.c_str(),
        (LPWSTR) L"----WindowsAppSDKPushServer", // Argument indicating activation through Push Notification
        nullptr, // process attributes
        nullptr, // thread attributes
        FALSE,   // inherit handles
        NORMAL_PRIORITY_CLASS, // creation flags
        nullptr, // lpEnvironment
        nullptr, // current directory for the process
        &startupInfo,
        &processInfo
    );

    return S_OK;
}
CATCH_RETURN()
