# Sample 1 - Fabrikam app using Contosso's Muffins package

Contoso publishes a framework package that provides Muffin-managing functionality. At runtime, Fabrikam wants to use this functionality if available, so it adds a dynamic dependency for the Contoso.Muffins package. The dynamic dependency is removed once Fabrikam is done using the Contoso Muffin-managing functionality.

```MddPinPackageDependency``` will fail if there are no packages registered to the user that satisfy the PackageDependency.

## Win32

```c++
#include <MsixDynamicDependency.hpp>
#include <wil/resource.h>

HRESULT ManageMuffins(int& countOfMuffinsManaged)
{
    countOfMuffinsManaged = 0;

    // Create a PackageDependency to pin the Contosso Muffin package
    // Fail if the PackageDependency cannot be resolved
    PCWSTR packageFamilyName = L"Contoso.muffins_1234567890abc";
    PACKAGE_VERSION minVersion{};
    minVersion.Major = 87;
    minVersion.Minor = 0;
    minVersion.Build = 1234;
    minVersion.Revision = 567;
    const auto architectureFilter = MddPackageDependencyProcessorArchitectures::None;
    const UINT32 pinFlags = MddPinPackageDependency::LifecycleHint_Process;
    wil::unique_hlocal_string packageDependencyId;
    RETURN_IF_FAILED(MddPinPackageDependency(nullptr,
        packageFamilyName, minVersion, architecture, pinFlags, &packageDependencyId));

    const INT32 rank = PACKAGE_DEPENDENCY_RANK_DEFAULT;
    const UINT32 addFlags = MddAddPackageDependency::None;
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext = nullptr;
    wil::unique_hlocal_string packageFullName;
    RETURN_IF_FAILED(MddAddPackageDependency(
        packageDependencyId.get(), rank, addFlags, &packageDependencyContext , &packageFullName));
    wprintf(L"Managing muffins via %ls", packageFullName.get());

    wil::unique_hmodule contosoMuffinsDll(::LoadLibrary(L"Contoso-Muffins"));
    RETURN_LAST_ERROR_IF(!contosoMuffinsDll);

    typedef int (WINAPI * ManageMuffins)();
    auto manageMuffins = GetProcAddressByFunctionDeclaration(contosoMuffinsDll, ManageMuffins);
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), manageMuffins);

    countOfMuffinsManaged = (*manageMuffins)();

    (void) LOG_IF_FAILED(MddRemovePackageDependency(packageDependencyContext));

    (void) LOG_IF_FAILED(MddUnpinPackageDependency(packageDependencyId.get()));

    return S_OK;
}
```

## WinRT

```c#
using Microsoft.ApplicationModel;
using System.Reflection;
using Windows.ApplicationModel;

int ManageMuffins()
{
    int countOfMuffinsManaged = 0;

    var packageFamilyName = "Contoso.muffins_1234567890abc";
    PACKAGE_VERSION minVersion;
    minVersion.Major = 87;
    minVersion.Minor = 0;
    minVersion.Build = 1234;
    minVersion.Revision = 567;
    var packageDependency = PackageDependency.Pin(packageFamilyName, minVersion, null);

    var packageDependencyContext = packageDependency.Add();
    Console.WriteLine($"Managing muffins via {packageDependencyContext.PackageFullName}");

    var assembly = Assembly.Load("Contoso-Muffins, Version=1.0.1967.0, Culture=neutral, PublicKeyToken=8744b20f8da049e3");
    if (assembly == null)
    {
        Console.WriteLine("Unable to load assembly");
    }
    else
    {
        countOfMuffinsManaged = Contoso.Muffins.Manage();
    }

    packageDependencyContext.Remove();

    packageDependency.Unpin();

    return countOfMuffinsManaged;
}
```
