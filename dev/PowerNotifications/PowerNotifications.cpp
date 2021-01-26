// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <PowerNotifications.h>
#include <PowerManager.g.cpp>


namespace winrt::Microsoft::ProjectReunion::implementation
{
    PowerManager::eventType PowerManager::m_energySaverStatusChangedEvent;
    PowerManager::eventType PowerManager::m_batteryStatusChangedEvent;
    PowerManager::eventType PowerManager::m_powerSupplyStatusChangedEvent;
    PowerManager::eventType PowerManager::m_remainingChargePercentChangedEvent;
    PowerManager::eventType PowerManager::m_remainingDischargeTimeChangedEvent;

    PowerManager::eventType PowerManager::m_powerSourceStatusChangedEvent;
    PowerManager::eventType PowerManager::m_displayStatusChangedEvent;
    PowerManager::eventType PowerManager::m_systemIdleStatusChangedEvent;
    PowerManager::eventType PowerManager::m_powerSchemePersonalityChangedEvent;
    PowerManager::eventType PowerManager::m_userPresenceStatusChangedEvent;
    PowerManager::eventType PowerManager::m_systemAwayModeStatusChangedEvent;
    

    void PowerManager::SystemAwayModeStatusChanged(winrt::event_token const& token)
    {
        m_systemAwayModeStatusChangedEvent.get().remove(token);

        auto f = make<winrt::Microsoft::ProjectReunion::factory_implementation::PowerManager>().as<Microsoft::ProjectReunion::IPowerManagerStatics>();
        m_systemAwayModeStatusChangedEvent.get()(f, nullptr);
    }
}
