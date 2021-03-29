#pragma once
#include <EnvironmentManager.h>
#include "IChangeTracker.h"
#include <wil/registry.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class PathChangeTracker :
        public IChangeTracker
    {
    public:
        PathChangeTracker(std::wstring const& pathPart, EnvironmentManager::Scope scope);
        HRESULT TrackChange(std::function<HRESULT(void)> callBack);

    private:
        const std::wstring USER_EV_REG_LOCATION = L"Environment";
        const std::wstring MACHINE_EV_REG_LOCATION = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

        std::wstring m_PathPart;
        EnvironmentManager::Scope m_Scope;

        std::wstring KeyName();

        wil::unique_hkey GetKeyForTrackingChange()
        {
            std::wstringstream subKeyStream;
            subKeyStream << L"Software\\ChangeTracker\\";
            subKeyStream << KeyName();
            subKeyStream << L"\\";
            subKeyStream << m_PackageFullName;
            subKeyStream << "\\";

            if (m_Scope == EnvironmentManager::Scope::Process)
            {
                subKeyStream << L"Process";
            }
            else if (m_Scope == EnvironmentManager::Scope::User)
            {
                subKeyStream << L"User";
            }
            else
            {
                subKeyStream << L"Machine";
            }

            subKeyStream << "\\";

            auto subKeyIntermediate = subKeyStream.str();
            auto subKey = subKeyIntermediate.c_str();

            wil::unique_hkey keyToTrackChanges;
            if (m_Scope == EnvironmentManager::Scope::User
                || m_Scope == EnvironmentManager::Scope::Process)
            {
                LSTATUS getResult = RegCreateKeyEx(HKEY_CURRENT_USER
                    , subKey
                    , 0
                    , nullptr
                    , REG_OPTION_NON_VOLATILE
                    , KEY_ALL_ACCESS
                    , nullptr
                    , keyToTrackChanges.put()
                    , nullptr);

                if (getResult != ERROR_SUCCESS)
                {
                    THROW_HR(HRESULT_FROM_WIN32(getResult));
                }
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

        std::wstring GetChangesFromRegistry()
        {
            wil::unique_hkey regLocationToWriteChange = GetKeyForTrackingChange();
            DWORD sizeOfPathChanges;

            // See how big we need the buffer to be
            LSTATUS queryResult = RegQueryValueEx(regLocationToWriteChange.get(), L"AppendedValues", 0, nullptr, nullptr, &sizeOfPathChanges);

            if (queryResult == ERROR_FILE_NOT_FOUND)
            {
                return L"";
            }

            if (queryResult != ERROR_SUCCESS)
            {

                THROW_HR(HRESULT_FROM_WIN32((queryResult)));
            }


            wchar_t* pathChanges = new wchar_t[sizeOfPathChanges];
            THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(regLocationToWriteChange.get(), L"AppendedValues", 0, nullptr, (LPBYTE)pathChanges, &sizeOfPathChanges))));

            return std::wstring(pathChanges);
        }
    };
}

