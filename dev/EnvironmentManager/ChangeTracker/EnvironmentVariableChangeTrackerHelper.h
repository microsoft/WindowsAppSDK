// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include <windows.h>
#include <wil/result.h>
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
    return SUCCEEDED(LOG_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, keyToChangeTracker.put())));
}

inline bool ShouldChangesBeTracked(EnvironmentManager::Scope scope)
{
    // process scope changes are never tracked becuase they go away when the process ends.
    // Non packaged apps don't have identity.  No way to revert changes, so don't track them.
    // Self-contained deployments aren't eligable for change tracking.
    if (scope == EnvironmentManager::Scope::Process || !AppModel::Identity::IsPackagedProcess() || WindowsAppRuntime::SelfContained::IsSelfContained())
    {
        return false;
    }

    return DoesChangeTrackingKeyExist();
}
