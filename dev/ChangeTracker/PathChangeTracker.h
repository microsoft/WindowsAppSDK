#pragma once
#include <EnvironmentWriter.h>
#include <EnvironmentHelper.h>
#include "IChangeTracker.h"
#include <wil/registry.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class PathChangeTracker :
        public IChangeTracker
    {
    public:
        PathChangeTracker(std::wstring const& pathPart, Scope scope);
        HRESULT TrackChange(std::function<HRESULT(void)> callBack);

    private:
        const std::wstring USER_EV_REG_LOCATION = L"Environment";
        const std::wstring MACHINE_EV_REG_LOCATION = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

        std::wstring m_PathPart;
        Scope m_Scope;

        std::wstring KeyName();

        wil::unique_hkey GetKeyForTrackingChange()
        {
            FAIL_FAST_HR_IF(E_INVALIDARG, m_Scope == Scope::Process);

            HKEY topLevelKey{};

            if (m_Scope == Scope::User)
            {
                topLevelKey = HKEY_CURRENT_USER;
            }
            else
            {
                topLevelKey = HKEY_LOCAL_MACHINE;
            }

            auto subKey = wil::str_printf<wil::unique_cotaskmem_string>(
                L"Software\\ChangeTracker\\%ws\\%ws\\", KeyName().c_str(), m_PackageFullName.c_str());

            wil::unique_hkey keyToTrackChanges{};

            THROW_IF_FAILED(HRESULT_FROM_WIN32(RegCreateKeyEx(topLevelKey
                , subKey.get()
                , 0
                , nullptr
                , REG_OPTION_NON_VOLATILE
                , KEY_ALL_ACCESS
                , nullptr
                , keyToTrackChanges.put()
                , nullptr)));

            return keyToTrackChanges;
        }

        std::wstring GetPathChanges()
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

            std::unique_ptr<wchar_t[]> pathChanges(new wchar_t[sizeOfPathChanges]);
            THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(regLocationToWriteChange.get(), L"AppendedValues", 0, nullptr, (LPBYTE)pathChanges.get(), &sizeOfPathChanges))));

            return std::wstring(pathChanges.get());
        }
    };
}

