// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddBootstrap.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

namespace Test::DynamicDependency
{
    HMODULE LoadBootstrapDll()
    {
        // We need to find Microsoft.WindowsAppRuntime.Bootstrap.dll.
        // Normally it's colocated with the application (i.e. same dir as the exe)
        // but that's not true of our test project (a dll) in our build environment
        // (different directories). So we'll explicitly find and load it so the
        // rest of our test is fine
        auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
        wil::unique_hmodule bootstrapDll{ LoadLibrary(bootstrapDllAbsoluteFilename.c_str()) };
        const auto lastError{ GetLastError() };
        VERIFY_IS_NOT_NULL(bootstrapDll.get(), WEX::Common::String().Format(L"LastError: %d (0x%X)", lastError, lastError));
        return bootstrapDll.release();
    }

    class BootstrapFixtures
    {
    public:
        static void SaveBootstrapDll(HMODULE bootstrapDll)
        {
            m_bootstrapDll.reset(bootstrapDll);
        }

        static bool Setup()
        {
            wil::unique_hmodule bootstrapDll{ LoadBootstrapDll() };

            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_WindowsAppRuntimeFramework();
            TP::RemovePackage_FrameworkWidgets();
            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();
            TP::AddPackage_WindowsAppRuntimeFramework();
            TP::AddPackage_DynamicDependencyDataStore();
            TP::AddPackage_DynamicDependencyLifetimeManager();

            SaveBootstrapDll(bootstrapDll.release());

            return true;
        }

        static bool Cleanup()
        {
            SaveBootstrapDll(nullptr);

            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_WindowsAppRuntimeFramework();

            return true;
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };

    wil::unique_hmodule Test::DynamicDependency::BootstrapFixtures::m_bootstrapDll;

    class ElevatedBootstrapTests
    {
    public:
        BEGIN_TEST_CLASS(ElevatedBootstrapTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_METHOD(Initialize_Elevated)
        {
            BootstrapFixtures::Setup();
            auto cleanup = wil::scope_exit([&] {
                BootstrapFixtures::Cleanup();
            });

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_SUCCEEDED(MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));

            MddBootstrapShutdown();
        }
    };

    class BootstrapTests
    {
    public:
        BEGIN_TEST_CLASS(BootstrapTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup)
        {
            return BootstrapFixtures::Setup();
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            return BootstrapFixtures::Cleanup();
        }

        TEST_METHOD(Initialize_DDLMNotFound)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor = 0.0 == No such framework package
            const UINT32 doesNotExist{};
            const PACKAGE_VERSION minVersionMatchAny{};
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(doesNotExist, nullptr, minVersionMatchAny));
        }

