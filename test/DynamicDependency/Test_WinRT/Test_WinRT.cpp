// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_WinRT.h"

#include <wil/winrt.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

wil::unique_hmodule Test::DynamicDependency::Test_WinRT::m_bootstrapDll;

bool Test::DynamicDependency::Test_WinRT::Setup()
{
    // Remove our packages in case they were previously installed and incompletely removed
    TP::RemovePackage_DynamicDependencyLifetimeManager();
    TP::RemovePackage_DynamicDependencyDataStore();
    TP::RemovePackage_ProjectReunionFramework();
    TP::RemovePackage_FrameworkMathMultiply();
    TP::RemovePackage_FrameworkMathAdd();

    // Install our needed packages
    TP::AddPackage_FrameworkMathAdd();
    TP::AddPackage_FrameworkMathMultiply();
    TP::AddPackage_ProjectReunionFramework();
    TP::AddPackage_DynamicDependencyDataStore();
    TP::AddPackage_DynamicDependencyLifetimeManager();

    // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
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

    VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

    // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
    const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
    const PACKAGE_VERSION minVersion{};
    VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

    m_bootstrapDll = std::move(bootstrapDll);

    return true;
}

bool Test::DynamicDependency::Test_WinRT::Cleanup()
{
    MddBootstrapShutdown();

    m_bootstrapDll.reset();

    TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();
    TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
    TP::RemovePackage_DynamicDependencyLifetimeManager();
    TP::RemovePackage_DynamicDependencyDataStore();
    TP::RemovePackage_ProjectReunionFramework();
    TP::RemovePackage_FrameworkMathMultiply();
    TP::RemovePackage_FrameworkMathAdd();

    return true;
}

void Test::DynamicDependency::Test_WinRT::Create_Delete()
{
    const winrt::hstring packageFamilyName{ TP::FrameworkMathAdd::c_PackageFamilyName };
    const winrt::Windows::ApplicationModel::PackageVersion minVersion{};
    auto packageDependency{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency::Create(packageFamilyName, minVersion) };

    packageDependency.Delete();
}

void Test::DynamicDependency::Test_WinRT::GetFromId_Empty()
{
    winrt::hstring packageDependencyId;
    auto packageDependency{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency::GetFromId(packageDependencyId) };
    VERIFY_IS_TRUE(!packageDependency);
}

void Test::DynamicDependency::Test_WinRT::GetFromId_NotFound()
{
    winrt::hstring packageDependencyId{ L"This.Does.Not.Exist" };
    auto packageDependency{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency::GetFromId(packageDependencyId) };
    VERIFY_IS_TRUE(!packageDependency);
}

void Test::DynamicDependency::Test_WinRT::FullLifecycle_ProcessLifetime_Framework_ProjectReunion()
{
    // Setup our dynamic dependencies

    winrt::hstring expectedPackageFullName_ProjectReunionFramework{ TP::ProjectReunionFramework::c_PackageFullName };
    winrt::hstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto pathEnvironmentVariable{ GetPathEnvironmentVariableMinusProjectReunionFramework() };
    auto packagePath_ProjectReunionFramework{ TP::GetPackagePath(expectedPackageFullName_ProjectReunionFramework) };
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.c_str());

    // -- Create

    auto packageDependency_FrameworkMathAdd{ _Create_FrameworkMathAdd() };
    VERIFY_IS_FALSE(!packageDependency_FrameworkMathAdd);
    auto packageDependencyId_FrameworkMathAdd{ packageDependency_FrameworkMathAdd.Id() };
    VERIFY_IS_FALSE(packageDependencyId_FrameworkMathAdd.empty());

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependency_FrameworkMathAdd, S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Add

    auto packageDependencyContext_FrameworkMathAdd{ packageDependency_FrameworkMathAdd.Add() };
    VERIFY_IS_FALSE(!packageDependencyContext_FrameworkMathAdd);
    VERIFY_ARE_EQUAL(std::wstring(packageDependencyContext_FrameworkMathAdd.PackageFullName()), std::wstring(expectedPackageFullName_FrameworkMathAdd));

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto packagePath_FrameworkMathAdd{ TP::GetPackagePath(expectedPackageFullName_FrameworkMathAdd) };
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependency_FrameworkMathAdd, S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Use it

    // Let's use resources from the dynamically added package
    auto mathAddDllFilename{ L"Microsoft.ProjectReunion.dll" };
    wil::unique_hmodule mathAddDll(LoadLibrary(mathAddDllFilename));
    {
        const auto lastError{ GetLastError() };
        auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, mathAddDllFilename) };
        VERIFY_IS_NOT_NULL(mathAddDll.get(), message.get());
    }

    auto mddGetResolvedPackageFullNameForPackageDependency{ GetProcAddressByFunctionDeclaration(mathAddDll.get(), MddGetResolvedPackageFullNameForPackageDependency) };
    VERIFY_IS_NOT_NULL(mddGetResolvedPackageFullNameForPackageDependency);

    wil::unique_process_heap_string resolvedPackageFullName;
    VERIFY_ARE_EQUAL(S_OK, mddGetResolvedPackageFullNameForPackageDependency(packageDependency_FrameworkMathAdd.Id().c_str(), &resolvedPackageFullName));
    VERIFY_IS_NOT_NULL(resolvedPackageFullName.get());
    winrt::hstring actualResolvedPackageFullName{ resolvedPackageFullName.get() };
    const auto& expectedResolvedPackageFullName{ expectedPackageFullName_FrameworkMathAdd };
    VERIFY_ARE_EQUAL(expectedResolvedPackageFullName, actualResolvedPackageFullName);

    // Tear down our dynamic dependencies

    // -- Remove

    packageDependencyContext_FrameworkMathAdd.Remove();

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Delete

    packageDependency_FrameworkMathAdd.Delete();

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
}

