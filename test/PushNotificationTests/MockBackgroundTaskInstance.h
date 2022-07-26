// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <winrt/Windows.ApplicationModel.background.h>

struct MockBackgroundTaskInstance : winrt::implements<MockBackgroundTaskInstance, winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance>
{
    MockBackgroundTaskInstance() {};

    winrt::guid InstanceId();
    UINT32 SuspendedCount();
    UINT32 Progress();
    UINT32 Progress(UINT32 progress);
    winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration Task();
    winrt::Windows::Foundation::IInspectable TriggerDetails();
    winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
    void Canceled(winrt::event_token const& token) noexcept;
    winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral();
};

struct MockBackgroundTaskInstanceFactory : winrt::implements<MockBackgroundTaskInstanceFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<MockBackgroundTaskInstance>().as(interfaceId, object);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};
