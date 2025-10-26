// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <filesystem>
#include <DeploymentManager.h>
#include <DeploymentResult.h>
#include <DeploymentActivityContext.h>
#include <TerminalVelocityFeatures-DeploymentAPI.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager.g.cpp>
#include <PushNotificationsLongRunningPlatform-Startup.h>
#include "WindowsAppRuntime-License.h"
#include "LicenseInstallerProxy.h"
#include "PackageDefinitions.h"
#include "PackageUtilities.h"
#include "Licensing.h"
#include "PackageDeployment.h"
#include "PackageRegistrar.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    HRESULT Initialize_Log(
        HRESULT hrInitialize,
        const AppModel::Identity::PackageIdentity& packageIdentity,
        const std::wstring& release) noexcept;

    HRESULT Initialize_OnError_ShowUI(
        const AppModel::Identity::PackageIdentity& packageIdentity,
        const std::wstring& release);
}

inline void Initialize_StopSuccessActivity(
    ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
    const winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus& deploymentStatus)
{
    initializeActivityContext.GetActivity().StopWithResult(
        S_OK,
        static_cast <UINT32>(0),
        static_cast<PCSTR>(nullptr),
        static_cast <unsigned int>(0),
        static_cast<PCWSTR>(nullptr),
        static_cast<PCSTR>(nullptr),
        static_cast <UINT32>(deploymentStatus),
        static_cast<UINT32>(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::None),
        static_cast<PCWSTR>(nullptr),
        S_OK,
        static_cast<PCWSTR>(nullptr),
        GUID{},
        ::WindowsAppRuntime::Deployment::Activity::Context::Get().GetUseExistingPackageIfHigherVersion());
}

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    static bool s_isInitialized{ false };
    static wil::srwlock m_isInitializedLock;

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::GetStatus()
    {
        FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), !AppModel::Identity::IsPackagedProcess());
        return GetStatus(::WindowsAppRuntime::Deployment::Package::GetCurrentFrameworkPackageFullName());
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize()
    {
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions options{};
        return Initialize(options);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize(
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions const& deploymentInitializeOptions)
    {
        return Initialize(::WindowsAppRuntime::Deployment::Package::GetCurrentFrameworkPackageFullName(), deploymentInitializeOptions);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Repair()
    {
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions options{};
        return Initialize(::WindowsAppRuntime::Deployment::Package::GetCurrentFrameworkPackageFullName(), options, true);
    }

    std::wstring ExtractFormattedVersionTag(const std::wstring& versionTag)
    {
        std::wstring result{};
        if (versionTag.size() > 1)
        {
            result = std::wstring(L"-") + versionTag[1];
        }
        unsigned int numberBeforeUnderscore{};
        if (swscanf_s(versionTag.c_str(), L"%*[^0-9]%u", &numberBeforeUnderscore) == 1)
        {
            result += std::to_wstring(numberBeforeUnderscore);
        }
        return result;
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::GetStatus(hstring const& packageFullName)
    {
        // Get PackageInfo for WinAppSDK framework package
        std::wstring frameworkPackageFullName{ packageFullName };
        auto frameworkPackageInfo{ ::WindowsAppRuntime::Deployment::Package::GetPackageInfoForPackage(frameworkPackageFullName) };

        // Should only be called with a framework name that exists.
        FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), frameworkPackageInfo.Count() != 1);

        // Only the Microsoft Publisher Id is supported.
        auto expectedPublisherId{ frameworkPackageInfo.Package(0).packageId.publisherId };
        FAIL_FAST_HR_IF(E_INVALIDARG, CompareStringOrdinal(expectedPublisherId, -1, WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID, -1, TRUE) != CSTR_EQUAL);

        // The framework and package naming scheme is specified here:
        //     https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackages.md#3-package-naming
        std::wstring frameworkName{ frameworkPackageInfo.Package(0).packageId.name };
        const int c_namePrefixLength{ ARRAYSIZE(WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX) - 1 };

        // We assume that since this is a framework there is no subtype name, meaning the remainder
        // of the name is the Version Identifier, which contains .Major.Minor-VersionTag
        auto packageNameVersionIdentifier{ frameworkName.substr(c_namePrefixLength) };

        // Version tag is the -Foo at the end, typically the channel.
        std::wstring packageNameVersionTag{};
        auto versionTagPos{ packageNameVersionIdentifier.find('-') };
        if (versionTagPos != std::string::npos)
        {
            packageNameVersionTag = packageNameVersionIdentifier.substr(versionTagPos);
        }

        // Loop through all of the target packages (i.e. main, signleton packages) and capture whether they are all installed or not
        // (i.e. if any of the target packages is not installed, GetStatus should return PackageInstallRequired).
        HRESULT verifyResult{};

        for (const auto &package : c_targetPackages)
        {
            // Build package family name based on the framework naming scheme.
            std::wstring packageFamilyName{};
            // The main and singleton packages contain a shortened version tag for the package family name.
            std::wstring formattedVersionTag{};

            // PackageFamilyName = Prefix + Subtypename + VersionTag + Suffix
            // On WindowsAppSDK 1.1+, Main and Singleton packages are sharing same Package Name Prefix.
            if (package.versionType == PackageVersionType::Versioned)
            {
                // To understand the package naming of main and singleton packages, see https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackages.md#3-package-naming
                if (!packageNameVersionTag.empty())
                {
                    formattedVersionTag = packageNameVersionIdentifier.substr(0, versionTagPos) + ExtractFormattedVersionTag(packageNameVersionTag);
                }
                else
                {
                    formattedVersionTag = packageNameVersionIdentifier.substr(0, versionTagPos); // "1.8"
                }
            }
            else if (package.versionType == PackageVersionType::Unversioned)
            {
                if (!packageNameVersionTag.empty())
                {
                    formattedVersionTag = ExtractFormattedVersionTag(packageNameVersionTag);
                }
                else
                {
                    formattedVersionTag = L"";
                }
            }
            else
            {
                // Other version types not supported.
                THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_UNSUPPORTED_TYPE), "%d", static_cast<int>(package.versionType));
            }

            packageFamilyName = std::format(WINDOWSAPPRUNTIME_PACKAGE_NAME_MAINPREFIX WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DELIMETER L"{}{}" WINDOWSAPPRUNTIME_PACKAGE_NAME_SUFFIX, package.identifier, formattedVersionTag);

            // Get target version based on the framework.
            auto targetPackageVersion{ frameworkPackageInfo.Package(0).packageId.version };

            verifyResult = ::WindowsAppRuntime::Deployment::Package::VerifyPackage(packageFamilyName, targetPackageVersion, package.identifier);
            if (FAILED(verifyResult))
            {
                break;
            }
        }

        DeploymentStatus status{};
        if (SUCCEEDED(verifyResult))
        {
            status = DeploymentStatus::Ok;
        }
        else
        {
            status = DeploymentStatus::PackageInstallRequired;
        }

        return winrt::make<implementation::DeploymentResult>(status, verifyResult);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize(
        hstring const& packageFullName)
    {
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions deploymentInitializeOptions{};
        return DeploymentManager::Initialize(packageFullName, deploymentInitializeOptions);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize(
        hstring const& packageFullName,
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions const& deploymentInitializeOptions,
        bool isRepair)
    {
        auto lock{ m_isInitializedLock.lock_exclusive() };

        if (s_isInitialized)
        {
            throw winrt::hresult_error(HRESULT_FROM_WIN32(ERROR_INVALID_STATE),
                                       L"DeploymentManager is already initialized (can only be initialized once). See https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applicationmodel.windowsappruntime.deploymentmanager.initialize?view=windows-app-sdk-1.7#microsoft-windows-applicationmodel-windowsappruntime-deploymentmanager-initialize");
        }

        auto& initializeActivityContext{ ::WindowsAppRuntime::Deployment::Activity::Context::Get() };
        const bool isPackagedProcess{ AppModel::Identity::IsPackagedProcess() };
        const int integrityLevel = Security::IntegrityLevel::GetIntegrityLevel();
        if (isPackagedProcess && integrityLevel >= SECURITY_MANDATORY_MEDIUM_RID)
        {
              // Marking the package as full trust because the call originates from a MediumIL package.
            // For a packaged MediumIL app (with a non-Microsoft publisher) to deploy main and singleton packages, a breakaway helper process is required.
            initializeActivityContext.SetIsFullTrustPackage();
        }

        initializeActivityContext.GetActivity().Start(deploymentInitializeOptions.ForceDeployment(), Security::IntegrityLevel::IsElevated(),
                                                      isPackagedProcess, initializeActivityContext.GetIsFullTrustPackage(), integrityLevel, isRepair);

        // DeploymentManager API requires a packaged process?
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult deploymentResult{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Unknown, S_OK };
        if (!isPackagedProcess)
        {
            // The process lacks package identity but that's OK. Do nothing
            return winrt::make<implementation::DeploymentResult>(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Ok, S_OK);
        }

        try
        {
            deploymentResult = _Initialize(initializeActivityContext, packageFullName, deploymentInitializeOptions, isRepair);
        }
        catch (winrt::hresult_error const& e)
        {
            const HRESULT hr{ e.code() };

            auto packageIdentity{ AppModel::Identity::PackageIdentity::FromPackageFullName(packageFullName.c_str()) };
            PCWSTR c_packageNamePrefix{ L"microsoft.windowsappruntime." };
            const size_t c_packageNamePrefixLength{ ARRAYSIZE(L"microsoft.windowsappruntime.") - 1 };
            std::wstring release;
            if (CompareStringOrdinal(packageIdentity.Name(), -1, c_packageNamePrefix, -1, TRUE) == CSTR_EQUAL)
            {
                release =  packageIdentity.Name() + c_packageNamePrefixLength;
            }
            else
            {
                release = std::format(L"??? ({})", packageFullName);
            }
            std::ignore = LOG_IF_FAILED(Initialize_Log(hr, packageIdentity, release));

            // NOTE: IsDebuggerPresent()=TRUE if running under a debugger context.
            //       IsDebuggerPresent()=FALSE if not running under a debugger context, even if AEDebug is set.
            if (IsDebuggerPresent())
            {
                DebugBreak();
            }

            if (deploymentInitializeOptions.OnErrorShowUI() ||
                ::Microsoft::Configuration::IsOptionEnabled(L"MICROSOFT_WINDOWSAPPRUNTIME_DEPLOYMENT_INITIALIZE_ONERRORSHOWUI"))
            {
                std::ignore = LOG_IF_FAILED(Initialize_OnError_ShowUI(packageIdentity, release));
            }

            THROW_HR_MSG(hr, "PackageFullName=%ls Options: ForceDeployment=%c OnErrorShowUI=%c isRepair:%c",
                         packageFullName.c_str(), deploymentInitializeOptions.ForceDeployment() ? 'Y' : 'N',
                         deploymentInitializeOptions.OnErrorShowUI() ? 'Y' : 'N', isRepair ? 'Y' : 'N' );
        }

        // Success!
        s_isInitialized = true;
        return deploymentResult;
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::_Initialize(
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        hstring const& packageFullName,
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions const& deploymentInitializeOptions,
        bool isRepair)
    {
        auto getStatusResult{ DeploymentManager::GetStatus(packageFullName) };
        // Repair API works independent of the current status of DeploymentManager.
        // Even for Repair, GetStatus will still need to be run as it also captures the package full name in case higher version is installed
        if (getStatusResult.Status() == DeploymentStatus::Ok &&
            !isRepair)
        {
            Initialize_StopSuccessActivity(initializeActivityContext, getStatusResult.Status());
            return getStatusResult;
        }

        std::wstring frameworkPackageFullName{ packageFullName };
        auto deployPackagesResult{ Deploy(frameworkPackageFullName, initializeActivityContext, deploymentInitializeOptions.ForceDeployment()) };

        DeploymentStatus status{};
        if (SUCCEEDED(deployPackagesResult))
        {
            status = DeploymentStatus::Ok;
            Initialize_StopSuccessActivity(initializeActivityContext, status);
        }
        else
        {
            if ((::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::Feature_DeploymentRepair::IsEnabled()) &&
                (isRepair))
            {
                status = DeploymentStatus::PackageRepairFailed;
            }
            else
            {
                status = DeploymentStatus::PackageInstallFailed;
            }

            initializeActivityContext.GetActivity().StopWithResult(
                deployPackagesResult,
                static_cast<UINT32>(initializeActivityContext.GetLastFailure().type),
                initializeActivityContext.GetLastFailure().file.c_str(),
                initializeActivityContext.GetLastFailure().lineNumber,
                initializeActivityContext.GetLastFailure().message.c_str(),
                initializeActivityContext.GetLastFailure().module.c_str(),
                static_cast<UINT32>(status),
                static_cast<UINT32>(initializeActivityContext.GetInstallStage()),
                initializeActivityContext.GetCurrentResourceId().c_str(),
                initializeActivityContext.GetDeploymentErrorExtendedHResult(),
                initializeActivityContext.GetDeploymentErrorText().c_str(),
                initializeActivityContext.GetDeploymentErrorActivityId(),
                initializeActivityContext.GetUseExistingPackageIfHigherVersion());
        }

        return winrt::make<implementation::DeploymentResult>(status, deployPackagesResult);
    }

    // Deploys all of the packages carried by the specified framework.
    HRESULT DeploymentManager::Deploy(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        const bool forceDeployment
    ) try
    {
        RETURN_IF_FAILED(InstallLicenses(frameworkPackageFullName, initializeActivityContext));
        RETURN_IF_FAILED(DeployPackages(frameworkPackageFullName, initializeActivityContext, forceDeployment));
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT DeploymentManager::InstallLicenses(const std::wstring& frameworkPackageFullName, ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext)
    {
        auto licenseInstaller{ ::Microsoft::Windows::ApplicationModel::Licensing::Installer{} };
        auto licenseInstallerProxy{ ::WindowsAppRuntime::Deployment::Licensing::LicenseInstallerProxy{ licenseInstaller } };

        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetLicensePath);

        auto packagePath = ::WindowsAppRuntime::Deployment::Package::GetPackagePath(frameworkPackageFullName);

        // Build path for licenses
        auto licensePath{ std::filesystem::path(packagePath) };
        licensePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
        auto licenseFilespec{ licensePath };
        licenseFilespec /= L"*_license.xml";

        // Deploy the licenses (if any)
        std::vector<std::wstring> licenseFiles;
        RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::Licensing::GetLicenseFiles(licenseFilespec, licenseFiles));
        RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::Licensing::InstallLicenses(licenseFiles, licensePath, licenseInstallerProxy, initializeActivityContext));
        return S_OK;
    }

    HRESULT DeploymentManager::DeployPackages(const std::wstring& frameworkPackageFullName, ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext, const bool forceDeployment)
    {
        const auto frameworkPackagePath = std::filesystem::path(::WindowsAppRuntime::Deployment::Package::GetPackagePath(frameworkPackageFullName));

        std::map<std::wstring, ::WindowsAppRuntime::Deployment::PackageDeployment::PackagePathInfo> existingTargetPackagesIfHigherVersion;
        for (const auto& [packageIdentifier, packageFullName] : g_existingTargetPackagesIfHigherVersion)
        {
            const auto packagePath = std::filesystem::path(::WindowsAppRuntime::Deployment::Package::GetPackagePath(packageFullName));
            existingTargetPackagesIfHigherVersion[packageIdentifier] = { packageFullName, packagePath };
        }

        const auto deploymentPackageArguments = ::WindowsAppRuntime::Deployment::PackageDeployment::GetDeploymentPackageArguments(frameworkPackagePath, initializeActivityContext, existingTargetPackagesIfHigherVersion);

        for (auto package : deploymentPackageArguments)
        {
            initializeActivityContext.Reset();
            initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::AddPackage);
            initializeActivityContext.SetCurrentResourceId(package.identifier);
            if (package.useExistingPackageIfHigherVersion)
            {
                initializeActivityContext.SetUseExistingPackageIfHigherVersion();
            }

            // If the current application has runFullTrust capability, then Deploy the target package in a Breakaway process.
            // Otherwise, call PackageManager API to deploy the target package.
            // The Singleton package will always set true for forceDeployment and the running process will be terminated to update the package.
            if (initializeActivityContext.GetIsFullTrustPackage())
            {
                RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackageInBreakAwayProcess(
                    package.packagePath,
                    package.useExistingPackageIfHigherVersion,
                    forceDeployment || package.isSingleton,
                    initializeActivityContext,
                    ::WindowsAppRuntime::Deployment::PackageRegistrar::GenerateDeploymentAgentPath()
                ));
            }
            else
            {
                auto packageManager = winrt::Windows::Management::Deployment::PackageManager{};
                RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackage(
                    package.packagePath,
                    package.useExistingPackageIfHigherVersion,
                    forceDeployment || package.isSingleton,
                    packageManager,
                    initializeActivityContext
                ));
            }
        }

        // Always restart Push Notifications Long Running Platform when Singleton package is processed and installed.
        for (const auto& package : deploymentPackageArguments)
        {
            if (package.isSingleton)
            {
                // WIL callback is set up to log telemetry events for Push Notifications LRP.
                std::ignore = LOG_IF_FAILED(StartupNotificationsLongRunningPlatform());
                break;
            }
        }
        return S_OK;
    }

    HRESULT Initialize_Log(
        HRESULT hrInitialize,
        const AppModel::Identity::PackageIdentity& packageIdentity,
        const std::wstring& release) noexcept try
    {
        HANDLE hEventLog{ RegisterEventSourceW(nullptr, L"Windows App Runtime") };
        RETURN_LAST_ERROR_IF_NULL(hEventLog);

        const DWORD c_eventId{ static_cast<DWORD>(hrInitialize) };
        PCWSTR message1{ L"Windows App Runtime" };
        WCHAR message2[1024]{};
        PCWSTR message2Format{ L"ERROR 0x%08X: DeploymentManager initialization failed for version %s (MSIX package version %hu.%hu.%hu.%hu)" };
        const PACKAGE_VERSION version{ packageIdentity.Version() };
        FAIL_FAST_IF_FAILED(StringCchPrintfW(message2, ARRAYSIZE(message2), message2Format,
                                             hrInitialize, release.c_str(),
                                             version.Major, version.Minor, version.Build, version.Revision));
        PCWSTR strings[2]{ message1, message2 };
        LOG_IF_WIN32_BOOL_FALSE(ReportEventW(hEventLog, EVENTLOG_ERROR_TYPE, 0, c_eventId, nullptr, ARRAYSIZE(strings), 0, strings, nullptr));

        DeregisterEventSource(hEventLog);

        return S_OK;
    }
    CATCH_RETURN()

    HRESULT Initialize_OnError_ShowUI(
        const AppModel::Identity::PackageIdentity& packageIdentity,
        const std::wstring& release)
    {
        // Get the message caption
        PCWSTR caption{};
        wil::unique_cotaskmem_string captionString;
        WCHAR captionOnError[100]{};
        try
        {
            PCWSTR executable{};
            wil::unique_cotaskmem_string module;
            auto hr{ LOG_IF_FAILED(wil::GetModuleFileNameW(nullptr, module)) };
            if (SUCCEEDED(hr))
            {
                auto delimiter{ wcsrchr(module.get(), L'\\') };
                if (delimiter)
                {
                    executable = delimiter + 1;
                }
                else
                {
                    executable = module.get();
                }
                PCWSTR captionSuffix{ L"This application could not be started" };
                captionString = wil::str_printf<wil::unique_cotaskmem_string>(L"%s - %s", executable, captionSuffix);
                caption = captionString.get();
            }
        }
        catch (...)
        {
        }
        if (!caption)
        {
            LOG_IF_FAILED(StringCchPrintfW(captionOnError, ARRAYSIZE(captionOnError),
                                           L"<Process %d> - This application could not be started",
                                           GetCurrentProcessId()));
            caption = captionOnError;
        }

        // Get the message body
        WCHAR text[1024]{};
        PCWSTR textFormat{ L"Required components of the Windows App Runtime are missing\n"
                           L"    Version %s\n"
                           L"    (MSIX package version %hu.%hu.%hu.%hu)\n"
                           L"\n"
                           L"Do you want to install a compatible Windows App Runtime now?"
                         };
        const PACKAGE_VERSION version{ packageIdentity.Version() };
        FAIL_FAST_IF_FAILED(StringCchPrintfW(text, ARRAYSIZE(text), textFormat,
                                             release.c_str(),
                                             version.Major, version.Minor, version.Build, version.Revision));

        // Show the prompt
        const auto yesno{ MessageBoxW(nullptr, text, caption, MB_YESNO | MB_ICONERROR) };
        if (yesno == IDYES)
        {
            SHELLEXECUTEINFOW sei{};
            sei.cbSize = sizeof(sei);
            sei.lpVerb = L"open";
            sei.lpFile = L"https://docs.microsoft.com/windows/apps/windows-app-sdk/downloads";
            sei.nShow = SW_SHOWNORMAL;
            LOG_IF_WIN32_BOOL_FALSE(ShellExecuteExW(&sei));
        }
        return S_OK;
    }
}
