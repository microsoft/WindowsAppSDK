#pragma once
#include <windows.h>
#include <wil/result.h>
#include <appmodel.h>
#include <Microsoft.Windows.System.EnvironmentManager.h>

using namespace winrt::Microsoft::Windows::System::implementation;

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

inline bool ShouldChangesBeTracked(EnvironmentManager::Scope scope)
{
    auto packageFullName{ PackageFullName() };
    auto doesChangeTrackingKeyExist{ DoesChangeTrackingKeyExist };
    auto isUserOrMachineScope{ scope != EnvironmentManager::Scope::Process };

    if (doesChangeTrackingKeyExist &&
        !packageFullName.empty() &&
        isUserOrMachineScope)
    {
        return true;
    }
    else
    {
        return false;
    }
}
