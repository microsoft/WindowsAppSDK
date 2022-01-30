#include <winrt/Windows.ApplicationModel.background.h>

struct PushBackgroundTaskInstance : winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance
{
    PushBackgroundTaskInstance() {};
    PushBackgroundTaskInstance(std::wstring const& payload): m_payload(payload) {};

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
    std::wstring m_payload;
};

