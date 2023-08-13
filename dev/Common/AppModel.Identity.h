// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __APPMODEL_IDENTITY_H
#define __APPMODEL_IDENTITY_H

#include <appmodel.h>

#include <memory>
#include <stdint>

namespace AppModel::Identity
{
inline bool IsPackagedProcess()
{
    UINT32 n{};
    const auto rc{ ::GetCurrentPackageFullName(&n, nullptr) };
    THROW_HR_IF_MSG(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER), "GetCurrentPackageFullName rc=%d", rc);
    return rc == ERROR_INSUFFICIENT_BUFFER;
}

constexpr winrt::Windows::System::ProcessorArchitecture GetCurrentArchitecture()
{
#if defined(_M_X64)
    return winrt::Windows::System::ProcessorArchitecture::X64;
#elif defined(_M_IX86)
    return winrt::Windows::System::ProcessorArchitecture::X86;
#elif defined(_M_ARM64)
    return winrt::Windows::System::ProcessorArchitecture::Arm64;
#elif defined(_M_ARM)
    return winrt::Windows::System::ProcessorArchitecture::Arm;
#else
#   error "Unknown processor architecture"
#endif
}

constexpr PCWSTR GetCurrentArchitectureAsString()
{
#if defined(_M_X64)
    return L"x64";
#elif defined(_M_IX86)
    return L"x86";
#elif defined(_M_ARM64)
    return L"arm64";
#elif defined(_M_ARM)
    return L"arm";
#else
#   error "Unknown processor architecture"
#endif
}

inline winrt::Windows::System::ProcessorArchitecture ParseArchitecture(_In_ PCWSTR architecture)
{
    if (CompareStringOrdinal(architecture, -1, L"x64", -1, TRUE) == CSTR_EQUAL)
    {
        return winrt::Windows::System::ProcessorArchitecture::X64;
    }
    else if (CompareStringOrdinal(architecture, -1, L"x86", -1, TRUE) == CSTR_EQUAL)
    {
        return winrt::Windows::System::ProcessorArchitecture::X86;
    }
    else if (CompareStringOrdinal(architecture, -1, L"arm64", -1, TRUE) == CSTR_EQUAL)
    {
    return winrt::Windows::System::ProcessorArchitecture::Arm64;
    }
    else if (CompareStringOrdinal(architecture, -1, L"arm", -1, TRUE) == CSTR_EQUAL)
    {
    return winrt::Windows::System::ProcessorArchitecture::Arm;
    }
    else
    {
        return winrt::Windows::System::ProcessorArchitecture::Unknown;
    }
}

constexpr PCWSTR GetCurrentArchitectureAsShortString()
{
#if defined(_M_X64)
    return L"x6";
#elif defined(_M_IX86)
    return L"x8";
#elif defined(_M_ARM64)
    return L"a6";
#elif defined(_M_ARM)
    return L"ar";
#else
#   error "Unknown processor architecture"
#endif
}

inline winrt::Windows::System::ProcessorArchitecture ParseShortArchitecture(_In_ PCWSTR architecture)
{
    if (CompareStringOrdinal(architecture, -1, L"x6", -1, TRUE) == CSTR_EQUAL)
    {
        return winrt::Windows::System::ProcessorArchitecture::X64;
    }
    else if (CompareStringOrdinal(architecture, -1, L"x8", -1, TRUE) == CSTR_EQUAL)
    {
        return winrt::Windows::System::ProcessorArchitecture::X86;
    }
    else if (CompareStringOrdinal(architecture, -1, L"a6", -1, TRUE) == CSTR_EQUAL)
    {
    return winrt::Windows::System::ProcessorArchitecture::Arm64;
    }
    else if (CompareStringOrdinal(architecture, -1, L"ar", -1, TRUE) == CSTR_EQUAL)
    {
    return winrt::Windows::System::ProcessorArchitecture::Arm;
    }
    else
    {
        return winrt::Windows::System::ProcessorArchitecture::Unknown;
    }
}

class PackageVersion : public PACKAGE_VERSION
{
public:
    PackageVersion()
    {
        Version = 0;
    }

    // Create an instance with the value `major.minor.build.revision`.
    PackageVersion(std::uint16_t major, std::uint16_t minor = 0, std::uint16_t build = 0, std::uint16_t revision = 0) :
        PACKAGE_VERSION()
    {
        Major = major;
        Minor = minor;
        Build = build;
        Revision = revision;
    }

