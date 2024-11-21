// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "winrt\Microsoft.Windows.Media.Capture.h"
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>
#include <TerminalVelocityFeatures-CameraCaptureUI.h>

using namespace std::chrono_literals;
using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt::Windows::Storage;

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace CameraCaptureUITests
{
    // Timeout in milliseconds
    class APITests
    {
    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"CameraCaptureUI-AppxManifest.xml")
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
        // The unit tests will be updated,first test might is there for testing purpose locally.
        // Focusing solely on functional tests for now. 
        TEST_METHOD(CapturePhoto_ShouldReturnFile)
        {
            if (!::Microsoft::Windows::Media::Capture::Feature_CameraCaptureUI::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"CameraCaptureUI API Features are not enabled.");
                return;
            }
            try
            {
                auto parentWindow = ::GetForegroundWindow();
                winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
                winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI(windowId);
                // Configure Photo Settings
                cameraUI.PhotoSettings().Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Png);
                cameraUI.PhotoSettings().AllowCropping(false);
                // Act
                auto photoOperation = cameraUI.CaptureFileAsync(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMode::Photo);
                auto photo = photoOperation.get();

                // Assert
                if (photo != nullptr)
                {
                    Log::Comment(L"Photo capture was successful.");
                    VERIFY_IS_TRUE(photo.Name().c_str() != nullptr);
                }
                else
                {
                    Log::Error(L"Photo capture failed or was canceled.");
                    VERIFY_FAIL(L"Photo capture returned null.");
                }
            }
            catch (const winrt::hresult_error& ex)
            {
                Log::Error((std::wstring(L"Exception thrown: ") + ex.message().c_str()).c_str());
                VERIFY_FAIL(L"Exception occurred during photo capture.");
            }
            catch (const std::exception& ex)
            {
                Log::Error((std::wstring(L"Standard exception thrown: ") + winrt::to_hstring(ex.what()).c_str()).c_str());
                VERIFY_FAIL(L"Standard exception occurred during photo capture.");
            }
        }
        TEST_METHOD(VerifyRequestedPhotoFormatsAreReadCorrectly)
        {
            if (!::Microsoft::Windows::Media::Capture::Feature_CameraCaptureUI::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"CameraCaptureUI API Features are not enabled.");
                return;
            }
            // Arrange
            auto parentWindow = ::GetForegroundWindow();
            winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI(windowId);

            // Act and Assert for JPEG format
            cameraUI.PhotoSettings().Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().Format()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg));

            // Act and Assert for JPEG XR format
            cameraUI.PhotoSettings().Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::JpegXR);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().Format()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::JpegXR));

            // Act and Assert for PNG format
            cameraUI.PhotoSettings().Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Png);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().Format()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Png));
        }


        TEST_METHOD(VerifyRequestedVideoFormatsAreReadCorrectly)
        {
            if (!::Microsoft::Windows::Media::Capture::Feature_CameraCaptureUI::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"CameraCaptureUI API Features are not enabled.");
                return;
            }
            // Arrange
            auto parentWindow = ::GetForegroundWindow();
            winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI(windowId);

            // Act and Assert for MP4 format
            cameraUI.VideoSettings().Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.VideoSettings().Format()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4));

            // Act and Assert for WMV format
            cameraUI.VideoSettings().Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat::Wmv);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.VideoSettings().Format()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat::Wmv));
        }
        TEST_METHOD(VerifyMaxVideoResolutionValues)
        {
            if (!::Microsoft::Windows::Media::Capture::Feature_CameraCaptureUI::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"CameraCaptureUI API Features are not enabled.");
                return;
            }
            // Arrange
            auto parentWindow = ::GetForegroundWindow();
            winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI(windowId);

            // Act and Assert for Highest Available resolution
            cameraUI.VideoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::HighestAvailable);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.VideoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::HighestAvailable));

            // Act and Assert for Low Definition resolution
            cameraUI.VideoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::LowDefinition);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.VideoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::LowDefinition));

            // Act and Assert for Standard Definition resolution
            cameraUI.VideoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::StandardDefinition);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.VideoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::StandardDefinition));

            // Act and Assert for High Definition resolution
            cameraUI.VideoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::HighDefinition);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.VideoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::HighDefinition));
        }

        TEST_METHOD(VerifyMaxPhotoResolutionValues)
        {
            if (!::Microsoft::Windows::Media::Capture::Feature_CameraCaptureUI::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"CameraCaptureUI API Features are not enabled.");
                return;
            }
            // Arrange
            auto parentWindow = ::GetForegroundWindow();
            winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI(windowId);

            // Act and Assert for Highest Available resolution
            cameraUI.PhotoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::HighestAvailable);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::HighestAvailable));

            // Act and Assert for Very Small QVGA resolution
            cameraUI.PhotoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::VerySmallQvga);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::VerySmallQvga));

            // Act and Assert for Small VGA resolution
            cameraUI.PhotoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::SmallVga);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::SmallVga));

            // Act and Assert for Medium XGA resolution
            cameraUI.PhotoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::MediumXga);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::MediumXga));

            // Act and Assert for Large 3M resolution
            cameraUI.PhotoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::Large3M);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::Large3M));

            // Act and Assert for Very Large 5M resolution
            cameraUI.PhotoSettings().MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::VeryLarge5M);
            VERIFY_ARE_EQUAL(static_cast<int>(cameraUI.PhotoSettings().MaxResolution()), static_cast<int>(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::VeryLarge5M));
        }
    };
}
