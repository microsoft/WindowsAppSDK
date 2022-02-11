// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "InstallActivityContext.h"

static InstallActivityContext g_installActivityContext;

InstallActivityContext& InstallActivityContext::Get()
{
    return g_installActivityContext;
}

void InstallActivityContext::Reset()
{
    m_installStage = InstallStage::None;
    m_currentResourceId.clear();
    m_currentResourceId.clear();
    m_deploymentErrorExtendedHresult = S_OK;
    m_deploymentErrorText.clear();
    m_deploymentErrorActivityId = GUID{};
}

InstallStage InstallActivityContext::GetInstallStage()
{
    return m_installStage;
}

std::wstring InstallActivityContext::GetCurrentResourceId()
{
    return m_currentResourceId;
}

HRESULT InstallActivityContext::GetDeploymentErrorExtendedHResult()
{
    return m_deploymentErrorExtendedHresult;
}

std::wstring InstallActivityContext::GetDeploymentErrorText()
{
    return m_deploymentErrorText;
}

GUID InstallActivityContext::GetDeploymentErrorActivityId()
{
    return m_deploymentErrorActivityId;
}

WindowsAppRuntimeInstaller_TraceLogger::Install InstallActivityContext::GetActivity()
{
    return m_activity;
}

WilFailure& InstallActivityContext::GetLastFailure()
{
    return lastFailure;
}

void InstallActivityContext::SetInstallStage(InstallStage installStage)
{
    m_installStage = installStage;
}

void InstallActivityContext::SetCurrentResourceId(std::wstring currentResourceId)
{
    m_currentResourceId = currentResourceId;
}

void InstallActivityContext::SetDeploymentErrorInfo(HRESULT deploymentErrorExtendedHresult, std::wstring deploymentErrorText, GUID deploymentErrorActivityId)
{
    m_deploymentErrorExtendedHresult = deploymentErrorExtendedHresult;
    m_deploymentErrorText = deploymentErrorText;
    SetDeploymentErrorActivityId(deploymentErrorActivityId);
}

void InstallActivityContext::SetDeploymentErrorActivityId(GUID deploymentErrorActivityId)
{
    m_deploymentErrorActivityId = deploymentErrorActivityId;
}

void InstallActivityContext::SetActivity(WindowsAppRuntimeInstaller_TraceLogger::Install activity)
{
    m_activity = activity;
}

void InstallActivityContext::SetLastFailure(const wil::FailureInfo& failure)
{
    lastFailure.type = failure.type;
    lastFailure.hr = failure.hr;

    if (failure.pszFile)
    {
        lastFailure.file = *(failure.pszFile);
    }

    lastFailure.lineNumer = failure.uLineNumber;

    if (failure.pszMessage)
    {
        lastFailure.message = *(failure.pszMessage);
    }
}
