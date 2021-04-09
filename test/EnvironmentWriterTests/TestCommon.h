#pragma once
#include "pch.h"

inline constexpr PCWSTR c_userEvRegLocation = L"Environment";
inline constexpr PCWSTR c_machineEvRegLocation = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

inline constexpr PCWSTR c_evKeyName = L"TheBestTestKey";
inline constexpr PCWSTR c_evValueName = L"TheBestTestValue";
inline constexpr PCWSTR c_evValueName2 = L"TheBestTestValue2";

inline constexpr PCWSTR c_pathName = L"Path";

inline bool IsElevated()
{
    HANDLE tokenHandle;
    THROW_IF_WIN32_BOOL_FALSE(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &tokenHandle));

    TOKEN_ELEVATION elevation;
    DWORD dwSize = sizeof(TOKEN_ELEVATION);
    THROW_IF_WIN32_BOOL_FALSE(GetTokenInformation(tokenHandle, TokenElevation, &elevation, sizeof(elevation), &dwSize));


    return elevation.TokenIsElevated;
    //return wil::get_token_information<TOKEN_ELEVATION>(wil::open_current_access_token().get()).TokenIsElevated == TRUE;
}
