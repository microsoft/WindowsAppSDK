// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "MddBootstrapActivity.h"

WindowsAppRuntime::MddBootstrap::Activity::Context& WindowsAppRuntime::MddBootstrap::Activity::Context::Get()
{
    return g_bootstrapActivityContext;
}

void WindowsAppRuntime::MddBootstrap::Activity::Context::SetLastFailure(const wil::FailureInfo& failure)
{
    m_lastFailure.type = failure.type;
    m_lastFailure.hr = failure.hr;

    if (failure.pszFile)
    {
        m_lastFailure.file = *failure.pszFile;
    }
    else
    {
        m_lastFailure.file.clear();
    }

    m_lastFailure.lineNumer = failure.uLineNumber;

    if (failure.pszMessage)
    {
        m_lastFailure.message = *failure.pszMessage;
    }
    else
    {
        m_lastFailure.message.clear();
    }

    if (failure.pszModule)
    {
        m_lastFailure.module = *failure.pszModule;
    }
    else
    {
        m_lastFailure.module.clear();
    }
}

uint32_t WindowsAppRuntime::MddBootstrap::Activity::Context::DecrementInitializationCount()
{
    const auto initializationCount{ m_initializationCount.load() };

    if (initializationCount > 1)
    {
        // Multiply initialized. Just decrement our count
        return --m_initializationCount;
    }
    else if (initializationCount == 0)
    {
        // Not initialized.
        SetInitializationPackageFullName(PWSTR{});
    }
    return m_initializationCount;
}

const WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags& WindowsAppRuntime::MddBootstrap::Activity::Context::GetIntegrityFlags(HANDLE token)
{
    WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags flags{};
    const auto integrityLevel{ Security::IntegrityLevel::GetIntegrityLevel(token) };
    if (integrityLevel >= SECURITY_MANDATORY_HIGH_RID)
    {
        flags |= WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags::IsHighIL;
    }
    else if (integrityLevel == SECURITY_MANDATORY_MEDIUM_RID)
    {
        flags |= WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags::IsMediumIL;
    }
    else if (integrityLevel == SECURITY_MANDATORY_LOW_RID)
    {
        flags |= WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags::IsLowIL;
        bool isAppContainer{};
        if (SUCCEEDED(LOG_IF_FAILED(wil::get_token_is_app_container_nothrow(token, isAppContainer))))
        {
            flags |= WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags::IsAppContainer;
        }
    }
    return flags;
}
