#pragma once

#include "tracelogging.h"

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
    std::wstring m_currentResourceId{};
    HRESULT m_deploymentErrorExtendedHresult{};
    std::wstring m_deploymentErrorText{};
    GUID m_deploymentErrorActivityId{};
    WindowsAppRuntimeInstaller_TraceLogger::Install m_activity{};
    WilFailure lastFailure{};

public:
    static InstallActivityContext& Get();

    void Reset();

    InstallStage GetInstallStage();

    std::wstring GetCurrentResourceId();

    HRESULT GetDeploymentErrorExtendedHResult();

    std::wstring GetDeploymentErrorText();

    GUID GetDeploymentErrorActivityId();

    WindowsAppRuntimeInstaller_TraceLogger::Install GetActivity();

    WilFailure& GetLastFailure();

    void SetInstallStage(const InstallStage installStage);

    void SetCurrentResourceId(const std::wstring currentResourceId);

    void SetDeploymentErrorInfo(const HRESULT deploymentErrorExtendedHresult, const std::wstring deploymentErrorText, const GUID deploymentErrorActivityId);

    void SetDeploymentErrorActivityId(const GUID deploymentErrorActivityId);

    void SetActivity(const WindowsAppRuntimeInstaller_TraceLogger::Install activity);

    void SetLastFailure(const wil::FailureInfo &failureInfo);
};
