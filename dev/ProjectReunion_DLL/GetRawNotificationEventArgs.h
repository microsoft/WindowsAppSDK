
#include <pch.h>
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
constexpr PCWSTR pushServerArgument = L"-ReunionPushServer";

namespace GetRawNotificationEventArgs
{
    static Windows::Foundation::IInspectable GetRawNotificationEventArgs()
    {
        winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs args = nullptr;

        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(pushServerArgument, 0);
        if (found != std::wstring::npos)
        {
            {
                auto lock = g_lock.lock();
                THROW_HR_IF_NULL_MSG(E_UNEXPECTED, g_waitHandleForArgs, "PushNotificationManager::RegisterActivator has not been called.");
            }

            if (WaitForSingleObject(g_waitHandleForArgs.get(), 1000) == WAIT_OBJECT_0)
            {
                auto lock = g_lock.lock();
                std::swap(args, g_activatedEventArgs);
            }
        }
        return args;
    }
}
