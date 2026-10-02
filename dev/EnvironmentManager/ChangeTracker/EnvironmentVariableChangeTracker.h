// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once
#include "IChangeTracker.h"
#include <Microsoft.Windows.System.EnvironmentManager.h>
#include <Filesystem>
#include <wil/registry.h>

using namespace winrt::Windows::Foundation::Collections;
namespace winrt::Microsoft::Windows::System::implementation
{
    struct EnvironmentVariableChangeTracker : public IChangeTracker
    {
        EnvironmentVariableChangeTracker(const std::wstring& key, const std::wstring& valueToSet, EnvironmentManager::Scope scope);
        HRESULT TrackChange(std::function<HRESULT(void)> callBack);

    private:
        EnvironmentManager::Scope m_Scope;
        std::wstring m_Key;
        std::wstring m_Value;

        PCWSTR KeyName() const;

        wil::unique_hkey GetKeyForEnvironmentVariable() const
        {
            FAIL_FAST_HR_IF(E_INVALIDARG, m_Scope == EnvironmentManager::Scope::Process);

            wil::unique_hkey environmentVariablesHKey{};
            if (m_Scope == EnvironmentManager::Scope::User)
            {
                THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation.c_str(), 0, KEY_READ, environmentVariablesHKey.addressof()));
            }
            else //Scope is Machine
            {
                THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation.c_str(), 0, KEY_READ, environmentVariablesHKey.addressof()));
            }

            return environmentVariablesHKey;
        }

        wil::unique_hkey GetKeyForTrackingChange(DWORD* disposition) const
        {
            std::filesystem::path subKey = std::filesystem::path{L"Software\\ChangeTracker"}
            / KeyName() / m_PackageFullName / ScopeToString() / m_Key;

            wil::unique_hkey keyToTrackChanges{};
            THROW_IF_WIN32_ERROR(RegCreateKeyEx(HKEY_CURRENT_USER,
                subKey.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE,
                KEY_ALL_ACCESS | KEY_WOW64_64KEY, nullptr, keyToTrackChanges.put(), disposition));

            return keyToTrackChanges;
        }

        std::wstring GetOriginalValueOfEV() const
        {
            wil::unique_hkey environmentVariableHKey{ GetKeyForEnvironmentVariable() };
            return QueryEvFromRegistry(m_Key, environmentVariableHKey.get());
        }

        std::wstring QueryEvFromRegistry(const std::wstring& variableKey, const HKEY KeyToOpen) const
        {
            DWORD sizeOfEnvironmentValue{};

            // See how big we need the buffer to be
            LSTATUS queryResult{ RegQueryValueEx(KeyToOpen,
                variableKey.c_str(), 0, nullptr, nullptr,
                &sizeOfEnvironmentValue) };

            if (queryResult != ERROR_SUCCESS)
            {
                if (queryResult == ERROR_FILE_NOT_FOUND)
                {
                    return {};
                }

                THROW_WIN32(queryResult);
            }

            std::unique_ptr<wchar_t[]> environmentValue(new wchar_t[sizeOfEnvironmentValue]);
            THROW_IF_WIN32_ERROR(RegQueryValueEx(
                KeyToOpen, variableKey.c_str(), 0, nullptr,
                reinterpret_cast<BYTE*>(environmentValue.get()),
                &sizeOfEnvironmentValue));

            return std::wstring(environmentValue.get());
        }

        std::wstring ScopeToString() const
        {
            if (m_Scope == EnvironmentManager::Scope::Process)
            {
                return L"process";
            }
            else if (m_Scope == EnvironmentManager::Scope::User)
            {
                return L"user";
            }
            else
            {
                return L"machine";
            }
        }
    };
}
