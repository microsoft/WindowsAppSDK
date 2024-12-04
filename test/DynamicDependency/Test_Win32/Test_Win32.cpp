// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_Win32.h"

#include <MddWin11.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

wil::unique_hmodule Test::DynamicDependency::Test_Win32::m_bootstrapDll;

bool Test::DynamicDependency::Test_Win32::Setup()
{
    // Remove our packages in case they were previously installed and incompletely removed
    TP::RemovePackage_DynamicDependencyLifetimeManager();
    TP::RemovePackage_DynamicDependencyDataStore();
    TP::RemovePackage_WindowsAppRuntimeFramework();
    TP::RemovePackage_FrameworkWidgets();
    TP::RemovePackage_FrameworkMathMultiply();
    TP::RemovePackage_FrameworkMathAdd();

    // Install our needed packages
    TP::AddPackage_FrameworkMathAdd();
    TP::AddPackage_FrameworkMathMultiply();
    TP::AddPackage_FrameworkWidgets();
    TP::AddPackage_WindowsAppRuntimeFramework();
    TP::AddPackage_DynamicDependencyDataStore();
    TP::AddPackage_DynamicDependencyLifetimeManager();

    // We need to find Microsoft.WindowsAppRuntime.Bootstrap.dll.
    // Normally it's colocated with the application (i.e. same dir as the exe)
    // but that's not true of our test project (a dll) in our build environment
    // (different directories). So we'll explicitly find and load it so the
    // rest of our test is fine
    auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
    wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
    {
        const auto lastError{ GetLastError() };
        auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, bootstrapDllAbsoluteFilename.c_str()) };
        VERIFY_IS_NOT_NULL(bootstrapDll.get(), message.get());
    }

    VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                      Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                      Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                      Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

    // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
    const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
    const PACKAGE_VERSION minVersion{};
    VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

    m_bootstrapDll = std::move(bootstrapDll);

    return true;
}

bool Test::DynamicDependency::Test_Win32::Cleanup()
{
    MddBootstrapShutdown();

    m_bootstrapDll.reset();

    TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();
    TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
    TP::RemovePackage_DynamicDependencyLifetimeManager();
    TP::RemovePackage_DynamicDependencyDataStore();
    TP::RemovePackage_WindowsAppRuntimeFramework();
    TP::RemovePackage_FrameworkWidgets();
    TP::RemovePackage_FrameworkMathMultiply();
    TP::RemovePackage_FrameworkMathAdd();

    return true;
}

void Test::DynamicDependency::Test_Win32::Create_Delete()
{
    // The process starts at GenerationId=0 but the bootstrap API was called which calls DynamicDependencies so it's now 1
    VerifyPackageGraphRevisionId(1);

    PCWSTR packageFamilyName{ TP::FrameworkMathAdd::c_PackageFamilyName };
    const PACKAGE_VERSION minVersion{};
    const MddPackageDependencyProcessorArchitectures architectureFilter{};
    const auto lifetimeKind{ MddPackageDependencyLifetimeKind::Process };
    PCWSTR lifetimeArtifact{};
    const MddCreatePackageDependencyOptions options{};
    wil::unique_process_heap_string packageDependencyId;
    VERIFY_ARE_EQUAL(S_OK, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectureFilter, lifetimeKind, lifetimeArtifact, options, &packageDependencyId));

    MddDeletePackageDependency(packageDependencyId.get());

    VerifyPackageGraphRevisionId(1);
}

void Test::DynamicDependency::Test_Win32::Delete_Null()
{
    PCWSTR packageDependencyId{};
    MddDeletePackageDependency(packageDependencyId);
}

void Test::DynamicDependency::Test_Win32::Delete_NotFound()
{
    PCWSTR packageDependencyId{ L"This.Does.Not.Exist" };
    MddDeletePackageDependency(packageDependencyId);
}

