// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "PushManager.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushManager
    {
        PushManager() = default;

        static void RegisterPushNotificationActivator(Microsoft::ProjectReunion::InProcActivatorDetails const& details);
        static void UnregisterPushNotificationActivator(Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& registration);
        static Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::ChannelResult, Microsoft::ProjectReunion::ChannelResult> CreateChannelAsync(winrt::guid remoteId);
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushManager : PushManagerT<PushManager, implementation::PushManager>
    {
    };
}
