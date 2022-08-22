// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once
#include "pch.h"
#include "PushNotificationLongRunningTaskTelemetry.h"

ToastRegistrationManager::ToastRegistrationManager()
{
    PushNotificationLongRunningTaskTelemetry::LogSomethingSomething(27);

    m_toastStorage = winrt::Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(
        L"Toast", winrt::Windows::Storage::ApplicationDataCreateDisposition::Always);

    for (auto pair : m_toastStorage.Values())
    {
        Add(pair.Key().c_str(), pair.Value().as<winrt::hstring>().c_str());
    }
}

void ToastRegistrationManager::Add(std::wstring const& processName, std::wstring const& toastAppId)
{
    PushNotificationLongRunningTaskTelemetry::LogSomethingSomething(28);

    auto lock = m_lock.lock_exclusive();
    m_registrationMap[processName] = toastAppId;

    m_toastStorage.Values().Insert(processName, winrt::box_value(toastAppId));
}

void ToastRegistrationManager::Remove(std::wstring const& processName)
{
    PushNotificationLongRunningTaskTelemetry::LogSomethingSomething(29);

    auto lock = m_lock.lock_exclusive();
    m_registrationMap.erase(processName);

    m_toastStorage.Values().Remove(processName);
}

std::wstring ToastRegistrationManager::GetToastRegistration(std::wstring const& processName)
{
    PushNotificationLongRunningTaskTelemetry::LogSomethingSomething(30);

    auto lock = m_lock.lock_shared();
    return m_registrationMap[processName];
}
