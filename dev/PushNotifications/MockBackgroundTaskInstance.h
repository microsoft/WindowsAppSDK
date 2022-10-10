// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <winrt/Windows.ApplicationModel.background.h>
#include "MockRawNotification.h"
#include "PushNotificationDummyDeferral.h"

// Mocks IBackgroundTaskInstance to send raw payloads to packaged apps in
// PushNotificationBackgroundTask::Run by com activation from PushNotificationsLongRunningProcess
struct MockBackgroundTaskInstance : winrt::implements<MockBackgroundTaskInstance, winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance>
{
    MockBackgroundTaskInstance() {};
    MockBackgroundTaskInstance(std::wstring const& payload) : m_rawNotification(winrt::make_self<MockRawNotification>(payload)) {};

    winrt::guid InstanceId() { return winrt::guid(); };
    UINT32 SuspendedCount() { return 0; };
    UINT32 Progress() { return 0; };
    UINT32 Progress(UINT32 /* progress */) { return 0; };
    winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration Task() { return nullptr; };
    winrt::Windows::Foundation::IInspectable TriggerDetails() { return m_rawNotification.as<IInspectable>(); };
    winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& /* handler */) { return winrt::event_token{}; };
    void Canceled(winrt::event_token const& /* token */) noexcept { return; };
    winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral() { return winrt::make<PushNotificationDummyDeferral>().as<winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral>(); };
private:
    winrt::com_ptr<MockRawNotification> m_rawNotification;
};

struct MockBackgroundTaskInstanceFactory : winrt::implements<MockBackgroundTaskInstanceFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final try
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<MockBackgroundTaskInstance>().as(interfaceId, object);
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
