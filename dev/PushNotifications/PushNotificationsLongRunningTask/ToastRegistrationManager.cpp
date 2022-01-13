#pragma once
#include "pch.h"

void ToastRegistrationManager::Add(std::wstring const& processName, std::wstring const& appId)
{
    auto lock = m_lock.lock_exclusive();
    m_registrationMap[processName] = appId;
}

void ToastRegistrationManager::Remove(std::wstring const& appId)
{
    auto lock = m_lock.lock_exclusive();
    m_registrationMap.erase(appId);
}

std::wstring ToastRegistrationManager::GetToastRegistration(std::wstring const& processName)
{
    auto lock = m_lock.lock_exclusive();
    return m_registrationMap[processName];
}
