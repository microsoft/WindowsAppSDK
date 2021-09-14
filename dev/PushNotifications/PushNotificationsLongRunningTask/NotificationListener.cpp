#include "pch.h"

HRESULT NotificationListener::RuntimeClassInitialize(
    std::shared_ptr<ForegroundSinkManager> foregroundSinkManager,
    std::wstring appId,
    std::wstring processName)
{
    m_foregroundSinkManager = foregroundSinkManager;

    m_appId = appId;
    m_processName = processName;

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationListener::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector*/) noexcept try
{
    auto lock = m_lock.lock_exclusive();

    winrt::com_array<uint8_t> payloadArray{ payload, payload + (payloadLength * sizeof(uint8_t)) };

    if (!m_foregroundSinkManager->InvokeForegroundHandlers(m_appId, payloadArray, payloadLength))
    {
        // Command line format: ----WindowsAppSDKPushServer:-Payload:"<payloadAsEscapedUriFormat>"
        std::wstring commandLine = L"----WindowsAppSDKPushServer:-Payload:\"";

        // Escape special characters to follow command line standards for any app activation type in AppLifecycle
        // (See AppInstance.cpp and Serialize() from other activation types)
        std::wstring payloadAsWideString = GetPayloadAsWideString(payloadLength, payload);
        auto payloadAsEscapedUriFormat = winrt::Windows::Foundation::Uri::EscapeComponent(payloadAsWideString.c_str());

        commandLine.append(payloadAsEscapedUriFormat);
        commandLine.append(L"\"");

        SHELLEXECUTEINFO shellExecuteInfo{};
        shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
        shellExecuteInfo.lpFile = m_processName.c_str();
        shellExecuteInfo.lpParameters = commandLine.c_str();

        shellExecuteInfo.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&shellExecuteInfo))
        {
            THROW_IF_WIN32_ERROR(GetLastError());
        }
    };

    return S_OK;
}
CATCH_RETURN()

const std::wstring NotificationListener::GetPayloadAsWideString(unsigned int payloadLength, byte* payload)
{
    int size_needed = MultiByteToWideChar(
        CP_UTF8,
        0,
        reinterpret_cast<PCSTR>(payload),
        payloadLength,
        nullptr,
        0);
    THROW_LAST_ERROR_IF(size_needed == 0);

    std::wstring payloadAsWideString(size_needed, 0);
    size_needed = MultiByteToWideChar(
        CP_UTF8,
        0,
        reinterpret_cast<PCSTR>(payload),
        payloadLength,
        &payloadAsWideString[0],
        size_needed);
    THROW_LAST_ERROR_IF(size_needed == 0);

    return payloadAsWideString;
}
