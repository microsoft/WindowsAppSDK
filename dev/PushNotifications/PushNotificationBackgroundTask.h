// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <winrt/Windows.ApplicationModel.background.h>

static long g_backgroundTaskServerLock = 0;

struct PushNotificationBackgroundTask : winrt::implements<PushNotificationBackgroundTask, winrt::Windows::ApplicationModel::Background::IBackgroundTask>
{
    PushNotificationBackgroundTask() {}

    void Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance);

    void OnCanceled(
        [[maybe_unused]] winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const&,
        [[maybe_unused]] winrt::Windows::ApplicationModel::Background::BackgroundTaskCancellationReason const&)
    {
    }
};

struct PushNotificationBackgroundTaskFactory : winrt::implements<PushNotificationBackgroundTaskFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<PushNotificationBackgroundTask>().as(interfaceId, object);
    }

    HRESULT __stdcall LockServer(BOOL lock) noexcept final
    {
        if (lock)
        {
            InterlockedIncrement(&g_backgroundTaskServerLock);
        }
        else
        {
            InterlockedDecrement(&g_backgroundTaskServerLock);
        }
        return S_OK;
    }
};
