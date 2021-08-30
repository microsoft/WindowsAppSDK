// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.h"
#include <windows.foundation.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct ChannelDetails {
        wil::unique_cotaskmem_string channelUri;
        wil::unique_cotaskmem_string channelId;
        wil::unique_cotaskmem_string appUserModelId;
        winrt::Windows::Foundation::DateTime channelExpiryTime;
    };

    struct PushNotificationManager
    {
        PushNotificationManager() = delete;

        static Microsoft::Windows::PushNotifications::PushNotificationRegistrationToken RegisterActivator(Microsoft::Windows::PushNotifications::PushNotificationActivationInfo const& details);
        static void UnregisterActivator(Microsoft::Windows::PushNotifications::PushNotificationRegistrationToken const& token, Microsoft::Windows::PushNotifications::PushNotificationRegistrationOptions const& options);

        static winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> CreateChannelAsync(const winrt::guid &remoteId);

        static bool IsActivatorSupported(Microsoft::Windows::PushNotifications::PushNotificationRegistrationOptions const& options);

    private:
        static bool IsChannelRequestRetryable(const winrt::hresult& hrException);
        static bool IsBackgroundTaskBuilderAvailable();
        static void RegisterUnpackagedApplicationHelper(const winrt::guid& remoteId, _Out_ wil::unique_cotaskmem_string& unpackagedAppUserModelId);
        static winrt::hresult CreateChannelWithRemoteIdHelper(const winrt::guid& remoteId, ChannelDetails& channelInfo);
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
