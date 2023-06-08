// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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

inline void InstallPackage(const std::wstring& packagePath)
{
    // Deploy packaged app to register handler through the manifest.
    winrt::Windows::Management::Deployment::PackageManager manager;
    IVector<winrt::Windows::Foundation::Uri> depPackagePaths;
    auto result = manager.AddPackageAsync(winrt::Windows::Foundation::Uri(packagePath), depPackagePaths,
        winrt::Windows::Management::Deployment::DeploymentOptions::ForceApplicationShutdown).get();
    auto errorText = result.ErrorText();
    auto errorCode = result.ExtendedErrorCode();
    VERIFY_SUCCEEDED(errorCode, errorText.c_str());
}

inline void RestoreUserPath(std::wstring originalPath)
{
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_PathName, 0, REG_EXPAND_SZ, (LPBYTE)originalPath.c_str(), static_cast<DWORD>(wcslen(originalPath.c_str()) * sizeof(wchar_t))));
}

inline void RestoreUserPathExt(std::wstring originalPathExt)
{
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_PathExtName, 0, REG_EXPAND_SZ, (LPBYTE)originalPathExt.c_str(), static_cast<DWORD>(wcslen(originalPathExt.c_str()) * sizeof(wchar_t))));
}

inline void RestoreMachinePath(std::wstring originalPath)
{
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_PathName, 0, REG_EXPAND_SZ, (LPBYTE)originalPath.c_str(), static_cast<DWORD>(wcslen(originalPath.c_str()) * sizeof(wchar_t))));
}

inline void RestoreMachinePathExt(std::wstring originalPathExt)
{
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_PathExtName, 0, REG_EXPAND_SZ, (LPBYTE)originalPathExt.c_str(), static_cast<DWORD>(wcslen(originalPathExt.c_str()) * sizeof(wchar_t))));
}

inline void RestoreProcessPath(std::wstring originalPath)
{
    BOOL result{ ::SetEnvironmentVariable(c_PathName, originalPath.c_str()) };

    if (result == 0)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void RestoreProcessPathExt(std::wstring originalPathExt)
{
    BOOL result{ ::SetEnvironmentVariable(c_PathExtName, originalPathExt.c_str()) };

    if (result == 0)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void ProcessSetup()
{
    processPath = GetEnvironmentVariableForProcess(c_PathName);

    processPathExt = GetEnvironmentVariableForProcess(c_PathExtName);

    BOOL setResult{ SetEnvironmentVariable(c_EvKeyName, c_EvValueName) };

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
    userPath = GetEnvironmentVariableForUser(c_PathName);

    userPathExt = GetEnvironmentVariableForUser(c_PathExtName);

    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_EvKeyNameForGet, 0, REG_SZ, (LPBYTE)c_EvValueName, static_cast<DWORD>((wcslen(c_EvValueName) + 1) * sizeof(wchar_t))));
}

inline void UserCleanup()
{
    RestoreUserPath(userPath);
    RestoreUserPathExt(userPathExt);
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    LSTATUS deleteResult = RegDeleteValueW(userEnvironmentVariablesHKey.get(), c_EvKeyNameForGet);

    if (deleteResult != ERROR_SUCCESS && deleteResult != ERROR_FILE_NOT_FOUND)
    {
        FAILED(HRESULT_FROM_WIN32(deleteResult));
    }

    RemoveUserChangeTracking();
}

inline void MachineSetup()
{
    machinePath = GetEnvironmentVariableForMachine(c_PathName);

    machinePathExt = GetEnvironmentVariableForMachine(c_PathExtName);

    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_EvKeyNameForGet, 0, REG_SZ, (LPBYTE)c_EvValueName, static_cast<DWORD>((wcslen(c_EvValueName) + 1) * sizeof(wchar_t))));
}

inline void MachineCleanup()
{
    RestoreMachinePath(machinePath);
    RestoreMachinePathExt(machinePathExt);
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    LSTATUS deleteResult{ RegDeleteValueW(machineEnvironmentVariablesHKey.get(), c_EvKeyNameForGet) };

    if (deleteResult != ERROR_SUCCESS && deleteResult != ERROR_FILE_NOT_FOUND)
    {
        FAILED(HRESULT_FROM_WIN32(deleteResult));
    }

    RemoveMachineChangeTracking();
}
