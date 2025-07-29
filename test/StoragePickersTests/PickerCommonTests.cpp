// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <wil/cppwinrt.h>

#include <FrameworkUdk/Containment.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>

#include "..\..\dev\Interop\StoragePickers\PickerCommon.h"

#include <vector>
#include <tuple>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace PickerCommon;

namespace Test::PickerCommonTests
{
    class PickerCommonTests
    {
    private:
        static const wchar_t s_rawStringWithNull[];
        static const winrt::hstring s_embeddedNullString;
    public:
        BEGIN_TEST_CLASS(PickerCommonTests)
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

        TEST_METHOD(VerifyConfigureDialog_WhenPickerParameters_FileTypeFilterNotSpecified_ExpectSuccess)
        {
            // Arrange.
            PickerParameters parameters{};

            // Act.
            auto dialog = winrt::create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CLSCTX_INPROC_SERVER);
            parameters.ConfigureDialog(dialog);

            // Assert.
            // Expect the action's successful.

        }

        TEST_METHOD(VerifyConfigureFileSaveDialog_WhenSuggestedSaveFilePathFolderDeleted_ExpectItsFileNameStillWork)
        {
            // Arrange.
            PickerParameters parameters{};
            parameters.SuggestedFileName = L"LowPriority.txt";
            parameters.SuggestedSaveFilePath = L"C:\\temp_filesavepicker_ut_temp\\HighPriority.txt";

            // Ensure the folder of SuggestedSaveFilePath doesn't exist anumore.
            std::filesystem::remove_all(L"C:\\temp_filesavepicker_ut_temp");

            // Act.
            auto dialog = winrt::create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
            parameters.ConfigureFileSaveDialog(dialog);

            // Assert.
            wil::unique_cotaskmem_string dialogFileName{};
            dialog->GetFileName(dialogFileName.put());
            VERIFY_IS_NOT_NULL(dialogFileName, L"The save dialog's file name should be set.");

            auto actualFileName = winrt::hstring{ dialogFileName.get() };
            auto message = L"Expected file name: HighPriority.txt, Actual: " + actualFileName;
            VERIFY_ARE_EQUAL(L"HighPriority.txt", actualFileName, message.c_str());
        }

        TEST_METHOD(VerifyConfigureFileSaveDialog_WhenSuggestedSaveFilePathFileNameEmptyAndFolderDeleted_ExpectItsFileNameStillWork)
        {
            // Arrange.
            PickerParameters parameters{};
            parameters.SuggestedFileName = L"LowPriority.txt";
            parameters.SuggestedSaveFilePath = L"C:\\temp_filesavepicker_ut_temp\\";

            // Ensure the folder of SuggestedSaveFilePath doesn't exist anumore.
            std::filesystem::remove_all(L"C:\\temp_filesavepicker_ut_temp");

            // Act.
            auto dialog = winrt::create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
            parameters.ConfigureFileSaveDialog(dialog);

            // Assert.
            wil::unique_cotaskmem_string dialogFileName{};
            dialog->GetFileName(dialogFileName.put());

            // Even the empty file name of SuggestedSaveFilePath takes precedence over SuggestedFileName.
            VERIFY_IS_NULL(dialogFileName, L"The save dialog's file name should be empty.");
        }

        TEST_METHOD(VerifyFilters_FileOpenPickerWhenFileTypeFiltersDefinedExpectAddingUnionedType)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            picker.FileTypeFilter().Append(L".txt");
            picker.FileTypeFilter().Append(L".doc");

            // Act.
            PickerParameters parameters{};
            parameters.CaptureFilterSpec(picker.FileTypeFilter().GetView());

