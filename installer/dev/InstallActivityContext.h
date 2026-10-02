// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

namespace WindowsAppRuntimeInstaller::InstallActivity
{
    enum class InstallStage
    {
        None = 0x0,
        InstallLicense = 0x1,
        GetPackageProperties = 0x2,
        CreatePackageURI = 0x3,
        AddPackage = 0x4,
        RegisterPackage = 0x5,
        ProvisionPackage = 0x6,
        RestartPushNotificationsLRP = 0x7,
        StagePackage = 0x8,
    };

    struct WilFailure
    {
        wil::FailureType type;
        HRESULT hr;
        std::string file;
        unsigned int lineNumber;
        std::wstring message;
    };

    class Context
    {
        InstallStage m_installStage{};
        std::wstring m_currentResourceId;
        HRESULT m_deploymentErrorHresult{};
        HRESULT m_deploymentErrorExtendedHresult{};
        std::wstring m_deploymentErrorText;
        GUID m_deploymentErrorActivityId{};
        WindowsAppRuntimeInstaller_TraceLogger::Install m_activity;
        WilFailure m_lastFailure{};
        HANDLE m_hEventLog{};
        bool m_isLocalSystemUser{ Security::User::IsLocalSystem() };
        winrt::hstring m_existingPackageIfHigherVersion;

    public:
        static WindowsAppRuntimeInstaller::InstallActivity::Context& Get();

        void Reset();

        const InstallStage& GetInstallStage() const
        {
            return m_installStage;
        }

        const std::wstring& GetCurrentResourceId() const
        {
            return m_currentResourceId;
        }

        const HRESULT& GetDeploymentErrorHresult() const
        {
            return m_deploymentErrorHresult;
        }

        const HRESULT& GetDeploymentErrorExtendedHResult() const
        {
            return m_deploymentErrorExtendedHresult;
        }

        const std::wstring& GetDeploymentErrorText() const
        {
            return m_deploymentErrorText;
        }

        const GUID& GetDeploymentErrorActivityId() const
        {
            return m_deploymentErrorActivityId;
        }

        WindowsAppRuntimeInstaller_TraceLogger::Install GetActivity() const
        {
            return m_activity;
        }

        const WilFailure& GetLastFailure() const
        {
            return m_lastFailure;
        }

        const bool IsLocalSystemUser() const
        {
            return m_isLocalSystemUser;
        }

        const winrt::hstring GetExistingPackageIfHigherVersion() const
        {
            return m_existingPackageIfHigherVersion;
        }

        void SetInstallStage(const InstallStage& installStage)
        {
            m_installStage = installStage;
        }

        void SetCurrentResourceId(const std::wstring& currentResourceId)
        {
            m_currentResourceId = currentResourceId;
        }

        void SetDeploymentErrorInfo(
            const HRESULT& deploymentErrorHresult,
            const HRESULT& deploymentErrorExtendedHresult,
            const std::wstring& deploymentErrorText,
            const GUID& deploymentErrorActivityId);

        void SetDeploymentErrorActivityId(const GUID& deploymentErrorActivityId)
        {
            m_deploymentErrorActivityId = deploymentErrorActivityId;
        }

        void SetActivity(const WindowsAppRuntimeInstaller_TraceLogger::Install& activity)
        {
            m_activity = activity;
        }

        void SetLastFailure(const wil::FailureInfo& failureInfo);

        void SetExistingPackageIfHigherVersion(const winrt::hstring& existingPackageIfHigherVersion)
        {
            m_existingPackageIfHigherVersion = existingPackageIfHigherVersion;
        }

        const HANDLE& RegisterInstallerEventSourceW()
        {
            m_hEventLog = RegisterEventSourceW(nullptr, L"WindowsAppRuntime Installer");
            return m_hEventLog;
        }

        const BOOL DeregisterInstallerEventSourceW()
        {
            return DeregisterEventSource(m_hEventLog);
        }

        BOOL LogInstallerCommandLineArgs(PCWSTR cmdlineArgs);

        BOOL LogInstallerSuccess()
        {
            return ReportEventW(m_hEventLog, EVENTLOG_SUCCESS, 0, 0, nullptr, 0, 0, nullptr, nullptr);
        }

        BOOL LogInstallerFailureEvent(HRESULT hresult);

        BOOL LogInstallerFailureEventWithResourceId(const WORD eventLogType, const HRESULT& hresult, PCWSTR failedComponentMessageFormat, const PCWSTR resourceId = nullptr);

    };

    static WindowsAppRuntimeInstaller::InstallActivity::Context g_installActivityContext;
}
