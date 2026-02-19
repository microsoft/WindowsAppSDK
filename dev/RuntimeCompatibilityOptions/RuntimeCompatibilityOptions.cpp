// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "RuntimeCompatibilityOptions.h"
#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions.g.cpp"
#include "AssemblyInfo.h"
#include <FrameworkUdk/Containment.h>
#include "RuntimeCompatibilityOptions_TraceLogger.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    winrt::Windows::Foundation::Collections::IVector<RuntimeCompatibilityChange> RuntimeCompatibilityOptions::DisabledChanges()
    {
        return m_disabledChanges;
    }

    void RuntimeCompatibilityOptions::Apply()
    {
        std::wstring patchLevel1Str = std::to_wstring(m_patchLevel1.Major) + L"." +
                                    std::to_wstring(m_patchLevel1.Minor) + L"." +
                                    std::to_wstring(m_patchLevel1.Patch);
        std::wstring patchLevel2Str = std::to_wstring(m_patchLevel2.Major) + L"." +
                                    std::to_wstring(m_patchLevel2.Minor) + L"." +
                                    std::to_wstring(m_patchLevel2.Patch);
        RuntimeCompatibilityOptions_TraceLogger::ApplyCalled(patchLevel1Str.c_str(), patchLevel2Str.c_str());

        WinAppSdk::Containment::WinAppSDKRuntimeConfiguration config;

        // If both patch levels are set to the same major.minor version, error out if the patch versions are different.
        if (m_patchLevel1.Major == m_patchLevel2.Major && m_patchLevel1.Minor == m_patchLevel2.Minor &&
            m_patchLevel1.Major != 0)
        {
            if (m_patchLevel1.Patch != m_patchLevel2.Patch)
            {
                RuntimeCompatibilityOptions_TraceLogger::ApplyFailed(
                    E_INVALIDARG,
                    L"Patch levels should target different Major.Minor versions or match Patch version."
                );
                throw hresult_invalid_argument(L"Patch levels should target different Major.Minor versions or match Patch version.");
            }
        }

        // Apply the patch level which applies to the major.minor version, if any.
        if (m_patchLevel1.Major == WINDOWSAPPSDK_RELEASE_MAJOR && m_patchLevel1.Minor == WINDOWSAPPSDK_RELEASE_MINOR)
        {
            // Apply patch level 1
            config.patchVersion = (WinAppSDKPatchVersion)WinAppSDKPatchVersionFromValues(m_patchLevel1.Major, m_patchLevel1.Minor, m_patchLevel1.Patch);
        }
        else if (m_patchLevel2.Major == WINDOWSAPPSDK_RELEASE_MAJOR && m_patchLevel2.Minor == WINDOWSAPPSDK_RELEASE_MINOR)
        {
            // Apply patch level 2
            config.patchVersion = (WinAppSDKPatchVersion)WinAppSDKPatchVersionFromValues(m_patchLevel2.Major, m_patchLevel2.Minor, m_patchLevel2.Patch);
        }

        // Add the set of disabled changes
        std::vector<UINT32> disabledChanges;
        for (auto changeId : m_disabledChanges)
        {
            // UINT32 is used internally for the changeId, so cast from the enum's Int32 to that.
            auto id = static_cast<UINT32>(changeId);
            RuntimeCompatibilityOptions_TraceLogger::ChangeDisabled(id);
            disabledChanges.push_back(id);
        }
        config.disabledChanges = disabledChanges.data();
        config.disabledChangesCount = static_cast<UINT32>(disabledChanges.size());

        HRESULT hr = WinAppSdk::Containment::SetConfiguration(&config);
        if (FAILED(hr))
        {
            if (hr == E_ILLEGAL_STATE_CHANGE)
            {
                RuntimeCompatibilityOptions_TraceLogger::ApplyFailed(
                    hr,
                    L"Configuration already set or locked."
                );
                throw winrt::hresult_illegal_state_change(L"Configuration already set or locked.");
            }

            RuntimeCompatibilityOptions_TraceLogger::ApplyFailed(
                hr,
                L"SetConfiguration failed."
            );
            winrt::throw_hresult(hr);
        }
    }
}
