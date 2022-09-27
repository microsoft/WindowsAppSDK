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
#include <WindowsAppRuntime.SelfContained.h>


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

inline bool ShouldChangesBeTracked(EnvironmentManager::Scope scope)
{
    // process scope changes are never tracked becuase they go away when the process ends.
    // Non packaged apps don't have identity.  No way to revert changes, so don't track them.
    // The framework package needs to be on the system, or, loaded into the system when a package is uninstalled.
    // CUrrently no way exists to see if the framework dll will be loaded into the system when a self-contained deployment is uninstalled.
    // Because of this self-contained deployments aren't eligable for change tracking.
    if (scope == EnvironmentManager::Scope::Process || !AppModel::Identity::IsPackagedProcess() || WindowsAppRuntime::SelfContained::IsSelfContained())
    {
        return false;
    }

    return DoesChangeTrackingKeyExist();
}
