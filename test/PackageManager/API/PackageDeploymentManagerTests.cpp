// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "PackageDeploymentManagerTests.h"

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;
namespace TPM = ::Test::Packages::Main;
namespace TPMT = ::Test::PackageManager::Tests;

namespace Test::PackageManager::Tests
{
    class PackageDeploymentManagerTests : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")    /****SEEME****/
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows10_20H1OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires >= 20H1 (Vibranium). Skipping tests");
                return true;
            }

            TD::DumpExecutionContext();

            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(IsPackageDeploymentFeatureSupported_InvalidParameter)
        {
            const auto feature{ static_cast<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature>(0) };
            VERIFY_IS_FALSE(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature));
        }
    };
}

void Test::PackageManager::Tests::VerifyDeploymentSucceeded(
    const winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult& deploymentResult,
    PCSTR filename,
    int line,
    PCSTR function)
{
    WEX::Common::String source;
    source.Format(L"File: %hs, Function: %hs, Line: %d", filename, function, line);
    PCWSTR message{ static_cast<PCWSTR>(source) };

    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"VERIFY Deployment Suceeded: %ls", message));

    const bool ok{ (deploymentResult.Status() == winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess) &&
                   (deploymentResult.Error() == S_OK) &&
                   (deploymentResult.ExtendedError() == S_OK) &&
                   deploymentResult.ErrorText().empty() };
    VERIFY_IS_TRUE(ok, WEX::Common::String().Format(L"Status:%d Error:0x%X ExtendedError:0x%X ErrorText:%ls %ls",
                   deploymentResult.Status(), deploymentResult.Error(), deploymentResult.ExtendedError(),
                   deploymentResult.ErrorText().c_str(), message));
}
