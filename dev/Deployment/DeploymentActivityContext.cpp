// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "DeploymentActivityContext.h"

#include <FrameworkUdk/Containment.h>

// Bug 57688028: [1.8 servicing] Deployment exceptions masked as ERROR_UNHANDLED_EXCEPTION; SetLastFailure logging single chars
#define WINAPPSDK_CHANGEID_57688028 57688028, WinAppSDK_1_8_7

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
        m_lastFailure.file = WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_57688028>() ? failure.pszFile : std::wstring(1, *failure.pszFile);
    }
    else
    {
        m_lastFailure.file.clear();
    }

    m_lastFailure.lineNumber = failure.uLineNumber;

    if (failure.pszMessage)
    {
        m_lastFailure.message = WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_57688028>() ? failure.pszMessage : std::wstring(1, *failure.pszMessage);
    }
    else
    {
        m_lastFailure.message.clear();
    }

    if (failure.pszModule)
    {
        m_lastFailure.module = WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_57688028>() ? failure.pszModule : std::wstring(1, *failure.pszModule);
    }
    else
    {
        m_lastFailure.module.clear();
    }
}
