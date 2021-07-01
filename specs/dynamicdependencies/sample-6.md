# Sample 6 - LolzKitten Installer / Uninstaller defining a 32bit PackageDependency

Contoso publishes a framework package. At runtime, LolzKittens wants to use Contoso's functionality but requires a 32bit framework (regardless if LolzKittens is 32 or 64bit and regardless the machine's cpu). The LolzKitten installer defines a package dependency with an architecture filter to ensure this.

## Win32

```c++
#include <MsixDynamicDependency.h>
#include <wil/resource.h>

HRESULT Install();
HRESULT Defin32bitPackageDependency();
PCWSTR GetLifetimeFile();
HRESULT SavePackageDependencyId(_In_ PCWSTR packageDependencyId);

HRESULT Install()
{
    // Define the package dependency before installing it, just in case we're the 1st to install it.
    // If we did the reverse order (Install then Define) and we're unlucky, Windows might check if
    // the framework package is needed after it's installed but before the package dependency is
    // defined, determine it's not needed and remove it, causing us much grief :-(
    RETURN_IF_FAILED(Define32bitPackageDependency(lifetimeFile));
    RETURN_IF_FAILED(InstallPackageDependency());
    return S_OK;
}

HRESULT Define32bitPackageDependency()
{
    PCWSTR packageFamilyName = L"Contoso.muffins_1234567890abc";
    PACKAGE_VERSION minVersion{};
    minVersion.Major = 87;
    minVersion.Minor = 0;
    minVersion.Build = 1234;
    minVersion.Revision = 567;
    // Specify a MddPackageDependencyProcessorArchitectures filter to ensure the package dependnency
    // will only resolve to a 32-bit package regardless of the caller's bitness at runtime.
    const auto architectureFilter = MddPackageDependencyProcessorArchitectures::X86 |
        MddPackageDependencyProcessorArchitectures::Arm | MddPackageDependencyProcessorArchitectures::X86A64;
    const auto options = MddCreatePackageDependencyOptions::LifecycleHint_FileOrPath;
    wil::unique_process_heap_string packageDependencyId;
    RETURN_IF_FAILED(MddTryCreatePackageDependency(nullptr,
        packageFamilyName, minVersion, architecture, GetLifetimeFile(), options, &packageDependencyId));

    RETURN_IF_FAILED(SavePackageDependencyId(packageDependencyId.get()));
    return S_OK;
}

PCWSTR GetLifetimeFile()
{
    // MddCreatePackageDependencyOptions::LifecycleHint_FileOrPath requires an absolute filename or path
    return "C:\\Program Files\\LolzKittens2020\\KittyKitty.exe";
}

HRESULT SavePackageDependencyId(_In_ PCWSTR packageDependencyId)
{
    // Store the package dependency identifier for later use
}
```

## WinRT

```c#
using Microsoft.ApplicationModel.DynamicDependency;
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
            Define32bitPackageDependency(lifetimeFile);
            InstallPackageDependency();
        }

        void Define32bitPackageDependency()
        {
            string packageFamilyName = L"Contoso.muffins_1234567890abc";
            PACKAGE_VERSION minVersion{};
            minVersion.Major = 87;
            minVersion.Minor = 0;
            minVersion.Build = 1234;
            minVersion.Revision = 567;
            // Specify a PackageDependencyProcessorArchitectures filter to ensure the package dependnency
            // will only resolve to a 32-bit package regardless of the caller's bitness at runtime.
            var options = new CreatePackageDependencyOptions(){
                Architectures = PackageDependencyProcessorArchitectures.X86 |
                                PackageDependencyProcessorArchitectures.Arm |
                                PackageDependencyProcessorArchitectures.X86A64,
                DoNotVerifyDependencyResolution = true,
                LifetimeArtifactFileOrPath = MuffinsLifetimeAbsoluteFilename
            };
            PackageDependency packageDependency = PackageDependency.Create(packageFamilyName, minVersion, options));

            SavePackageDependencyId(L"muffins", packageDependency.Id);
        }

        string GetLifetimeFile
        {
            get
            {
                // MddCreatePackageDependencyOptions::LifecycleHint_FileOrPath requires an absolute filename or path
                return @"C:\Program Files\LolzKittens2020\KittyKitty.exe";
            }
        }

        void SavePackageDependencyId(string packageDependencyId)
        {
            // Store the package dependency identifier for later use
        }
    }
}
```
