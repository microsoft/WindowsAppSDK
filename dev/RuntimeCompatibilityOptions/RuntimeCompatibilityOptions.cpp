// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "CompatibilityOptions.h"
#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.CompatibilityOptions.g.cpp"
#include "AssemblyInfo.h"
#include <FrameworkUdk/Containment.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    winrt::Windows::Foundation::Collections::IVector<CompatibilityChange> CompatibilityOptions::DisabledChanges()
    {
        return m_disabledChanges;
    }

    void CompatibilityOptions::Apply()
    {
        WinAppSdk::Containment::WinAppSDKRuntimeConfiguration config;

        // If both patch modes are set to the same major.minor version, error out if the patch versions are different.
        if (m_patchMode1.Major == m_patchMode2.Major && m_patchMode1.Minor == m_patchMode2.Minor &&
            m_patchMode1.Major != 0)
        {
            if (m_patchMode1.Patch != m_patchMode2.Patch)
            {
                throw hresult_invalid_argument(L"Patch modes should target different Major.Minor versions or match Patch version.");
            }
        }

        // Apply the patch mode which applies to the major.minor version, if any.
        if (m_patchMode1.Major == WINDOWSAPPSDK_RELEASE_MAJOR && m_patchMode1.Minor == WINDOWSAPPSDK_RELEASE_MINOR)
        {
            // Apply patch mode 1
            config.patchVersion = (WinAppSDKPatchVersion)WinAppSDKPatchVersionFromValues(m_patchMode1.Major, m_patchMode1.Minor, m_patchMode1.Patch);
        }
        else if (m_patchMode2.Major == WINDOWSAPPSDK_RELEASE_MAJOR && m_patchMode2.Minor == WINDOWSAPPSDK_RELEASE_MINOR)
        {
            // Apply patch mode 2
            config.patchVersion = (WinAppSDKPatchVersion)WinAppSDKPatchVersionFromValues(m_patchMode2.Major, m_patchMode2.Minor, m_patchMode2.Patch);
        }

        // Add the set of disabled changes
        std::vector<UINT32> disabledChanges;
        for (auto changeId : m_disabledChanges)
        {
            // TODO: Telemetry!  Log the changeId that was disabled.
            // UINT32 is used internally for the changeId, so cast from the enum's Int32 to that.
            disabledChanges.push_back(static_cast<UINT32>(changeId));
        }
        config.disabledChanges = disabledChanges.data();
        config.disabledChangesCount = static_cast<UINT32>(disabledChanges.size());

        HRESULT hr = WinAppSdk::Containment::SetConfiguration(&config);
        if (FAILED(hr))
        {
            if (hr == E_ILLEGAL_STATE_CHANGE)
            {
                throw winrt::hresult_illegal_state_change(L"Configuration already set or locked.");
            }
            winrt::throw_hresult(hr);
        }
    }
}
