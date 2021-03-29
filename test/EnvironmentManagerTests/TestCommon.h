#pragma once
#include "pch.h"

inline constexpr PCWSTR c_userEvRegLocation = L"Environment";
inline constexpr PCWSTR c_machineEvRegLocation = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

inline constexpr PCWSTR c_evKeyName = L"TestKey";
inline constexpr PCWSTR c_evValueName = L"TestValue";

inline constexpr PCWSTR c_evKeyName2 = L"TestKey2";
inline constexpr PCWSTR c_evValueName2 = L"TestValue2";

inline constexpr PCWSTR c_pathName = L"Path";

inline const std::wstring c_trackerKeyLocationForUser()
{
    return std::wstring(L"EnvironmentVariables\\Microsoft.Process.Environment.Centennial.Tests_1.0.0.0_neutral_en-us_8wekyb3d8bbwe\\")
        .append(c_evKeyName2)
        .append(std::wstring(L"\\User"));
}

inline const std::wstring c_trackerKeyLocationForMachine()
{
    return std::wstring(L"EnvironmentVariables\\Microsoft.Process.Environment.Centennial.Tests_1.0.0.0_neutral_en-us_8wekyb3d8bbwe\\")
        .append(c_evKeyName2)
        .append(std::wstring(L"\\Machine"));
}
