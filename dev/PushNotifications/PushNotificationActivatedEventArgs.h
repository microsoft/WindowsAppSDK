// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "PushNotificationActivatedEventArgs.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationActivatedEventArgs : PushNotificationActivatedEventArgsT<PushNotificationActivatedEventArgs>
    {
        PushNotificationActivatedEventArgs() = default;

        PushNotificationActivatedEventArgs(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        com_array<uint8_t> Payload();
        void GetDeferral();
        void CompleteDeferral();
        winrt::event_token Canceled(Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
        void Canceled(winrt::event_token const& token) noexcept;
        uint32_t SuspendedCount();
        Windows::ApplicationModel::Activation::ActivationKind Kind();
        Windows::ApplicationModel::Activation::ApplicationExecutionState PreviousExecutionState();
        Windows::ApplicationModel::Activation::SplashScreen SplashScreen();
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationActivatedEventArgs : PushNotificationActivatedEventArgsT<PushNotificationActivatedEventArgs, implementation::PushNotificationActivatedEventArgs>
    {
    };
}
