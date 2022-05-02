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
}

// This is Informational Log
BOOL WindowsAppRuntimeInstaller::InstallActivity::Context::LogInstallerCommandLineArgs(PCWSTR cmdlineArgs)
{
    DWORD eventId{ 0x4000 };
    if (m_hEventLog)
    {
        WCHAR message[1024]{};
        PCWSTR messageFormat{ L"Windows App Runtime Installer (ActivityId: %s) is called with Command Line Args: %s" };
        wchar_t szInstallerActivityId[64] = { 0 };
        std::ignore = StringFromGUID2(*m_activity.Id(), szInstallerActivityId, 64);
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), messageFormat, szInstallerActivityId, cmdlineArgs));
        PCWSTR messageStrings[1]{ message };
        return ReportEventW(m_hEventLog, EVENTLOG_INFORMATION_TYPE, 0, eventId, nullptr, ARRAYSIZE(messageStrings), 0, messageStrings, nullptr);
    }
    return false;
}

// This is Error Log
BOOL WindowsAppRuntimeInstaller::InstallActivity::Context::LogInstallerFailureEvent(const HRESULT& hresult)
{
    DWORD eventId{ static_cast<DWORD>(hresult) };
    if (m_hEventLog)
    {
        WCHAR message[1024]{};
        PCWSTR messageFormat{ L"Error 0x%08X: Windows App Runtime Installer (Activity ID: %s) failed" };
        wchar_t szGUID[64] = { 0 };
        std::ignore = StringFromGUID2(*m_activity.Id(), szGUID, 64);
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), messageFormat, hresult, szGUID));
        PCWSTR messageStrings[1]{ message };
        return ReportEventW(m_hEventLog, EVENTLOG_ERROR_TYPE, 0, eventId, nullptr, ARRAYSIZE(messageStrings), 0, messageStrings, nullptr);
    }
    return false;
}

// This is Error Log
BOOL WindowsAppRuntimeInstaller::InstallActivity::Context::LogInstallerFailureEvent(
    HRESULT hresult,
    UINT32 failureType,
    PCSTR failureFile,
    UINT32 failureLineNumber,
    PCWSTR failureMessage,
    UINT32 failedInstallStage,
    PCWSTR currentResourceId,
    HRESULT deploymentErrorExtendedHResult,
    PCWSTR deploymentErrorText,
    GUID deploymentErrorActivityId)
{
    DWORD eventId{ static_cast<DWORD>(hresult) };
    if (m_hEventLog)
    {
        WCHAR message[1024]{};
        std::wstring szCustomMessage{};

        switch (failedInstallStage)
        {
            case static_cast<UINT32>(InstallStage::CreatePackageURI):
            {
                szCustomMessage = L"Creating Package URI for Package: %s";
                FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), szCustomMessage.c_str(), currentResourceId));
                break;
            }
            case static_cast<UINT32>(InstallStage::GetPackageProperties):
            {
                szCustomMessage = L"Getting Package Properties for Package: %s";
                FAIL_FAST_IF_FAILED(StringCchPrintfW(message,
                    ARRAYSIZE(message),
                    szCustomMessage.c_str(),
                    currentResourceId));
                break;
            }
            case static_cast<UINT32>(InstallStage::AddPackage):
            case static_cast<UINT32>(InstallStage::RegisterPackage):
            {
                wchar_t szDeploymentActivityId[64] = { 0 };
                std::ignore = StringFromGUID2(*m_activity.Id(), szDeploymentActivityId, 64);
                szCustomMessage = L"Deploying Package %s with DeploymentExtendedError: 0x%08X, DeploymentExtendedText:%s, DeploymentActivityId: %s";
                FAIL_FAST_IF_FAILED(StringCchPrintfW(message,
                                                     ARRAYSIZE(message),
                                                     szCustomMessage.c_str(),
                                                     currentResourceId,
                                                     deploymentErrorExtendedHResult,
                                                     deploymentErrorText,
                                                     szDeploymentActivityId));
                break;
            }
            case static_cast<UINT32>(InstallStage::InstallLicense):
            {
                szCustomMessage = L"Installing License: %s";
                FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), szCustomMessage.c_str(), currentResourceId));
                break;
            }
            case static_cast<UINT32>(InstallStage::RestartPushNotificationsLRP):
            {
                szCustomMessage = L"Restarting Push Notifications' Long Running Process";
                break;
            }
            default:
                break;
        }
        PCWSTR messageFormat{ L"Error 0x%08X: Windows App Runtime Installer (Activity ID: %s) failed in %s" };
        wchar_t szInstallerActivityId[64] = { 0 };
        std::ignore = StringFromGUID2(*m_activity.Id(), szInstallerActivityId, 64);
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), messageFormat, hresult, szInstallerActivityId, message));
        PCWSTR messageStrings[1]{ message };
        return ReportEventW(m_hEventLog, EVENTLOG_ERROR_TYPE, 0, eventId, nullptr, ARRAYSIZE(messageStrings), 0, messageStrings, nullptr);
    }
    return false;
}

// This is Warning Log
BOOL WindowsAppRuntimeInstaller::InstallActivity::Context::LogInstallerRestartPushNotificationsLRPFailureEvent(const HRESULT& hresult)
{
    DWORD eventId{ static_cast<DWORD>(hresult) };
    if (m_hEventLog)
    {
        WCHAR message[1024]{};
        PCWSTR messageFormat{ L"Error 0x%08X: Windows App Runtime Installer (Activity ID: %s) failed in restarting Push Notificiations Long Running Process" };
        wchar_t szInstallerActivityId[64] = { 0 };
        std::ignore = StringFromGUID2(*m_activity.Id(), szInstallerActivityId, 64);
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), messageFormat, hresult, szInstallerActivityId));
        PCWSTR messageStrings[1]{ message };
        return ReportEventW(m_hEventLog, EVENTLOG_WARNING_TYPE, 0, eventId, nullptr, ARRAYSIZE(messageStrings), 0, messageStrings, nullptr);
    }
    return false;
}

// This is Warning Log
BOOL WindowsAppRuntimeInstaller::InstallActivity::Context::LogInstallerProvisioningFailureEvent(const HRESULT& hresult, PCWSTR currentResourceId)
{
    DWORD eventId{ static_cast<DWORD>(hresult) };
    if (m_hEventLog)
    {
        WCHAR message[1024]{};
        PCWSTR messageFormat{ L"Error 0x%08X: Windows App Runtime Installer (Activity ID: %s) failed in Provisioning Package (Activity Id:%s) for Package: %s" };
        wchar_t szInstallerActivityId[64] = { 0 };
        std::ignore = StringFromGUID2(*m_activity.Id(), szInstallerActivityId, 64);
        wchar_t szDeploymentActivityId[64] = { 0 };
        std::ignore = StringFromGUID2(m_deploymentErrorActivityId, szDeploymentActivityId, 64);
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), messageFormat, hresult, szInstallerActivityId, szDeploymentActivityId, currentResourceId));
        PCWSTR messageStrings[1]{ message };
        return ReportEventW(m_hEventLog, EVENTLOG_WARNING_TYPE, 0, eventId, nullptr, ARRAYSIZE(messageStrings), 0, messageStrings, nullptr);
    }
    return false;
}