    // Create an instance from a version as a uint64.
    PackageVersion(std::uint64_t version)
    {
        Version = version;
    }

// NOTE: There's no preprocessor symbol for Windows.ApplicationModel.PackageVersion
//       or Windows.ApplicationModel.h so test for Windows.ApplicationModel.IPackageId
//       as a close proxy for the ABI struct PackageVersion is defined.
#if defined(____x_ABI_CWindows_CApplicationModel_CIPackageId_INTERFACE_DEFINED__)
    PackageVersion(ABI::Windows::ApplicationModel::PackageVersion packageVersion) :
        PACKAGE_VERSION()
    {
        Major = packageVersion.Major;
        Minor = packageVersion.Minor;
        Build = packageVersion.Build;
        Revision = packageVersion.Revision;
    }
#endif // defined(____x_ABI_CWindows_CApplicationModel_CIPackageId_INTERFACE_DEFINED__)

#if defined(WINRT_Windows_ApplicationModel_2_H)
    PackageVersion(winrt::Windows::ApplicationModel::PackageVersion packageVersion) :
        PACKAGE_VERSION()
    {
        Major = packageVersion.Major();
        Minor = packageVersion.Minor();
        Build = packageVersion.Build();
        Revision = packageVersion.Revision();
    }
#endif // defined(WINRT_Windows_ApplicationModel_2_H)

    // Return the version as a uint64.
    std::uint64_t ToVersion() const
    {
        return Version;
    }

#if defined(____x_ABI_CWindows_CApplicationModel_CIPackageId_INTERFACE_DEFINED__)
    ABI::Windows::ApplicationModel::PackageVersion ToPackageVersion() const
    {
        return ABI::Windows::ApplicationModel::PackageVersion{ Major, Minor, Build, Revision };
    }
#endif // defined(____x_ABI_CWindows_CApplicationModel_CIPackageId_INTERFACE_DEFINED__)

#if defined(WINRT_Windows_ApplicationModel_2_H)
    winrt::Windows::ApplicationModel::PackageVersion ToWinrtPackageVersion() const
    {
        return winrt::Windows::ApplicationModel::PackageVersion{ Major, Minor, Build, Revision };
    }
#endif // defined(WINRT_Windows_ApplicationModel_2_H)

#if defined(_XSTRING_) && defined(_STRSAFE_H_INCLUDED_) && defined(WI_VERIFY)
    // Return the string as a formatted value "major.minor.build.revision".
    std::wstring ToString() const
    {
        return ToString(Major, Minor, Build, Revision);
    }

    static std::wstring ToString(std::uint16_t major, std::uint16_t minor, std::uint16_t build, std::uint16_t revision)
    {
        wchar_t formattedVersion[5 + 1 + 5 + 1 + 5 + 1 + 5 + 1]{};  // "12345.12345.12345.12345" + null-terminator
        WI_VERIFY(SUCCEEDED(StringCchPrintfW(formattedVersion, ARRAYSIZE(formattedVersion), L"%hu.%hu.%hu.%hu", major, minor, build, revision)));
        return std::wstring(formattedVersion);
    }
#endif defined(_XSTRING_) && defined(_STRSAFE_H_INCLUDED_) && defined(WI_VERIFY)
};

inline bool operator==(const PackageVersion& packageVersion1, const PackageVersion& packageVersion2)
{
    return packageVersion1.ToVersion() == packageVersion2.ToVesion();
}
inline bool operator!=(const PackageVersion& packageVersion1, const PackageVersion& packageVersion2)
{
    return packageVersion1.ToVersion() != packageVersion2.ToVesion();
}
inline bool operator<(const PackageVersion& packageVersion1, const PackageVersion& packageVersion2)
{
    return packageVersion1.ToVersion() < packageVersion2.ToVesion();
}
inline bool operator<=(const PackageVersion& packageVersion1, const PackageVersion& packageVersion2)
{
    return packageVersion1.ToVersion() <= packageVersion2.ToVesion();
}
inline bool operator>(const PackageVersion& packageVersion1, const PackageVersion& packageVersion2)
{
    return packageVersion1.ToVersion() > packageVersion2.ToVesion();
}
inline bool operator>=(const PackageVersion& packageVersion1, const PackageVersion& packageVersion2)
{
    return packageVersion1.ToVersion() >= packageVersion2.ToVesion();
}

