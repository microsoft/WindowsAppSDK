#pragma once

#include "pch.h"

void ToastRegistrationManager::Add(std::wstring const& appId, std::wstring const& toastGuid)
{
    auto lock = m_lock.lock_exclusive();
    m_registrationMap[appId] = toastGuid;
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
