# Sample 2 - Fabrikam app using Contosso's Muffins package with smart class helpers

Variant of Sample 1 using RAII classes to manage packageDependencyId, packageDependencyContext and DLL lifetimes.

```MddPinPackageDependency``` will fail if there are no packages registered for the calling user satisfying the PackageDependency.

## Win32

```c++
#include <MsixDynamicDependency.hpp>
#include <wil/resource.h>

class MddPackageDependencyContextAndDll
{
public:
    MddPackageDependencyContextAndDll() = default;

    ~MddPackageDependencyContextAndDll()
    {
        (void) LOG_IF_FAILED(MddRemovePackageDependency(m_packageDependencyContext));
        (void) LOG_IF_WIN32_BOOL_FALSE(FreeLibrary(m_module.get()));
    }

    HRESULT Add(
        _In_ PCWSTR packageDependencyId,
        INT32 rank,
        MddAddPackageDependency flags,
        _In_ PCWSTR dllFilename)
    {
        RETURN_IF_FAILED(MddAddPackageDependency(
            packageDependencyId, rank, flags, &m_packageDependencyContext , &m_packageFullName));
        m_module = ::LoadLibrary(L"Contoso-Muffins");
        RETURN_LAST_ERROR_IF(!m_module);
        return S_OK
    }

    PCWSTR GetPackageFullName() const
    {
        Return m_packageFullName.get();
    }

    HMODULE GetModule()
    {
        Return m_module.get();
    }

private:
    MDD_PACKAGEDEPENDENCY_CONTEXT m_packageDependencyContext = nullptr;
    wil::unique_hlocal_string m_packageFullName;
    wil::unique_hmodule m_module;
};

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
    wil::unique_packagedependencyid packageDependencyId;
    RETURN_IF_FAILED(MddPinPackageDependency(nullptr,
        packageFamilyName, minVersion, architecture, nullptr, pinFlags, &packageDependencyId));

    const INT32 rank = PACKAGE_DEPENDENCY_RANK_DEFAULT;
    const UINT32 addFlags = MddAddPackageDependency::None;
    MddPackageDependencyContextAndDll context;
    RETURN_IF_FAILED(context.Add(packageDependencyId.get(), rank, addFlags, L"Contoso-Muffins"));
    wprintf(L"Managing muffins via %ls", context.GetPackageFullName());

    typedef int (WINAPI * ManageMuffins)();
    auto manageMuffins = GetProcAddressByFunctionDeclaration(contosoMuffinsDll, ManageMuffins);
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), manageMuffins);

    countOfMuffinsManaged = (*manageMuffins)();

    return S_OK;
}
```
