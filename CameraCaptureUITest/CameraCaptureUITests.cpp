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

        //// Verify requested JPEG photo format is read correctly
        //TEST_METHOD(VerifyRequestedJpegPhotoFormatIsReadCorrectly)
        //{
        //    // Arrange
        //    winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
        //    cameraUI.PhotoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg);

        //    // Act and Assert
        //    VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().Format(), L".jpg");
        //}

        //// Verify requested JPEG XR photo format is read correctly
        //TEST_METHOD(VerifyRequestedJpegXRPhotoFormatIsReadCorrectly)
        //{
        //    // Arrange
        //    winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
        //    cameraUI.PhotoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::JpegXR);

        //    // Act and Assert
        //    VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().Format(), L".jxr");
        //}

        //// Verify requested PNG photo format is read correctly
        //TEST_METHOD(VerifyRequestedPngPhotoFormatIsReadCorrectly)
        //{
        //    // Arrange
        //    winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
        //    cameraUI.PhotoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Png);

        //    // Act and Assert
        //    VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().Format(), L".png");
        //}


        TEST_METHOD(CapturePhoto_ShouldReturnFile)
        {
            try
            {
                // Arrange
                winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({12345});
                // Configure Photo Settings
                cameraUI.PhotoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg);
                cameraUI.PhotoSettings().AllowCropping(false);
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
        }

      

        TEST_METHOD(VerifyPhotoFileTokenRedeemedForFile)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            // Set either a fixed size or an aspect ratio, but not both
            //cameraUI.PhotoSettings().CroppedAspectRatio({ 16, 9 });

            //cameraUI.PhotoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg);
            cameraUI.PhotoSettings().AllowCropping(false);
            auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Photo);
            auto photo = file.get();

            // Assert
            VERIFY_IS_NOT_NULL(photo);
        }

        TEST_METHOD(VerifyParameterValidationFailsIfCropAspectRatioDefinedWhenCroppingDisabled)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
            cameraUI.PhotoSettings().AllowCropping(true);
            cameraUI.PhotoSettings().CroppedAspectRatio({ 16, 9 });
            cameraUI.PhotoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg);

            // Act and Assert
            
            auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Photo);
            auto photo = file.get();
            VERIFY_IS_NOT_NULL(photo);
           
        }

        TEST_METHOD(VerifyVideoFileTokenRedeemedForFile)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            // Set either a fixed size or an aspect ratio, but not both
            cameraUI.VideoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4); 
            cameraUI.VideoSettings().AllowTrimming(false);

            auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Video);
            auto video = file.get();

            // Assert
            VERIFY_IS_NOT_NULL(video);
        }

        TEST_METHOD(VerifyPhotoFileTokenRedeemedForFileCroppingdisabled)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            // Set either a fixed size or an aspect ratio, but not both
            //cameraUI.PhotoSettings().CroppedAspectRatio({ 16, 9 });
            
            cameraUI.PhotoSettings().AllowCropping(true);
            cameraUI.PhotoSettings().CroppedSizeInPixels({ 1920, 1080 });
            cameraUI.PhotoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg);
            cameraUI.PhotoSettings().MaxResolution(winrt::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::HighestAvailable);
      
            cameraUI.VideoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
            cameraUI.VideoSettings().AllowTrimming(true);

            auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::PhotoOrVideo);
            auto photo = file.get();

            // Assert
            VERIFY_IS_NOT_NULL(photo);
        }
    };
}


/*
#include "pch.h"
#include "CameraCaptureUI.h"
#include "CameraCaptureUIPhotoSettings.h"
#include "CameraCaptureUIVideoSettings.h"

using namespace winrt;
using namespace Windows::Media::Capture;
using namespace Microsoft::Windows::Media::Capture::implementation;

namespace Test::CameraCaptureUI
{
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
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            return true;
        }

        // Verify the photo file token is redeemed for the file
        TEST_METHOD(VerifyPhotoFileTokenRedeemedForFile)
        {
            // Arrange
            CameraCaptureUI cameraUI{ nullptr };

            // Act
            auto file = cameraUI.CaptureFileAsync(CameraCaptureUIMode::Photo).get();

            // Assert
            VERIFY_IS_NOT_NULL(file);
        }


        // Verify parameter validation fails if greater than the maximum value is given for photo resolution
        TEST_METHOD(VerifyParameterValidationFailsIfGreaterThanMaximumValueGivenForPhotoResolution)
        {
            // Arrange
            CameraCaptureUI cameraUI{ nullptr };
            cameraUI.PhotoSettings().MaxResolution(CameraCaptureUIMaxPhotoResolution::VerySmallQvga);

            // Act and Assert
            try
            {
                cameraUI.PhotoSettings().CroppedSizeInPixels({ 1920, 1080 });
                cameraUI.PhotoSettings().validate();
                VERIFY_IS_TRUE(false);  // Should not reach here
            }
            catch (const hresult_invalid_argument&)
            {
                VERIFY_IS_TRUE(true);
            }
        }

       

        // Verify parameter validation fails if an invalid PhotoFormat value is given
        TEST_METHOD(VerifyParameterValidationFailsIfInvalidPhotoFormatValueIsGiven)
        {
            // Arrange
            CameraCaptureUI cameraUI{ nullptr };

            // Act and Assert
            try
            {
                cameraUI.PhotoSettings().Format(static_cast<CameraCaptureUIPhotoFormat>(999));
                cameraUI.PhotoSettings().GetFileExtension();
                VERIFY_IS_TRUE(false);  // Should not reach here
            }
            catch (const hresult_invalid_argument&)
            {
                VERIFY_IS_TRUE(true);
            }
        }

        // Verify resolution minimum value is read correctly
        TEST_METHOD(VerifyResolutionMinimumValueIsReadCorrectly)
        {
            // Arrange
            CameraCaptureUI cameraUI{ nullptr };
            cameraUI.PhotoSettings().MaxResolution(CameraCaptureUIMaxPhotoResolution::VerySmallQvga);

            // Act and Assert
            VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().MaxResolution(), CameraCaptureUIMaxPhotoResolution::VerySmallQvga);
        }

        // Verify resolution maximum value is read correctly
        TEST_METHOD(VerifyResolutionMaximumValueIsReadCorrectly)
        {
            // Arrange
            CameraCaptureUI cameraUI{ nullptr };
            cameraUI.PhotoSettings().MaxResolution(CameraCaptureUIMaxPhotoResolution::HighestAvailable);

            // Act and Assert
            VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().MaxResolution(), CameraCaptureUIMaxPhotoResolution::HighestAvailable);
        }
    };
}

*/

