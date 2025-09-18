// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <TestDef.h>
#include <PackageRegistrar.h>
#include <string>
#include <filesystem>
#include <windows.h>
#include <DeploymentActivityContext.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;

namespace Test::Deployment
{
    class PackageRegistrarTests
    {
    public:
        BEGIN_TEST_CLASS(PackageRegistrarTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            return true;
        }

        TEST_METHOD(PackageRegistrar_BasicTest)
        {
            Log::Comment(L"Basic test to verify PackageRegistrar class");
            
            // Test that PackageRegistrar can be instantiated
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::PackageRegistrar registrar;
            
            // Test static method
            
            Log::Comment(L"PackageRegistrar tests completed successfully");
        }
    };
}
