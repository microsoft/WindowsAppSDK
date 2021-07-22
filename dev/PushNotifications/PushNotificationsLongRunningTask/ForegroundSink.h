#include "pch.h"
#include <list>
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>

class ForegroundSink
{
    typedef winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Networking::PushNotifications::PushNotificationChannel, winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs> PushNotificationReceivedEventHandler;

    public:
        ForegroundSink() = default;
        ~ForegroundSink() = default;

        bool AddEvent();
        bool Invoke();
        bool InvokeAll();
        bool Remove();
        bool RemoveAll();

    private:
        Microsoft::WRL::EventSource<PushNotificationReceivedEventHandler> m_event;
};
