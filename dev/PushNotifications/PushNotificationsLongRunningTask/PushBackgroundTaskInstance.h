#include <winrt/Windows.ApplicationModel.background.h>

// Mocks IBackgroundTaskInstance to send raw payloads to packaged apps in
// PushNotificationBackgroundTask::Run by com activation from PushNotificationsLongRunningProcess
struct PushBackgroundTaskInstance : winrt::implements<PushBackgroundTaskInstance, winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance>
{
    PushBackgroundTaskInstance() {};
    PushBackgroundTaskInstance(winrt::com_ptr<PushRawNotification> rawNotification): m_rawNotification(rawNotification) {};

    winrt::guid InstanceId();
    UINT32 SuspendedCount();
    UINT32 Progress();
    UINT32 Progress(UINT32 progress);
    winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration Task();
    winrt::Windows::Foundation::IInspectable TriggerDetails();
    winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
    void Canceled(winrt::event_token const& token) noexcept;
    winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral();
private:
    winrt::com_ptr<PushRawNotification> m_rawNotification{ nullptr };
};

struct PushBackgroundTaskInstanceFactory : winrt::implements<PushBackgroundTaskInstanceFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<PushBackgroundTaskInstance>().as(interfaceId, object);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};
