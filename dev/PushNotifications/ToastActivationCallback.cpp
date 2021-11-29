#include "pch.h"
#include <ToastActivationCallback.h>
#include "ToastActivatedEventArgs.h"
#include "externs.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <iostream>
namespace winrt
{
    using namespace Microsoft::Windows::PushNotifications;
    using namespace Windows::ApplicationModel::Core;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
}

HRESULT __stdcall ToastActivationCallback::Activate(
    LPCWSTR appUserModelId,
    LPCWSTR invokedArgs,
    [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
    [[maybe_unused]] ULONG dataCount)
{
    winrt::IMap<winrt::hstring, winrt::hstring> userInput{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
    for (unsigned long i = 0; i < dataCount; i++)
    {
        userInput.Insert(data[i].Key, data[i].Value);
    }

    auto appProperties = winrt::CoreApplication::Properties();
    winrt::ToastActivatedEventArgs activatedEventArgs = winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::ToastActivatedEventArgs>(invokedArgs, userInput);

    if (GetToastHandleCount())
    {
        GetToastHandlers()(*this, activatedEventArgs);
    }
    else
    {
        appProperties.Insert(ACTIVATED_EVENT_ARGS_KEY, activatedEventArgs);
        SetEvent(GetWaitHandleForArgs().get());
    }
    return S_OK;
}