        TEST_METHOD(Initialize_DDLMMinVersionNoMatch)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Version <major>.65535.65535.65535 to find framework packages for the major.minor version but none meeting this minVersion criteria
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            PACKAGE_VERSION minVersionNoMatch{ static_cast<UINT64>(Test::Packages::DynamicDependencyLifetimeManager::c_Version.Major) << 48 | 0x0000FFFFFFFFFFFFuI64 };
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersionNoMatch));
        }

        TEST_METHOD(Initialize)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));

            MddBootstrapShutdown();
        }

        TEST_METHOD(Initialize2x)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));

            MddBootstrapShutdown();
            MddBootstrapShutdown();
        }

        TEST_METHOD(Initialize2xIncompatible)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));

            const UINT32 c_Version_MajorMinor_Incompatible{ c_Version_MajorMinor + 1 };
            VERIFY_ARE_EQUAL(MDD_E_BOOTSTRAP_INITIALIZE_INCOMPATIBLE, MddBootstrapInitialize(c_Version_MajorMinor_Incompatible, nullptr, c_minVersion));

            VERIFY_ARE_EQUAL(MDD_E_BOOTSTRAP_INITIALIZE_INCOMPATIBLE, MddBootstrapInitialize(c_Version_MajorMinor, L"NotTheVersionTag", c_minVersion));

            const PACKAGE_VERSION c_minVersion_Incompatible{ UINT64_MAX };
            VERIFY_ARE_EQUAL(MDD_E_BOOTSTRAP_INITIALIZE_INCOMPATIBLE, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion_Incompatible));

            MddBootstrapShutdown();
        }

        TEST_METHOD(InitializeShutdownMultiple)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor1{ Test::Packages::WindowsAppRuntimeFramework::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion1{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor1, nullptr, c_minVersion1));
            MddBootstrapShutdown();

            // Same criteria but MinVersion=package version. Verify Initialize+Shutdown brings us back
            // to initial state so we can initialize again with different (but successful) criteria
            const UINT32 c_Version_MajorMinor2{ Test::Packages::WindowsAppRuntimeFramework::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion2{ Test::Packages::WindowsAppRuntimeFramework::GetPackageVersion() };
            VERIFY_ARE_NOT_EQUAL(c_minVersion2.Version, c_minVersion1.Version);
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor2, nullptr, c_minVersion2));
            MddBootstrapShutdown();

            // Incompatible criteria. Verify Initialize+Shutdown brought us
            // back to initial state so we can fail to initialize as expected
            const UINT32 c_Version_MajorMinor3{ Test::Packages::WindowsAppRuntimeFramework::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion3{};
            VERIFY_ARE_EQUAL(c_minVersion3.Version, c_minVersion1.Version);
            VERIFY_ARE_NOT_EQUAL(c_minVersion3.Version, c_minVersion2.Version);
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(c_Version_MajorMinor3, L"NotTheVersionTag", c_minVersion3));

            // Incompatible criteria. Verify Initialize+Shutdown brought us
            // back to initial state so we can fail to initialize as expected
            const UINT32 c_Version_MajorMinor4{ Test::Packages::WindowsAppRuntimeFramework::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion4{ Test::Packages::WindowsAppRuntimeFramework::GetPackageVersion().Version + 1 };
            VERIFY_ARE_NOT_EQUAL(c_minVersion4.Version, c_minVersion1.Version);
            VERIFY_ARE_NOT_EQUAL(c_minVersion4.Version, c_minVersion2.Version);
            VERIFY_ARE_NOT_EQUAL(c_minVersion4.Version, c_minVersion3.Version);
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(c_Version_MajorMinor4, nullptr, c_minVersion4));

            // Same criteria but MinVersion<package version. Verify Initialize+Shutdown brings us back
            // to initial state so we can initialize again with different (but successful) criteria
            const UINT32 c_Version_MajorMinor5{ Test::Packages::WindowsAppRuntimeFramework::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion5{ Test::Packages::WindowsAppRuntimeFramework::GetPackageVersion().Version - 1 };
            VERIFY_ARE_NOT_EQUAL(c_minVersion5.Version, c_minVersion1.Version);
            VERIFY_ARE_NOT_EQUAL(c_minVersion5.Version, c_minVersion2.Version);
            VERIFY_ARE_NOT_EQUAL(c_minVersion5.Version, c_minVersion3.Version);
            VERIFY_ARE_NOT_EQUAL(c_minVersion5.Version, c_minVersion4.Version);
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor5, nullptr, c_minVersion5));
            MddBootstrapShutdown();
        }

        TEST_METHOD(ShutdownWithoutInitialize)
        {
            MddBootstrapShutdown();
            MddBootstrapShutdown();
        }

        TEST_METHOD(GetCurrentPackageInfo_NotPackaged_InvalidParameter)
        {
            const UINT32 c_filter{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };

            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, nullptr, nullptr, nullptr)));
            }
            {
                UINT32 count{};
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, nullptr, nullptr, &count)));
            }

            {
                UINT32 bufferLength{ 1 };
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, nullptr, nullptr)));
            }
            {
                UINT32 bufferLength{ 1 };
                UINT32 count{};
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, nullptr, &count)));
            }

            {
                BYTE buffer[1]{};
                UINT32 bufferLength{ static_cast<UINT32>(ARRAYSIZE(buffer)) };
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, buffer, nullptr)));
            }
        }

        TEST_METHOD(GetCurrentPackageInfo_NotPackaged)
        {
            VerifyGetCurrentPackageInfo();

            winrt::hstring packageFamilyName{ Test::Packages::DynamicDependencyLifetimeManager::c_PackageFamilyName };
            auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));

            VerifyGetCurrentPackageInfo(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 700);

            winrt::Windows::ApplicationModel::AppExtensions::AppExtensionCatalog::Open(L"Does.Not.Exist");

            MddBootstrapShutdown();

            VerifyGetCurrentPackageInfo();
        }

#if defined(TODO_EnableAfterConvertingToTAEF)
        TEST_METHOD(GetCurrentPackageInfo_Packaged)
        {
            VerifyGetCurrentPackageInfo();

            winrt::hstring packageFamilyName{ Test::Packages::DynamicDependencyLifetimeManager::c_PackageFamilyName };
            auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));

            VerifyGetCurrentPackageInfo();
        }
