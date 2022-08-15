// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <winrt/Windows.ApplicationModel.background.h>

// Mocks IBackgroundTaskInstance to send raw payloads to packaged apps in
// PushNotificationBackgroundTask::Run by com activation from PushNotificationsLongRunningProcess
struct PushBackgroundTaskInstance : winrt::implements<PushBackgroundTaskInstance, winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance>
{
    PushBackgroundTaskInstance() {};
    PushBackgroundTaskInstance(std::wstring const& payload): m_payload(payload) {};

    winrt::guid InstanceId() { return winrt::guid(); };
    UINT32 SuspendedCount() { return 0; };
    UINT32 Progress() { return 0; };
    UINT32 Progress(UINT32 /* progress */) { return 0; };
    winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration Task() { return nullptr; };
    winrt::Windows::Foundation::IInspectable TriggerDetails() { return winrt::box_value(m_payload); };
    winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& /* handler */) { return winrt::event_token{}; };
    void Canceled(winrt::event_token const& /* token */) noexcept { return; };
    winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral() { return nullptr; };
private:
    std::wstring m_payload;
};

struct PushBackgroundTaskInstanceFactory : winrt::implements<PushBackgroundTaskInstanceFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final try
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<PushBackgroundTaskInstance>().as(interfaceId, object);
    } 
    CATCH_RETURN()

    STDMETHODIMP LockServer(BOOL fLock) noexcept final
    {
        if (fLock)
        {
            ++winrt::get_module_lock();
        }
        else
        {
            --winrt::get_module_lock();
        }
        return S_OK;
    }
};
