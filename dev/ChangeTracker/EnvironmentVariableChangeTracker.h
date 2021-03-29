#pragma once
#include <EnvironmentManager.h>
#include "IChangeTracker.h"
#include <wil/registry.h>

using namespace winrt::Windows::Foundation::Collections;
namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct EnvironmentVariableChangeTracker : public IChangeTracker
    {
        EnvironmentVariableChangeTracker(std::wstring const& key, std::wstring const& valueToSet, EnvironmentManager::Scope scope);
        HRESULT TrackChange(std::function<HRESULT(void)> callBack);

    private:
        const std::wstring c_userEvRegLocation = L"Environment";
        const std::wstring c_machineEvRegLocation = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";


        EnvironmentManager::Scope m_Scope;
        std::wstring m_Key;
        std::wstring m_Value;

        std::wstring KeyName();

        wil::unique_hkey GetRegHKeyForEVUserAndMachineScope()
        {
            assert(m_Scope != EnvironmentManager::Scope::Process);

            wil::unique_hkey environmentVariablesHKey;
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

        wil::unique_hkey GetKeyForTrackingChange()
        {
            std::wstringstream subKeyStream;
            subKeyStream << L"Software\\ChangeTracker\\";
            subKeyStream << KeyName();
            subKeyStream << L"\\";
            subKeyStream << m_PackageFullName;
            subKeyStream << "\\";
            subKeyStream << m_Key;
            subKeyStream << "\\";

            if (m_Scope == EnvironmentManager::Scope::User)
            {
                subKeyStream << L"User";
            }
            else
            {
                subKeyStream << L"Machine";
            }

            subKeyStream << "\\";


            wil::unique_hkey keyToTrackChanges;
            if (m_Scope == EnvironmentManager::Scope::User)
            {
                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_CURRENT_USER
                    , subKeyStream.str().c_str()
                    , 0
                    , nullptr
                    , REG_OPTION_NON_VOLATILE
                    , KEY_ALL_ACCESS
                    , nullptr
                    , keyToTrackChanges.put()
                    , nullptr)));
            }
            else //Machine level scope
            {
                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_LOCAL_MACHINE
                    , subKeyStream.str().c_str()
                    , 0
                    , nullptr
                    , REG_OPTION_NON_VOLATILE
                    , KEY_WRITE
                    , nullptr
                    , keyToTrackChanges.put()
                    , nullptr)));
            }

            return keyToTrackChanges;
        }

        bool IsEVBeingCreated(HKEY keyToChangeTracker)
        {
            LSTATUS queryStatus = RegQueryValueEx(keyToChangeTracker, L"PreviousValue", 0, nullptr, nullptr, nullptr);

            if (queryStatus == ERROR_FILE_NOT_FOUND)
            {
                return true;
            }
            else if (queryStatus == ERROR_SUCCESS)
            {
                return false;
            }
            else
            {
                THROW_HR(HRESULT_FROM_WIN32(queryStatus));
            }


        }

        std::wstring GetOriginalValueOfEV()
        {
            wil::unique_hkey environmentVariableHKey = GetRegHKeyForEVUserAndMachineScope();
            return QueryEvFromRegistry(m_Key, environmentVariableHKey.get());
        }

        std::wstring QueryEvFromRegistry(std::wstring variableKey, HKEY KeyToOpen)
        {
            DWORD sizeOfEnvironmentValue;

            // See how big we need the buffer to be
            LSTATUS queryResult = RegQueryValueEx(KeyToOpen, variableKey.c_str(), 0, nullptr, nullptr, &sizeOfEnvironmentValue);

            if (queryResult != ERROR_SUCCESS)
            {
                if (queryResult == ERROR_FILE_NOT_FOUND)
                {
                    return L"";
                }

                THROW_HR(HRESULT_FROM_WIN32((queryResult)));
            }

            std::unique_ptr<wchar_t[]> environmentValue(new wchar_t[sizeOfEnvironmentValue]);
            THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(KeyToOpen, variableKey.c_str(), 0, nullptr, (LPBYTE)environmentValue.get(), &sizeOfEnvironmentValue))));

            return std::wstring(environmentValue.get());
        }
    };
}
