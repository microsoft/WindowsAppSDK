// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <winrt/Windows.Networking.PushNotifications.h>
#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Security.Cryptography.h>

struct PushRawNotification : winrt::implements<PushRawNotification, winrt::Windows::Networking::PushNotifications::IRawNotification, winrt::Windows::Networking::PushNotifications::IRawNotification2, winrt::Windows::Networking::PushNotifications::IRawNotification3>
{
    PushRawNotification() {};
    PushRawNotification(std::wstring const& payload): m_payload(payload) {};

    winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> Headers() { return {}; };
    winrt::hstring ChannelId() { return {}; };
    winrt::hstring Content() { return winrt::to_hstring(m_payload.c_str()); };
    winrt::Windows::Storage::Streams::IBuffer ContentBytes() {
        return winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(m_payload,
            winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf8);
    };

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
