#pragma once
#include "TestCommon.h"
#include "EnvironmentVariableHelper.h"
#include "ChangeTrackerHelper.h"

inline std::wstring processPath{};
inline std::wstring processPathExt{};

inline std::wstring userPath{};
inline std::wstring userPathExt{};

inline std::wstring machinePath{};
inline std::wstring machinePathExt{};

inline void RestoreUserPath(std::wstring originalPath)
{
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_pathName, 0, REG_EXPAND_SZ, (LPBYTE)originalPath.c_str(), static_cast<DWORD>(wcslen(originalPath.c_str()) * sizeof(wchar_t))));
}

inline void RestoreUserPathExt(std::wstring originalPathExt)
{
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_pathExtName, 0, REG_EXPAND_SZ, (LPBYTE)originalPathExt.c_str(), static_cast<DWORD>(wcslen(originalPathExt.c_str()) * sizeof(wchar_t))));
}

inline void RestoreMachinePath(std::wstring originalPath)
{
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_pathName, 0, REG_EXPAND_SZ, (LPBYTE)originalPath.c_str(), static_cast<DWORD>(wcslen(originalPath.c_str()) * sizeof(wchar_t))));
}

inline void RestoreMachinePathExt(std::wstring originalPathExt)
{
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_pathExtName, 0, REG_EXPAND_SZ, (LPBYTE)originalPathExt.c_str(), static_cast<DWORD>(wcslen(originalPathExt.c_str()) * sizeof(wchar_t))));
}

inline void RestoreProcessPath(std::wstring originalPath)
{
    BOOL result{ ::SetEnvironmentVariable(c_pathName, originalPath.c_str()) };

    if (result == 0)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void RestoreProcessPathExt(std::wstring originalPathExt)
{
    BOOL result{ ::SetEnvironmentVariable(c_pathExtName, originalPathExt.c_str()) };

    if (result == 0)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void ProcessSetup()
{
    processPath = GetEnvironmentVariableForProcess(c_pathName);

    processPathExt = GetEnvironmentVariableForProcess(c_pathExtName);

    BOOL setResult{ SetEnvironmentVariable(c_evKeyName, c_evValueName) };

    if (!setResult)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void ProcessCleanup()
{
    RestoreProcessPath(processPath);
    RestoreProcessPathExt(processPathExt);
}

inline void UserSetup()
{
    userPath = GetEnvironmentVariableForUser(c_pathName);

    userPathExt = GetEnvironmentVariableForUser(c_pathExtName);

    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_evKeyNameForGet, 0, REG_SZ, (LPBYTE)c_evValueName, static_cast<DWORD>((wcslen(c_evValueName) + 1) * sizeof(wchar_t))));
}

inline void UserCleanup()
{
    RestoreUserPath(userPath);
    RestoreUserPathExt(userPathExt);
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
    machinePath = GetEnvironmentVariableForMachine(c_pathName);

    machinePathExt = GetEnvironmentVariableForMachine(c_pathExtName);

    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_evKeyNameForGet, 0, REG_SZ, (LPBYTE)c_evValueName, static_cast<DWORD>((wcslen(c_evValueName) + 1) * sizeof(wchar_t))));
}

inline void MachineCleanup()
{
    RestoreMachinePath(machinePath);
    RestoreMachinePathExt(machinePathExt);
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    LSTATUS deleteResult{ RegDeleteValueW(machineEnvironmentVariablesHKey.get(), c_evKeyNameForGet) };

    if (deleteResult != ERROR_SUCCESS && deleteResult != ERROR_FILE_NOT_FOUND)
    {
        FAILED(HRESULT_FROM_WIN32(deleteResult));
    }

    RemoveMachineChangeTracking();
}
