#include "pch.h"
#include "winrt\Microsoft.Windows.Storage.Pickers.h"
#include "winrt\Microsoft.Windows.Media.Capture.h"
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>
#include "winrt\Microsoft.Windows.Media.Capture.h"
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
    class PickersAPITests
    {
    public:
        BEGIN_TEST_CLASS(PickersAPITests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            //TEST_CLASS_PROPERTY(L"RunAs", L"Restricted")
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
        TEST_METHOD(CapturePhoto_ShouldReturnFile_Desktop)
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
                return;
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

        TEST_METHOD(FileSavePicker_ShouldCreateNewFile)
        {
            try
            {
                auto parentWindow = ::GetForegroundWindow();
                winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
                //{
                //    winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI cameraUI(windowId);
                //}
                winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker savePicker(windowId);
                //savePicker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
                savePicker.FileTypeChoices().Insert(L"Plain Text", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));
                savePicker.SuggestedFileName(L"test.txt");
                // Act
                auto fileOperation = savePicker.PickSaveFileAsync();
                auto file = fileOperation.get();

                // Assert
                if (file != nullptr)
                {
                    Log::Comment(L"File save was successful.");
                    VERIFY_IS_TRUE(file.Name().c_str() != nullptr);
                }
                else
                {
                    Log::Error(L"Photo capture failed or was canceled.");
                    VERIFY_FAIL(L"File save returned null.");
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
    };
}
