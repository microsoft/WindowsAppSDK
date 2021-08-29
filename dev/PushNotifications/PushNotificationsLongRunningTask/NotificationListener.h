#pragma once

#define MIDL_NS_PREFIX

#include <FrameworkUdk/PushNotificationsRT.h>

class NotificationListener : public Microsoft::WRL::RuntimeClass<::ABI::Microsoft::Internal::PushNotifications::INotificationListener>
{
public:
    NotificationListener(std::wstring appId);

    STDMETHOD(OnRawNotificationReceived)(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING correlationVector) noexcept;

private:
    std::wstring m_appId;
    wil::srwlock m_lock;
};
