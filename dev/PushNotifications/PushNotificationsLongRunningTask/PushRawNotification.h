#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>

struct PushRawNotification : winrt::implements<PushRawNotification, winrt::Windows::Networking::PushNotifications::IRawNotification, winrt::Windows::Networking::PushNotifications::IRawNotification2, winrt::Windows::Networking::PushNotifications::IRawNotification3>
{
    PushRawNotification() {};
    PushRawNotification(std::wstring const& payload): m_payload(payload) {};

    winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> Headers();
    winrt::hstring ChannelId();
    winrt::hstring Content();
    winrt::Windows::Storage::Streams::IBuffer ContentBytes();
private:
    std::wstring m_payload;
};

struct PushRawNotificationFactory : winrt::implements<PushRawNotificationFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<PushRawNotification>().as(interfaceId, object);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};
