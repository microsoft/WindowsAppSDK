// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <FrameworkUdk/Containment.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

namespace Test::StoragePickersTests
{
    class StoragePickersTests
    {
    public:
        BEGIN_TEST_CLASS(StoragePickersTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA") // MTA is required for ::Test::Bootstrap::SetupPackages()
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"UAP")
            //TEST_CLASS_PROPERTY(L"RunAs", L"UAP")

            END_TEST_CLASS()

            TEST_CLASS_SETUP(ClassSetup)
        {
            ::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());

            // The test method setup and execution is on a different thread than the class setup.
            // Initialize the framework for the test thread.
            ::Test::Bootstrap::SetupBootstrap();
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            ::Test::Bootstrap::CleanupBootstrap();
            return true;
        }
       // The unit tests will be updated,first test might is there for testing purpose locally.
       // Focusing solely on functional tests for now.

       // Commenting out this test as it is an E2E scenario test that requires UI automation for pipeline execution.
       /*

        TEST_METHOD(FileOpenPicker_ShouldPickFile)
        {
            try
            {
                auto parentWindow = ::GetForegroundWindow();
                winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
                winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker{ windowId };
                picker.FileTypeFilter().Append(L"*");
                // Act
                auto operation = picker.PickSingleFileAsync();
                auto file = operation.get();
                auto path = file.Path();
                // Assert
                if (file != nullptr)
                {
                    Log::Comment(L"File open was successful");
                }
                else
                {
                    Log::Error(L"File open canceled.");
                }
            }
            catch (const winrt::hresult_error& ex)
            {
                Log::Error((std::wstring(L"Exception thrown: ") + ex.message().c_str()).c_str());
                VERIFY_FAIL(L"Exception occurred during file open picker.");
            }
            catch (const std::exception& ex)
            {
                Log::Error((std::wstring(L"Standard exception thrown: ") + winrt::to_hstring(ex.what()).c_str()).c_str());
                VERIFY_FAIL(L"Standard exception occurred during file open picker.");
            }
        }

        TEST_METHOD(FileSavePicker_ShouldCreateNewFile)
        {
            try
            {
                auto parentWindow = ::GetForegroundWindow();
                winrt::Microsoft::UI::WindowId windowId{ reinterpret_cast<uint64_t>(parentWindow) };
                winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker savePicker(windowId);
                //savePicker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
                savePicker.FileTypeChoices().Insert(L"Plain Text", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));
                savePicker.SuggestedFileName(L"test.txt");
                // Act
                auto fileOperation = savePicker.PickSaveFileAsync();
                auto file = fileOperation.get();
                auto path = file.Path();

                // Assert
                if (file != nullptr)
                {
                    Log::Comment(L"File save was successful.");
                }
                else
                {
                    Log::Error(L"File save failed or was canceled.");
                }
            }
            catch (const winrt::hresult_error& ex)
            {
                Log::Error((std::wstring(L"Exception thrown: ") + ex.message().c_str()).c_str());
                VERIFY_FAIL(L"Exception occurred during file save picker.");
            }
            catch (const std::exception& ex)
            {
                Log::Error((std::wstring(L"Standard exception thrown: ") + winrt::to_hstring(ex.what()).c_str()).c_str());
                VERIFY_FAIL(L"Standard exception occurred during file save picker.");
            }
        }

       */


        TEST_METHOD(VerifyFileOpenPickerOptionsAreReadCorrectly)
        {
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);

            picker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
            VERIFY_ARE_EQUAL(picker.SuggestedStartLocation(), winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

            picker.CommitButtonText(L"commit");
            VERIFY_ARE_EQUAL(picker.CommitButtonText(), L"commit");

            picker.FileTypeFilter().Append(L"*");
            VERIFY_ARE_EQUAL(picker.FileTypeFilter().GetAt(0), L"*");

            auto openPickerChoices = winrt::single_threaded_vector<winrt::hstring>();
            openPickerChoices.Append(L".txt");
            picker.FileTypeChoices().Insert(L"Documents", openPickerChoices);
            VERIFY_ARE_EQUAL(picker.FileTypeChoices().Lookup(L"Documents").GetAt(0), L".txt");

            picker.SuggestedFolder(L"C:\\temp_fileopenpicker_ut_temp");
            VERIFY_ARE_EQUAL(picker.SuggestedFolder(), L"C:\\temp_fileopenpicker_ut_temp");

            picker.SuggestedStartFolder(L"C:\\temp_fileopenpicker_ut_start");
            VERIFY_ARE_EQUAL(picker.SuggestedStartFolder(), L"C:\\temp_fileopenpicker_ut_start");
        }

        TEST_METHOD(VerifyFileSavePickerOptionsAreReadCorrectly)
        {
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            picker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
            VERIFY_ARE_EQUAL(picker.SuggestedStartLocation(), winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

            std::filesystem::remove_all(L"C:\\temp_filesavepicker_ut_temp");
            picker.SuggestedFolder(L"C:\\temp_filesavepicker_ut_temp");
            VERIFY_ARE_EQUAL(picker.SuggestedFolder(), L"C:\\temp_filesavepicker_ut_temp");

            picker.CommitButtonText(L"commit");
            VERIFY_ARE_EQUAL(picker.CommitButtonText(), L"commit");

            auto filters = winrt::single_threaded_vector<winrt::hstring>();
            filters.Append(L"*");
            picker.FileTypeChoices().Insert(L"All Files", filters);
            VERIFY_ARE_EQUAL(picker.FileTypeChoices().Lookup(L"All Files").GetAt(0), L"*");

            picker.SuggestedStartFolder(L"C:\\temp_filesavepicker_start");
            VERIFY_ARE_EQUAL(picker.SuggestedStartFolder(), L"C:\\temp_filesavepicker_start");
        }

        TEST_METHOD(VerifyFolderPickerOptionsAreReadCorrectly)
        {
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FolderPicker picker(windowId);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);

            picker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
            VERIFY_ARE_EQUAL(picker.SuggestedStartLocation(), winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

            picker.CommitButtonText(L"commit");
            VERIFY_ARE_EQUAL(picker.CommitButtonText(), L"commit");

            picker.SuggestedFolder(L"C:\\temp_folderpicker_ut_temp");
            VERIFY_ARE_EQUAL(picker.SuggestedFolder(), L"C:\\temp_folderpicker_ut_temp");

            picker.SuggestedStartFolder(L"C:\\temp_folderpicker_ut_start");
            VERIFY_ARE_EQUAL(picker.SuggestedStartFolder(), L"C:\\temp_folderpicker_ut_start");
        }

    };
}
