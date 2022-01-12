#pragma once

#include "pch.h"
#include "../PushNotificationUtility.h"

HRESULT NotificationListener::RuntimeClassInitialize(
    std::shared_ptr<ForegroundSinkManager> foregroundSinkManager,
    std::shared_ptr<ToastRegistrationManager> toastRegistrationManager,
    std::wstring appId,
    std::wstring processName)
{
    m_foregroundSinkManager = foregroundSinkManager;
    m_toastRegistrationManager = toastRegistrationManager;

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
        THROW_IF_FAILED(winrt::Microsoft::Windows::PushNotifications::Helpers::ProtocolLaunchHelper(m_processName, payloadLength, payload));
    };

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationListener::OnToastNotificationReceived(
    ABI::Microsoft::Internal::ToastNotifications::INotificationProperties* notificationProperties,
    ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties* notificationTransientProperties) noexcept try
{
    auto lock = m_lock.lock_exclusive();

    std::wstring toastGuid{ m_toastRegistrationManager->GetToastRegistration(m_processName) };

    DWORD notificationId{ 0 };
    ToastNotifications_PostToast(toastGuid.c_str(), notificationProperties, notificationTransientProperties, &notificationId);
    return S_OK;
}
CATCH_RETURN()
