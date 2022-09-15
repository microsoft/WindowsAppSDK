// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <windows.h>
#include <memory>
#include <wil/result.h>
#include <appmodel.h>
#include <winrt/Windows.Management.Deployment.h>
#include <Microsoft.Windows.System.EnvironmentManager.h>
#include <AppModel.Identity.h>
#include <Security.IntegrityLevel.h>
#include <Microsoft.Windows.System.EnvironmentManager.Insights.h>
#include <WindowsAppRuntime.VersionInfo.h>


using namespace winrt::Microsoft::Windows::System::implementation;

static bool DoesChangeTrackingKeyExist()
{
    const auto subKey = std::filesystem::path{ LR"(Software\Microsoft\AppModel\RegistryWriteVirtualization\ExcludedKeys\HKEY_CURRENT_USER/Software/ChangeTracker)" };
    wil::unique_hkey keyToChangeTracker{};
    LSTATUS openResult{ RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, keyToChangeTracker.put()) };

    if (FAILED_WIN32(openResult))
    {
        EnvironmentManagerInsights::TraceLoggingInfo("Could not find the change tracking HKLM key.  Changes will not be tracked");
        LOG_IF_WIN32_ERROR(openResult);
        return false;
    }

    return true;
}

inline bool IsDllOnSystemAndRegistered()
{
    const auto frameworkPackageFamily{::WindowsAppRuntime::VersionInfo::Framework::GetPackageFamilyName()};

    std::unique_ptr<WCHAR> frameworkPackageFamilyName{ new WCHAR[PACKAGE_FAMILY_NAME_MAX_LENGTH + 1] };

    // UINT16_MAX is big.  50 should be a reasonable MAJOR and MINOR.
    constexpr uint16_t maxMajorToSearch{ 50 };
    constexpr uint16_t maxMinorToSearch{ 50 };
    bool foundAPackageInstalledForTheUser{};
    for (uint16_t major = 1; major < maxMajorToSearch; major++)
    {
        for (uint16_t minor = 0; minor < maxMinorToSearch; minor++)
        {
            wsprintf(frameworkPackageFamilyName.get(), frameworkPackageFamily.data(), major, minor);

            UINT32 packageCount = 0;
            UINT32 packageNameLength = 0;
            long returnCode{ FindPackagesByPackageFamily(frameworkPackageFamilyName.get(), PACKAGE_FILTER_DIRECT, &packageCount, nullptr, &packageNameLength, nullptr, nullptr)};

            if (returnCode != ERROR_SUCCESS && returnCode != ERROR_INSUFFICIENT_BUFFER)
            {
                LOG_WIN32_MSG(returnCode, "Could error with trying to find the framework package.  Treating as 'Changes won't be tracked'");
                return false;
            }

            if (packageNameLength > 0)
            {
                foundAPackageInstalledForTheUser = true;
                break;
            }
        }

        if (foundAPackageInstalledForTheUser)
        {
            break;
        }
    }

    if (foundAPackageInstalledForTheUser)
    {
        return true;
    }

    // At this point no framework packages are installed for the current user.  However, a framework package might be installed
    // machine wide.  Check that.  However, the process needs to be elevated to check.
    if (!Security::IntegrityLevel::IsElevated())
    {
        return false;
    }

    winrt::Windows::Management::Deployment::PackageManager packageManager{};
    auto currentArch{ AppModel::Identity::GetCurrentArchitecture() };
    for (uint16_t major = 1; major < maxMajorToSearch; major++)
    {
        for (uint16_t minor = 0; minor < maxMinorToSearch; minor++)
        {
            wsprintf(frameworkPackageFamilyName.get(), frameworkPackageFamily.data(), major, minor);

            for (auto package : packageManager.FindPackagesWithPackageTypes(frameworkPackageFamilyName.get(), winrt::Windows::Management::Deployment::PackageTypes::Framework))
            {
                if (package.Id().Architecture() == currentArch)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

inline bool ShouldChangesBeTracked(EnvironmentManager::Scope scope)
{
    // process scope changes are never tracked becuase they go away when the process ends.
    // Non packaged apps don't have identity.  No way to revert changes, so don't track them.
    if (scope == EnvironmentManager::Scope::Process || !AppModel::Identity::IsPackagedProcess())
    {
        return false;
    }

    return DoesChangeTrackingKeyExist() && IsDllOnSystemAndRegistered();
}
