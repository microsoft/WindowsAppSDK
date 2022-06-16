// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <windows.h>
#include <wil/result.h>
#include <appmodel.h>
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

inline bool ShouldChangesBeTracked(EnvironmentManager::Scope scope)
{
    auto isUserOrMachineScope{ scope != EnvironmentManager::Scope::Process };

    bool willChangesBeTracked{ isUserOrMachineScope && DoesChangeTrackingKeyExist() && ::AppModel::Identity::IsPackagedProcess() };

    if (scope == EnvironmentManager::Scope::Machine)
    {
        willChangesBeTracked &= ::Security::IntegrityLevel::IsElevated();
    }

    return willChangesBeTracked;
}
