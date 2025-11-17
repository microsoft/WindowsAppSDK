// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "DeploymentTracelogging.h"

namespace WindowsAppRuntime::Deployment::Activity
{
    enum class DeploymentStage
    {
        None = 0x0,
        GetLicensePath = 0x1,
        InstallLicense = 0x2,
        GetPackagePath = 0x3,
        AddPackage = 0x4,
        RestartPushNotificationsLRP = 0x5,
    };

    struct WilFailure
    {
        wil::FailureType type { wil::FailureType::Exception };
        HRESULT hr { S_OK };
        std::string file;
        unsigned int lineNumber{ 0 };
        std::wstring message;
        std::string module;
    };

    class Context
    {
        DeploymentStage m_installStage{};
        std::wstring m_currentResourceId;
        HRESULT m_deploymentErrorExtendedHresult{};
        std::wstring m_deploymentErrorText;
        GUID m_deploymentErrorActivityId{};
        WindowsAppRuntimeDeployment_TraceLogger::Initialize m_activity;
        WilFailure m_lastFailure;
        bool m_isFullTrustPackage{};
        bool m_useExistingPackageIfHigherVersion{};

    public:
        static WindowsAppRuntime::Deployment::Activity::Context& Get();

        void Reset();

        const DeploymentStage& GetInstallStage() const
        {
            return m_installStage;
        }

        const std::wstring& GetCurrentResourceId() const
        {
            return m_currentResourceId;
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

        WindowsAppRuntimeDeployment_TraceLogger::Initialize& GetActivity()
        {
            return m_activity;
        }

        const WilFailure& GetLastFailure() const
        {
            return m_lastFailure;
        }

        const bool GetIsFullTrustPackage() const
        {
            return m_isFullTrustPackage;
        }

        const bool GetUseExistingPackageIfHigherVersion() const
        {
            return m_useExistingPackageIfHigherVersion;
        }

        void SetInstallStage(const DeploymentStage& installStage)
        {
            m_installStage = installStage;
        }

        void SetCurrentResourceId(const std::wstring& currentResourceId)
        {
            m_currentResourceId = currentResourceId;
        }

        void SetDeploymentErrorInfo(
            const HRESULT& deploymentErrorExtendedHresult,
            const std::wstring& deploymentErrorText,
            const GUID& deploymentErrorActivityId);

        void SetDeploymentErrorActivityId(const GUID& deploymentErrorActivityId)
        {
            m_deploymentErrorActivityId = deploymentErrorActivityId;
        }

        void SetActivity(const WindowsAppRuntimeDeployment_TraceLogger::Initialize& activity)
        {
            m_activity = activity;
        }

        void SetLastFailure(const wil::FailureInfo& failure);

        void SetIsFullTrustPackage()
        {
            m_isFullTrustPackage = true;
        }

        void SetUseExistingPackageIfHigherVersion()
        {
            m_useExistingPackageIfHigherVersion = true;
        }
    };

    static WindowsAppRuntime::Deployment::Activity::Context g_DeploymentActivityContext;
}
