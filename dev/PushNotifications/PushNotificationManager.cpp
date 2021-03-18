#include "pch.h"

#include "PushNotificationManager.h"
#include "PushNotificationManager.g.cpp"

#include <winrt/Windows.ApplicationModel.background.h>
#include "PushNotificationBackgroundTask.h"

constexpr PCWSTR backgroundTaskName = L"PushNotificationBackgroundTask";

using namespace winrt::Windows::ApplicationModel::Background;

extern wil::unique_handle g_waitHandleForArgs;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Microsoft::ProjectReunion::PushNotificationRegistrationToken PushNotificationManager::RegisterActivator(Microsoft::ProjectReunion::PushNotificationActivationInfo const& details)
    {
        int passedFlags = static_cast<int>(details.Kind());
        winrt::guid taskClsid = details.TaskClsid();

        BackgroundTaskRegistration registeredTask = nullptr;

        if (passedFlags & static_cast<int>(PushNotificationRegistrationKind::PushTrigger))
        {
            bool taskRegistered = false;

            for (auto task : BackgroundTaskRegistration::AllTasks())
            {
                if (task.Value().Name() == backgroundTaskName)
                {
                    taskRegistered = true;
                    break;
                }
            }

            if (!taskRegistered)
            {
                BackgroundTaskBuilder builder;
                builder.Name(backgroundTaskName);

                PushNotificationTrigger trigger{};
                builder.SetTrigger(trigger);

                // QUERY IF API EXISTS (Vb and beyond)
                if (taskClsid != winrt::guid())
                {
                    // Only applicable for a Win32 app
                    builder.SetTaskEntryPointClsid(taskClsid);
                }

                registeredTask = builder.Register();
            }
        }

        if (passedFlags & static_cast<int>(PushNotificationRegistrationKind::ComActivator))
        {
            if (taskClsid != winrt::guid()) // Register with COM for Win32
            {
                // Define handle that will be set during background task execution
                g_waitHandleForArgs = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));

                ::CoRegisterClassObject(
                    taskClsid,
                    winrt::make<PushNotificationBackgroundTaskFactory>().get(),
                    CLSCTX_LOCAL_SERVER,
                    REGCLS_MULTIPLEUSE,
                    &s_cookie);
            }
        }

        return PushNotificationRegistrationToken{s_cookie, registeredTask};
    }

    void PushNotificationManager::UnregisterActivator(Microsoft::ProjectReunion::PushNotificationRegistrationToken const& token, Microsoft::ProjectReunion::PushNotificationRegistrationKind const& kind)
    {
        bool taskRegistered = false;
        int passedFlags = static_cast<int>(kind);

        if (passedFlags & static_cast<int>(PushNotificationRegistrationKind::PushTrigger))
        {
            for (auto task : BackgroundTaskRegistration::AllTasks())
            {
                if (task.Value().Name() == backgroundTaskName)
                {
                    task.Value().Unregister(false /*cancel task*/);
                }
            }
        }

        if (passedFlags & static_cast<int>(PushNotificationRegistrationKind::ComActivator) && s_cookie != 0)
        {
            ::CoRevokeClassObject(s_cookie);
            s_cookie = 0;
        }
    }

    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushNotificationCreateChannelResult, Microsoft::ProjectReunion::PushNotificationCreateChannelResult> PushNotificationManager::CreateChannelAsync(winrt::guid remoteId)
    {
        // Sharath's work
        throw hresult_not_implemented();
    }
}
