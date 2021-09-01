#pragma once

#include <FrameworkUdk/PushNotificationsRT.h>

class NotificationListener : public Microsoft::WRL::RuntimeClass<::ABI::Microsoft::Internal::PushNotifications::INotificationListener>
{
public:
    HRESULT RuntimeClassInitialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::wstring appId);

    STDMETHOD(OnRawNotificationReceived)(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING correlationVector) noexcept;

private:
    std::shared_ptr<ForegroundSinkManager> m_foregroundSinkManager;

    std::wstring m_processName;
    wil::srwlock m_lock;
};
