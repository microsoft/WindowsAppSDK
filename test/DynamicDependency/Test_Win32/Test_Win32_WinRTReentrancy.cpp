// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <winrt/Microsoft.Test.DynamicDependency.Widgets.h>

#include "Test_Win32.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

void Test::DynamicDependency::Test_Win32::WinRTReentrancy()
{
    // Setup our dynamic dependencies

    std::wstring expectedPackageFullName_WindowsAppRuntimeFramework{ TP::WindowsAppRuntimeFramework::c_PackageFullName };
    std::wstring expectedPackageFullName_FrameworkWidgets{ TP::FrameworkWidgets::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkWidgets, S_OK);
    auto pathEnvironmentVariable{ GetPathEnvironmentVariableMinusWindowsAppRuntimeFramework() };
    auto packagePath_WindowsAppRuntimeFramework{ TP::GetPackagePath(expectedPackageFullName_WindowsAppRuntimeFramework) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());

    // -- TryCreate

    // We're using the Neutral arhitecture as that's our test package's defined architecture.
    // That's OK, what matters is we're not using MddPackageDependencyProcessorArchitectures::None
    // so we exercise the not-default-whatever-deemed-appropriate architecture codepath.
    auto architectures{ MddPackageDependencyProcessorArchitectures::Neutral };
    wil::unique_process_heap_string packageDependencyId_FrameworkWidgets{ Mdd_TryCreate_FrameworkWidgets(architectures) };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkWidgets, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkWidgets.get(), S_OK, expectedPackageFullName_FrameworkWidgets);

    // -- Add

    wil::unique_process_heap_string packageFullName_FrameworkWidgets;
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_FrameworkWidgets{ Mdd_Add(packageDependencyId_FrameworkWidgets.get(), packageFullName_FrameworkWidgets) };
    VERIFY_IS_NOT_NULL(packageFullName_FrameworkWidgets.get(), WEX::Common::String().Format(L"PackageFullName=%s Expected=not-<null>", !packageFullName_FrameworkWidgets ? L"<null>" : packageFullName_FrameworkWidgets.get()));
    std::wstring actualPackageFullName_FrameworkWidgets{ packageFullName_FrameworkWidgets.get() };
    VERIFY_ARE_EQUAL(actualPackageFullName_FrameworkWidgets, expectedPackageFullName_FrameworkWidgets);

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkWidgets, S_OK);
    auto packagePath_FrameworkWidgets{ TP::GetPackagePath(expectedPackageFullName_FrameworkWidgets) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkWidgets, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkWidgets.get(), S_OK, expectedPackageFullName_FrameworkWidgets);

    // -- Use it

    // Let's use resources from the dynamically added package
#if 0
    winrt::Microsoft::Test::DynamicDependency::Widgets::Widget2 widget2;
    VERIFY_IS_NOT_NULL(widget2);
    auto widget1{ widget2.GetWidget1() };
    VERIFY_IS_NOT_NULL(widget1);
    //
    auto before{ widget1.Value() };
    VERIFY_ARE_EQUAL(0, before);
    widget1.Value(before + 1);
    auto after{ widget1.Value() };
    VERIFY_ARE_EQUAL(before + 1, after);
    //
    auto widget1a{ widget2.GetWidget1() };
    VERIFY_IS_NOT_NULL(widget1);
    auto beforea{ widget1a.Value() };
    VERIFY_ARE_EQUAL(0, beforea);

    auto staticWidget1{ winrt::Microsoft::Test::DynamicDependency::Widgets::Widget2::GetStaticWidget1() };
    VERIFY_IS_NOT_NULL(staticWidget1);
    //
    auto staticBefore{ staticWidget1.Value() };
    VERIFY_ARE_EQUAL(0, staticBefore);
    staticWidget1.Value(staticBefore + 1);
    auto staticAfter{ staticWidget1.Value() };
    VERIFY_ARE_EQUAL(staticBefore + 1, staticAfter);
    //
    auto staticWidget2{ winrt::Microsoft::Test::DynamicDependency::Widgets::Widget2::GetStaticWidget1() };
    VERIFY_IS_NOT_NULL(staticWidget2);
    auto staticBefore2{ staticWidget2.Value() };
    VERIFY_ARE_EQUAL(staticAfter, staticBefore2);
#else
    auto widget1{ winrt::Microsoft::Test::DynamicDependency::Widgets::Widget2::GetStaticWidget1() };
    VERIFY_IS_NOT_NULL(widget1);
    //
    auto before{ widget1.Value() };
    VERIFY_ARE_EQUAL(0, before);
    widget1.Value(before + 1);
    auto after{ widget1.Value() };
    VERIFY_ARE_EQUAL(before + 1, after);
    //
    auto widget2{ winrt::Microsoft::Test::DynamicDependency::Widgets::Widget2::GetStaticWidget1() };
    VERIFY_IS_NOT_NULL(widget2);
    auto value2{ widget2.Value() };
    VERIFY_ARE_EQUAL(after, value2);
#endif

    // Tear down our dynamic dependencies

    // -- Remove

    MddRemovePackageDependency(packageDependencyContext_FrameworkWidgets);

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkWidgets, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkWidgets.get(), S_OK, expectedPackageFullName_FrameworkWidgets);

    // -- Delete

    MddDeletePackageDependency(packageDependencyId_FrameworkWidgets.get());

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkWidgets, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkWidgets.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
}
