#pragma once

#define MIDL_NS_PREFIX

#include <FrameworkUdk/PushNotificationsRT.h>

struct NotificationsLongRunningPlatformImpl;

class NotificationListener : public Microsoft::WRL::RuntimeClass<::ABI::Microsoft::Internal::PushNotifications::INotificationListener>
{
public:
    HRESULT RuntimeClassInitialize(NotificationsLongRunningPlatformImpl* platform, std::wstring appId);

    STDMETHOD(OnRawNotificationReceived)(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING correlationVector) noexcept;

private:
    NotificationsLongRunningPlatformImpl* m_platform = nullptr;

    std::wstring m_appId;
    wil::srwlock m_lock;
};
