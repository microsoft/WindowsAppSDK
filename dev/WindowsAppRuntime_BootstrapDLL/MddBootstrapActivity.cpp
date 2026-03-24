// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "MddBootstrapActivity.h"

#include <FrameworkUdk/Containment.h>

// Bug 61543987: [1.8 servicing] Deployment exceptions masked as ERROR_UNHANDLED_EXCEPTION; SetLastFailure logging single chars
#define WINAPPSDK_CHANGEID_61543987 61543987, WinAppSDK_1_8_7

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
        if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_61543987>())
        {
            m_lastFailure.file = failure.pszFile;
        }
        else
        {
            m_lastFailure.file = *failure.pszFile;
        }
    }
    else
    {
        m_lastFailure.file.clear();
    }

    m_lastFailure.lineNumber = failure.uLineNumber;

    if (failure.pszMessage)
    {
        if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_61543987>())
        {
            m_lastFailure.message = failure.pszMessage;
        }
        else
        {
            m_lastFailure.message = *failure.pszMessage;
        }
    }
    else
    {
        m_lastFailure.message.clear();
    }

    if (failure.pszModule)
    {
        if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_61543987>())
        {
            m_lastFailure.module = failure.pszModule;
        }
        else
        {
            m_lastFailure.module = *failure.pszModule;
        }
    }
    else
    {
        m_lastFailure.module.clear();
    }
}

void WindowsAppRuntime::MddBootstrap::Activity::Context::DecrementInitializationCount()
{
    const uint32_t initializationCount{ m_initializationCount.load() };
    if (initializationCount == 0)
    {
        // Not initialized
        SetInitializationPackageFullName(nullptr);
    }
    else
    {
        // Initialized (at least once). Decrement our count
        --m_initializationCount;
    }
}

const WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags WindowsAppRuntime::MddBootstrap::Activity::Context::GetIntegrityFlags(HANDLE token)
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
