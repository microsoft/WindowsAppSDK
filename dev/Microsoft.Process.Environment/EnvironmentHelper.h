#pragma once
#include "pch.h"

constexpr PCWSTR USER_EV_REG_LOCATION = L"Environment";
constexpr PCWSTR MACHINE_EV_REG_LOCATION = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

enum Scope
{
    Process = 0,
    User = 1,
    Machine = 2
};

inline std::wstring GetProcessEnvironmentVariable(const std::wstring variableName)
{
    // Get the size of the buffer.
    DWORD sizeNeededInCharacters = ::GetEnvironmentVariable(variableName.c_str(), nullptr, 0);

    // If we got an error
    if (sizeNeededInCharacters == 0)
    {
        DWORD lastError = GetLastError();

        if (lastError == ERROR_ENVVAR_NOT_FOUND)
        {
            return L"";
        }
        else
        {
            THROW_HR(HRESULT_FROM_WIN32(lastError));
        }
    }

    std::wstring environmentVariableValue{};

    environmentVariableValue.resize(sizeNeededInCharacters - 1);
    DWORD getResult = ::GetEnvironmentVariable(variableName.c_str(), &environmentVariableValue[0], sizeNeededInCharacters);

    if (getResult == 0)
    {
        THROW_HR(HRESULT_FROM_WIN32(GetLastError()));
    }

    return environmentVariableValue;
}

inline wil::unique_hkey GetRegHKeyForEVUserAndMachineScope(Scope scope, bool needsWriteAccess = false)
{
    FAIL_FAST_HR_IF(E_INVALIDARG, scope == Scope::Process);

    REGSAM registrySecurity = KEY_READ;

    if (needsWriteAccess)
    {
        registrySecurity |= KEY_WRITE;
    }

    wil::unique_hkey environmentVariablesHKey;
    if (scope == Scope::User)
    {
        THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER, USER_EV_REG_LOCATION, 0, registrySecurity, environmentVariablesHKey.addressof())));
    }
    else //Scope is Machine
    {
        THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_LOCAL_MACHINE, MACHINE_EV_REG_LOCATION, 0, registrySecurity, environmentVariablesHKey.addressof())));
    }

    return environmentVariablesHKey;
}

inline std::wstring GetUserOrMachineEnvironmentVariable(Scope scope, const std::wstring variableName)
{
    wil::unique_hkey environmentVariableHKey = GetRegHKeyForEVUserAndMachineScope(scope);

    DWORD sizeOfEnvironmentValue;

    // See how big we need the buffer to be
    LSTATUS queryResult = RegQueryValueEx(environmentVariableHKey.get(), variableName.c_str(), 0, nullptr, nullptr, &sizeOfEnvironmentValue);

    if (queryResult != ERROR_SUCCESS)
    {
        if (queryResult == ERROR_FILE_NOT_FOUND)
        {
            return L"";
        }

        THROW_HR(HRESULT_FROM_WIN32((queryResult)));
    }

    std::unique_ptr<wchar_t[]> environmentValue(new wchar_t[sizeOfEnvironmentValue]);
    THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(environmentVariableHKey.get(), variableName.c_str(), 0, nullptr, (LPBYTE)environmentValue.get(), &sizeOfEnvironmentValue))));

    return std::wstring(environmentValue.get());
}
