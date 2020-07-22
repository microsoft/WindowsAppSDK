# Sample 4 - LolzKitten Installer / Uninstaller with File+Registry LifetimeArtifacts

Contoso publishes 2 framework packages. The LolzKitten installer installs the framework packages and defines package dependency, and likewise reverts its work when uninstalled.

The 'muffins' package dependency definition is pinned until the specified file is deleted.

The 'waffles' package dependency definition is pinned until the specified registry key is deleted.

## Win32

```c++
#include <MsixDynamicDependency.hpp>
#include <wil/resource.h>

HRESULT SavePackageDependencyId(_In_ PCWSTR what, _In_ PCWSTR packageDependencyId);
HRESULT DeletePackageDependencyId(_In_ PCWSTR what);
HRESULT LoadPackageDependencyId(_In_ PCWSTR what, wil::unique_ptr<WCHAR[]>& packageDependencyId);
HRESULT DefinePackageDependencies();
HRESULT DefinePackageDependency_Muffins();
HRESULT DefinePackageDependency_Waffles();
PCWSTR GetMuffinsLifetimeAbsoluteFilename();
PCWSTR GetWafflesLifetimeRegistryKey();
HRESULT DeletePackageDependencyIds();

HRESULT Install()
{
    // Define the package dependency before installing it, just in case we're the 1st to install it.
    // If we did the reverse order (Install then Define) and we're unlucky, Windows might check if
    // the framework package is needed after it's installed but before the package dependency is
    // defined, determine it's not needed and remove it, causing us much grief :-(
    RETURN_IF_FAILED(DefinePackageDependencies());
    RETURN_IF_FAILED(InstallPackagesViaPackageManagerAddPackageAsync());
    return S_OK;
}

HRESULT Uninstall()
{
    RETURN_IF_FAILED(UndefinePackageDependency());
    RETURN_IF_FAILED(UninstallPackageDependency());
    return S_OK;
}

HRESULT DefinePackageDependencies()
{
    RETURN_IF_FAILED(DefinePackageDependency_Muffins());
    RETURN_IF_FAILED(DefinePackageDependency_Waffles());
    return S_OK;
}

HRESULT DefinePackageDependency_Muffins()
{
    PCWSTR packageFamilyName = L"Contoso.muffins_1234567890abc";
    PACKAGE_VERSION minVersion{};
    minVersion.Major = 87;
    minVersion.Minor = 0;
    minVersion.Build = 1234;
    minVersion.Revision = 567;
    const auto architectureFilter = MddPackageDependencyProcessorArchitectures::None;
    PCWSTR lifetimeArtifact = GetMuffinsLifetimeAbsoluteFilename();
    const UINT32 pinFlags = MddPinPackageDependency::DoNotVerifyDependencyResolution |
                            MddPinPackageDependency::LifecycleHint_FileOrPath;
    wil::unique_hlocal_string packageDependencyId;
    RETURN_IF_FAILED(MddPinPackageDependency(nullptr,
        packageFamilyName, minVersion, architecture, nullptr, pinFlags, &packageDependencyId));

    RETURN_IF_FAILED(SavePackageDependencyId(L"muffins", packageDependencyId.get()));
    return S_OK;
}

HRESULT DefinePackageDependency_Waffles()
{
    PCWSTR packageFamilyName = L"Contoso.puppies_1234567890abc";
    PACKAGE_VERSION minVersion{};
    minVersion.Major = 1;
    minVersion.Minor = 9;
    minVersion.Build = 67;
    minVersion.Revision = 0;
    const auto architectureFilter = MddPackageDependencyProcessorArchitectures::None;
    PCWSTR lifetimeArtifact = GetWafflesLifetimeRegistryKey();
    const UINT32 pinFlags = MddPinPackageDependency::DoNotVerifyDependencyResolution |
                            MddPinPackageDependency::LifecycleHint_RegistrySubkey;
    wil::unique_hlocal_string packageDependencyId;
    RETURN_IF_FAILED(MddPinPackageDependency(nullptr,
        packageFamilyName, minVersion, architecture, nullptr, pinFlags, &packageDependencyId));

    RETURN_IF_FAILED(SavePackageDependencyId(L"waffles", packageDependencyId.get()));
    return S_OK;
}

PCWSTR GetMuffinsLifetimeAbsoluteFilename()
{
    // MddPinPackageDependency::LifecycleHint_FileOrPath requires an absolute filename or path
    return "C:\\Program Files\\LolzKittens2020\\KittyKitty.exe";
}

PCWSTR GetWafflesLifetimeRegistryKey()
{
    // MddPinPackageDependency::LifecycleHint_RegistrySubkey requires a string
    // in the format 'root\\subkey' where root is one of the following: HKLM, HKCU, HKCR, HKU
    return "HKLM\\SOFTWARE\\LolzCatEnterprises\\LolzKitten\\PackageDependencies\\Contoso.puppies";
}

HRESULT DeletePackageDependencyIds()
{
    // No need to call MddUnpinPackageDependency() because we defined our package depedencies with
    // file and registry lifetime artifacts. The install will delete that file and registry key
    // so we only need to delete the package dependency ids we saved when we pinned the package dependencies

    LOG_IF_FAILED(DeletePackageDependencyId(L"muffins"));
    LOG_IF_FAILED(DeletePackageDependencyId(L"waffles"));
    return S_OK;
}

HRESULT SavePackageDependencyId(_In_ PCWSTR what, _In_ PCWSTR packageDependencyId)
{
    // Store the package dependency identifier for later use
}

HRESULT DeletePackageDependencyId(_In_ PCWSTR what)
{
    // Delete the previously stored package dependency identifier
}

HRESULT LoadPackageDependencyId(_In_ PCWSTR what, wil::unique_ptr<WCHAR[]>& packageDependencyId)
{
    // Load the previously stored package dependency identifier
}
```

