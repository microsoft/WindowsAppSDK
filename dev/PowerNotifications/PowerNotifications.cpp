// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <PowerNotifications.h>
#include <PowerManager.g.cpp>


namespace winrt::Microsoft::ProjectReunion::implementation
{
    winrt::event<Windows::Foundation::EventHandler<Windows::Foundation::IInspectable>> PowerManager::m_energySaverStatusChangedEvent;
    winrt::event<Windows::Foundation::EventHandler<Windows::Foundation::IInspectable>> PowerManager::m_batteryStatusChangedEvent;
}
