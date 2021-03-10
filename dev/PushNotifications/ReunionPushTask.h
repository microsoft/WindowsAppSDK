
struct ReunionPushTask : winrt::implements<ReunionPushTask, winrt::Windows::ApplicationModel::Background::IBackgroundTask>
{
    ReunionPushTask() {}

    void Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance taskInstance);

    void OnCanceled(
        winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance taskInstance,
        winrt::Windows::ApplicationModel::Background::BackgroundTaskCancellationReason cancellationReason)
    {
    }
};

struct ReunionPushTaskFactory : winrt::implements<ReunionPushTaskFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final
    {
        if (aggregateInterface != nullptr) {
            return CLASS_E_NOAGGREGATION;
        }

        return winrt::make<ReunionPushTask>().as(interfaceId, object);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};
