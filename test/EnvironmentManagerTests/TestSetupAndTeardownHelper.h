#pragma once
#include "TestCommon.h"
#include "EnvironmentVariableHelper.h"
#include "ChangeTrackerHelper.h"

inline std::wstring processPath{};
inline std::wstring userPath{};
inline std::wstring machinePath{};

inline void RestoreUserPath(std::wstring originalPath)
{
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_pathName, 0, REG_EXPAND_SZ, (LPBYTE)originalPath.c_str(), static_cast<DWORD>(wcslen(originalPath.c_str()) * sizeof(wchar_t))));
}

inline void RestoreMachinePath(std::wstring originalPath)
{
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_pathName, 0, REG_EXPAND_SZ, (LPBYTE)originalPath.c_str(), static_cast<DWORD>(wcslen(originalPath.c_str()) * sizeof(wchar_t))));
}

inline void RestoreProcessPath(std::wstring originalPath)
{
    BOOL result{ ::SetEnvironmentVariable(L"Path", originalPath.c_str()) };

    if (result == 0)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void ProcessSetup()
{
    processPath = GetEnvironmentVariableForProcess(L"PATH");

    BOOL setResult{ SetEnvironmentVariable(c_evKeyName, c_evValueName) };

    if (!setResult)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void ProcessCleanup()
{
    RestoreProcessPath(processPath);
}

inline void UserSetup()
{
    userPath = GetEnvironmentVariableForUser(L"PATH");

    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_evKeyNameForGet, 0, REG_SZ, (LPBYTE)c_evValueName, static_cast<DWORD>((wcslen(c_evValueName) + 1) * sizeof(wchar_t))));
}

inline void UserCleanup()
{
    RestoreUserPath(userPath);
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    LSTATUS deleteResult = RegDeleteValueW(userEnvironmentVariablesHKey.get(), c_evKeyNameForGet);

    if (deleteResult != ERROR_SUCCESS && deleteResult != ERROR_FILE_NOT_FOUND)
    {
        FAILED(HRESULT_FROM_WIN32(deleteResult));
    }

    RemoveUserChangeTracking();
}

inline void MachineSetup()
{
    machinePath = GetEnvironmentVariableForMachine(L"PATH");
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_evKeyNameForGet, 0, REG_SZ, (LPBYTE)c_evValueName, static_cast<DWORD>((wcslen(c_evValueName) + 1) * sizeof(wchar_t))));
}

inline void MachineCleanup()
{
    RestoreMachinePath(machinePath);
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    LSTATUS deleteResult{ RegDeleteValueW(machineEnvironmentVariablesHKey.get(), c_evKeyNameForGet) };

    if (deleteResult != ERROR_SUCCESS && deleteResult != ERROR_FILE_NOT_FOUND)
    {
        FAILED(HRESULT_FROM_WIN32(deleteResult));
    }

    RemoveMachineChangeTracking();

}
