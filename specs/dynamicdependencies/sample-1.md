# Sample 1 - Fabrikam app using Contoso's Muffins package

Contoso publishes a framework package that provides Muffin-managing functionality. At runtime, Fabrikam wants to use this functionality if available, so it adds a dynamic dependency for the Contoso.Muffins package. The dynamic dependency is removed once Fabrikam is done using the Contoso Muffin-managing functionality.

```MddTryCreatePackageDependency``` will fail if there are no packages registered to the user that satisfy the PackageDependency.

## Win32

```c++
#include <MsixDynamicDependency.h>
#include <wil/resource.h>

HRESULT ManageMuffins(int& countOfMuffinsManaged)
{
    countOfMuffinsManaged = 0;

    // Create a PackageDependency to pin the Contoso Muffin package
    // Fail if the PackageDependency cannot be resolved
    PCWSTR packageFamilyName = L"Contoso.muffins_1234567890abc";
    PACKAGE_VERSION minVersion{};
    minVersion.Major = 87;
    minVersion.Minor = 0;
    minVersion.Build = 1234;
    minVersion.Revision = 567;
    const auto architectureFilter = MddPackageDependencyProcessorArchitectures::None;
    const auto lifetimeKind = MddPackageDependencyLifetimeKind::Process;
    const auto createOptions = MddCreatePackageDependencyOptions::None;
    wil::unique_process_heap_string packageDependencyId;
    RETURN_IF_FAILED(MddTryCreatePackageDependency(nullptr,
        packageFamilyName, minVersion, architecture, lifetimeKind, nullptr, createOptions, &packageDependencyId));

    const INT32 rank = MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT;
    const auto addOptions = MddAddPackageDependencyOptions::None;
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext = nullptr;
    wil::unique_process_heap_string packageFullName;
    RETURN_IF_FAILED(MddAddPackageDependency(
        packageDependencyId.get(), rank, addOptions, &packageDependencyContext , &packageFullName));
    wprintf(L"Managing muffins via %ls", packageFullName.get());

    wil::unique_hmodule contosoMuffinsDll(::LoadLibrary(L"Contoso-Muffins"));
    RETURN_LAST_ERROR_IF(!contosoMuffinsDll);

    typedef int (WINAPI * ManageMuffins)();
    auto manageMuffins = GetProcAddressByFunctionDeclaration(contosoMuffinsDll, ManageMuffins);
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), manageMuffins);

    countOfMuffinsManaged = (*manageMuffins)();

    (void) LOG_IF_FAILED(MddRemovePackageDependency(packageDependencyContext));

    MddDeletePackageDependency(packageDependencyId.get());

    return S_OK;
}
```

## WinRT

```c#
using Microsoft.ApplicationModel.DynamicDependency;
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
    PackageDependency packageDependency = PackageDependency.Create(packageFamilyName, minVersion, null);

    PackageDependencyContext packageDependencyContext = packageDependency.Add();
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

    packageDependency.Delete();

    return countOfMuffinsManaged;
}
```
