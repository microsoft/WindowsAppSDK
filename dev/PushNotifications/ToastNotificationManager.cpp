#include "pch.h"

#include "ToastNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.cpp"
#include "winrt/Windows.UI.h"
#include <frameworkudk/pushnotifications.h>
#include "NotificationsLongRunningProcess_h.h"
#include "PushNotificationTelemetry.h"
#include <TerminalVelocityFeatures-PushNotifications.h>

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace Windows::Foundation;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    void ToastNotificationManager::RegisterActivator(winrt::hstring displayName, Uri iconUri, Color const& color)
    {
        auto notificationPlatform{ wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));

        THROW_IF_FAILED(notificationPlatform->RegisterFullTrustApplication(processName.get(), remoteId, &unpackagedAppUserModelId));

        
        return;
    }    
}
