// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "EnvironmentVariableChangeTracker.h"
#include "EnvironmentVariableChangeTrackerHelper.h"

namespace winrt::Microsoft::Windows::System::implementation
{
    EnvironmentVariableChangeTracker::EnvironmentVariableChangeTracker(const std::wstring& evName, const std::wstring& valueToSet, EnvironmentManager::Scope scope)
        : m_eVName(evName), m_eVValue(valueToSet), m_scope(scope)
    {
        m_PackageFullName = PackageFullName();
    }

    PCWSTR EnvironmentVariableChangeTracker::KeyName() const
    {
        return L"EnvironmentVariables";
    }

    HRESULT EnvironmentVariableChangeTracker::TrackChange(std::function<HRESULT(void)> callback)
    {
        if (ShouldChangesBeTracked())
        {
            DWORD disposition{};
            wil::unique_hkey regLocationToWriteChange{ GetKeyForTrackingChange(&disposition) };

            // Do not update previous value if this package wrote
            // to this EV once before.
            if (disposition == REG_CREATED_NEW_KEY)
            {
                std::wstring originalValue{ GetOriginalValueOfEV() };
                RETURN_IF_WIN32_ERROR(RegSetValueEx(regLocationToWriteChange.get(),
                    L"PreviousValue", 0, REG_SZ,
                    reinterpret_cast<const BYTE*>(originalValue.c_str()),
                    static_cast<DWORD>((originalValue.size() + 1) * sizeof(wchar_t))));
            }

            RETURN_IF_WIN32_ERROR(RegSetValueEx(regLocationToWriteChange.get(),
                L"CurrentValue", 0, REG_SZ,
                reinterpret_cast<const BYTE*>(m_eVValue.c_str()),
                static_cast<DWORD>((m_eVValue.size() + 1) * sizeof(wchar_t))));

            std::chrono::nanoseconds insertionTime{ std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) };
            long long nanoSecondTicks{ insertionTime.count() };
            RETURN_IF_WIN32_ERROR(RegSetValueEx(regLocationToWriteChange.get(),
                L"InsertionTime", 0, REG_QWORD,
                reinterpret_cast<const BYTE*>(&nanoSecondTicks),
                sizeof(long long)));
        }

        return callback();
    }
}
