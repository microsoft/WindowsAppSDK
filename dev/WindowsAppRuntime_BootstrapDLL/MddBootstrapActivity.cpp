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
