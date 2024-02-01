// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_DIAGNOSTICS_H
#define __WINDOWSAPPRUNTIME_TEST_DIAGNOSTICS_H

#include <WexTestClass.h>

#include <sddl.h>

#include <filesystem>

#include <wil\resource.h>
#include <wil\token_helpers.h>

#include <Security.IntegrityLevel.h>

namespace Test::Diagnostics
{
inline PCWSTR IntegrityLevelToString(DWORD integrityLevel)
{
    switch (integrityLevel)
    {
        case SECURITY_MANDATORY_UNTRUSTED_RID:          return L"Untrusted";
        case SECURITY_MANDATORY_LOW_RID:                return L"Low";
        case SECURITY_MANDATORY_MEDIUM_RID:             return L"Medium";
        case SECURITY_MANDATORY_MEDIUM_PLUS_RID:        return L"MediumPlus";
        case SECURITY_MANDATORY_HIGH_RID:               return L"High";
        case SECURITY_MANDATORY_SYSTEM_RID:             return L"System";
        case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:  return L"ProtectedProcess";
        default:                                        return L"???";
    }
}

inline void DumpUser(PCWSTR context, _In_ HANDLE token, PSID userSid)
{
    if (userSid)
    {
        wil::unique_hlocal_string userSidAsString;
        VERIFY_WIN32_BOOL_SUCCEEDED(ConvertSidToStringSidW(userSid, &userSidAsString));
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"UserSid:%s %s", context, userSidAsString.get()));

        const DWORD integrityLevel{ ::Security::IntegrityLevel::GetIntegrityLevel(token) };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"IntegrityLevel: 0x%08X (%s)", integrityLevel, IntegrityLevelToString(integrityLevel)));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"UserSid:%s null", context));
    }
}

inline void DumpExecutionContext()
{
    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
        DumpUser(L"Effective", GetCurrentThreadEffectiveToken(), tokenUser->User.Sid);
    }

    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentProcessToken()) };
        DumpUser(L"Process", GetCurrentProcessToken(), tokenUser->User.Sid);
    }

    const auto isAppContainer{ wil::get_token_is_app_container() };
    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"IsAppContainer:%s", isAppContainer ? L"True" : L"False"));

    WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
    UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
    const auto rc = ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName);
    if (rc == APPMODEL_ERROR_NO_PACKAGE)
    {
        WEX::Logging::Log::Comment(L"PackageFullName: <none>");
    }
    else if (rc == ERROR_SUCCESS)
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageFullName: %s", packageFullName));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetCurrentPackageFullName(): %d (0x%X)", rc, rc));
    }

    std::filesystem::path currentPath{ std::filesystem::current_path() };
    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"CurrentDirectory: %s", currentPath.c_str()));
}
}

#endif // __WINDOWSAPPRUNTIME_TEST_DIAGNOSTICS_H
