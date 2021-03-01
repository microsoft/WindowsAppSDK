// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushNotificationActivatedEventArgs.h"
#include "PushNotificationActivatedEventArgs.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushNotificationActivatedEventArgs::PushNotificationActivatedEventArgs(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask)
    {
        throw hresult_not_implemented();
    }
    com_array<uint8_t> PushNotificationActivatedEventArgs::Payload()
    {
        throw hresult_not_implemented();
    }
    void PushNotificationActivatedEventArgs::GetDeferral()
    {
        throw hresult_not_implemented();
    }
    void PushNotificationActivatedEventArgs::CompleteDeferral()
    {
        throw hresult_not_implemented();
    }
    winrt::event_token PushNotificationActivatedEventArgs::Canceled(Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler)
    {
        throw hresult_not_implemented();
    }
    void PushNotificationActivatedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
    }
    uint32_t PushNotificationActivatedEventArgs::SuspendedCount()
    {
        throw hresult_not_implemented();
    }
    Windows::ApplicationModel::Activation::ActivationKind PushNotificationActivatedEventArgs::Kind()
    {
        throw hresult_not_implemented();
    }
    Windows::ApplicationModel::Activation::ApplicationExecutionState PushNotificationActivatedEventArgs::PreviousExecutionState()
    {
        throw hresult_not_implemented();
    }
    Windows::ApplicationModel::Activation::SplashScreen PushNotificationActivatedEventArgs::SplashScreen()
    {
        throw hresult_not_implemented();
    }
}
