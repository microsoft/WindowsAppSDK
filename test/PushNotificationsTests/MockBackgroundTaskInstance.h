#include <winrt/Windows.ApplicationModel.background.h>
#include "MockRawNotification.h"
struct MockBackgroundTaskInstance : winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance
{
    MockBackgroundTaskInstance() {}
public:

    winrt::Windows::Networking::PushNotifications::RawNotification TriggerDetails()
    {
        MockRawNotification result;
        return result.as<winrt::Windows::Networking::PushNotifications::RawNotification>();
    }
};
