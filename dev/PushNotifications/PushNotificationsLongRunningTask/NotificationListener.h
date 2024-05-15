// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <FrameworkUdk/PushNotificationsRT.h>
#include <FrameworkUdk/ToastNotificationsRT.h>
#include "ToastRegistrationManager.h"

class NotificationListener : public Microsoft::WRL::RuntimeClass<::ABI::Microsoft::Internal::PushNotifications::INotificationListener,
                                                                    ::ABI::Microsoft::Internal::PushNotifications::INotificationListener2>
{
public:
    HRESULT RuntimeClassInitialize(
        std::shared_ptr<ForegroundSinkManager> foregroundSinkManager,
        std::shared_ptr<ToastRegistrationManager> toastRegistrationManager,
        std::wstring const& appId,
        std::wstring const& processName,
        winrt::guid const& comServerClsid) noexcept;

    STDMETHOD(OnRawNotificationReceived)(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING correlationVector) noexcept;
    STDMETHOD(OnToastNotificationReceived)(ABI::Microsoft::Internal::ToastNotifications::INotificationProperties* notificationProperties,
        ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties*) noexcept;
private:
    std::shared_ptr<ForegroundSinkManager> m_foregroundSinkManager;
    std::shared_ptr<ToastRegistrationManager> m_toastRegistrationManager;

    std::wstring m_appId;
    std::wstring m_processName;
    winrt::guid m_comServerClsid{};
    wil::srwlock m_lock;
};
