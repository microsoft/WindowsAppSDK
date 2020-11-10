// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <PowerManager.g.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PowerManager
    {
        PowerManager() = default;

        static EnergySaverStatus EnergySaverStatus()
        {
            return EnergySaverStatus::Disabled;
        }

        static winrt::event_token EnergySaverStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_energySaverStatusChangedEvent.add(handler);
        }

        static void EnergySaverStatusChanged(winrt::event_token const& token)
        {
            m_energySaverStatusChangedEvent.remove(token);
        }

        static BatteryStatus BatteryStatus()
        {
            return BatteryStatus::Charging;
        }

        static winrt::event_token BatteryStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_batteryStatusChangedEvent.add(handler);
        }

        static void BatteryStatusChanged(winrt::event_token const& token)
        {
            m_batteryStatusChangedEvent.remove(token);
        }

    private:
        // REVIEW: what's the lifetime model for static state in C++/WinRT? Their implementation pushes toward true C++
        // statics, which are a natural fit for convenient authoring, but bring in the ever-present problem of "don't
        // do COM stuff under DllMain". Whereas state hanging directly off of a factory instance can be cleaned up as
        // part of DllCanUnloadNow, before DllMain.
        static winrt::event<Windows::Foundation::EventHandler<Windows::Foundation::IInspectable>> m_energySaverStatusChangedEvent;
        static winrt::event<Windows::Foundation::EventHandler<Windows::Foundation::IInspectable>> m_batteryStatusChangedEvent;
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PowerManager : PowerManagerT<PowerManager, implementation::PowerManager>
    {
    };
}
