#include "pch.h"

HRESULT NotificationListener::RuntimeClassInitialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::wstring processName)
{
    m_foregroundSinkManager = foregroundSinkManager;
    m_processName = processName;

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationListener::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector*/) noexcept try
{
    auto lock = m_lock.lock_exclusive();

    winrt::com_array<uint8_t> payloadArray{ payload, payload + (payloadLength * sizeof(uint8_t)) };

    if (!m_foregroundSinkManager->InvokeForegroundHandlers(m_processName, payloadArray, payloadLength))
    {
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
    };

    return S_OK;
}
CATCH_RETURN()