void Test::DynamicDependency::Test_Win32::FullLifecycle_ProcessLifetime_Framework_WindowsAppRuntime()
{
    // The process starts at GenerationId=0 but the bootstrap API was called which calls DynamicDependencies so it's now 1
    VerifyPackageGraphRevisionId(1);

    // Setup our dynamic dependencies

    std::wstring expectedPackageFullName_WindowsAppRuntimeFramework{ TP::WindowsAppRuntimeFramework::c_PackageFullName };
    std::wstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto pathEnvironmentVariable{ GetPathEnvironmentVariableMinusWindowsAppRuntimeFramework() };
    auto packagePath_WindowsAppRuntimeFramework{ TP::GetPackagePath(expectedPackageFullName_WindowsAppRuntimeFramework) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageGraphRevisionId(1);

    // -- TryCreate

    wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd{ Mdd_TryCreate_FrameworkMathAdd() };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);
    VerifyPackageGraphRevisionId(1);

    // -- Add

    wil::unique_process_heap_string packageFullName_FrameworkMathAdd;
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_FrameworkMathAdd{ Mdd_Add(packageDependencyId_FrameworkMathAdd.get(), packageFullName_FrameworkMathAdd) };
    VERIFY_IS_NOT_NULL(packageFullName_FrameworkMathAdd.get(), WEX::Common::String().Format(L"PackageFullName=%s Expected=not-<null>", !packageFullName_FrameworkMathAdd ? L"<null>" : packageFullName_FrameworkMathAdd.get()));
    std::wstring actualPackageFullName_FrameworkMathAdd{ packageFullName_FrameworkMathAdd.get() };
    VERIFY_ARE_EQUAL(actualPackageFullName_FrameworkMathAdd, expectedPackageFullName_FrameworkMathAdd);

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto packagePath_FrameworkMathAdd{ TP::GetPackagePath(expectedPackageFullName_FrameworkMathAdd) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);
    VerifyPackageGraphRevisionId(2);

    // -- Use it

    // Let's use resources from the dynamically added package
    auto windowsAppRuntimeDllFilename{ L"Microsoft.WindowsAppRuntime.dll" };
    wil::unique_hmodule windowsAppRuntimeDll(LoadLibrary(windowsAppRuntimeDllFilename));
    {
        const auto lastError{ GetLastError() };
        auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, windowsAppRuntimeDllFilename) };
        VERIFY_IS_NOT_NULL(windowsAppRuntimeDll.get(), message.get());
    }

    auto mddGetResolvedPackageFullNameForPackageDependency{ GetProcAddressByFunctionDeclaration(windowsAppRuntimeDll.get(), MddGetResolvedPackageFullNameForPackageDependency) };
    VERIFY_IS_NOT_NULL(mddGetResolvedPackageFullNameForPackageDependency);

    wil::unique_process_heap_string resolvedPackageFullName;
    VERIFY_ARE_EQUAL(S_OK, mddGetResolvedPackageFullNameForPackageDependency(packageDependencyId_FrameworkMathAdd.get(), &resolvedPackageFullName));
    VERIFY_IS_NOT_NULL(resolvedPackageFullName.get(), WEX::Common::String().Format(L"PackageFullName=%s Expected=not-<null>", !resolvedPackageFullName ? L"<null>" : resolvedPackageFullName.get()));
    std::wstring actualResolvedPackageFullName{ resolvedPackageFullName.get() };
    const auto& expectedResolvedPackageFullName{ expectedPackageFullName_FrameworkMathAdd };
    VERIFY_ARE_EQUAL(expectedResolvedPackageFullName, actualResolvedPackageFullName);
    VerifyPackageGraphRevisionId(2);

    // Tear down our dynamic dependencies

    // -- Remove

    MddRemovePackageDependency(packageDependencyContext_FrameworkMathAdd);

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);
    VerifyPackageGraphRevisionId(3);

    // -- Delete

    MddDeletePackageDependency(packageDependencyId_FrameworkMathAdd.get());

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
    VerifyPackageGraphRevisionId(3);
}

void Test::DynamicDependency::Test_Win32::GetResolvedPackageFullName_Null()
{
    PCWSTR packageDependencyId{};
    wil::unique_process_heap_string packageFullName;
    VERIFY_ARE_EQUAL(E_INVALIDARG, MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName));
}

