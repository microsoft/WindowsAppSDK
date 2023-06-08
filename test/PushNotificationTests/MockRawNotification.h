// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <TestDef.h>

struct MockRawNotification : winrt::implements<MockRawNotification, winrt::Windows::Networking::PushNotifications::IRawNotification, winrt::Windows::Networking::PushNotifications::IRawNotification2, winrt::Windows::Networking::PushNotifications::IRawNotification3>
{
    MockRawNotification() {};

    winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> Headers();
    winrt::hstring ChannelId();
    winrt::hstring Content();
    winrt::Windows::Storage::Streams::IBuffer ContentBytes();
};

struct MockRawNotificationFactory : winrt::implements<MockRawNotificationFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<MockRawNotification>().as(interfaceId, object);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};
