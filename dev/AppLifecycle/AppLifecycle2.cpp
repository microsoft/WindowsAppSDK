#include "pch.h"

#include <synchapi.h>
#include <wil/resource.h>

#include "AppLifecycle2.h"
#include "AppLifecycle2.g.cpp"

#include <ActivatedEventArgsExtension.h>

#include "../PushNotifications/PushNotificationActivatedEventArgs.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Microsoft::ProjectReunion::ActivatedEventArgsExtension AppLifecycle2::GetActivatedEventArgs()
    {
        DWORD waitResult = 0;

        // Read command line args to determine ActivationKind
        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(L"-ReunionPushServer", 0);

        if (found)
        {
            // Wait for the args from background task
            winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs activatedEventArgs = 
                PushNotificationActivatedEventArgs::GetPushNotificationActivatedEventArgs();

            if (activatedEventArgs == nullptr)
            {
                winrt::Microsoft::ProjectReunion::ActivatedEventArgsExtension argsExtension{ activatedEventArgs, ActivationKindExtension::Launch };
                return argsExtension;
            }
            else
            {
                winrt::Microsoft::ProjectReunion::ActivatedEventArgsExtension argsExtension{ activatedEventArgs, ActivationKindExtension::Push };
                return argsExtension;
            }
        }
        
        winrt::Microsoft::ProjectReunion::ActivatedEventArgsExtension argsExtension{ nullptr, ActivationKindExtension::Launch };
        return argsExtension;
    }
}
