
#include <pch.h>
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;

namespace GetRawNotificationEventArgs {
    
    // static com_ptr<Windows::Foundation::IInspectable> GetRawNotificationEventArgs() {
    static Windows::Foundation::IInspectable GetRawNotificationEventArgs() {
        Windows::Foundation::IInspectable args = nullptr;

        // Read command line args to determine ActivationKind
        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(L"-ReunionPushServer", 0);
  
        if (found != std::wstring::npos)
        {
            if (g_waitHandleForArgs == nullptr)
            {
                winrt::throw_hresult(E_UNEXPECTED);
            }

            DWORD waitResult = WaitForSingleObject(g_waitHandleForArgs.get(), 1000);
            if (waitResult == WAIT_OBJECT_0)
            {
                args = g_activatedEventArgs.as<Windows::Foundation::IInspectable>();
            }
        }
        return args;
    }
}