void Test::DynamicDependency::Test_Win32::GetResolvedPackageFullName_NotFound()
{
    PCWSTR packageDependencyId{ L"This.Does.Not.Exist" };
    wil::unique_process_heap_string packageFullName;
    VERIFY_SUCCEEDED(MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName));
    VERIFY_IS_NULL(packageFullName, WEX::Common::String().Format(L"PackageFullName=%s Expected=<null>", !packageFullName ? L"<null>" : packageFullName.get()));
}

void Test::DynamicDependency::Test_Win32::GetIdForPackageDependencyContext_Null()
{
    wil::unique_process_heap_string id;
    VERIFY_ARE_EQUAL(E_INVALIDARG, MddGetIdForPackageDependencyContext(nullptr, wil::out_param(id)));
}

void Test::DynamicDependency::Test_Win32::GetIdForPackageDependencyContext()
{
    wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd{ Mdd_TryCreate_FrameworkMathAdd() };
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_FrameworkMathAdd{ Mdd_Add(packageDependencyId_FrameworkMathAdd.get()) };

    wil::unique_process_heap_string id;
    VERIFY_ARE_EQUAL(S_OK, MddGetIdForPackageDependencyContext(packageDependencyContext_FrameworkMathAdd, wil::out_param(id)));
    VERIFY_ARE_EQUAL(std::wstring(packageDependencyId_FrameworkMathAdd.get()), std::wstring(id.get()));

    MddRemovePackageDependency(packageDependencyContext_FrameworkMathAdd);
    MddDeletePackageDependency(packageDependencyId_FrameworkMathAdd.get());
}

void Test::DynamicDependency::Test_Win32::VerifyPackageDependency(
    PCWSTR packageDependencyId,
    const HRESULT expectedHR,
    PCWSTR expectedPackageFullName)
{
    // Given an unknown/undefined packageDependencyId our caller specifies expectedHR=HRESULT_FROM_WIN32(ERROR_NOT_FOUND).
    // Handle the condition appropriately:
    //
    // API                                                                | HRESULT                                 | packageFullName
    // -------------------------------------------------------------------|-----------------------------------------|----------------
    // MddGetResolvedPackageFullNameForPackageDependency                  | S_OK                                    | NULL
    // MddGetResolvedPackageFullNameForPackageDependency2 (Supported)     | HRESULT_FROM_WIN32(ERROR_NOT_FOUND)     | NULL
    // MddGetResolvedPackageFullNameForPackageDependency2 (not Supported) | HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED) | NULL

    const HRESULT expectedHR1{ (expectedHR == HRESULT_FROM_WIN32(ERROR_NOT_FOUND)) ? S_OK : expectedHR };
    const HRESULT expectedHR2{
        MddCore::Win11::IsSupported() && !MddCore::Win11::IsGetResolvedPackageFullNameForPackageDependency2Supported() ?
            HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED) :
            expectedHR };

    wil::unique_process_heap_string packageFullName1;
    VERIFY_ARE_EQUAL(expectedHR1, MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName1));
    if (FAILED(expectedHR1) || !expectedPackageFullName)
    {
        VERIFY_IS_NULL(packageFullName1, WEX::Common::String().Format(L"PackageFullName=%s Expected=<null>", !packageFullName1 ? L"<null>" : packageFullName1.get()));
    }
    else
    {
        VERIFY_IS_NOT_NULL(packageFullName1, WEX::Common::String().Format(L"PackageFullName=null Expected=%s", expectedPackageFullName));
        VERIFY_ARE_EQUAL(std::wstring(packageFullName1.get()), std::wstring(expectedPackageFullName));
    }

    wil::unique_process_heap_string packageFullName2;
    VERIFY_ARE_EQUAL(expectedHR2, MddGetResolvedPackageFullNameForPackageDependency2(packageDependencyId, &packageFullName2));
    if (FAILED(expectedHR2) || !expectedPackageFullName)
    {
        VERIFY_IS_NULL(packageFullName2, WEX::Common::String().Format(L"PackageFullName=%s Expected=<null>", !packageFullName2 ? L"<null>" : packageFullName2.get()));
    }
    else
    {
        VERIFY_IS_NOT_NULL(packageFullName2, WEX::Common::String().Format(L"PackageFullName=null Expected=%s", expectedPackageFullName));
        VERIFY_ARE_EQUAL(std::wstring(packageFullName2.get()), std::wstring(expectedPackageFullName));
    }
}

