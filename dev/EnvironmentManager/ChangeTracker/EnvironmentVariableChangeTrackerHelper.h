#pragma once
#include <windows.h>
#include <wil/result.h>
#include <appmodel.h>

enum AreChangesTracked
{
    NOT_DEFINED,
    YES,
    NO
};

static AreChangesTracked areChangedTracked{};

static bool DoesChangeTrackingKeyExist()
{
    std::filesystem::path subKey = std::filesystem::path{ LR"(Software\Microsoft\AppModel\RegistryWriteVirtualization\ExcludedKeys\HKEY_CURRENT_USER/Software/ChangeTracker)" };
    wil::unique_hkey keyToChangeTracker{};
    LSTATUS openResult{ RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey.c_str(), 0, KEY_READ, keyToChangeTracker.put()) };
    if (openResult == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static std::wstring PackageFullName()
{
    WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
    UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
    const long getPackageFullNameRC{ ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName) };

    if (getPackageFullNameRC == APPMODEL_ERROR_NO_PACKAGE)
    {
        return {};
    }
    else if (getPackageFullNameRC == ERROR_SUCCESS)
    {
        return packageFullName;
    }
    else
    {
        THROW_WIN32(getPackageFullNameRC);
    }
}

// Technically process scoped changes aren't tracked because all changes are in memory only.
// Don't consider the process scope here because the changes will go away when the process exits.
static bool ShouldChangesBeTracked()
{
    if (areChangedTracked == NOT_DEFINED)
    {
        auto packageFullName{PackageFullName()};
        auto doesChangeTrackingKeyExist{ DoesChangeTrackingKeyExist };

        if (doesChangeTrackingKeyExist && !packageFullName.empty())
        {
            areChangedTracked = YES;
        }
        else
        {
            areChangedTracked = NO;
        }
    }

    if (areChangedTracked == YES)
    {
        return true;
    }
    else if (areChangedTracked == NO)
    {
        return false;
    }
    else
    {
        THROW_HR_MSG(E_UNEXPECTED, "areChangesTracked should been YES or NO at this point");
    }
}
