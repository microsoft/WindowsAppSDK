#include "pch.h"
#include "helpers.h"
#include "constants.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace winrt::Windows::System;

namespace ProjectReunionInstallerTests
{
	TEST_CLASS(FunctionalTests)
	{
	public:

        TEST_METHOD_INITIALIZE(Initialize)
        {
            RemoveAllPackages();
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
            RemoveAllPackages();
        }

        TEST_METHOD(VerifyInstallerRuns)
        {
            auto result = RunInstaller();
            Assert::AreEqual(S_OK, result);
        }

        TEST_METHOD(VerifyArgsQuiet)
        {
            auto result = RunInstaller(L"--quiet");
            Assert::AreEqual(S_OK, result);
        }

        TEST_METHOD(VerifyArgsHelp)
        {
            auto result = RunInstaller(L"--help");
            Assert::AreEqual(S_OK, result);
        }
        TEST_METHOD(VerifyArgsInvalid)
        {
            // Installer should fail with bad arguments error code.
            auto result = RunInstaller(L"--kittens");
            Assert::AreEqual(HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS), result);
        }

        TEST_METHOD(RunInstallerAndVerifyPackages)
        {
            // Run and verify installer
            auto result = RunInstaller();
            Assert::AreEqual(S_OK, result);

            // Verify frameworks based on system architecture
            auto systemArch = GetSystemArchitecture();

            if (systemArch == ProcessorArchitecture::X86)
            {
                Assert::AreEqual(true, IsPackageRegistered(c_x86FrameworkName));
                Assert::AreEqual(true, IsPackageRegistered(c_x86MainName));
                Assert::AreEqual(true, IsPackageRegistered(c_x86DDLMName));
            }

            if (systemArch == ProcessorArchitecture::X64)
            {
                // x86 Framework should also be present.
                Assert::AreEqual(true, IsPackageRegistered(c_x86FrameworkName));
                Assert::AreEqual(true, IsPackageRegistered(c_x64FrameworkName));
                Assert::AreEqual(true, IsPackageRegistered(c_x64MainName));
                Assert::AreEqual(true, IsPackageRegistered(c_x86DDLMName));
                Assert::AreEqual(true, IsPackageRegistered(c_x64DDLMName));
            }

            if (systemArch == ProcessorArchitecture::Arm64)
            {
                // All frameworks are applicable on Arm64.
                Assert::AreEqual(true, IsPackageRegistered(c_x86FrameworkName));
                Assert::AreEqual(true, IsPackageRegistered(c_x64FrameworkName));
                Assert::AreEqual(true, IsPackageRegistered(c_arm64FrameworkName));
                Assert::AreEqual(true, IsPackageRegistered(c_arm64MainName));
                Assert::AreEqual(true, IsPackageRegistered(c_x86DDLMName));
                Assert::AreEqual(true, IsPackageRegistered(c_x64DDLMName));
                Assert::AreEqual(true, IsPackageRegistered(c_arm64DDLMName));
            }
        }
	};
}