#endif

    private:
        static void VerifyGetCurrentPackageInfo(
            const HRESULT expectedHR = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE),
            const UINT32 expectedCount = 0,
            const UINT32 minExpectedBufferLength = 0)
        {
            UINT32 bufferLength{};
            UINT32 count{};
            VERIFY_ARE_EQUAL(expectedHR, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC, &bufferLength, nullptr, &count)));
            VERIFY_ARE_EQUAL(expectedCount, count);
            if (minExpectedBufferLength > 0)
            {
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"GetCurrentPackageInfo() expectedBufferLength>=%u bufferLength=%u", minExpectedBufferLength, bufferLength) };
                VERIFY_IS_TRUE(bufferLength >= minExpectedBufferLength, message.get());
            }
            else
            {
                VERIFY_ARE_EQUAL(0u, bufferLength);
            }
        }
    };

    class BootstrapTests_Elevated : BootstrapTests
    {
    public:
        BEGIN_TEST_CLASS(BootstrapTests_Elevated)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup_Elevated)
        {
            return Setup();
        }

        TEST_CLASS_CLEANUP(Cleanup_Elevated)
        {
            return Cleanup();
        }

        TEST_METHOD(Initialize_DDLMNotFound_Elevated)
        {
            Initialize_DDLMNotFound();
        }

        TEST_METHOD(Initialize_DDLMMinVersionNoMatch_Elevated)
        {
            Initialize_DDLMMinVersionNoMatch();
        }

        TEST_METHOD(Initialize_Elevated)
        {
            Initialize();
        }

        TEST_METHOD(ShutdownWithoutInitialize_Elevated)
        {
            ShutdownWithoutInitialize();
        }

        TEST_METHOD(GetCurrentPackageInfo_NotPackaged_InvalidParameter_Elevated)
        {
            GetCurrentPackageInfo_NotPackaged_InvalidParameter();
        }

        TEST_METHOD(GetCurrentPackageInfo_NotPackaged_Elevated)
        {
            GetCurrentPackageInfo_NotPackaged();
        }

#if defined(TODO_EnableAfterConvertingToTAEF)
        TEST_METHOD(GetCurrentPackageInfo_Packaged_Elevated)
        {
            GetCurrentPackageInfo_Packaged();
        }
#endif
    };

    class BootstrapPackagedTests
    {
    public:
        BEGIN_TEST_CLASS(BootstrapPackagedTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:NoSplashScreen", L"true")
            TEST_CLASS_PROPERTY(L"UAP:RuntimeBehavior", L"PackagedClassicApp")
            TEST_CLASS_PROPERTY(L"UAP:TrustLevel", L"MediumIL")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup)
        {
            return BootstrapFixtures::Setup();
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            return BootstrapFixtures::Cleanup();
        }

        TEST_METHOD(Initialize_Packaged_NotSupported)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));
        }

        TEST_METHOD(Initialize_Packaged_NOP)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            const auto c_options{ MddBootstrapInitializeOptions_OnPackageIdentity_NOOP };
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize2(c_Version_MajorMinor, nullptr, c_minVersion, c_options));

            MddBootstrapShutdown();
        }

        TEST_METHOD(Initialize_Packaged_NOP_Multiple)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            const auto c_options{ MddBootstrapInitializeOptions_OnPackageIdentity_NOOP };
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize2(c_Version_MajorMinor, nullptr, c_minVersion, c_options));
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize2(c_Version_MajorMinor, nullptr, c_minVersion, c_options));

            MddBootstrapShutdown();
            MddBootstrapShutdown();

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize2(c_Version_MajorMinor, nullptr, c_minVersion, c_options));
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize2(c_Version_MajorMinor, nullptr, c_minVersion, c_options));

            MddBootstrapShutdown();
        }
    };

    class BootstrapRuntimeNotInstalledTests : BootstrapFixtures
    {
    public:
        BEGIN_TEST_CLASS(BootstrapRuntimeNotInstalledTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup)
        {
            wil::unique_hmodule bootstrapDll{ LoadBootstrapDll() };

            BootstrapFixtures::Cleanup();

            SaveBootstrapDll(bootstrapDll.release());
            return true;
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            SaveBootstrapDll(nullptr);
            return true;
        }

        TEST_METHOD(Initialize_RuntimeNotFound)
        {
            PCWSTR c_doesNotExist{ L"DoesNotExist" };
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(c_doesNotExist,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor = 0.0 == No such framework package
            const UINT32 doesNotExist{};
            const PACKAGE_VERSION minVersionMatchAny{};
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(doesNotExist, nullptr, minVersionMatchAny));
        }
    };

    class BootstrapRuntimeNotInstalledTests_Elevated : BootstrapFixtures
    {
    public:
        BEGIN_TEST_CLASS(BootstrapRuntimeNotInstalledTests_Elevated)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup)
        {
            wil::unique_hmodule bootstrapDll{ LoadBootstrapDll() };

            BootstrapFixtures::Cleanup();

            SaveBootstrapDll(bootstrapDll.release());
            return true;
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            SaveBootstrapDll(nullptr);
            return true;
        }

        TEST_METHOD(Initialize_RuntimeNotFound)
        {
            PCWSTR c_doesNotExist{ L"DoesNotExist" };
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(c_doesNotExist,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

            // Major.Minor = 0.0 == No such framework package
            const UINT32 doesNotExist{};
            const PACKAGE_VERSION minVersionMatchAny{};
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(doesNotExist, nullptr, minVersionMatchAny));
        }
    };
}
