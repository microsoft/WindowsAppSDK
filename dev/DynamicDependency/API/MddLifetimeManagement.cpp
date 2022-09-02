// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "MddLifetimeManagement.h"
#include "MddLifetimeManagementTest.h"

static std::wstring g_test_ddlmPackageNamePrefix;
static std::wstring g_test_ddlmPackagePublisherId;

STDAPI MddLifetimeManagementTestInitialize(
    _In_ PCWSTR ddlmPackageNamePrefix,
    _In_ PCWSTR ddlmPackagePublisherId) noexcept try
{
    RETURN_HR_IF(E_INVALIDARG, !ddlmPackageNamePrefix);
    RETURN_HR_IF(E_INVALIDARG, *ddlmPackageNamePrefix == L'0');
    RETURN_HR_IF(E_INVALIDARG, !ddlmPackagePublisherId);
    RETURN_HR_IF(E_INVALIDARG, *ddlmPackagePublisherId == L'0');

    g_test_ddlmPackageNamePrefix = ddlmPackageNamePrefix;
    g_test_ddlmPackagePublisherId = ddlmPackagePublisherId;
    return S_OK;
} CATCH_RETURN();

namespace MddCore::LifetimeManagement
{
class DDLMPackage
{
public:
    DDLMPackage(
        const std::wstring& packageFullName,
        PACKAGE_VERSION version) :
        m_packageFullName(packageFullName),
        m_version(version)
    {
    }

    constexpr bool operator>(const DDLMPackage& rhs) const
    {
        return m_version.Version > rhs.m_version.Version;
    }

    const std::wstring& PackageFullName() const
    {
        return m_packageFullName;
    }

    void RemovePackage(
        const winrt::Windows::Management::Deployment::PackageManager& packageManager) const
    {
        try
        {
            auto deploymentResult{ packageManager.RemovePackageAsync(m_packageFullName.c_str()).get() };
            if (!deploymentResult)
            {
                const HRESULT hr{ deploymentResult.ExtendedErrorCode() };
                if (hr == HRESULT_FROM_WIN32(ERROR_PACKAGES_IN_USE))
                {
                    (void) LOG_HR_MSG(deploymentResult.ExtendedErrorCode(), "RemovePackage('%ls') = 0x%0X %ls. Will try again later", m_packageFullName.c_str(), deploymentResult.ExtendedErrorCode().value, deploymentResult.ErrorText().c_str());
                }
                else
                {
                    (void) LOG_HR_MSG(deploymentResult.ExtendedErrorCode(), "RemovePackage('%ls') = 0x%0X %ls", m_packageFullName.c_str(), deploymentResult.ExtendedErrorCode().value, deploymentResult.ErrorText().c_str());
                }
            }
        }
        catch (...)
        {
            const auto e{ winrt::hresult_error(winrt::to_hresult(), winrt::take_ownership_from_abi) };
            const auto hr{ e.code() };
            const auto message { e.message() };
            (void) LOG_HR_MSG(hr, "%ls PackageFullName:%ls", message.c_str(), m_packageFullName.c_str());
        }
    }

private:
    std::wstring m_packageFullName;
    PACKAGE_VERSION m_version{};
};
}

