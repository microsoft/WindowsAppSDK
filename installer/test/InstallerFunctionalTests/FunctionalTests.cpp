// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "helpers.h"
#include "constants.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt::Windows::System;

namespace WindowsAppRuntimeInstallerTests
{
    class FunctionalTests
    {
    private:

    public:
        BEGIN_TEST_CLASS(FunctionalTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {

            Log::Comment(WEX::Common::String().Format(L"Test module path: %ws", GetModulePath().c_str()));
            Log::Comment(WEX::Common::String().Format(L"Common root path: %ws", GetCommonRootPath().c_str()));
            Log::Comment(WEX::Common::String().Format(L"Installer path: %ws", GetInstallerPath().c_str()));
            VERIFY_IS_TRUE(std::filesystem::exists(GetInstallerPath()));
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            RemoveAllPackages();
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            RemoveAllPackages();
            return true;
        }

        TEST_METHOD(VerifyInstallerRuns)
        {
            auto result{ RunInstaller() };
            VERIFY_ARE_EQUAL(S_OK, result);
        }

        TEST_METHOD(VerifyArgsQuiet)
        {
            auto result{ RunInstaller(L"--quiet") };
            VERIFY_ARE_EQUAL(S_OK, result);
        }

        TEST_METHOD(VerifyArgsHelp)
        {
            auto result{ RunInstaller(L"--help") };
            VERIFY_ARE_EQUAL(S_OK, result);
        }
        TEST_METHOD(VerifyArgsInvalid)
        {
            // Installer should fail with bad arguments error code.
            auto result{ RunInstaller(L"--kittens") };
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS), result);
        }

        TEST_METHOD(RunInstallerAndVerifyPackages)
        {
            // Run and verify installer
            auto result{ RunInstaller() };
            VERIFY_ARE_EQUAL(S_OK, result);

            // Verify frameworks based on system architecture
            auto systemArch{ GetSystemArchitecture() };

            if (systemArch == ProcessorArchitecture::X86)
            {
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86FrameworkName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86MainName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86SingletonName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86DDLMName));
            }

            if (systemArch == ProcessorArchitecture::X64)
            {
                // x86 Framework should also be present.
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86FrameworkName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x64FrameworkName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x64MainName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x64SingletonName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86DDLMName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x64DDLMName));
            }

            if (systemArch == ProcessorArchitecture::Arm64)
            {
                // All frameworks are applicable on Arm64.
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86FrameworkName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x64FrameworkName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_arm64FrameworkName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_arm64MainName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_arm64SingletonName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x86DDLMName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_x64DDLMName));
                VERIFY_ARE_EQUAL(true, IsPackageRegistered(c_arm64DDLMName));
            }
        }
	};
}
