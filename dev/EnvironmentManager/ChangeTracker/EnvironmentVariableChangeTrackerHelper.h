// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <windows.h>
#include <memory>
#include <wil/result.h>
#include <appmodel.h>
#include <winrt/Windows.Management.Deployment.h>
#include <Microsoft.Windows.System.EnvironmentManager.h>
#include "AppModel.Identity.h"


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
    constexpr std::wstring_view frameworkPackageFamily{ L"Microsoft.WindowsAppRuntime.8wekyb3d8bbwe" };

    UINT32 count{};
    UINT32 bufferLength{};
    THROW_HR_IF(E_UNEXPECTED, ERROR_INSUFFICIENT_BUFFER != FindPackagesByPackageFamily(frameworkPackageFamily.data(), PACKAGE_INFORMATION_BASIC, &count, nullptr, &bufferLength, nullptr, nullptr));

    // dll for reverting tracking is registered and on the system for the current user.
    if (count > 0)
    {
        return true;
    }

    std::unique_ptr<wchar_t> buffer{ new wchar_t[bufferLength] };
    std::unique_ptr<wchar_t> fullNames{ new wchar_t[count] };

    THROW_HR_IF(E_UNEXPECTED, ERROR_SUCCESS != FindPackagesByPackageFamily(frameworkPackageFamily.data(), PACKAGE_INFORMATION_BASIC, &count, reinterpret_cast<PWSTR*>(fullNames.get()), &bufferLength, buffer.get(), nullptr));

}

inline bool ShouldChangesBeTracked(EnvironmentManager::Scope scope)
{
    if (scope == EnvironmentManager::Scope::Process)
    {
        return false;
    }

    
    //auto isUserOrMachineScope{ scope != EnvironmentManager::Scope::Process };

    //bool willChangesBeTracked{ isUserOrMachineScope && DoesChangeTrackingKeyExist() && ::AppModel::Identity::IsPackagedProcess() };

    //if (scope == EnvironmentManager::Scope::Machine)
    //{
    //    willChangesBeTracked &= ::Security::IntegrityLevel::IsElevated();
    //}

    //winrt::Windows::Management::Deployment::PackageManager manager{};
    //manager.FindPackage
    //

    //return willChangesBeTracked;
}
