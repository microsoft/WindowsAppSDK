// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <winrt/Microsoft.Windows.Media.Capture.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Media::Capture;
using namespace Microsoft::Windows::Media::Capture;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::System;



namespace Test::CameraCaptureUI
{
    class CameraCaptureUITests
    {
    public:
        BEGIN_TEST_CLASS(CameraCaptureUITests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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

        TEST_METHOD(CapturePhoto_ShouldReturnFile)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                END_TEST_METHOD_PROPERTIES();

            // Arrange
            CameraCaptureUI cameraUI;

            // Act
            auto photoOperation = cameraUI.CaptureFileAsync(CameraCaptureUIMode::Photo);
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
        TEST_METHOD(CaptureVideo_ShouldReturnFile)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                END_TEST_METHOD_PROPERTIES();

            // Arrang
            CameraCaptureUI cameraUI;

            // Act
            auto videoOperation = cameraUI.CaptureFileAsync(CameraCaptureUIMode::Video);
            auto video = videoOperation.get();

            // Assert
            if (video != nullptr)
            {
                Log::Comment(L"Video capture was successful.");
                VERIFY_IS_TRUE(video.Name().c_str() != nullptr);
            }
            else
            {
                Log::Error(L"Video capture failed or was canceled.");
                VERIFY_FAIL(L"Video capture returned null.");
            }
        }

        TEST_METHOD(CapturePhoto_ShouldReturnNullOnCancel)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                END_TEST_METHOD_PROPERTIES();

            // Arrange
            CameraCaptureUI cameraUI;

            // Act
            StorageFile photo = nullptr;
            try
            {
                auto photoOperation = cameraUI.CaptureFileAsync(CameraCaptureUIMode::Photo);
                photo = photoOperation.get();
            }
            catch (hresult_canceled const&)
            {
                Log::Comment(L"Photo capture was canceled.");
            }

            // Assert
            VERIFY_IS_NULL(photo);
        }
        TEST_METHOD(CaptureVideo_ShouldReturnNullOnCancel)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                END_TEST_METHOD_PROPERTIES();

            // Arrange
            CameraCaptureUI cameraUI;

            // Simulate cancellation by the user
            StorageFile video = nullptr;
            try
            {
                video = cameraUI.CaptureFileAsync(CameraCaptureUIMode::Video).get();
            }
            catch (hresult_canceled const&)
            {
                Log::Comment(L"Video capture was canceled.");
            }

            // Assert
            VERIFY_IS_NULL(video);
        }
    };
}
