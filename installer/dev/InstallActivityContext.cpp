// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "InstallActivityContext.h"

WindowsAppRuntimeInstaller::InstallActivity::Context& WindowsAppRuntimeInstaller::InstallActivity::Context::Get()
{
    return g_installActivityContext;
}

void WindowsAppRuntimeInstaller::InstallActivity::Context::Reset()
{
    m_installStage = InstallStage::None;
    m_currentResourceId.clear();
    m_deploymentErrorExtendedHresult = S_OK;
    m_deploymentErrorText.clear();
    m_deploymentErrorActivityId = GUID{};
}

void WindowsAppRuntimeInstaller::InstallActivity::Context::SetDeploymentErrorInfo(
    const HRESULT& deploymentErrorExtendedHresult,
    const std::wstring& deploymentErrorText,
    const GUID& deploymentErrorActivityId)
{
    m_deploymentErrorExtendedHresult = deploymentErrorExtendedHresult;
    m_deploymentErrorText = deploymentErrorText;
    SetDeploymentErrorActivityId(deploymentErrorActivityId);
}

void WindowsAppRuntimeInstaller::InstallActivity::Context::SetLastFailure(const wil::FailureInfo& failure)
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

    if (failure.pszCode)
    {
        m_lastFailure.code = *failure.pszCode;
    }
    else
    {
        m_lastFailure.code.clear();
    }
}
