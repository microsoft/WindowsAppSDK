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


using namespace winrt::Microsoft::Windows::System::implementation;

static bool DoesChangeTrackingKeyExist()
{
    const auto subKey = std::filesystem::path{ LR"(Software\Microsoft\AppModel\RegistryWriteVirtualization\ExcludedKeys\HKEY_CURRENT_USER/Software/ChangeTracker)" };
    wil::unique_hkey keyToChangeTracker{};
    LSTATUS openResult{ RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, keyToChangeTracker.put()) };

    LOG_IF_WIN32_ERROR_MSG(openResult, "Open key result to check if tracking exists: %i. Errors are treated as \"Do not track changes\"", openResult);

    return openResult == ERROR_SUCCESS;
}

inline bool IsDllOnSystemAndRegistered()
{

    // Maybe a better way exists to switch between the test package family name and the production family name.
    // This does not work because the test code and EM code are in two different processes.
#if defined(__WINDOWSAPPRUNTIME_TEST_METADATA_H)
    constexpr std::wstring_view frameworkPackageFamily{ L"Microsoft.WindowsAppRuntime.Framework-%i.%i_8wekyb3d8bbwe" };
#else
    constexpr std::wstring_view frameworkPackageFamily{ L"Microsoft.WindowsAppRuntime.%i.%i_8wekyb3d8bbwe" };
#endif

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
