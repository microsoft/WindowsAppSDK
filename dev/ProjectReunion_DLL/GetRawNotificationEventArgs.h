
#include <pch.h>
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;

constexpr PCWSTR reunionPushServerArg = L"-ReunionPushServer";

namespace GetRawNotificationEventArgs {
    static Windows::Foundation::IInspectable GetRawNotificationEventArgs() {
        Windows::Foundation::IInspectable args = nullptr;

        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(reunionPushServerArg, 0);
        if (found != std::wstring::npos)
        {
            {
                auto lock = g_lock.lock();
                THROW_HR_IF_NULL_MSG(E_UNEXPECTED, g_waitHandleForArgs, "PushNotificationManager::RegisterActivator has not been called.");
            }

            DWORD waitResult = WaitForSingleObject(g_waitHandleForArgs.get(), 1000);
            if (waitResult == WAIT_OBJECT_0)
            {
                auto lock = g_lock.lock();
                args = g_activatedEventArgs.as<Windows::Foundation::IInspectable>();
                g_activatedEventArgs = nullptr;
            }
        }
        return args;
    }
}
