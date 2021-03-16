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
            Assert::AreEqual(result, S_OK);
        }

        TEST_METHOD(VerifyArgsQuiet)
        {
            auto result = RunInstaller(L"--quiet");
            Assert::AreEqual(result, S_OK);
        }

        TEST_METHOD(VerifyArgsHelp)
        {
            auto result = RunInstaller(L"--help");
            Assert::AreEqual(result, S_OK);
        }
        TEST_METHOD(VerifyArgsInvalid)
        {
            // Installer should fail with bad arguments error code.
            auto result = RunInstaller(L"--kittens");
            Assert::AreEqual(result, HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS));
        }

        TEST_METHOD(RunInstallerAndVerifyPackages)
        {
            // Run and verify installer
            auto result = RunInstaller();
            Assert::AreEqual(result, S_OK);

            // Verify frameworks based on system architecture
            auto systemArch = GetSystemArchitecture();

            // x86 should be registered on every platform.
            Assert::AreEqual(true, IsPackageRegistered(c_x86FrameworkName));

            // x64 should be registered on x64 and arm64.
            if (systemArch == ProcessorArchitecture::X64 || systemArch == ProcessorArchitecture::Arm64)
            {
                Assert::AreEqual(true, IsPackageRegistered(c_x64FrameworkName));
            }

            // arm64 should be registered on arm64.
            if (systemArch == ProcessorArchitecture::Arm64)
            {
                Assert::AreEqual(true, IsPackageRegistered(c_arm64FrameworkName));
            }
        }
	};
}
