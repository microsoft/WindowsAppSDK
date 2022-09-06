// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include "EnvironmentVariableChangeTracker.h"

namespace winrt::Microsoft::Windows::System::implementation
{
    EnvironmentVariableChangeTracker::EnvironmentVariableChangeTracker(const std::wstring& key, const std::wstring& valueToSet, EnvironmentManager::Scope scope)
    {
        THROW_HR_IF(E_INVALIDARG, key.empty());

        // Check if we need to track the changes.
        // If we do need to track the changes get the Package Full Name
        WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
        const long getPackageFullNameRC{ ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName) };


        if (scope == EnvironmentManager::Scope::Process || getPackageFullNameRC == APPMODEL_ERROR_NO_PACKAGE)
        {
            m_ShouldTrackChange = false;
        }
        else if (getPackageFullNameRC == ERROR_SUCCESS)
        {
            m_PackageFullName = std::wstring(packageFullName);
            m_ShouldTrackChange = true;
        }
        else
        {
            THROW_WIN32(getPackageFullNameRC);
        }

        m_Scope = scope;
        m_Key = key;
        m_Value = valueToSet;
    }

    PCWSTR EnvironmentVariableChangeTracker::KeyName() const
    {
        return L"EnvironmentVariables";
    }

    HRESULT EnvironmentVariableChangeTracker::TrackChange(std::function<HRESULT(void)> callback)
    {
        if (m_ShouldTrackChange)
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
                reinterpret_cast<const BYTE*>(m_Value.c_str()),
                static_cast<DWORD>((m_Value.size() + 1) * sizeof(wchar_t))));

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