            // Assert.
            VERIFY_ARE_EQUAL(parameters.FileTypeFilterPara.size(), 3);

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[0].pszSpec),
                L"*.txt");

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[1].pszSpec),
                L"*.doc");

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[2].pszSpec),
                L"*.txt;*.doc");
        }

        TEST_METHOD(VerifyFilters_FileOpenPickerWhenNoFileTypeFiltersDefinedExpectAsteriskSpec)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            // Act.
            PickerParameters parameters{};
            parameters.CaptureFilterSpec(picker.FileTypeFilter().GetView());

            // Assert.
            VERIFY_ARE_EQUAL(parameters.FileTypeFilterPara.size(), 1);

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[0].pszSpec),
                L"*");
        }

        TEST_METHOD(VerifyFilters_FileOpenPickerWhenAsteriskFileTypeFilterDefinedExpectAsteriskSpec)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            picker.FileTypeFilter().Append(L"*");

            // Act.
            PickerParameters parameters{};
            parameters.CaptureFilterSpec(picker.FileTypeFilter().GetView());

            // Assert.
            VERIFY_ARE_EQUAL(parameters.FileTypeFilterPara.size(), 1);

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[0].pszSpec),
                L"*");
        }

        TEST_METHOD(VerifyFilters_FileSavePickerWhenFileTypeChoicesDefinedExpectMatchingSpec)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            picker.FileTypeChoices().Insert(
                L"Documents", winrt::single_threaded_vector<winrt::hstring>({ L".txt", L".doc", L".docx" }));
            picker.FileTypeChoices().Insert(
                L"Pictures", winrt::single_threaded_vector<winrt::hstring>({ L".png", L".jpg", L".jpeg", L".bmp" }));

            // Act.
            PickerParameters parameters{};
            parameters.CaptureFilterSpec(picker.FileTypeChoices().GetView());

            // Assert.
            VERIFY_ARE_EQUAL(parameters.FileTypeFilterPara.size(), 2);

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[0].pszSpec),
                L"*.txt;*.doc;*.docx");
            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[1].pszSpec),
                L"*.png;*.jpg;*.jpeg;*.bmp");
        }

        TEST_METHOD(VerifyFilters_FileSavePickerWhenNoFileTypeChoicesDefinedExpectAsteriskSpec)
        {
            // Note that is is a different behavior than the UWP pickers, where FileTypeChoices are required.

            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            // Act.
            PickerParameters parameters{};
            parameters.CaptureFilterSpec(picker.FileTypeChoices().GetView());

            // Assert.
            VERIFY_ARE_EQUAL(parameters.FileTypeFilterPara.size(), 1);

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[0].pszSpec),
                L"*");
        }

        TEST_METHOD(VerifyFilters_FileSavePickerWhenAsteriskFileTypeChoicesDefinedExpectAsteriskSpec)
        {
            // Note that is is a different behavior than the UWP pickers, where FileTypeChoices cannot be *.

            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            picker.FileTypeChoices().Insert(
                L"All Files", winrt::single_threaded_vector<winrt::hstring>({ L"*" }));

            // Act.
            PickerParameters parameters{};
            parameters.CaptureFilterSpec(picker.FileTypeChoices().GetView());

            // Assert.
            VERIFY_ARE_EQUAL(parameters.FileTypeFilterPara.size(), 1);

            VERIFY_ARE_EQUAL(
                std::wstring(parameters.FileTypeFilterPara[0].pszSpec),
                L"*");
        }

        TEST_METHOD(VerifyFileSaveDialog_SuggestedFileNameWorksWhenSuggestedSaveFilePathNotSet)
        {
            // Arrange.
            PickerParameters parameters{};
            parameters.SuggestedFileName = L"MyFile1.txt";

            // Act.
            auto dialog = winrt::create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
            parameters.ConfigureFileSaveDialog(dialog);

            // Assert.
            wil::unique_cotaskmem_string fileName{};
            dialog->GetFileName(fileName.put());
            VERIFY_ARE_EQUAL(L"MyFile1.txt", std::wstring(fileName.get()));
        }

        TEST_METHOD(VerifyFileSaveDialog_SuggestedSaveFilePathTakesPrecedenceOverSuggestedFileName)
        {
            // Arrange.
            PickerParameters parameters{};
            parameters.SuggestedSaveFilePath = L"C:\\temp\\MyFile2.txt";
            parameters.SuggestedFileName = L"MyFile1.txt";

            // Act.
            auto dialog = winrt::create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
            parameters.ConfigureFileSaveDialog(dialog);

            // Assert.
            winrt::com_ptr<IShellItem> folderItem{};
            dialog->GetFolder(folderItem.put());
            wil::unique_cotaskmem_string dialogFolder{};
            folderItem->GetDisplayName(SIGDN_FILESYSPATH, dialogFolder.put());
            VERIFY_ARE_EQUAL(L"C:\\temp", std::wstring(dialogFolder.get()));

            wil::unique_cotaskmem_string fileName{};
            dialog->GetFileName(fileName.put());
            VERIFY_ARE_EQUAL(L"MyFile2.txt", std::wstring(fileName.get()));
        }

        TEST_METHOD(VerifyParseFolderItemAndFileName)
        {
            // Arrange.
            std::wstring testFolder = L"C:\\temp\\testsuggestedSaveFilePath";

            std::vector<std::tuple<bool, std::wstring, std::wstring, bool>> test_cases {
            // test folder exists      folder        file              expect non-empty result
                {true,              testFolder,      L"MyFile.txt",     true },
                {true,              testFolder,      L"MyFile",         true },
                {true,              testFolder,      L".source",        true },
                {true,              testFolder,      L"",               true },
                {true,              L"C:",           L".source",        true },
                {false,             L"C:",           L".source",        true },
                {false,             testFolder,      L".source",        false },
            };

            for (const auto& test_case : test_cases)
            {
                bool testFolderExists = std::get<0>(test_case);
                std::wstring folder = std::get<1>(test_case);
                std::wstring fileName = std::get<2>(test_case);
                bool expectNonEmptyResult = std::get<3>(test_case);

                // Act.
                if (testFolderExists)
                {
                    std::filesystem::create_directories(testFolder);
                }
                else
                {
                    std::filesystem::remove_all(testFolder);
                }

                winrt::hstring filePath {folder + L"\\" + fileName};
                auto [folderItem, resultFileName] = PickerCommon::ParseFolderItemAndFileName(filePath);
                std::wstring message;
                if (!expectNonEmptyResult)
                {
                    message = L"This input should not return a valid folder item: '" + filePath + L"'";
                    VERIFY_ARE_EQUAL(nullptr, folderItem, message.c_str());
                }
                else
                {
                    message = L"Expected a valid folder item for: " + filePath;
                    VERIFY_ARE_NOT_EQUAL(nullptr, folderItem, message.c_str());

                    wil::unique_cotaskmem_string resultFolderPath{};
                    folderItem->GetDisplayName(SIGDN_FILESYSPATH, resultFolderPath.put());
                    winrt::hstring resultFolderPathString(resultFolderPath.get());
                    message = L"Verify folder path of '" + filePath + L"', expect: '" + folder + L"', actual: '" + resultFolderPathString + L"'";
                    if (folder == L"C:")
                    {
                        folder += L"\\";
                    }
                    VERIFY_ARE_EQUAL(folder, resultFolderPathString, message.c_str());
                }

                // The file name should always be returned, no matter the folder exists or not.
                message = L"Verify filename of '" + filePath + L"', expect: '" + fileName + L"', actual: '" + resultFileName + L"'";
                VERIFY_ARE_EQUAL(fileName, resultFileName, message.c_str());
                
            }
            
        }

        TEST_METHOD(VerifyValidateViewMode)
        {
            // Arrange.
            std::vector<std::tuple<int, bool>> test_cases {
                {0, true}, // PickerViewMode::List
                {1, true}, // PickerViewMode::Thumbnail
                {2, false}, // An invalid value out of range
                {-1, false}, // Negative value
                {100, false} // An very large value out of range
            };
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            // Act & Assert
            for (const auto& test_case : test_cases)
            {
                int viewModeValue = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);
                
                if (expectValid)
                {
                    picker.ViewMode((winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode)viewModeValue);
                    VERIFY_ARE_EQUAL(picker.ViewMode(), (winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode)viewModeValue);
                }
                else
                {
                    try
                    {
                        picker.ViewMode((winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode)viewModeValue);
                        VERIFY_FAIL(L"Expected exception for invalid view mode");
                    }
                    catch (...)
                    {
                        // Expected exception for invalid view mode
                    }
                }
            }
        }

        TEST_METHOD(VerifyValidateSuggestedStartLocation)
        {
            // Arrange.
            std::vector<std::tuple<int, bool>> test_cases {
                {0, true}, // DocumentsLibrary
                {1, true}, // ComputerFolder
                {2, true}, // Desktop
                {3, true}, // Downloads
                {4, false}, // HomeGroup is removed, should return false.
                {5, true}, // MusicLibrary
                {6, true}, // PicturesLibrary
                {7, true}, // VideosLibrary
                {8, true}, // Objects3D
                {9, true}, // Unspecified
                {10, false}, // An invalid value out of range
                {-1, false}, // Negative value
                {100, false}, // An very large value out of range
            };
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            // Act & Assert
            for (const auto& test_case : test_cases)
            {
                int locationValue = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);
                
                if (expectValid)
                {
                    picker.SuggestedStartLocation((winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId)locationValue);
                    VERIFY_ARE_EQUAL(picker.SuggestedStartLocation(), (winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId)locationValue);
                }
                else
                {
                    try
                    {
                        picker.SuggestedStartLocation((winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId)locationValue);
                        VERIFY_FAIL(L"Expected exception for invalid suggested start location");
                    }
                    catch (...)
                    {
                        // Expected exception for invalid suggested start location
                    }
                }
            }
        }

        TEST_METHOD(VerifyValidateSuggestedFileName)
        {
            // Arrange.
            auto test_cases = std::vector<std::tuple<winrt::hstring, bool>>{
                {L"validFileName.txt", true},   // Valid file name
                {s_embeddedNullString, false},      // embedded null
                {L"", true},                            // Allow Empty string
                {L"validFileNameWithSpaces .txt", true},// Allow spaces
                {
                    L"too_long_file_name_that_exceeds_the_maximum_length_of_a_file_name_usually_260_characters_too_long_file_name_that_exceeds_the_maximum_length_of_a_file_name_usually_260_characters_too_long_file_name_that_exceeds_the_maximum_length_of_a_file_name_usually_260_characters.txt",
                    false, // File name too long
                },
            };

            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            // Act & Assert
            for (const auto& test_case : test_cases)
            {
                winrt::hstring suggestedFileName = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);
                if (expectValid)
                {
                    picker.SuggestedFileName(suggestedFileName);
                    VERIFY_ARE_EQUAL(picker.SuggestedFileName(), suggestedFileName);
                }
                else
                {
                    try
                    {
                        picker.SuggestedFileName(suggestedFileName);

                        std::wstring errorMessage = L"Expected exception for invalid suggested file name: " + std::wstring(suggestedFileName);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid suggested file name
                    }
                }
            }
        }

        std::vector<std::tuple<winrt::hstring, bool>> cbsi_text_test_cases{
            {L"Valid", true}, // Valid commit button text
            {L"", true}, // Allow empty string
            {L"Valid Text", true}, // Allow spaces
            {s_embeddedNullString, false}, // Embedded null is invalid
        };

        TEST_METHOD(VerifyFolderPicker_ValidateCommitButtonText)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FolderPicker picker(windowId);

            // Act & Assert            
            for (const auto& test_case : cbsi_text_test_cases)
            {
                winrt::hstring commitButtonText = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);
                
                if (expectValid)
                {
                    picker.CommitButtonText(commitButtonText);
                    VERIFY_ARE_EQUAL(picker.CommitButtonText(), commitButtonText);
                }
                else
                {
                    try
                    {
                        picker.CommitButtonText(commitButtonText);
                        std::wstring errorMessage = L"Expected exception for invalid commit button text: " + std::wstring(commitButtonText);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid commit button text
                    }
                }
            }
        }

        TEST_METHOD(VerifyFileOpenPicker_ValidateCommitButtonText)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            // Act & Assert            
            for (const auto& test_case : cbsi_text_test_cases)
            {
                winrt::hstring commitButtonText = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);

                if (expectValid)
                {
                    picker.CommitButtonText(commitButtonText);
                    VERIFY_ARE_EQUAL(picker.CommitButtonText(), commitButtonText);
                }
                else
                {
                    try
                    {
                        picker.CommitButtonText(commitButtonText);
                        std::wstring errorMessage = L"Expected exception for invalid commit button text: " + std::wstring(commitButtonText);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid commit button text
                    }
                }
            }
        }

        TEST_METHOD(VerifyFileSavePicker_ValidateCommitButtonText)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            // Act & Assert            
            for (const auto& test_case : cbsi_text_test_cases)
            {
                winrt::hstring commitButtonText = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);

                if (expectValid)
                {
                    picker.CommitButtonText(commitButtonText);
                    VERIFY_ARE_EQUAL(picker.CommitButtonText(), commitButtonText);
                }
                else
                {
                    try
                    {
                        picker.CommitButtonText(commitButtonText);
                        std::wstring errorMessage = L"Expected exception for invalid commit button text: " + std::wstring(commitButtonText);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid commit button text
                    }
                }
            }
        }

        TEST_METHOD(VerifyValidateSuggestedSaveFilePath)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);
            std::vector<std::tuple<winrt::hstring, bool>> ssfp_test_cases{
                {L"C:\\temp\\valid.txt", true}, // Valid path
                {L"", true},                    // Allow empty string
                {s_embeddedNullString, false},  // Embedded null is invalid
                {L"1.txt", false},              // Input without a folder is invalid
                {
                    L"C:\\temp\\too_long_file_name_that_exceeds_the_maximum_length_of_a_file_name_usually_260_characters_too_long_file_name_that_exceeds_the_maximum_length_of_a_file_name_usually_260_characters_too_long_file_name_that_exceeds_the_maximum_length_of_a_file_name_usually_260_characters.txt",
                    false                       // file name too long is invalid.
                },
                {L"C:\\>:di*r\\1.txt", false},  // Throw error on invalid characters
            };

            // Act & Assert
            for (const auto& test_case : ssfp_test_cases)
            {
                winrt::hstring suggestedPath = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);

                if (expectValid)
                {
                    picker.SuggestedSaveFilePath(suggestedPath);
                    VERIFY_ARE_EQUAL(picker.SuggestedSaveFilePath(), suggestedPath);
                }
                else
                {
                    try
                    {
                        picker.SuggestedSaveFilePath(suggestedPath);
                        std::wstring errorMessage = L"Expected exception for invalid suggested save file path: " + std::wstring(suggestedPath);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid suggested save file path
                    }
                }
            }
        }

        std::vector<std::tuple<winrt::hstring, bool>> file_extension_validation_test_cases{
            {L".txt", true},
            {L"*", true},       // One asterisk is valid
            {L"**", false},     // More than one asterisk is invalid
            {L"*.docx", false}, // Filter (if not "*") must start with '.'
            {L"txt", false}, // Must start with '.' or '*'
            {L"", false},    // Must start with '.' or '*', empty string is invalid
            {L".t*t", false},   // Should not contain other wildcards
            {L".t.", false},    // Should not contain other wildcards
            {L".?txt", false},  // Should not contain other wildcards
        };

        TEST_METHOD(VerifyValidateSingleFileTypeFilterElement)
        {
            for (const auto& test_case : file_extension_validation_test_cases)
            {
                winrt::hstring filter = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);
                
                if (expectValid)
                {
                    PickerCommon::ValidateSingleFileTypeFilterElement(filter);
                }
                else
                {
                    try
                    {
                        PickerCommon::ValidateSingleFileTypeFilterElement(filter);

                        std::wstring errorMessage = L"Expected exception for invalid single file type filter element: " + std::wstring(filter);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid single file type filter element
                    }
                }
            }
        }

        TEST_METHOD(VerifyValidateFileTypeFilter)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            // Act & Assert
            for (const auto& test_case : file_extension_validation_test_cases)
            {
                auto& filter = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);

                if (expectValid)
                {
                    picker.FileTypeFilter().Append(filter);
                    auto newFilters = picker.FileTypeFilter().GetView();
                    VERIFY_ARE_EQUAL(newFilters.GetAt(newFilters.Size() - 1), filter);
                }
                else
                {
                    try
                    {
                        picker.FileTypeFilter().Append(filter);

                        std::wstring errorMessage = L"Expected exception for invalid file type filter: " + std::wstring(filter);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid file type filter
                    }
                }
            }
        }

        TEST_METHOD(VerifyValidateFileTypeChoices)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            // Act & Assert
            for (const auto& test_case : file_extension_validation_test_cases)
            {
                auto& choice = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);

                if (expectValid)
                {
                    // Create a vector with the extension
                    auto extensions = winrt::single_threaded_vector<winrt::hstring>({ choice });
                    picker.FileTypeChoices().Insert(L"TestChoice", extensions);

                    // Verify that the choice was added
                    auto choices = picker.FileTypeChoices();
                    VERIFY_IS_TRUE(choices.HasKey(L"TestChoice"));
                    auto newExtensions = choices.Lookup(L"TestChoice");
                    VERIFY_ARE_EQUAL(newExtensions.GetAt(0), choice);
                }
                else
                {
                    // Attempt to insert a key-value pair that has invalid choice
                    try
                    {
                        auto extensions = winrt::single_threaded_vector<winrt::hstring>({ choice });
                        picker.FileTypeChoices().Insert(L"InvalidChoice", extensions);

                        std::wstring errorMessage = L"Expected exception when inserting an invalid file type choice: " + std::wstring(choice);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid file type choice
                    }

                    // Attempt to append an invalid choice to the existing choices
                    picker.FileTypeChoices().Insert(
                        L"ValidChoice",
                        winrt::single_threaded_vector<winrt::hstring>({ L".txt", L".doc" }));

                    try
                    {
                        picker.FileTypeChoices().Lookup(L"ValidChoice").Append(choice);

                        std::wstring errorMessage = L"Expected exception when appending an invalid file type choice: " + std::wstring(choice);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid file type filter
                    }
                }
            }
        }

    };

    const wchar_t PickerCommonTests::s_rawStringWithNull[] = L"in\0valid.txt";
    const winrt::hstring PickerCommonTests::s_embeddedNullString{ std::wstring_view(s_rawStringWithNull, 12) };

}