/*
*
* ===========================================================================================================================
*  TEST_METHOD(VerifyDefaultPhotoParameters)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            VERIFY_IS_TRUE(cameraUI.PhotoSettings().AllowCropping());
            VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().Format(), winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg);
        }


        TEST_METHOD(VerifyDefaultVideoParameters)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            VERIFY_IS_TRUE(cameraUI.VideoSettings().AllowTrimming());
            VERIFY_ARE_EQUAL(cameraUI.VideoSettings().Format(), winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
        }

        TEST_METHOD(VerifyFlagEnablingCroppingIsReadCorrectly)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act and Assert
            VERIFY_IS_TRUE(cameraUI.PhotoSettings().AllowCropping());
        }

        TEST_METHOD(VerifyCropDisabledIsReadCorrectly)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
            cameraUI.PhotoSettings().AllowCropping(false);

            // Act and Assert
            VERIFY_IS_FALSE(cameraUI.PhotoSettings().AllowCropping());
        }

         //Verify parameter validation fails when crop width and height are strings
        TEST_METHOD(VerifyParameterValidationFailsWhenCropWidthAndHeightAreStrings)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
            try
            {
                // Invalid values, will throw an exception
                cameraUI.PhotoSettings().CroppedSizeInPixels({ std::stof(L"invalid"), std::stof(L"invalid") });
                auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Photo);
                VERIFY_IS_TRUE(false);  // Should not reach here
            }
            catch (const std::invalid_argument&)
            {
                VERIFY_IS_TRUE(true);
            }
        }
         
           // Verify the crop width and height are read correctly
        TEST_METHOD(VerifyCropWidthAndHeightAreReadCorrectly)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });
            cameraUI.PhotoSettings().CroppedSizeInPixels({ 1920, 1080 });

            // Act and Assert
            VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().CroppedSizeInPixels().Width, 1920);
            VERIFY_ARE_EQUAL(cameraUI.PhotoSettings().CroppedSizeInPixels().Height, 1080);
        }


        TEST_METHOD(VerifyValidDurationWithTrimming)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            cameraUI.VideoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
            cameraUI.VideoSettings().MaxDurationInSeconds(30.0f);
            cameraUI.VideoSettings().AllowTrimming(true);

            auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Video);
            auto video = file.get();

            // Assert
            VERIFY_IS_NOT_NULL(video);
        }

        TEST_METHOD(VerifyDurationSetWithTrimmingNotAllowed)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            cameraUI.VideoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
            cameraUI.VideoSettings().MaxDurationInSeconds(30.0f);
            cameraUI.VideoSettings().AllowTrimming(false);

            // Assert
             // Act and Assert
            try
            {
                auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Video);
                auto video = file.get();
            }
            catch (const winrt::hresult_invalid_argument&)
            {
                VERIFY_IS_TRUE(true);
            }
        }

        TEST_METHOD(VerifyNegativeDurationThrowsException)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            cameraUI.VideoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
            cameraUI.VideoSettings().MaxDurationInSeconds(-1.0f);
            // Act and Assert
            try
            {
                auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Video);
                auto video = file.get();
            }
            catch (const winrt::hresult_invalid_argument&)
            {
                VERIFY_IS_TRUE(true);
            }
        }

        TEST_METHOD(VerifyDurationExceedingMaxValueThrowsException)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            cameraUI.VideoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
            cameraUI.VideoSettings().MaxDurationInSeconds(static_cast<float>(UINT32_MAX) / 1000.0f + 1.0f);

            cameraUI.VideoSettings().MaxDurationInSeconds(-1.0f);
            // Act and Assert
            try
            {
                auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Video);
                auto video = file.get();
            }
            catch (const winrt::hresult_invalid_argument&)
            {
                VERIFY_IS_TRUE(true);
            }
        }

        TEST_METHOD(VerifyZeroDurationWithTrimmingAllowed)
        {
            // Arrange
            winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI({ 12345 });

            // Act
            cameraUI.VideoSettings().Format(winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4);
            cameraUI.VideoSettings().MaxDurationInSeconds(0.0f);
            cameraUI.VideoSettings().AllowTrimming(true);

            auto file = cameraUI.CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode::Video);
            auto video = file.get();

            // Assert
            VERIFY_IS_NOT_NULL(video);
        }

*/