## WinRT

```c#
using Microsoft.ProjectReunion.ApplicationModel
using Windows.ApplicationModel;

namespace LolzKitten
{
    public class Installer
    {
        public void Install()
        {
            // Define the package dependency before installing it, just in case we're the 1st to install it.
            // If we did the reverse order (Install then Define) and we're unlucky, Windows might check if
            // the framework package is needed after it's installed but before the package dependency is
            // defined, determine it's not needed and remove it, causing us much grief :-(
            DefinePackageDependencies();
            InstallPackagesViaPackageManagerAddPackageAsync();
        }

        public void Uninstall()
        {
            UndefinePackageDependency();
            UninstallPackageDependency();
        }

        void DefinePackageDependencies()
        {
            DefinePackageDependency_Muffins();
            DefinePackageDependency_Waffles();
        }

        void DefinePackageDependency_Muffins()
        {
            string packageFamilyName = L"Contoso.muffins_1234567890abc";
            PACKAGE_VERSION minVersion{};
            minVersion.Major = 87;
            minVersion.Minor = 0;
            minVersion.Build = 1234;
            minVersion.Revision = 567;
            var options = new PinPackageDependencyOptions(){
                DoNotVerifyDependencyResolution = true,
                LifetimeArtifactFileOrPath = MuffinsLifetimeAbsoluteFilename
            };
            PackageDependency packageDependency = PackageDependency.Pin(packageFamilyName, minVersion, options));

            SavePackageDependencyId(L"muffins", packageDependency.Id);
            return S_OK;
        }

        void DefinePackageDependency_Waffles()
        {
            string packageFamilyName = L"Contoso.puppies_1234567890abc";
            PACKAGE_VERSION minVersion;
            minVersion.Major = 1;
            minVersion.Minor = 9;
            minVersion.Build = 67;
            minVersion.Revision = 0;
            var options = new PinPackageDependencyOptions(){
                DoNotVerifyDependencyResolution = true,
                LifetimeArtifactFileOrPath = WafflesLifetimeRegistryKey
            };
            PackageDependency packageDependency = PackageDependency.Pin(packageFamilyName, minVersion, options));

            SavePackageDependencyId(L"waffles", packageDependency.Id);
            return S_OK;
        }

        string MuffinsLifetimeAbsoluteFilename
        {
            get
            {
                // MddPinPackageDependency::LifecycleHint_FileOrPath requires an absolute filename or path
                return @"C:\Program Files\LolzKittens2020\KittyKitty.exe";
            }
        }

        string WafflesLifetimeRegistryKey
        {
            get
            {
                // MddPinPackageDependency::LifecycleHint_RegistrySubkey requires a string
                // in the format 'root\subkey' where root is one of the following: HKLM, HKCU, HKCR, HKU
                return @"HKLM\SOFTWARE\LolzCatEnterprises\LolzKitten\PackageDependencies\Contoso.puppies";
            }
        }

        void DeletePackageDependencyIds()
        {
            // No need to call PackageDependency.Unpin() because we defined our package depedencies with
            // file and registry lifetime artifacts. The install will delete that file and registry key
            // so we only need to delete the package dependency ids we saved when we pinned the package dependencies

            DeletePackageDependencyId(L"muffins");
            DeletePackageDependencyId(L"waffles");
        }

        void SavePackageDependencyId(string what, string packageDependencyId)
        {
            // Store the package dependency identifier for later use
        }

        void DeletePackageDependencyId(string what)
        {
            // Delete the previously stored package dependency identifier
        }

        string LoadPackageDependencyId(string what)
        {
            // Load the previously stored package dependency identifier
        }
    }
}
```
