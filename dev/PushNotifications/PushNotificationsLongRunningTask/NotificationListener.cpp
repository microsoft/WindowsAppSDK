#include "pch.h"

#include "NotificationListener.h"
#include "platform.h"

HRESULT NotificationListener::RuntimeClassInitialize(NotificationsLongRunningPlatformImpl* platform, std::wstring appId)
{
    m_platform = platform;
    m_appId = appId;

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationListener::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector*/) noexcept try
{
    auto lock = m_lock.lock_shared();

    // TODO: Look for foreground handler. If not, then do protocol activation

    std::string commandLine = "----WindowsAppSDKPushServer:-Payload:\"";
    commandLine.append(reinterpret_cast<char*>(payload), payloadLength);
    commandLine.append("\"");

    SHELLEXECUTEINFOA shellExecuteInfo{};
    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
    shellExecuteInfo.lpFile = "processName";
    shellExecuteInfo.lpParameters = commandLine.c_str();

    shellExecuteInfo.nShow = SW_NORMAL;

    if (!ShellExecuteExA(&shellExecuteInfo))
    {
        THROW_IF_WIN32_ERROR(GetLastError());
    }

    return S_OK;
}
CATCH_RETURN()