void Test::DynamicDependency::Test_WinRT::WinRT_RoGetActivationFactory_1()
{
    IInspectable* packageDependency{};
    {
        auto acid{ wil::make_unique_string < wil::unique_hstring>(L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency") };
        VERIFY_SUCCEEDED(::RoGetActivationFactory(acid.get(), IID_PPV_ARGS(&packageDependency)));
    }
    VERIFY_IS_NOT_NULL(packageDependency);

    packageDependency->Release();
}

void Test::DynamicDependency::Test_WinRT::WinRT_RoGetActivationFactory_2()
{
    IInspectable* packageDependency{};
    {
        auto acid{ wil::make_unique_string < wil::unique_hstring>(L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency") };
        VERIFY_SUCCEEDED(::RoGetActivationFactory(acid.get(), IID_PPV_ARGS(&packageDependency)));
    }
    VERIFY_IS_NOT_NULL(packageDependency);

    IInspectable* activationRegistrationManager{};
    {
        auto acid{ wil::make_unique_string < wil::unique_hstring>(L"Microsoft.Windows.AppLifecycle.ActivationRegistrationManager") };
        VERIFY_SUCCEEDED(::RoGetActivationFactory(acid.get(), IID_PPV_ARGS(&activationRegistrationManager)));
    }
    VERIFY_IS_NOT_NULL(activationRegistrationManager);

    activationRegistrationManager->Release();
    packageDependency->Release();
}

void Test::DynamicDependency::Test_WinRT::WinRT_RoGetActivationFactory_NotFound()
{
    IInspectable* doesNotExist{};
    {
        auto acid{ wil::make_unique_string < wil::unique_hstring>(L"Does.Not.Exist") };
        VERIFY_ARE_EQUAL(REGDB_E_CLASSNOTREG, ::RoGetActivationFactory(acid.get(), IID_PPV_ARGS(&doesNotExist)));
    }
    VERIFY_IS_NULL(doesNotExist);
}

void Test::DynamicDependency::Test_WinRT::VerifyPackageDependency(
    PCWSTR packageDependencyId,
    const HRESULT expectedHR,
    PCWSTR expectedPackageFullName)
{
    wil::unique_process_heap_string packageFullName;
    VERIFY_ARE_EQUAL(expectedHR, MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName));
    if (!expectedPackageFullName)
    {
        VERIFY_IS_TRUE(!packageFullName);
    }
    else
    {
        VERIFY_ARE_EQUAL(std::wstring(packageFullName.get()), std::wstring(expectedPackageFullName));
    }
}

void Test::DynamicDependency::Test_WinRT::VerifyPackageDependency(
    PCWSTR packageDependencyId,
    const HRESULT expectedHR,
    const std::wstring& expectedPackageFullName)
{
    VerifyPackageDependency(packageDependencyId, expectedHR, expectedPackageFullName.c_str());
}

void Test::DynamicDependency::Test_WinRT::VerifyPackageDependency(
    const winrt::hstring& packageDependencyId,
    const HRESULT expectedHR)
{
    VerifyPackageDependency(packageDependencyId.c_str(), expectedHR);
}

void Test::DynamicDependency::Test_WinRT::VerifyPackageDependency(
    const winrt::hstring& packageDependencyId,
    const HRESULT expectedHR,
    const winrt::hstring& expectedPackageFullName)
{
    VerifyPackageDependency(packageDependencyId.c_str(), expectedHR, expectedPackageFullName.c_str());
}

void Test::DynamicDependency::Test_WinRT::VerifyPackageDependency(
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency& packageDependency,
    const HRESULT expectedHR)
{
    VerifyPackageDependency(packageDependency.Id().c_str(), expectedHR);
}

void Test::DynamicDependency::Test_WinRT::VerifyPackageDependency(
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency& packageDependency,
    const HRESULT expectedHR,
    const winrt::hstring& expectedPackageFullName)
{
    VerifyPackageDependency(packageDependency.Id().c_str(), expectedHR, expectedPackageFullName.c_str());
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(PCWSTR path)
{
    std::wstring expectedPath{ path };
    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path)
{
    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    std::wstring expectedPath{ std::wstring(path1) + L";" + path };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path)
{
    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    std::wstring expectedPath{ std::wstring(path1) + L";" + path2 + L";" + path };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path3, PCWSTR path)
{
    std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
    std::wstring expectedPath{ std::wstring(path1) + L";" + path2 + L";" + path3 + L";" + path };
    VERIFY_ARE_EQUAL(expectedPath, pathEnvironmentVariable);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(const std::wstring& path1, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path2.c_str(), path);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, const std::wstring& path3, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path2.c_str(), path3.c_str(), path);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(const winrt::hstring& path1, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(const winrt::hstring& path1, const winrt::hstring& path2, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path2.c_str(), path);
}

void Test::DynamicDependency::Test_WinRT::VerifyPathEnvironmentVariable(const winrt::hstring& path1, const winrt::hstring& path2, const winrt::hstring& path3, PCWSTR path)
{
    VerifyPathEnvironmentVariable(path1.c_str(), path2.c_str(), path3.c_str(), path);
}

void Test::DynamicDependency::Test_WinRT::VerifyPackageInPackageGraph(
    const winrt::hstring& packageFullName,
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

void Test::DynamicDependency::Test_WinRT::VerifyPackageNotInPackageGraph(
    const winrt::hstring& packageFullName,
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

HRESULT Test::DynamicDependency::Test_WinRT::GetCurrentPackageInfo(
    UINT32& packageInfoCount,
    const PACKAGE_INFO*& packageInfo,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer)
{
    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_BUNDLE | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    const PackagePathType packagePathType{ PackagePathType_Effective };
    return GetCurrentPackageInfo(flags, packagePathType, packageInfoCount, packageInfo, buffer);
}

HRESULT Test::DynamicDependency::Test_WinRT::GetCurrentPackageInfo(
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

int Test::DynamicDependency::Test_WinRT::FindPackageFullNameInPackageInfoArray(
    const winrt::hstring& packageFullName,
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

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create(
    const winrt::hstring& packageFamilyName,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return _Create(S_OK, packageFamilyName, lifetimeKind, lifetimeArtifact);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create(
    const HRESULT expectedHR,
    const winrt::hstring& packageFamilyName,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architectures{};
    return _Create(expectedHR, packageFamilyName, architectures, lifetimeKind, lifetimeArtifact);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create(
    const HRESULT expectedHR,
    const winrt::hstring& packageFamilyName,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architectures,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions options;
    options.Architectures(architectures);
    options.LifetimeArtifactKind(lifetimeKind);
    if (lifetimeArtifact)
    {
        options.LifetimeArtifact(lifetimeArtifact);
    }
    return _Create(expectedHR, packageFamilyName, options);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create(
    const HRESULT expectedHR,
    const winrt::hstring& packageFamilyName,
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions& options)
{
    try
    {
        winrt::Windows::ApplicationModel::PackageVersion minVersion{};
        auto packageDependency{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency::Create(packageFamilyName, minVersion, options) };
        VERIFY_ARE_EQUAL(expectedHR, S_OK);
        return packageDependency;
    }
    catch (const winrt::hresult_error& e)
    {
        VERIFY_ARE_EQUAL(static_cast<int32_t>(expectedHR), e.code().value, e.message().c_str());
        throw;
    }
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create_ProjectReunionFramework(
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return _Create(TP::ProjectReunionFramework::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create_FrameworkMathAdd()
{
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process };
    PCWSTR lifetimeArtifact{};
    return _Create(S_OK, TP::FrameworkMathAdd::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create_FrameworkMathAdd(
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return _Create(TP::FrameworkMathAdd::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create_FrameworkMathAdd(
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architectures,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return _Create(S_OK, TP::FrameworkMathAdd::c_PackageFamilyName, architectures, lifetimeKind, lifetimeArtifact);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create_FrameworkMathAdd(
    const HRESULT expectedHR,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
    PCWSTR lifetimeArtifact)
{
    return _Create(expectedHR, TP::FrameworkMathAdd::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency Test::DynamicDependency::Test_WinRT::_Create_FrameworkMathAdd(
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions& options)
{
    return _Create(S_OK, TP::FrameworkMathAdd::c_PackageFamilyName, options);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContext Test::DynamicDependency::Test_WinRT::_Add(
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency packageDependency)
{
    return _Add(S_OK, packageDependency);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContext Test::DynamicDependency::Test_WinRT::_Add(
    const HRESULT expectedHR,
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency packageDependency)
{
    const auto rank{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyRank::Default() };
    return _Add(expectedHR, packageDependency, rank);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContext Test::DynamicDependency::Test_WinRT::_Add(
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency packageDependency,
    const INT32 rank)
{
    return _Add(S_OK, packageDependency, rank);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContext Test::DynamicDependency::Test_WinRT::_Add(
    const HRESULT expectedHR,
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency packageDependency,
    const INT32 rank)
{
    try
    {
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions options;
        options.Rank(rank);
        auto packageDependencyContext{ packageDependency.Add(options) };
        VERIFY_ARE_EQUAL(expectedHR, S_OK);
        return packageDependencyContext;
    }
    catch (const winrt::hresult_error& e)
    {
        VERIFY_ARE_EQUAL(static_cast<int32_t>(expectedHR), e.code().value, e.message().c_str());
        throw;
    }
}

HANDLE Test::DynamicDependency::Test_WinRT::File_CreateTemporary(
    const std::filesystem::path& filename)
{
    wil::unique_hfile file{ ::CreateFileW(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
                                          nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_DELETE_ON_CLOSE, nullptr)};
    VERIFY_IS_TRUE(file.is_valid());
    VERIFY_IS_TRUE(std::filesystem::exists(filename));
    return file.release();
}

HKEY Test::DynamicDependency::Test_WinRT::Registry_CreateKey(
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

void Test::DynamicDependency::Test_WinRT::Registry_DeleteKey(
    const std::wstring& key)
{
    PCWSTR subkey{};
    auto root{ Registry_Key_Parse(key, subkey) };

    auto rc{ ::RegDeleteKeyExW(root, subkey, 0, 0) };
    VERIFY_IS_TRUE((rc == ERROR_SUCCESS) || (rc == ERROR_FILE_NOT_FOUND));
}

HKEY Test::DynamicDependency::Test_WinRT::Registry_Key_Parse(
    const std::wstring& key,
    PCWSTR& subkey)
{
    size_t offset{};
    auto root = Registry_Key_Parse(key, offset);
    subkey = key.c_str() + offset;
    return root;
}

HKEY Test::DynamicDependency::Test_WinRT::Registry_Key_Parse(
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

std::wstring Test::DynamicDependency::Test_WinRT::GetPathEnvironmentVariable()
{
    return std::wstring{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
}

std::wstring Test::DynamicDependency::Test_WinRT::GetPathEnvironmentVariableMinusPathPrefix(
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

std::wstring Test::DynamicDependency::Test_WinRT::GetPathEnvironmentVariableMinusPathPrefix(
    const std::wstring& pathPrefix)
{
    return GetPathEnvironmentVariableMinusPathPrefix(pathPrefix.c_str());
}

std::wstring Test::DynamicDependency::Test_WinRT::GetPathEnvironmentVariableMinusProjectReunionFramework()
{
    auto packagePath_ProjectReunionFramework{ TP::GetPackagePath(TP::ProjectReunionFramework::c_PackageFullName) };
    return GetPathEnvironmentVariableMinusPathPrefix(packagePath_ProjectReunionFramework);
}

winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures Test::DynamicDependency::Test_WinRT::GetCurrentArchitectureAsFilter()
{
#if defined(_M_ARM)
    return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm;
#elif defined(_M_ARM64)
    return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm64;
#elif defined(_M_IX86)
    return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86;
#elif defined(_M_X64)
    return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X64;
#else
#   error "Unknown processor architecture"
#endif
}
