// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "CompatibilityOptions.h"
#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.CompatibilityOptions.g.cpp"
#include "AssemblyInfo.h"

#define DEFINE_WinAppSDKRuntimeConfiguration
#include <FrameworkUdk/Containment.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    winrt::Windows::Foundation::Collections::IVector<uint64_t> CompatibilityOptions::DisabledChanges()
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
        for (auto changeId : m_disabledChanges)
        {
            // TODO: Telemetry!  Log the changeId that was disabled.
            // Currently only UINT32 is used internally for the changeId, so cast down to that.
            config.disabledChanges.push_back(static_cast<UINT32>(changeId));
        }

        HRESULT hr = WinAppSdk::Containment::SetConfiguration(&config);
        if (FAILED(hr))
        {
            if (hr == E_ACCESSDENIED)
            {
                throw winrt::hresult_access_denied(L"Configuration already set or locked.");
            }
            winrt::throw_hresult(hr);
        }
    }
}
