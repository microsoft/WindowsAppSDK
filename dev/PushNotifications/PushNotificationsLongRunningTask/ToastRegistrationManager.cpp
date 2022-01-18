#pragma once
#include "pch.h"

void ToastRegistrationManager::Add(std::wstring const& processName, std::wstring const& toastAppId)
{
    auto lock = m_lock.lock_exclusive();
    m_registrationMap[processName] = toastAppId;

    m_toastStorage.Values().Insert(processName, winrt::box_value(toastAppId));
}

void ToastRegistrationManager::Remove(std::wstring const& processName)
{
    auto lock = m_lock.lock_exclusive();
    m_registrationMap.erase(processName);

    m_toastStorage.Values().Remove(processName);
}

std::wstring ToastRegistrationManager::GetToastRegistration(std::wstring const& processName)
{
    auto lock = m_lock.lock_shared();
    return m_registrationMap[processName];
}
