// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
//using namespace winrt;
//using namespace Windows::Foundation;
//using namespace Windows::Storage;
//using namespace Windows::Media::Capture;
//using namespace Microsoft::Windows::Media::Capture;
//using namespace winrt::Windows::ApplicationModel::Activation;
//using namespace winrt::Windows::Foundation::Collections;
//using namespace winrt::Windows::Management::Deployment;
//using namespace winrt::Windows::System;


namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;


namespace Test::CameraCaptureUI
{
    struct MockWindowId
    {
        UINT64 Value;
    };

    class CameraCaptureUITests
    {
    public:
        BEGIN_TEST_CLASS(CameraCaptureUITests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"CameraCaptureUI-AppxManifest.xml")
            END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
			//::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
			//::Test::Bootstrap::CleanupPackages();
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

        TEST_METHOD(CapturePhoto_ShouldReturnFile)
        {
            try
            {
                // Arrange
                //MockWindowId mockWindowId{ 12345 };
                //com_ptr<Microsoft::Windows::Media::Capture::CameraCaptureUI> cameraUI = make_self<Microsoft::Windows::Media::Capture::CameraCaptureUI>(reinterpret_cast<WindowId&>(mockWindowId));
                //auto cameraUI{ Microsoft::Windows::Media::Capture::CameraCaptureUI(reinterpret_cast<WindowId&>(mockWindowId)) };
                winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({12345});
                
                // Act
                auto photoOperation = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Photo);
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
            catch (...)
            {
                Log::Error(L"Unknown exception thrown during photo capture.");
                VERIFY_FAIL(L"Unknown exception occurred during photo capture.");
            }
        }
        

        //TEST_METHOD(CaptureVideo_ShouldReturnFile)
        //{
        //    BEGIN_TEST_METHOD_PROPERTIES()
        //        TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
        //        END_TEST_METHOD_PROPERTIES();

        //    // Arrange
        //    MockWindowId mockWindowId{ 12345 };
        //    CameraCaptureUI cameraUI{ mockWindowId };

        //    // Act
        //    auto videoOperation = cameraUI.CaptureFileAsync(CameraCaptureUIMode::Video);
        //    auto video = videoOperation.get();

        //    // Assert
        //    if (video != nullptr)
        //    {
        //        Log::Comment(L"Video capture was successful.");
        //        VERIFY_IS_TRUE(video.Name().c_str() != nullptr);
        //    }
        //    else
        //    {
        //        Log::Error(L"Video capture failed or was canceled.");
        //        VERIFY_FAIL(L"Video capture returned null.");
        //    }
        //}

        TEST_METHOD(CapturePhoto_ShouldReturnNullOnCancel)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                END_TEST_METHOD_PROPERTIES();

            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
            winrt::Windows::Storage::StorageFile photo = nullptr;
            // Act
            try
            {
                auto photoOperation = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Photo);
                photo = photoOperation.get();
            }
            catch (winrt::hresult_canceled const&)
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
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
            winrt::Windows::Storage::StorageFile video = nullptr;
            // Act
            try
            {
                video = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Video).get();
            }
            catch (winrt::hresult_canceled const&)
            {
                Log::Comment(L"Video capture was canceled.");
            }

            // Assert
            VERIFY_IS_NULL(video);
        }
    };
}