STDAPI MddLifetimeManagementGC() noexcept try
{
    // Enumerate for all DynamicDependency Lifetime Management (DDLM) packages and remove redundantly unnecessary packages
    // 1. Same MAJOR.MINOR version (breaking change boundary)
    // 2. Same architecture
    //
    // For each permutation of 1+2 if 2+ package are found determine the 'best match' to keep. Other packages found
    // with a version less than the 'best match' are redundant and can be removed.
    //
    // Don't remove pacakges in use. We can't determine if a package is in-use but Windows can.
    // Attempting to remove a package in-use will fail with HRESULT_FROM_WIN32(ERROR_PACKAGES_IN_USE).
    // Treat that as a non-error.
    //
    // We have no direct way to determine all DDLM packages so we'll enumerate each possible MAJOR version
    // up to a reasonable maximum. This is a maintenance type API not needed in hot paths so the minor cost
    // to ask for a few potential future versions with no matches isn't a performance concern.

    // Create a PackageManager instance for use across all calls
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    winrt::hstring currentUser;

    const UINT16 c_majorMinorVersions[][3]{ // [n] = { Major, minMinor, maxMinor }
        { 0, 8, 9 },
        { 1, 0, 2 }
    };
    for (auto majorMinorVersion : c_majorMinorVersions)
    {
        const UINT16 majorVersion{ static_cast<UINT16>(majorMinorVersion[0]) };
        const UINT16 minMinorVersion{ static_cast<UINT16>(majorMinorVersion[1]) };
        const UINT16 maxMinorVersion{ static_cast<UINT16>(majorMinorVersion[2]) };
        for (UINT32 minorVersion=minMinorVersion; minorVersion <= maxMinorVersion; ++minorVersion)
        {
            PCWSTR c_shortArchitectures[]{ L"x6", L"x8", L"a6" };
            for (auto shortArchitecture : c_shortArchitectures)
            {
                // Build the list of DDLMs
                std::vector<MddCore::LifetimeManagement::DDLMPackage> ddlmPackages;

                // Look for windows.appExtension with name="microsoft.winappruntime.ddlm-<majorversion>.<minorversion>-<shortarchitecture>[-shorttag]"
                // NOTE: We don't support VersionTag (i.e. we only support 'Stable' versions)
                WCHAR appExtensionName[100]{};
                wsprintf(appExtensionName, L"microsoft.winappruntime.ddlm-%hu.%hu-%s", majorVersion, minorVersion, shortArchitecture);

                auto catalog{ winrt::Windows::ApplicationModel::AppExtensions::AppExtensionCatalog::Open(appExtensionName) };
                auto appExtensions{ catalog.FindAllAsync().get() };
                for (auto appExtension : appExtensions)
                {
                    // Check the package identity against the package identity test qualifiers (if any)
                    if (!g_test_ddlmPackageNamePrefix.empty())
                    {
                        const auto packageId{ appExtension.Package().Id() };
                        std::wstring name{ packageId.Name().c_str() };
                        if ((name.rfind(g_test_ddlmPackageNamePrefix.c_str(), 0) != 0) ||
                            (CompareStringOrdinal(packageId.PublisherId().c_str(), -1, g_test_ddlmPackagePublisherId.c_str(), -1, TRUE) != CSTR_EQUAL))
                        {
                            // The package's Name prefix or PublisherId don't match the expected value. Skip it
                            continue;
                        }
                    }

                    // appExtension.Id == "ddlm-<major.minor.build.revision>-<architecture>"
                    const auto id{ appExtension.Id() };
                    PACKAGE_VERSION version{};
                    WCHAR architectureAsString[9 + 1]{};
                    const auto maxIdLength{ ARRAYSIZE(L"ddlm-12345.12345.12345.12345-abcdefghi") - 1 }; // -1 for length not counting null-terminator
                    if ((id.size() >= maxIdLength) ||
                        (swscanf_s(id.c_str(), L"ddlm-%hu.%hu.%hu.%hu-%9s", &version.Major, &version.Minor, &version.Build, &version.Revision, architectureAsString, static_cast<unsigned>(ARRAYSIZE(architectureAsString))) != 5))
                    {
                        (void)LOG_WIN32_MSG(ERROR_INVALID_DATA, "%ls", id.c_str());
                        continue;
                    }

                    // Found one
                    auto packageFullName{ appExtension.Package().Id().FullName().c_str() };
                    ddlmPackages.push_back(MddCore::LifetimeManagement::DDLMPackage(packageFullName, version));
                }

                // Did we find more than one?
                if (ddlmPackages.size() <= 1)
                {
                    // Nothing to remove
                    continue;
                }

                // Sort the list by version in descending order to simplify using it
                std::sort(ddlmPackages.begin(), ddlmPackages.end(), std::greater<MddCore::LifetimeManagement::DDLMPackage>());

                // What's the highest version with a healthy status
                auto keeper{ ddlmPackages.begin() };
                for (; keeper != ddlmPackages.end(); ++keeper)
                {
                    auto package{ packageManager.FindPackageForUser(currentUser, keeper->PackageFullName()) };
                    auto status{ package.Status() };
                    if (status.VerifyIsOK())
                    {
                        break;
                    }
                }

                // Remove all older packages (best effort)
                for (++keeper; keeper != ddlmPackages.end(); ++keeper)
                {
                    keeper->RemovePackage(packageManager);
                }
            }
        }
    }
    return S_OK;
}
CATCH_RETURN();
