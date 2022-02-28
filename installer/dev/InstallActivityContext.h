// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

namespace WindowsAppRuntimeInstaller::InstallActivityContent
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
    };

    struct WilFailure
    {
        wil::FailureType type;
        HRESULT hr;
        std::wstring file;
        unsigned int lineNumer;
        std::wstring message;
    };

    class InstallActivityContext
    {
        InstallStage m_installStage{ InstallStage::None };
        std::wstring m_currentResourceId;
        HRESULT m_deploymentErrorExtendedHresult{};
        std::wstring m_deploymentErrorText;
        GUID m_deploymentErrorActivityId{};
        WindowsAppRuntimeInstaller_TraceLogger::Install m_activity;
        WilFailure m_lastFailure{};

    public:
        static InstallActivityContext& Get();

        void Reset();

        const InstallStage& GetInstallStage() const
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

        WindowsAppRuntimeInstaller_TraceLogger::Install GetActivity() const
        {
            return m_activity;
        }

        const WilFailure& GetLastFailure() const
        {
            return m_lastFailure;
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
    };

    static InstallActivityContext g_installActivityContext;
}
