#pragma once

#include "pch.h"
#include "../PushNotificationUtility.h"
#include <winrt/Windows.ApplicationModel.background.h>
#include "PushBackgroundTaskInstance.h"

using namespace winrt::Windows::ApplicationModel::Background;
namespace ToastNotifications
{
    using namespace ABI::Microsoft::Internal::ToastNotifications;
}

HRESULT NotificationListener::RuntimeClassInitialize(
    std::shared_ptr<ForegroundSinkManager> foregroundSinkManager,
    std::shared_ptr<ToastRegistrationManager> toastRegistrationManager,
    std::wstring const& appId,
    std::wstring const& processName,
    winrt::guid const& comServerClsid) noexcept try
{
    m_foregroundSinkManager = foregroundSinkManager;
    m_toastRegistrationManager = toastRegistrationManager;
    m_comServerClsid = comServerClsid;

    m_appId = appId;
    m_processName = processName;

    return S_OK;
}
CATCH_RETURN();

STDMETHODIMP_(HRESULT __stdcall) NotificationListener::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector*/) noexcept try
{
    auto lock = m_lock.lock_exclusive();

    winrt::com_array<uint8_t> payloadArray{ payload, payload + (payloadLength * sizeof(uint8_t)) };

    if (!m_foregroundSinkManager->InvokeForegroundHandlers(m_appId, payloadArray, payloadLength))
    {
        if (m_comServerClsid == winrt::guid())
        {
            THROW_IF_FAILED(winrt::Microsoft::Windows::PushNotifications::Helpers::ProtocolLaunchHelper(m_processName, payloadLength, payload));
        }
        else
        {
            std::wstring payloadString(payloadArray.begin(), payloadArray.end());

            auto localBackgroundTask = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(m_comServerClsid, CLSCTX_ALL);
            auto pushBackgroundTaskInstance{ winrt::make<PushBackgroundTaskInstance>() };
            pushBackgroundTaskInstance.as<PushBackgroundTaskInstance>()->SetRawNotificationPayload(payloadString);
            localBackgroundTask.Run(pushBackgroundTaskInstance);
        }
    };

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationListener::OnToastNotificationReceived(
    ToastNotifications::INotificationProperties* notificationProperties,
    ToastNotifications::INotificationTransientProperties* notificationTransientProperties) noexcept try
{
    std::wstring appId;
    {
        auto lock{ m_lock.lock_shared() };
        appId = m_toastRegistrationManager->GetToastRegistration(m_processName);
    }

    DWORD notificationId{ 0 };
    ToastNotifications_PostToast(appId.c_str(), notificationProperties, notificationTransientProperties, &notificationId);
    return S_OK;
}
CATCH_RETURN()