void Test::DynamicDependency::Test_Win32::VerifyPackageDependency(
    PCWSTR packageDependencyId,
    const HRESULT expectedHR,
    const std::wstring& expectedPackageFullName)
{
    VerifyPackageDependency(packageDependencyId, expectedHR, expectedPackageFullName.c_str());
}

void Test::DynamicDependency::Test_Win32::VerifyPathEnvironmentVariable(PCWSTR path)
{
    // N/A when DynamicDependency delegates to the Win11 OS API
    if (MddCore::Win11::IsSupported())
    {
        return;
    }

    std::wstring expectedPath{ path };
    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_Win32::VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path)
{
    // N/A when DynamicDependency delegates to the Win11 OS API
    if (MddCore::Win11::IsSupported())
    {
        return;
    }

    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    std::wstring expectedPath{ std::wstring(path1) + L";" + path };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_Win32::VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path)
{
    // N/A when DynamicDependency delegates to the Win11 OS API
    if (MddCore::Win11::IsSupported())
    {
        return;
    }

    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    std::wstring expectedPath{ std::wstring(path1) + L";" + path2 + L";" + path };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_Win32::VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path3, PCWSTR path)
{
    // N/A when DynamicDependency delegates to the Win11 OS API
    if (MddCore::Win11::IsSupported())
    {
        return;
    }

    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    std::wstring expectedPath{ std::wstring(path1) + L";" + path2 + L";" + path3 + L";" + path };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_Win32::VerifyPathEnvironmentVariable(const std::wstring& path1, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path);
}

void Test::DynamicDependency::Test_Win32::VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path2.c_str(), path);
}

void Test::DynamicDependency::Test_Win32::VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, const std::wstring& path3, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path2.c_str(), path3.c_str(), path);
}

void Test::DynamicDependency::Test_Win32::VerifyPackageInPackageGraph(
    const std::wstring& packageFullName,
    const HRESULT expectedHR)
{
    UINT32 packageInfoCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> packageInfosBuffer;
    VERIFY_ARE_EQUAL(expectedHR, GetCurrentPackageInfo(packageInfoCount, packageInfo, packageInfosBuffer));
    if (expectedHR == S_OK)
    {
        VERIFY_ARE_NOT_EQUAL(-1, FindPackageFullNameInPackageInfoArray(packageFullName, packageInfoCount, packageInfo));
    }
}

void Test::DynamicDependency::Test_Win32::VerifyPackageNotInPackageGraph(
    const std::wstring& packageFullName,
    const HRESULT expectedHR)
{
    UINT32 packageInfoCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> packageInfosBuffer;
    VERIFY_ARE_EQUAL(expectedHR, GetCurrentPackageInfo(packageInfoCount, packageInfo, packageInfosBuffer));
    if (expectedHR == S_OK)
    {
        VERIFY_ARE_EQUAL(-1, FindPackageFullNameInPackageInfoArray(packageFullName, packageInfoCount, packageInfo));
    }
}

HRESULT Test::DynamicDependency::Test_Win32::GetCurrentPackageInfo(
    UINT32& packageInfoCount,
    const PACKAGE_INFO*& packageInfo,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer)
{
    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_BUNDLE | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    const PackagePathType packagePathType{ PackagePathType_Effective };
    return GetCurrentPackageInfo(flags, packagePathType, packageInfoCount, packageInfo, buffer);
}