inline bool IsValidVersionShortTag(
    const std::wstring& versionShortTag)
{
    // VersionShortTag must be "" or 1 ASCII letter optionally followed by 1 ASCII digit
    if (versionShortTag.empty())
    {
        return true;
    }

    const size_t c_maxVersionShortTagLength{ 2 };
    const auto versionShortTagLength{ versionShortTag.length() };
    if (versionShortTagLength > c_maxVersionShortTagLength)
    {
        return false;
    }
    const auto tagPrefix{ versionShortTag[0] };
    const auto isTagPrefixALetter{ (('a' <= tagPrefix) && (tagPrefix <= 'z')) ||
                                   (('A' <= tagPrefix) && (tagPrefix <= 'Z')) };
    if (!isTagPrefixALetter)
    {
        return false;
    }
    if (versionShortTagLength > 1)
    {
        const auto tagSuffix{ versionShortTag[1] };
        const auto isTagSuffixADigit{ ('0' <= tagSuffix) && (tagSuffix <= '9') };
        if (!isTagSuffixADigit)
        {
            return false;
        }
    }
    return true;
}

/// VersionShortTag = VersionTag[0] [+ VersionTag[last] if 0-9]
inline std::wstring GetVersionShortTagFromVersionTag(
    PCWSTR versionTag)
{
    std::wstring versionShortTag;
    if (versionTag && (versionTag[0] != L'\0'))
    {
        versionShortTag = versionTag[0];
        const auto versionTagLength{ wcslen(versionTag) };
        if (versionTagLength > 1)
        {
            auto lastCharInVersionTag{ versionTag[versionTagLength - 1] };
            if ((L'0' <= lastCharInVersionTag) && (lastCharInVersionTag <= '9'))
            {
                versionShortTag += lastCharInVersionTag;
            }
        }
        THROW_HR_IF_MSG(E_INVALIDARG, !IsValidVersionShortTag(versionShortTag.c_str()), "VersionTag=%ls", versionTag);
    }
    return versionShortTag;
}

/// Package Identity
class PackageIdentity
{
public:
    static PackageIdentity FromPackageFullName(PCWSTR packageFullName)
    {
        PackageIdentity packageIdentity;
        UINT32 bufferLength{ sizeof(packageIdentity.m_buffer) };
        THROW_IF_WIN32_ERROR(PackageIdFromFullName(packageFullName, PACKAGE_INFORMATION_BASIC, &bufferLength, packageIdentity.m_buffer));
        packageIdentity.m_packageId = reinterpret_cast<PACKAGE_ID*>(packageIdentity.m_buffer);
        packageIdentity.m_packageFullName = packageFullName;
        return packageIdentity;
    }

public:
    PackageIdentity() = default;

    PackageIdentity(PackageIdentity&& other) :
        m_packageFullName(std::move(other.m_packageFullName))
    {
        memcpy(m_buffer, other.m_buffer, sizeof(m_buffer));
        m_packageId = reinterpret_cast<PACKAGE_ID*>(m_buffer);

        other.m_packageId = nullptr;
        memset(other.m_buffer, 0, sizeof(other.m_buffer));
    }

    ~PackageIdentity() = default;

    PackageIdentity& operator=(PackageIdentity&& other)
    {
        if (this != &other)
        {
            m_packageFullName = std::move(other.m_packageFullName);
            memcpy(m_buffer, other.m_buffer, sizeof(m_buffer));
            m_packageId = reinterpret_cast<PACKAGE_ID*>(m_buffer);

            other.m_packageId = nullptr;
            memset(other.m_buffer, 0, sizeof(other.m_buffer));
        }
        return *this;
    }

    const std::wstring& PackageFullName() const
    {
        return m_packageFullName;
    }

    PCWSTR Name() const
    {
        return m_packageId->name;
    }

    PACKAGE_VERSION Version() const
    {
        return m_packageId->version;
    }

    winrt::Windows::System::ProcessorArchitecture Architecture() const
    {
        return static_cast<winrt::Windows::System::ProcessorArchitecture>(m_packageId->processorArchitecture);
    }

    PCWSTR ResourceId() const
    {
        return m_packageId->resourceId;
    }

    PCWSTR PublisherId() const
    {
        return m_packageId->publisherId;
    }

    explicit operator bool() const
    {
        return m_packageId != nullptr;
    }

private:
    std::wstring m_packageFullName;
    const PACKAGE_ID * m_packageId{};
    BYTE m_buffer[sizeof(PACKAGE_ID) + (PACKAGE_NAME_MAX_LENGTH + 1 +
                                        PACKAGE_RESOURCEID_MAX_LENGTH + 1 +
                                        PACKAGE_PUBLISHERID_MAX_LENGTH + 1) * sizeof(WCHAR)]{};
};
}

#endif // __APPMODEL_IDENTITY_H
