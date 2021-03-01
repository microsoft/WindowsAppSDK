// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "InProcActivatorDetails.h"
#include "InProcActivatorDetails.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    InProcActivatorDetails::InProcActivatorDetails(hstring const& taskClsid)
    {
        throw hresult_not_implemented();
    }
    hstring InProcActivatorDetails::TaskClsid()
    {
        throw hresult_not_implemented();
    }
    Windows::ApplicationModel::Background::IBackgroundCondition InProcActivatorDetails::Condition()
    {
        throw hresult_not_implemented();
    }
    void InProcActivatorDetails::Condition(Windows::ApplicationModel::Background::IBackgroundCondition const& value)
    {
        throw hresult_not_implemented();
    }
    winrt::event_token InProcActivatorDetails::PushActivated(Windows::Foundation::EventHandler<Microsoft::ProjectReunion::PushNotificationActivatedEventArgs> const& handler)
    {
        throw hresult_not_implemented();
    }
    void InProcActivatorDetails::PushActivated(winrt::event_token const& token) noexcept
    {
    }
    Windows::ApplicationModel::Background::IBackgroundTaskRegistration InProcActivatorDetails::Registration()
    {
        throw hresult_not_implemented();
    }
    void InProcActivatorDetails::Registration(Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& value)
    {
        throw hresult_not_implemented();
    }
}
