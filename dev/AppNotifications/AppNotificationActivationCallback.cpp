#include "pch.h"
#include <AppNotificationActivationCallback.h>
#include "AppNotificationActivatedEventArgs.h"
#include "externs.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <iostream>
#include <AppNotificationUtility.h>
#include <AppNotificationManager.h>

namespace winrt
{
    using namespace Microsoft::Windows::AppNotifications;
    using namespace Windows::ApplicationModel::Core;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
}

using namespace Microsoft::Windows::AppNotifications::Helpers;

HRESULT __stdcall AppNotificationActivationCallback::Activate(
    LPCWSTR /* appUserModelId */,
    LPCWSTR invokedArgs,
    [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
    [[maybe_unused]] ULONG dataCount) noexcept try
{
    winrt::IMap<winrt::hstring, winrt::hstring> userInput{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
    for (unsigned long i = 0; i < dataCount; i++)
    {
        userInput.Insert(data[i].Key, data[i].Value);
    }

    winrt::AppNotificationActivatedEventArgs activatedEventArgs = winrt::make<winrt::Microsoft::Windows::AppNotifications::implementation::AppNotificationActivatedEventArgs>(invokedArgs, userInput);

    winrt::AppNotificationManager notificationManager = winrt::AppNotificationManager::Default();
    winrt::Microsoft::Windows::AppNotifications::implementation::AppNotificationManager* notificationManagerImpl = winrt::get_self<winrt::Microsoft::Windows::AppNotifications::implementation::AppNotificationManager>(notificationManager);
    if (notificationManagerImpl->ContainsInvokeHandler())
    {
        /* As the process is already launched, we invoke the foreground toast event handlers with the activatedEventArgs */
        notificationManagerImpl->InvokeHandler(activatedEventArgs);
    }
    else
    {
        /* Activation results in a process launch, we cache the activatedEventArgs in the COM static store
           and fire an event to let the main thread know that it is okay to infer into AppLifeCycle::GetToastActivatedEventArgs().
        */
        auto appProperties = winrt::CoreApplication::Properties();
        appProperties.Insert(ACTIVATED_EVENT_ARGS_KEY, activatedEventArgs);
        SetEvent(GetWaitHandleForArgs().get());
    }

    return S_OK;
}
CATCH_RETURN()
