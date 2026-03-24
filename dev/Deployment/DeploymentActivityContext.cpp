// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "DeploymentActivityContext.h"

#include <FrameworkUdk/Containment.h>

// Bug 61543987: [1.8 servicing] Deployment exceptions masked as ERROR_UNHANDLED_EXCEPTION; SetLastFailure logging single chars
#define WINAPPSDK_CHANGEID_61543987 61543987, WinAppSDK_1_8_7

WindowsAppRuntime::Deployment::Activity::Context& WindowsAppRuntime::Deployment::Activity::Context::Get()
{
    return g_DeploymentActivityContext;
}

void WindowsAppRuntime::Deployment::Activity::Context::Reset()
{
    m_installStage = DeploymentStage::None;
    m_currentResourceId.clear();
    m_deploymentErrorExtendedHresult = S_OK;
    m_deploymentErrorText.clear();
    m_deploymentErrorActivityId = GUID{};
    m_useExistingPackageIfHigherVersion = false;
}

void WindowsAppRuntime::Deployment::Activity::Context::SetDeploymentErrorInfo(
    const HRESULT& deploymentErrorExtendedHresult,
    const std::wstring& deploymentErrorText,
    const GUID& deploymentErrorActivityId)
{
    m_deploymentErrorExtendedHresult = deploymentErrorExtendedHresult;
    m_deploymentErrorText = deploymentErrorText;
    SetDeploymentErrorActivityId(deploymentErrorActivityId);
}

void WindowsAppRuntime::Deployment::Activity::Context::SetLastFailure(const wil::FailureInfo& failure)
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
            m_lastFailure.file = std::wstring(1, *failure.pszFile);
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
            m_lastFailure.message = std::wstring(1, *failure.pszMessage);
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
            m_lastFailure.module = std::wstring(1, *failure.pszModule);
        }
    }
    else
    {
        m_lastFailure.module.clear();
    }
}
