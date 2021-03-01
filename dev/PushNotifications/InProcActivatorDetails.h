﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "InProcActivatorDetails.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct InProcActivatorDetails : InProcActivatorDetailsT<InProcActivatorDetails>
    {
        InProcActivatorDetails() = default;

        InProcActivatorDetails(hstring const& taskClsid);
        hstring TaskClsid();
        Windows::ApplicationModel::Background::IBackgroundCondition Condition();
        void Condition(Windows::ApplicationModel::Background::IBackgroundCondition const& value);
        winrt::event_token PushActivated(Windows::Foundation::EventHandler<Microsoft::ProjectReunion::PushNotificationActivatedEventArgs> const& handler);
        void PushActivated(winrt::event_token const& token) noexcept;
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration Registration();
        void Registration(Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& value);
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct InProcActivatorDetails : InProcActivatorDetailsT<InProcActivatorDetails, implementation::InProcActivatorDetails>
    {
    };
}
