// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>

#include "PushNotificationReceivedEventArgs.h"

#include <NotificationAppLifecycle.h>
#include <NotificationAppLifecycle.g.cpp>

#include "NotificationActivationArguments.h"

extern wil::unique_handle g_waitHandleForArgs;
extern winrt::Microsoft::ProjectReunion::PushNotificationReceivedEventArgs g_activatedEventArgs;

namespace winrt
{
    using namespace Windows::Foundation;
    using Windows::ApplicationModel::Activation::IActivatedEventArgs;
}

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Microsoft::ProjectReunion::NotificationActivationArguments NotificationAppLifecycle::GetRawNotificationEventArgs()
    {
        DWORD waitResult = 0;

        // Read command line args to determine ActivationKind
        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(L"-ReunionPushServer", 0);

        if (found)
        {
            if (g_waitHandleForArgs == nullptr)
            {
                winrt::throw_hresult(E_UNEXPECTED);
            }

            waitResult = WaitForSingleObject(g_waitHandleForArgs.get(), 1000);

            if (waitResult != WAIT_OBJECT_0)
            {
                return make<NotificationActivationArguments>(NotificationActivationKind::Launch, nullptr);
            }

            IInspectable pushData = g_activatedEventArgs.as<IInspectable>();
            return make<NotificationActivationArguments>(NotificationActivationKind::Push, pushData);
        }
        else
        {
            return make<NotificationActivationArguments>(NotificationActivationKind::Launch, nullptr);
        }
    }
}
