#pragma once
#include "IChangeTracker.h"
#include <EnvironmentManager.h>
#include <wil/registry.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PathExtChangeTracker : public IChangeTracker
    {

        PathExtChangeTracker(std::wstring const& pathExtPart, EnvironmentManager::Scope scope, PathOperation operation);
        HRESULT TrackChange(std::function<HRESULT(void)> callBack);


    private:
        EnvironmentManager::Scope m_Scope;
        std::wstring m_PathExtPart{};
        std::wstring KeyName();
        PathOperation m_Operation;

        wil::unique_hkey GetKeyForEnvironmentVariable()
        {
            FAIL_FAST_HR_IF(E_INVALIDARG, m_Scope == EnvironmentManager::Scope::Process);

            wil::unique_hkey environmentVariablesHKey{};
            if (m_Scope == EnvironmentManager::Scope::User)
            {
                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation.c_str(), 0, KEY_READ, environmentVariablesHKey.addressof())));
            }
            else //Scope is Machine
            {
                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation.c_str(), 0, KEY_READ, environmentVariablesHKey.addressof())));
            }

            return environmentVariablesHKey;
        }

        wil::unique_hkey GetKeyForTrackingChange(LPDWORD disposition)
        {
            HKEY topLevelKey{};

            if (m_Scope == EnvironmentManager::Scope::User)
            {
                topLevelKey = HKEY_CURRENT_USER;
            }
            else
            {
                topLevelKey = HKEY_LOCAL_MACHINE;
            }

            auto subKey{ wil::str_printf<wil::unique_cotaskmem_string>(
                L"Software\\ChangeTracker\\%ws\\%ws\\", KeyName().c_str(), m_PackageFullName.c_str()) };

            wil::unique_hkey keyToTrackChanges{};
            THROW_IF_FAILED(HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_CURRENT_USER,
                subKey.get(), 0, nullptr, REG_OPTION_NON_VOLATILE,
                KEY_ALL_ACCESS | KEY_WOW64_64KEY, nullptr, keyToTrackChanges.put(), disposition)));

            return keyToTrackChanges;
        }

        std::wstring GetValueFromTracking(std::wstring valueName)
        {
            wil::unique_hkey changeTrackingKey{ GetKeyForTrackingChange(nullptr) };
            DWORD sizeOfEnvironmentValue;

            // See how big we need the buffer to be
            LSTATUS queryResult{ RegQueryValueEx(changeTrackingKey.get(),
                valueName.c_str(), 0, nullptr, nullptr,
                &sizeOfEnvironmentValue) };

            if (queryResult != ERROR_SUCCESS)
            {
                if (queryResult == ERROR_FILE_NOT_FOUND)
                {
                    return L"";
                }

                THROW_HR(HRESULT_FROM_WIN32((queryResult)));
            }

            std::unique_ptr<wchar_t[]> environmentValue(new wchar_t[sizeOfEnvironmentValue]);
            THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(
                changeTrackingKey.get(), valueName.c_str(), 0, nullptr,
                (LPBYTE)environmentValue.get(),
                &sizeOfEnvironmentValue))));

            return std::wstring(environmentValue.get());
        }

        std::wstring QueryEvFromRegistry(std::wstring variableKey, HKEY KeyToOpen)
        {
            DWORD sizeOfEnvironmentValue;

            // See how big we need the buffer to be
            LSTATUS queryResult{ RegQueryValueEx(KeyToOpen,
                variableKey.c_str(), 0, nullptr, nullptr,
                &sizeOfEnvironmentValue) };

            if (queryResult != ERROR_SUCCESS)
            {
                if (queryResult == ERROR_FILE_NOT_FOUND)
                {
                    return L"";
                }

                THROW_HR(HRESULT_FROM_WIN32((queryResult)));
            }

            std::unique_ptr<wchar_t[]> environmentValue(new wchar_t[sizeOfEnvironmentValue]);
            THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(
                KeyToOpen, variableKey.c_str(), 0, nullptr,
                (LPBYTE)environmentValue.get(),
                &sizeOfEnvironmentValue))));

            return std::wstring(environmentValue.get());
        }
    };
}
