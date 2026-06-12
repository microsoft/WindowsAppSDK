// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <winrt\Microsoft.Windows.Graphics.Capture.h>
#include <winrt\Windows.Graphics.Capture.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace GraphicsCaptureTests
{
    class APITests
    {
    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"GraphicsCapture-AppxManifest.xml")
            END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD(TryCreateFromWindowId_NullWindowId_ReturnsNull)
        {
            // Arrange: use an invalid (null) WindowId
            winrt::Microsoft::UI::WindowId nullWindowId{ 0 };

            // Act
            auto item{ winrt::Microsoft::Windows::Graphics::Capture::GraphicsCaptureItem::TryCreateFromWindowId(nullWindowId) };

            // Assert: TryCreate should return null for an invalid WindowId
            VERIFY_IS_NULL(item);
        }

        TEST_METHOD(TryCreateFromDisplayId_NullDisplayId_ReturnsNull)
        {
            // Arrange: use an invalid (null) DisplayId
            winrt::Microsoft::UI::DisplayId nullDisplayId{ 0 };

            // Act
            auto item{ winrt::Microsoft::Windows::Graphics::Capture::GraphicsCaptureItem::TryCreateFromDisplayId(nullDisplayId) };

            // Assert: TryCreate should return null for an invalid DisplayId
            VERIFY_IS_NULL(item);
        }
    };
}
