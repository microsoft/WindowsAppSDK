
#include <pch.h>
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"
#include <iostream>
using namespace winrt;
using namespace winrt::Windows::Foundation;

namespace GetRawNotificationEventArgs {
    static Windows::Foundation::IInspectable GetRawNotificationEventArgs() {
        Windows::Foundation::IInspectable args = nullptr;

        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(L"-ReunionPushServer", 0);
        if (found != std::wstring::npos)
        {
            auto lock = g_lock.lock();
            THROW_HR_IF_NULL(E_UNEXPECTED, g_waitHandleForArgs);

            DWORD waitResult = WaitForSingleObject(g_waitHandleForArgs.get(), 1000);
            if (waitResult == WAIT_OBJECT_0)
            {
                args = g_activatedEventArgs.as<Windows::Foundation::IInspectable>();
            }
        }
        return args;
    }
}
