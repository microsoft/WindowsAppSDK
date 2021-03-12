# Sample 2 - Fabrikam app using Contoso's Muffins package with smart class helpers

Variant of Sample 1 using RAII classes to manage packageDependencyId, packageDependencyContext and DLL lifetimes.

```MddTryCreatePackageDependency``` will fail if there are no packages registered for the calling user satisfying the PackageDependency.

## Win32

```c++
#include <MsixDynamicDependency.h>
#include <wil/resource.h>

class MddPackageDependencyContextAndDll
{
public:
    MddPackageDependencyContextAndDll() = default;

    MddPackageDependencyContextAndDll(MddPackageDependencyContextAndDll&& other)
    {
        if (&other != this)
        {
            m_packageDependencyContext = other.m_packageDependencyContext;
            other.m_packageDependencyContext = nullptr;

            m_packageFullName = wistd::move(other.m_packageDependencyContext);
            m_module = wistd::move(other.m_module);
        }
    }

    MddPackageDependencyContextAndDll(MddPackageDependencyContextAndDll&) = delete;

    MddPackageDependencyContextAndDll& operator=(MddPackageDependencyContextAndDll&) = delete;

    ~MddPackageDependencyContextAndDll()
    {
        (void) LOG_IF_FAILED(MddRemovePackageDependency(m_packageDependencyContext));
    }

    MddPackageDependencyContextAndDll& operator=(MddPackageDependencyContextAndDll&& other)
    {
        if (&other != this)
        {
            m_packageDependencyContext = other.m_packageDependencyContext;
            other.m_packageDependencyContext = nullptr;

            m_packageFullName = wistd::move(other.m_packageDependencyContext);
            m_module = wistd::move(other.m_module);
        }
        return *this;
    }

    HRESULT Add(
        _In_ PCWSTR packageDependencyId,
        INT32 rank,
        MddAddPackageDependencyOptions options,
        _In_ PCWSTR dllFilename)
    {
        MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext = nullptr;
        wil::unique_process_heap_string packageFullName;
        RETURN_IF_FAILED(MddAddPackageDependency(
            packageDependencyId, rank, options, &m_packageDependencyContext , &m_packageFullName));

        wil::unique_hmodule module(::LoadLibrary(L"Contoso-Muffins"));
        RETURN_LAST_ERROR_IF(!module);

        m_packageDependencyContext = packageDependencyContext
        m_packageFullName = wistd::move(packageFullName);
        m_module = wistd::move(module);
        return S_OK
    }

    PCWSTR GetPackageFullName() const
    {
        return m_packageFullName.get();
    }

    HMODULE GetModule() const
    {
        return m_module.get();
    }

private:
    MDD_PACKAGEDEPENDENCY_CONTEXT m_packageDependencyContext = nullptr;
    wil::unique_process_heap_string m_packageFullName;
    mutable wil::unique_hmodule m_module;
};

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
    const auto createOptions = MddCreatePackageDependencyOptions::LifecycleHint_Process;
    wil::unique_packagedependencyid packageDependencyId;
    RETURN_IF_FAILED(MddTryCreatePackageDependency(nullptr,
        packageFamilyName, minVersion, architecture, nullptr, createOptions, &packageDependencyId));

    const INT32 rank = MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT;
    const auto addOptions = MddAddPackageDependencyOptions::None;
    MddPackageDependencyContextAndDll context;
    RETURN_IF_FAILED(context.Add(packageDependencyId.get(), rank, addOptions, L"Contoso-Muffins"));
    wprintf(L"Managing muffins via %ls", context.GetPackageFullName());

    typedef int (WINAPI * ManageMuffins)();
    auto manageMuffins = GetProcAddressByFunctionDeclaration(contosoMuffinsDll, ManageMuffins);
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), manageMuffins);

    countOfMuffinsManaged = (*manageMuffins)();

    return S_OK;
}
```
