# Sample 5 - LolzKitten app using PackageDependency pinned by LolzKitten Installer

Contoso publishes a framework package. At runtime, LolzKittens wants to use Contoso's functionality as specified by the package dependency defined when LolzKittens was installed.

## Win32

```c++
#include <MsixDynamicDependency.h>
#include <wil/resource.h>

HRESULT LoadPackageDependencyId(_In_ PCWSTR what, wil::unique_ptr<WCHAR[]>& packageDependencyId);

HRESULT ManageMuffins(int& countOfMuffinsManaged)
{
    countOfMuffinsManaged = 0;

    wil::unique_ptr<WCHAR[]> packageDependencyId;
    RETURN_IF_FAILED(LoadPackageDependencyId(L"muffins", packageDependencyId));

    const INT32 rank = MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT;
    const auto addOptions = MddAddPackageDependencyOptions::None;
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext = nullptr;
    wil::unique_process_heap_string packageFullName;
    RETURN_IF_FAILED(MddAddPackageDependency(
        packageDependencyId.get(), rank, addOptions, &packageDependencyContext, &packageFullName));
    wprintf(L"Managing muffins via %ls", packageFullName.get());

    wil::unique_hmodule contosoMuffinsDll(::LoadLibrary(L"Contoso-Muffins"));
    RETURN_LAST_ERROR_IF(!contosoMuffinsDll);

    typedef int (WINAPI * ManageMuffins)();
    auto manageMuffins = GetProcAddressByFunctionDeclaration(contosoMuffinsDll, ManageMuffins);
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), manageMuffins);

    countOfMuffinsManaged = (*manageMuffins)();

    (void) LOG_IF_FAILED(MddRemovePackageDependency(packageDependencyContext));

    return S_OK;
}

HRESULT LoadPackageDependencyId(_In_ PCWSTR what, wil::unique_ptr<WCHAR[]>& packageDependencyId)
{
    // Load the previously stored package dependency identifier
}
```

## WinRT

```c#
using Microsoft.ApplicationModel.DynamicDependency;
using System.Reflection;

namespace LolzKitten
{
    public Runtime
    {
        public static int ManageMuffins()
        {
            int countOfMuffinsManaged = 0;

            string packageDependencyId = LoadPackageDependencyId("muffins");
            var packageDependency = new PackageDependency.GetFromId(packageDependencyId);

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

            return countOfMuffinsManaged;
        }

        static string LoadPackageDependencyId(string what)
        {
            // Load the previously stored package dependency identifier
        }
    }
}
```
