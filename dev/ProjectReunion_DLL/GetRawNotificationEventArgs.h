
#include <pch.h>
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"
#include <iostream>
using namespace winrt;
using namespace winrt::Windows::Foundation;

namespace GetRawNotificationEventArgs {
    
    //static com_ptr<Windows::Foundation::IInspectable> GetRawNotificationEventArgs() {
    static Windows::Foundation::IInspectable GetRawNotificationEventArgs() {
        Windows::Foundation::IInspectable args = nullptr;
        std::cout << "GetRawNotificationEventArgs -> Start" << std::endl;
        // Read command line args to determine ActivationKind
        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(L"-ReunionPushServer", 0);

        std::cout << g_sample << std::endl;
        if (found != std::wstring::npos)
        {
            // auto lock = g_lock.lock();
            DWORD waitResult = WaitForSingleObject(g_waitHandleForArgs.get(), 1000);
            if (waitResult == WAIT_OBJECT_0)
            {
                std::cout << "g_waitHandleForArgs != nullptr" << std::endl;
                args = g_activatedEventArgs.as<Windows::Foundation::IInspectable>();
            }
        }
        std::cout << "GetRawNotificationEventArgs -> End" << std::endl;
        return args;
    }
}