HRESULT Test::DynamicDependency::Test_Win32::GetCurrentPackageInfo(
    const UINT32 flags,
    const PackagePathType packagePathType,
    UINT32& packageInfoCount,
    const PACKAGE_INFO*& packageInfo,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer)
{
    UINT32 bufferLength{};
    LONG rc{ GetCurrentPackageInfo2(flags, packagePathType, &bufferLength, nullptr, nullptr) };
    RETURN_HR_IF(HRESULT_FROM_WIN32(rc), rc != ERROR_INSUFFICIENT_BUFFER);

    buffer = wil::make_unique_cotaskmem<BYTE[]>(bufferLength);
    RETURN_IF_WIN32_ERROR(GetCurrentPackageInfo2(flags, packagePathType, &bufferLength, buffer.get(), &packageInfoCount));
    packageInfo = reinterpret_cast<PACKAGE_INFO*>(buffer.get());
    return S_OK;
}

int Test::DynamicDependency::Test_Win32::FindPackageFullNameInPackageInfoArray(
    const std::wstring& packageFullName,
    const size_t packageInfoCount,
    const PACKAGE_INFO* packageInfo)
{
    for (UINT32 index = 0; index < packageInfoCount; ++index, ++packageInfo)
    {
        if (CompareStringOrdinal(packageFullName.c_str(), -1, packageInfo->packageFullName, -1, TRUE) == CSTR_EQUAL)
        {
            return true;
        }
    }
    return -1;
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate(
    PCWSTR packageFamilyName,
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options)
{
    return Mdd_TryCreate(S_OK, packageFamilyName, lifetimeKind, lifetimeArtifact, options);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate(
    const HRESULT expectedHR,
    PCWSTR packageFamilyName,
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options)
{
    const MddPackageDependencyProcessorArchitectures architectures{};
    return Mdd_TryCreate(expectedHR, packageFamilyName, architectures, lifetimeKind, lifetimeArtifact, options);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate(
    const HRESULT expectedHR,
    PCWSTR packageFamilyName,
    MddPackageDependencyProcessorArchitectures architectures,
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options)
{
    const PACKAGE_VERSION minVersion{};
    wil::unique_process_heap_string packageDependencyId;
    VERIFY_ARE_EQUAL(expectedHR, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectures, lifetimeKind, lifetimeArtifact, options, &packageDependencyId));
    return packageDependencyId;
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_WindowsAppRuntimeFramework(
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return Mdd_TryCreate(TP::WindowsAppRuntimeFramework::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkMathAdd(
    MddCreatePackageDependencyOptions options)
{
    const MddPackageDependencyLifetimeKind lifetimeKind{ MddPackageDependencyLifetimeKind::Process };
    PCWSTR lifetimeArtifact{};
    return Mdd_TryCreate(S_OK, TP::FrameworkMathAdd::c_PackageFamilyName, lifetimeKind, lifetimeArtifact, options);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkMathAdd(
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return Mdd_TryCreate(TP::FrameworkMathAdd::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkMathAdd(
    const MddPackageDependencyProcessorArchitectures architectures,
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return Mdd_TryCreate(S_OK, TP::FrameworkMathAdd::c_PackageFamilyName, architectures, lifetimeKind, lifetimeArtifact);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkMathAdd(
    const HRESULT expectedHR,
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options)
{
    return Mdd_TryCreate(expectedHR, TP::FrameworkMathAdd::c_PackageFamilyName, lifetimeKind, lifetimeArtifact, options);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkWidgets(
    MddCreatePackageDependencyOptions options)
{
    const MddPackageDependencyLifetimeKind lifetimeKind{ MddPackageDependencyLifetimeKind::Process };
    PCWSTR lifetimeArtifact{};
    return Mdd_TryCreate(S_OK, TP::FrameworkWidgets::c_PackageFamilyName, lifetimeKind, lifetimeArtifact, options);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkWidgets(
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return Mdd_TryCreate(TP::FrameworkWidgets::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkWidgets(
    const MddPackageDependencyProcessorArchitectures architectures,
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return Mdd_TryCreate(S_OK, TP::FrameworkWidgets::c_PackageFamilyName, architectures, lifetimeKind, lifetimeArtifact);
}

wil::unique_process_heap_string Test::DynamicDependency::Test_Win32::Mdd_TryCreate_FrameworkWidgets(
    const HRESULT expectedHR,
    const MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options)
{
    return Mdd_TryCreate(expectedHR, TP::FrameworkWidgets::c_PackageFamilyName, lifetimeKind, lifetimeArtifact, options);
}

MDD_PACKAGEDEPENDENCY_CONTEXT Test::DynamicDependency::Test_Win32::Mdd_Add(
    PCWSTR packageDependencyId)
{
    return Mdd_Add(S_OK, packageDependencyId);
}

MDD_PACKAGEDEPENDENCY_CONTEXT Test::DynamicDependency::Test_Win32::Mdd_Add(
    const HRESULT expectedHR,
    PCWSTR packageDependencyId)
{
    const MddAddPackageDependencyOptions options{};
    wil::unique_process_heap_string packageFullName;
    return Mdd_Add(expectedHR, packageDependencyId, MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT, options, packageFullName);
}

MDD_PACKAGEDEPENDENCY_CONTEXT Test::DynamicDependency::Test_Win32::Mdd_Add(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName)
{
    return Mdd_Add(packageDependencyId, MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT, packageFullName);
}

MDD_PACKAGEDEPENDENCY_CONTEXT Test::DynamicDependency::Test_Win32::Mdd_Add(
    PCWSTR packageDependencyId,
    const INT32 rank,
    wil::unique_process_heap_string& packageFullName)
{
    const MddAddPackageDependencyOptions options{};
    return Mdd_Add(packageDependencyId, rank, options, packageFullName);
}

MDD_PACKAGEDEPENDENCY_CONTEXT Test::DynamicDependency::Test_Win32::Mdd_Add(
    PCWSTR packageDependencyId,
    const INT32 rank,
    const MddAddPackageDependencyOptions options,
    wil::unique_process_heap_string& packageFullName)
{
    return Mdd_Add(S_OK, packageDependencyId, rank, options, packageFullName);
}

MDD_PACKAGEDEPENDENCY_CONTEXT Test::DynamicDependency::Test_Win32::Mdd_Add(
    const HRESULT expectedHR,
    PCWSTR packageDependencyId,
    const INT32 rank,
    const MddAddPackageDependencyOptions options,
    wil::unique_process_heap_string& packageFullName)
{
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext{};
    VERIFY_ARE_EQUAL(expectedHR, MddAddPackageDependency(packageDependencyId, rank, options, &packageDependencyContext, &packageFullName));
    return packageDependencyContext;
}

HANDLE Test::DynamicDependency::Test_Win32::File_CreateTemporary(
    const std::filesystem::path& filename)
{
    wil::unique_hfile file{ ::CreateFileW(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
                                          nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_DELETE_ON_CLOSE, nullptr)};
    VERIFY_IS_TRUE(file.is_valid());
    VERIFY_IS_TRUE(std::filesystem::exists(filename));
    return file.release();
}

HKEY Test::DynamicDependency::Test_Win32::Registry_CreateKey(
    const std::wstring& key)
{
    PCWSTR subkey{};
    auto root{ Registry_Key_Parse(key, subkey) };

    wil::unique_hkey hkey;
    DWORD disposition{};
    VERIFY_ARE_EQUAL(ERROR_SUCCESS, ::RegCreateKeyExW(root, subkey, 0, nullptr, REG_OPTION_VOLATILE,
                                                      KEY_READ | KEY_WRITE, nullptr, wil::out_param(hkey), &disposition));
    return hkey.release();
}

void Test::DynamicDependency::Test_Win32::Registry_DeleteKey(
    const std::wstring& key)
{
    PCWSTR subkey{};
    auto root{ Registry_Key_Parse(key, subkey) };

    auto rc{ ::RegDeleteKeyExW(root, subkey, 0, 0) };
    VERIFY_IS_TRUE((rc == ERROR_SUCCESS) || (rc == ERROR_FILE_NOT_FOUND));
}

HKEY Test::DynamicDependency::Test_Win32::Registry_Key_Parse(
    const std::wstring& key,
    PCWSTR& subkey)
{
    size_t offset{};
    auto root = Registry_Key_Parse(key, offset);
    subkey = key.c_str() + offset;
    return root;
}

HKEY Test::DynamicDependency::Test_Win32::Registry_Key_Parse(
    const std::wstring& key,
    size_t& offsetToSubkey)
{
    HKEY root{};
    auto offset = key.find(L'\\');
    VERIFY_ARE_NOT_EQUAL(std::wstring::npos, offset);
    VERIFY_ARE_NOT_EQUAL(size_t{0}, offset);
    auto prefix{ key.substr(0, offset) };
    if (prefix == L"HKCR")
    {
        root = HKEY_CLASSES_ROOT;
    }
    else if (prefix == L"HKCU")
    {
        root = HKEY_CURRENT_USER;
    }
    else if (prefix == L"HKLM")
    {
        root = HKEY_LOCAL_MACHINE;
    }
    else if (prefix == L"HKU")
    {
        root = HKEY_USERS;
    }
    VERIFY_IS_TRUE(root != HKEY{});
    VERIFY_IS_TRUE(key.length() > prefix.length() + 1);

    offsetToSubkey = ++offset;
    return root;
}

std::wstring Test::DynamicDependency::Test_Win32::GetPathEnvironmentVariable()
{
    return std::wstring{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
}

std::wstring Test::DynamicDependency::Test_Win32::GetPathEnvironmentVariableMinusPathPrefix(
    PCWSTR pathPrefix)
{
    const auto pathPrefixLength{ wcslen(pathPrefix) };

    auto pathEnvironmentVariable{ GetPathEnvironmentVariable() };
    VERIFY_IS_TRUE(pathEnvironmentVariable.length() >= pathPrefixLength);

    auto pathMinusPrefix{ pathEnvironmentVariable.c_str() + pathPrefixLength };
    if (*pathMinusPrefix == L';')
    {
        ++pathMinusPrefix;
    }

    return std::wstring(pathMinusPrefix);
}

std::wstring Test::DynamicDependency::Test_Win32::GetPathEnvironmentVariableMinusPathPrefix(
    const std::wstring& pathPrefix)
{
    return GetPathEnvironmentVariableMinusPathPrefix(pathPrefix.c_str());
}

std::wstring Test::DynamicDependency::Test_Win32::GetPathEnvironmentVariableMinusWindowsAppRuntimeFramework()
{
    auto packagePath_WindowsAppRuntimeFramework{ TP::GetPackagePath(TP::WindowsAppRuntimeFramework::c_PackageFullName) };
    return GetPathEnvironmentVariableMinusPathPrefix(packagePath_WindowsAppRuntimeFramework);
}

MddPackageDependencyProcessorArchitectures Test::DynamicDependency::Test_Win32::GetCurrentArchitectureAsFilter()
{
#if defined(_M_ARM)
    return MddPackageDependencyProcessorArchitectures::Arm;
#elif defined(_M_ARM64)
    return MddPackageDependencyProcessorArchitectures::Arm64;
#elif defined(_M_IX86)
    return MddPackageDependencyProcessorArchitectures::X86;
#elif defined(_M_X64)
    return MddPackageDependencyProcessorArchitectures::X64;
#else
#   error "Unknown processor architecture"
#endif
}

void Test::DynamicDependency::Test_Win32::VerifyPackageGraphRevisionId(
    const UINT32 expectedPackageGraphRevisionId)
{
    const auto actualPackageGraphRevisionId{ MddGetPackageGraphRevisionId() };
    VERIFY_ARE_EQUAL(expectedPackageGraphRevisionId, actualPackageGraphRevisionId);

    // GenerationId is deprecated but verify until removed
    VerifyGenerationId(expectedPackageGraphRevisionId);
}

void Test::DynamicDependency::Test_Win32::VerifyGenerationId(
    const UINT32 expectedGenerationId)
{
    const auto actualGenerationId{ MddGetGenerationId() };
    VERIFY_ARE_EQUAL(expectedGenerationId, actualGenerationId);
}
