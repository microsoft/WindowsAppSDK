// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <DeploymentManager.h>
#include <DeploymentResult.h>
#include <DeploymentActivityContext.h>
#include <PackageInfo.h>
#include <TerminalVelocityFeatures-DeploymentAPI.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager.g.cpp>
#include <PushNotificationsLongRunningPlatform-Startup.h>
#include "WindowsAppRuntime-License.h"

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

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::GetStatus()
    {
        FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), !AppModel::Identity::IsPackagedProcess());
        return GetStatus(GetCurrentFrameworkPackageFullName());
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize()
    {
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions options{};
        return Initialize(options);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize(
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions const& deploymentInitializeOptions)
    {
        return Initialize(GetCurrentFrameworkPackageFullName(), deploymentInitializeOptions);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Repair()
    {
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions options{};
        return Initialize(GetCurrentFrameworkPackageFullName(), options, true);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::GetStatus(hstring const& packageFullName)
    {
        // Get PackageInfo for WinAppSDK framework package
        std::wstring frameworkPackageFullName{ packageFullName };
        auto frameworkPackageInfo{ GetPackageInfoForPackage(frameworkPackageFullName) };

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

        for (const auto package : c_targetPackages)
        {
            // Build package family name based on the framework naming scheme.
            std::wstring packageFamilyName{};
            if (package.versionType == PackageVersionType::Versioned)
            {
                // PackageFamilyName = Prefix + SubTypeName + VersionIdentifier + Suffix
                // On WindowsAppSDK 1.1+, Main and Singleton packages are sharing same Package Name Prefix.
                packageFamilyName = WINDOWSAPPRUNTIME_PACKAGE_NAME_MAINPREFIX WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DELIMETER + package.identifier + packageNameVersionIdentifier + WINDOWSAPPRUNTIME_PACKAGE_NAME_SUFFIX;
            }
            else if (package.versionType == PackageVersionType::Unversioned)
            {
                // PackageFamilyName = Prefix + Subtypename + VersionTag + Suffix
                // On WindowsAppSDK 1.1+, Main and Singleton packages are sharing same Package Name Prefix.
                packageFamilyName = WINDOWSAPPRUNTIME_PACKAGE_NAME_MAINPREFIX WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DELIMETER + package.identifier + packageNameVersionTag + WINDOWSAPPRUNTIME_PACKAGE_NAME_SUFFIX;
            }
            else
            {
                // Other version types not supported.
                FAIL_FAST_HR(HRESULT_FROM_WIN32(ERROR_UNSUPPORTED_TYPE));
            }

            // Get target version based on the framework.
            auto targetPackageVersion{ frameworkPackageInfo.Package(0).packageId.version };

            verifyResult = VerifyPackage(packageFamilyName, targetPackageVersion, package.identifier);
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
        auto& initializeActivityContext{ ::WindowsAppRuntime::Deployment::Activity::Context::Get() };
        const bool isPackagedProcess{ AppModel::Identity::IsPackagedProcess() };
        const int integrityLevel = Security::IntegrityLevel::GetIntegrityLevel();
        if (isPackagedProcess && integrityLevel >= SECURITY_MANDATORY_MEDIUM_RID)
        {
            initializeActivityContext.SetIsFullTrustPackage();
        }

            ::WindowsAppRuntime::Deployment::Activity::Context::Get().SetIsFullTrustPackage();
        initializeActivityContext.GetActivity().Start(deploymentInitializeOptions.ForceDeployment(),
                                                      Security::IntegrityLevel::IsElevated(),
                                                      isPackagedProcess,
                                                      initializeActivityContext.GetIsFullTrustPackage(),
                                                      Security::IntegrityLevel::GetIntegrityLevel(),
                                                      isRepair);

        // DeploymentManager API requires a packaged process?
        HRESULT hr{};
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult deploymentResult{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Unknown, S_OK };
        if (!isPackagedProcess)
        {
            // The process lacks package identity but that's OK. Do nothing
            const auto c_status{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Ok };
            return winrt::make<implementation::DeploymentResult>(c_status, S_OK);
        }

        try
        {
            deploymentResult = _Initialize(initializeActivityContext, packageFullName, deploymentInitializeOptions, isRepair);
        }
        catch (winrt::hresult_error const& e)
        {
            hr = e.code();
        }
        if (FAILED(hr))
        {
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
                release = std::wstring{ L"??? (" } + std::wstring(packageFullName.c_str()) + L")";
            }
            LOG_IF_FAILED(Initialize_Log(hr, packageIdentity, release));

            // NOTE: IsDebuggerPresent()=TRUE if running under a debugger context.
            //       IsDebuggerPresent()=FALSE if not running under a debugger context, even if AEDebug is set.
            if (IsDebuggerPresent())
            {
                DebugBreak();
            }

            if (deploymentInitializeOptions.OnErrorShowUI() ||
                ::Microsoft::Configuration::IsOptionEnabled(L"MICROSOFT_WINDOWSAPPRUNTIME_DEPLOYMENT_INITIALIZE_ONERRORSHOWUI"))
            {
                LOG_IF_FAILED(Initialize_OnError_ShowUI(packageIdentity, release));
            }

            THROW_HR(hr);
        }

        // Success!
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
        auto deployPackagesResult{ Deploy(frameworkPackageFullName, deploymentInitializeOptions.ForceDeployment()) };
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

    MddCore::PackageInfo DeploymentManager::GetPackageInfoForPackage(std::wstring const& packageFullName)
    {
        wil::unique_package_info_reference packageInfoReference;
        THROW_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName.c_str(), 0, &packageInfoReference));
        return MddCore::PackageInfo::FromPackageInfoReference(packageInfoReference.get());
    }

    // Borrowed and repurposed from Dynamic Dependencies
    std::vector<std::wstring> DeploymentManager::FindPackagesByFamily(std::wstring const& packageFamilyName)
    {
        UINT32 count{};
        UINT32 bufferLength{};
        const auto rc{ FindPackagesByPackageFamily(packageFamilyName.c_str(), PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, nullptr, &bufferLength, nullptr, nullptr) };
        if (rc == ERROR_SUCCESS)
        {
            // The package family has no packages registered to the user
            return std::vector<std::wstring>();
        }
        else if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            THROW_WIN32(rc);
        }

        auto packageFullNames{ wil::make_unique_cotaskmem<PWSTR[]>(count) };
        auto buffer{ wil::make_unique_cotaskmem<WCHAR[]>(bufferLength) };
        THROW_IF_WIN32_ERROR(FindPackagesByPackageFamily(packageFamilyName.c_str(), PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, packageFullNames.get(), &bufferLength, buffer.get(), nullptr));

        std::vector<std::wstring> packageFullNamesList;
        for (UINT32 index=0; index < count; ++index)
        {
            const auto packageFullName{ packageFullNames[index] };
            packageFullNamesList.push_back(std::wstring(packageFullName));
        }
        return packageFullNamesList;
    }

    HRESULT DeploymentManager::VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion,
        const std::wstring& packageIdentifier) try
    {
        auto packageFullNames{ FindPackagesByFamily(packageFamilyName) };
        bool match{};
        for (const auto& packageFullName : packageFullNames)
        {
            auto packagePath{ GetPackagePath(packageFullName) };
            if (packagePath.empty())
            {
                continue;
            }

            auto packageId{ AppModel::Identity::PackageIdentity::FromPackageFullName(packageFullName.c_str()) };
            if (packageId.Version().Version >= targetVersion.Version)
            {
                match = true;
                if (packageId.Version().Version > targetVersion.Version)
                {
                    g_existingTargetPackagesIfHigherVersion.insert(std::make_pair(packageIdentifier, packageFullName));
                }
                break;
            }
        }

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !match);
        return S_OK;
    }
    CATCH_RETURN()

    // Gets the package path, which is a fast and reliable way to check if the package is
    // at least staged on the device, even without package query capabilities.
    std::wstring DeploymentManager::GetPackagePath(std::wstring const& packageFullName)
    {
        UINT32 pathLength{};
        const auto rc{ GetPackagePathByFullName(packageFullName.c_str(), &pathLength, nullptr) };
        if (rc == ERROR_NOT_FOUND)
        {
            return std::wstring();
        }
        else if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            THROW_WIN32(rc);
        }

        auto path{ wil::make_process_heap_string(nullptr, pathLength) };
        THROW_IF_WIN32_ERROR(GetPackagePathByFullName(packageFullName.c_str(), &pathLength, path.get()));
        return std::wstring{ path.get() };
    }

    // If useExistingPackageIfHigherVersion == false, Adds the current version package at the passed in path using PackageManager.
    // If useExistingPackageIfHigherVersion == true, Registers the higher version package using the passed in path as manifest path and PackageManager.
    // This requires the 'packageManagement' or 'runFullTrust' capabilities.
    HRESULT DeploymentManager::AddOrRegisterPackage(const std::filesystem::path& path, const bool useExistingPackageIfHigherVersion, const bool forceDeployment) try
    {
        winrt::Windows::Management::Deployment::PackageManager packageManager;

        const auto options{ forceDeployment ?
                            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
                            winrt::Windows::Management::Deployment::DeploymentOptions::None };

        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Management::Deployment::DeploymentResult,
            winrt::Windows::Management::Deployment::DeploymentProgress> deploymentOperation;

        const auto pathUri { winrt::Windows::Foundation::Uri(path.c_str()) };
        if (useExistingPackageIfHigherVersion)
        {
            deploymentOperation = packageManager.RegisterPackageAsync(pathUri, nullptr, options);
        }
        else
        {
            deploymentOperation = packageManager.AddPackageAsync(pathUri, nullptr, options);
        }
        deploymentOperation.get();
        const auto deploymentResult{ deploymentOperation.GetResults() };
        HRESULT deploymentOperationHResult{};
        HRESULT deploymentOperationExtendedHResult{};

        if (deploymentOperation.Status() != winrt::Windows::Foundation::AsyncStatus::Completed)
        {
            deploymentOperationHResult = static_cast<HRESULT>(deploymentOperation.ErrorCode());
            deploymentOperationExtendedHResult = deploymentResult.ExtendedErrorCode();

            ::WindowsAppRuntime::Deployment::Activity::Context::Get().SetDeploymentErrorInfo(
                deploymentOperationExtendedHResult,
                deploymentResult.ErrorText().c_str(),
                deploymentResult.ActivityId());
        }

        // If deploymentOperationHResult indicates success, take that, ignore deploymentOperationExtendedHResult.
        // Otherwise, return deploymentOperationExtendedHResult if there is an error in it, if not, return deploymentOperationHResult.
        return SUCCEEDED(deploymentOperationHResult) ? deploymentOperationHResult :
            (FAILED(deploymentOperationExtendedHResult) ? deploymentOperationExtendedHResult : deploymentOperationHResult);
    }
    CATCH_RETURN()

    std::wstring DeploymentManager::GenerateDeploymentAgentPath()
    {
        // Calculate the path to the restart agent as being in the same directory as the current module.
        wil::unique_hmodule module;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<PCWSTR>(DeploymentManager::GenerateDeploymentAgentPath), &module));

        std::filesystem::path modulePath{ wil::GetModuleFileNameW<std::wstring>(module.get()) };
        return modulePath.parent_path() / c_deploymentAgentFilename;
    }

    /// @warning This function is ONLY for processes with package identity. It's the caller's responsibility to ensure this.
    HRESULT DeploymentManager::AddOrRegisterPackageInBreakAwayProcess(const std::filesystem::path& path, const bool useExistingPackageIfHigherVersion, const bool forceDeployment) try
    {
        auto exePath{ GenerateDeploymentAgentPath() };
        auto activityId{ winrt::to_hstring(*::WindowsAppRuntime::Deployment::Activity::Context::Get().GetActivity().Id()) };

        // <currentdirectory>\deploymentagent.exe <custom arguments passed by caller>
        auto cmdLine{ wil::str_printf<wil::unique_cotaskmem_string>(L"\"%s\" %u \"%s\" %u %s", exePath.c_str(), (useExistingPackageIfHigherVersion ? 1 : 0), path.c_str(), (forceDeployment ? 1 : 0), activityId.c_str()) };

        SIZE_T attributeListSize{};
        auto attributeCount{ 1 };

        // attributeCount is always >0 so we need to allocate a buffer. Call InitializeProcThreadAttributeList()
        // to determine the size needed so we always expect ERROR_INSUFFICIENT_BUFFER.
        THROW_HR_IF(E_UNEXPECTED, !!InitializeProcThreadAttributeList(nullptr, attributeCount, 0, &attributeListSize));
        const auto lastError{ GetLastError() };
        THROW_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_INSUFFICIENT_BUFFER);
        wistd::unique_ptr<BYTE[]> attributeListBuffer{ new BYTE[attributeListSize] };
        auto attributeList{ reinterpret_cast<PPROC_THREAD_ATTRIBUTE_LIST>(attributeListBuffer.get()) };
        THROW_IF_WIN32_BOOL_FALSE(InitializeProcThreadAttributeList(attributeList, attributeCount, 0, &attributeListSize));
        auto freeAttributeList{ wil::scope_exit([&] { DeleteProcThreadAttributeList(attributeList); }) };

        // https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-updateprocthreadattribute
        // The process being created will create any child processes outside of the desktop app runtime environment.
        // This behavior is the default for processes for which no policy has been set
        DWORD policy{ PROCESS_CREATION_DESKTOP_APP_BREAKAWAY_ENABLE_PROCESS_TREE };
        THROW_IF_WIN32_BOOL_FALSE(UpdateProcThreadAttribute(attributeList, 0, PROC_THREAD_ATTRIBUTE_DESKTOP_APP_POLICY, &policy, sizeof(policy), nullptr, nullptr));

        STARTUPINFOEX info{};
        info.StartupInfo.cb = sizeof(info);
        info.lpAttributeList = attributeList;

        wil::unique_process_information processInfo;
        THROW_IF_WIN32_BOOL_FALSE(CreateProcess(nullptr, cmdLine.get(), nullptr, nullptr, FALSE, EXTENDED_STARTUPINFO_PRESENT, nullptr, nullptr, &info.StartupInfo, &processInfo));

        // This API is designed to only return to the caller on failure, otherwise block until process termination.
        // Wait for the agent to exit.  If the agent succeeds, it will terminate this process.  If the agent fails,
        // it can exit or crash.  This API will be able to detect the failure and return.
        wil::handle_wait(processInfo.hProcess);

        DWORD processExitCode{};
        THROW_IF_WIN32_BOOL_FALSE_MSG(GetExitCodeProcess(processInfo.hProcess, &processExitCode), "CmdLine: %ls, processExitCode: %u", cmdLine.get(), processExitCode);
        RETURN_IF_FAILED_MSG(HRESULT_FROM_WIN32(processExitCode), "DeploymentAgent exitcode:0x%X", processExitCode);
        return S_OK;
    }
    CATCH_RETURN()

    // Deploys all of the packages carried by the specified framework.
    HRESULT DeploymentManager::Deploy(const std::wstring& frameworkPackageFullName, const bool forceDeployment) try
    {
        RETURN_IF_FAILED(InstallLicenses(frameworkPackageFullName));
        RETURN_IF_FAILED(DeployPackages(frameworkPackageFullName, forceDeployment));
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT DeploymentManager::InstallLicenses(const std::wstring& frameworkPackageFullName)
    {
        ::WindowsAppRuntime::Deployment::Activity::Context::Get().SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetLicensePath);

        // Build path for licenses
        auto licensePath{ std::filesystem::path(GetPackagePath(frameworkPackageFullName)) };
        licensePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
        auto licenseFilespec{ licensePath };
        licenseFilespec /= L"*_license.xml";

        ::WindowsAppRuntime::Deployment::Activity::Context::Get().SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::InstallLicense);

        // Deploy the licenses (if any)
        ::Microsoft::Windows::ApplicationModel::Licensing::Installer licenseInstaller;
        WIN32_FIND_DATA findFileData{};
        wil::unique_hfind hfind{ FindFirstFileW(licenseFilespec.c_str(), &findFileData) };
        if (!hfind)
        {
            const auto lastError{ GetLastError() };
            RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(lastError), (lastError != ERROR_FILE_NOT_FOUND) && (lastError != ERROR_PATH_NOT_FOUND),
                             "FindFirstFile:%ls", licenseFilespec.c_str());
            return S_OK;
        }
        for (;;)
        {
            // Install the license file
            auto licenseFilename{ licensePath };
            licenseFilename /= findFileData.cFileName;

            ::WindowsAppRuntime::Deployment::Activity::Context::Get().Reset();
            ::WindowsAppRuntime::Deployment::Activity::Context::Get().SetCurrentResourceId(licenseFilename);

            RETURN_IF_FAILED_MSG(licenseInstaller.InstallLicenseFile(licenseFilename.c_str()),
                                 "LicenseFile:%ls", licenseFilename.c_str());

            // Next! (if any)
            if (!FindNextFileW(hfind.get(), &findFileData))
            {
                const auto lastError{ GetLastError() };
                RETURN_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_NO_MORE_FILES);
                break;
            }
        }
        return S_OK;
    }

    HRESULT DeploymentManager::DeployPackages(const std::wstring& frameworkPackageFullName, const bool forceDeployment)
    {
        auto initializeActivity{ ::WindowsAppRuntime::Deployment::Activity::Context::Get() };

        initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetPackagePath);
        const auto frameworkPath{ std::filesystem::path(GetPackagePath(frameworkPackageFullName)) };

        initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::AddPackage);
        for (auto package : c_targetPackages)
        {
            initializeActivity.Reset();
            initializeActivity.SetCurrentResourceId(package.identifier);

            std::filesystem::path packagePath{};

            // If there is exisiting target package version higher than that of framework current version package, then re-register it.
            // Otherwise, deploy the target msix package from the current framework package version.
            auto existingPackageIfHigherVersion = g_existingTargetPackagesIfHigherVersion.find(package.identifier);
            auto useExistingPackageIfHigherVersion { existingPackageIfHigherVersion != g_existingTargetPackagesIfHigherVersion.end() };
            if (useExistingPackageIfHigherVersion)
            {
                initializeActivity.SetUseExistingPackageIfHigherVersion();
                packagePath = std::filesystem::path(GetPackagePath(existingPackageIfHigherVersion->second));
                packagePath /= WINDOWSAPPRUNTIME_PACKAGE_MANIFEST_FILE;
            }
            else
            {
                packagePath = frameworkPath;
                packagePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
                packagePath /= package.identifier + WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION;
            }

            // If the current application has runFullTrust capability, then Deploy the target package in a Breakaway process.
            // Otherwise, call PackageManager API to deploy the target package.
            if (initializeActivity.GetIsFullTrustPackage())
            {

                RETURN_IF_FAILED(AddOrRegisterPackageInBreakAwayProcess(packagePath, useExistingPackageIfHigherVersion, forceDeployment));
            }
            else
            {
                RETURN_IF_FAILED(AddOrRegisterPackage(packagePath, useExistingPackageIfHigherVersion, forceDeployment));
            }

            // Restart Push Notifications Long Running Platform when ForceDeployment option is applied.
            if (forceDeployment &&
                CompareStringOrdinal(package.identifier.c_str(), -1, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON, -1, TRUE) == CSTR_EQUAL)
            {
                // wil callback is set up to log telemetry events for Push Notifications LRP.
                LOG_IF_FAILED_MSG(StartupNotificationsLongRunningPlatform(), "Restarting Notifications LRP failed in all 3 attempts.");
            }
        }

        return S_OK;
    }

    hstring DeploymentManager::GetCurrentFrameworkPackageFullName()
    {
        // Get current package identity.
        WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
        const auto rc{ ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName) };
        if (rc != ERROR_SUCCESS)
        {
            THROW_WIN32(rc);
        }

        // Get the PackageInfo of current package and it's dependency packages
        std::wstring currentPackageFullName{ packageFullName };
        auto currentPackageInfo{ GetPackageInfoForPackage(currentPackageFullName) };

        // Index starts at 1 since the first package is the current package and we are interested in
        // dependency packages only.
        for (size_t i = 0; i < currentPackageInfo.Count(); ++i)
        {
            auto dependencyPackage{ currentPackageInfo.Package(i) };

            // Verify PublisherId matches.
            if (CompareStringOrdinal(currentPackageInfo.Package(i).packageId.publisherId, -1, WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID, -1, TRUE) != CSTR_EQUAL)
            {
                continue;
            }

            // Verify that the WindowsAppRuntime prefix identifier is in the name.
            // This should also be the beginning of the name, so its find position is expected to be 0.
            std::wstring dependencyPackageName{ currentPackageInfo.Package(i).packageId.name };
            if (dependencyPackageName.find(WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX) != 0)
            {
                continue;
            }

            // On WindowsAppSDK 1.1+, there is no need to check and rule out Main, Singleton and DDLM Package identifiers as their names don't have a overlap with WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX.

            return hstring(currentPackageInfo.Package(i).packageFullName);
        }

        THROW_WIN32(ERROR_NOT_FOUND);
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
