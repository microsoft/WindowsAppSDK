// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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
    const HRESULT& deploymentErrorHresult,
    const HRESULT& deploymentErrorExtendedHresult,
    const std::wstring& deploymentErrorText,
    const GUID& deploymentErrorActivityId)
{
    m_deploymentErrorHresult = deploymentErrorHresult;
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

    m_lastFailure.lineNumber = failure.uLineNumber;

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
        auto installerActivityId{ winrt::to_hstring(*m_activity.Id()) };
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), messageFormat, installerActivityId.data(), cmdlineArgs));
        PCWSTR messageStrings[1]{ message };
        return ReportEventW(m_hEventLog, EVENTLOG_INFORMATION_TYPE, 0, eventId, nullptr, ARRAYSIZE(messageStrings), 0, messageStrings, nullptr);
    }
    return false;
}

BOOL WindowsAppRuntimeInstaller::InstallActivity::Context::LogInstallerFailureEvent(HRESULT hresult)
{
    if (m_hEventLog)
    {
        switch (m_installStage)
        {
            case InstallStage::None:
            {
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_ERROR_TYPE, hresult, L"Bad arguments"));
                break;
            }
            case InstallStage::CreatePackageURI:
            {
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_ERROR_TYPE, hresult, L"Creating Package URI for Package: %s", m_currentResourceId.c_str()));
                break;
            }
            case InstallStage::GetPackageProperties:
            {
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_ERROR_TYPE, hresult, L"Getting Package Properties for Package: %s", m_currentResourceId.c_str()));
                break;
            }
            case InstallStage::AddPackage:
            {
                WCHAR customMessage[1024]{};
                auto deploymentErrorActivityId{ winrt::to_hstring(m_deploymentErrorActivityId) };
                auto customMessageFormat{ L"Installing Package %s with DeploymentExtendedError: 0x%08X, DeploymentExtendedText:%s, DeploymentActivityId: %s" };
                FAIL_FAST_IF_FAILED(StringCchPrintfW(customMessage,
                                                     ARRAYSIZE(customMessage),
                                                     customMessageFormat,
                                                     m_currentResourceId.c_str(),
                                                     m_deploymentErrorExtendedHresult,
                                                     m_deploymentErrorText.c_str(),
                                                     deploymentErrorActivityId.data()));
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_ERROR_TYPE, hresult, customMessage));
                break;
            }
            case InstallStage::InstallLicense:
            {
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_ERROR_TYPE, hresult, L"Installing License: %s", m_currentResourceId.c_str()));
                break;
            }
            case InstallStage::RestartPushNotificationsLRP:
            {
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_WARNING_TYPE, hresult, L"Restarting Push Notifications Long Running Process"));
                break;
            }
            case InstallStage::ProvisionPackage:
            {
                WCHAR customProvisionMessage[1024]{};
                auto provisionActivityId{ winrt::to_hstring(*m_activity.Id()) };
                auto customProvisionMessageFormat{ L"Provisioning Package %s (Activity Id:%s)" };
                FAIL_FAST_IF_FAILED(StringCchPrintfW(customProvisionMessage, ARRAYSIZE(customProvisionMessage), customProvisionMessageFormat, m_currentResourceId.c_str(), provisionActivityId.data()));
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_WARNING_TYPE, hresult, customProvisionMessage));
                break;
            }
            case InstallStage::StagePackage:
            {
                WCHAR customMessage[1024]{};
                auto deploymentErrorActivityId{ winrt::to_hstring(m_deploymentErrorActivityId) };
                auto customMessageFormat{ L"Staging Package %s with DeploymentExtendedError: 0x%08X, DeploymentExtendedText:%s, DeploymentActivityId: %s" };
                FAIL_FAST_IF_FAILED(StringCchPrintfW(customMessage,
                                                     ARRAYSIZE(customMessage),
                                                     customMessageFormat,
                                                     m_currentResourceId.c_str(),
                                                     m_deploymentErrorExtendedHresult,
                                                     m_deploymentErrorText.c_str(),
                                                     deploymentErrorActivityId.data()));
                THROW_IF_WIN32_BOOL_FALSE(LogInstallerFailureEventWithResourceId(EVENTLOG_ERROR_TYPE, hresult, customMessage));
                break;
            }
            default:
                break;
        }
    }
    return false;
}

// This is Log with eventLog type and custom message provided by the caller and that will include resourceId.
BOOL WindowsAppRuntimeInstaller::InstallActivity::Context::LogInstallerFailureEventWithResourceId(const WORD eventLogType, const HRESULT& hresult, PCWSTR failedComponentMessageFormat, const PCWSTR resourceId)
{
    DWORD eventId{ static_cast<DWORD>(hresult) };
    if (m_hEventLog)
    {
        WCHAR failedComponentMessage[512]{};
        if (resourceId)
        {
            FAIL_FAST_IF_FAILED(StringCchPrintfW(failedComponentMessage, ARRAYSIZE(failedComponentMessage), failedComponentMessageFormat, resourceId));
        }

        WCHAR message[1024]{};
        PCWSTR messageFormat{ L"Error 0x%08X: Windows App Runtime Installer (Activity ID: %s) failed in %s" };
        auto installerActivityId{ winrt::to_hstring(*m_activity.Id()) };
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message, ARRAYSIZE(message), messageFormat, hresult, installerActivityId.data(), (resourceId ? failedComponentMessage : failedComponentMessageFormat)));

        PCWSTR messageStrings[1]{ message };
        return ReportEventW(m_hEventLog, eventLogType, 0, eventId, nullptr, ARRAYSIZE(messageStrings), 0, messageStrings, nullptr);
    }
    return false;
}
