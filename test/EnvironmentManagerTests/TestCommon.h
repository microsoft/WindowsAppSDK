#pragma once
#include "pch.h"

inline constexpr PCWSTR c_userEvRegLocation = L"Environment";
inline constexpr PCWSTR c_machineEvRegLocation = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

inline constexpr PCWSTR c_evKeyName = L"TheBestTestKey";
inline constexpr PCWSTR c_evKeyNameForGet = L"TheBestTestKey2";
inline constexpr PCWSTR c_evValueName = L"TheBestTestValue";
inline constexpr PCWSTR c_evValueName2 = L"TheBestTestValue2";

inline constexpr PCWSTR c_packageFullName = L"TAEF.TailoredApplication.HostProcess_1.0.0.0_neutral_en-us_8wekyb3d8bbwe";

inline constexpr PCWSTR c_pathName = L"Path";

enum class ProcessRunLevel
{
    UntrustedIL,
    AppContainer,
    LegacyLowIL,
    Standard,
    Elevated
};

inline bool IsILAtOrAbove(ProcessRunLevel minimumIL)
{
    HANDLE processToken;
    VERIFY_WIN32_BOOL_SUCCEEDED(OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &processToken));

    auto mandatoryLabel = wil::get_token_information<TOKEN_MANDATORY_LABEL>(processToken);
    LONG levelRid = static_cast<SID*>(mandatoryLabel->Label.Sid)->SubAuthority[0];

    bool isExpectedRunLevel = false;
    switch (minimumIL)
    {
    case ProcessRunLevel::UntrustedIL:
        isExpectedRunLevel = levelRid >= SECURITY_MANDATORY_UNTRUSTED_RID;
        break;

    case ProcessRunLevel::AppContainer:
    case ProcessRunLevel::LegacyLowIL:
        isExpectedRunLevel = levelRid >= SECURITY_MANDATORY_LOW_RID;
        break;

    case ProcessRunLevel::Standard:
        isExpectedRunLevel = levelRid >= SECURITY_MANDATORY_MEDIUM_RID;
        break;

    case ProcessRunLevel::Elevated:
        isExpectedRunLevel = levelRid >= SECURITY_MANDATORY_HIGH_RID;
        break;

    default:
        VERIFY_FAIL(L"Unexpected ProcessRunLevel");
    }

    return isExpectedRunLevel;
}

inline std::wstring GetPackageFullName()
{
    // Check if we need to track the changes.
        // If we do need to track the changes get the Package Full Name
    UINT32 sizeOfBuffer{};
    long fullNameResult{ ::GetCurrentPackageFullName(&sizeOfBuffer, nullptr) };

    if (fullNameResult == ERROR_INSUFFICIENT_BUFFER)
    {
        std::unique_ptr<WCHAR> packageFullName(new WCHAR[sizeOfBuffer]);

        LONG getNameResult{ ::GetCurrentPackageFullName(&sizeOfBuffer, packageFullName.get()) };
        THROW_IF_WIN32_ERROR(getNameResult);
        return std::wstring{ packageFullName.get() };
    }
    else
    {
        THROW_HR(HRESULT_FROM_WIN32(fullNameResult));
    }
}
