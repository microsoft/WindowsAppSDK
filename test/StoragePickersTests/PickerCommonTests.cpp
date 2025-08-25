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

        static const wchar_t s_rawStringWithNullFolder[];
        static const winrt::hstring s_embeddedNullFolder;
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

        TEST_METHOD(VerifyConfigureFileSaveDialog)
        {
            // Arrange.
            auto mockFileName = L"test.txt";
            auto mockFolderPath = L"C:\\temp_filesavepicker_ut_temp";
            PickerParameters parameters{};
            parameters.SuggestedFileName = mockFileName;
            parameters.SuggestedFolder = mockFolderPath;

            // Ensure the SuggestedFolder exists.
            if (!std::filesystem::exists(mockFolderPath))
            {
                std::filesystem::create_directory(mockFolderPath);
            }

            // Act.
            auto dialog = winrt::create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
            parameters.ConfigureFileSaveDialog(dialog);

            // Assert.
            wil::unique_cotaskmem_string dialogFileName{};
            dialog->GetFileName(dialogFileName.put());
            VERIFY_ARE_EQUAL(std::wstring(dialogFileName.get()), mockFileName,
                L"The save dialog's file name should match the suggested file name.");

            winrt::com_ptr<IShellItem> dialogFolder{};
            dialog->GetFolder(dialogFolder.put());
            VERIFY_IS_NOT_NULL(dialogFolder.get(), L"The save dialog's folder should not be null.");

            wil::unique_cotaskmem_string dialogFolderPath{};
            dialogFolder->GetDisplayName(SIGDN_FILESYSPATH, dialogFolderPath.put());
            VERIFY_ARE_EQUAL(std::wstring(dialogFolderPath.get()), mockFolderPath,
                L"The save dialog's folder path should match the suggested folder path.");
        }
        TEST_METHOD(VerifyConfigureFileSaveDialog_WhenSuggestedFolderDeleted_ExpectItsNoError)
        {
            // Arrange.
            std::wstring mockFileName = L"test.txt";
            std::wstring mockFolderPath = L"C:\\temp_filesavepicker_ut_temp";
            PickerParameters parameters{};
            parameters.SuggestedFileName = winrt::hstring{ mockFileName };
            parameters.SuggestedFolder = winrt::hstring{ mockFolderPath };

            // Ensure the folder of SuggestedFolder doesn't exist anumore.
            std::filesystem::remove_all(mockFolderPath);

            // Act.
            auto dialog = winrt::create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
            parameters.ConfigureFileSaveDialog(dialog);

            // Assert.
            wil::unique_cotaskmem_string dialogFileName{};
            dialog->GetFileName(dialogFileName.put());
            VERIFY_ARE_EQUAL(mockFileName, std::wstring(dialogFileName.get()),
                L"The save dialog's file name should match the suggested file name.");
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

        TEST_METHOD(VerifyFileSaveDialog_SuggestedFileName)
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

        TEST_METHOD(VerifyTryParseFolderItem)
        {
            // Arrange.
            std::wstring testFolder = L"C:\\temp\\testsuggestedFolder";
            std::wstring rootFolder = L"C:\\";
            std::vector<std::tuple<bool, std::wstring, std::wstring>> test_cases {
            // folder exists  test folder            expect
                {true,        testFolder,            testFolder},
                {true,        testFolder + L"\\",    testFolder},
                {false,       testFolder,            L""},        // stands for null result.
                {true,        rootFolder,            rootFolder},
            };

            for (const auto& test_case : test_cases)
            {
                bool testFolderExists = std::get<0>(test_case);
                std::wstring folder = std::get<1>(test_case);
                std::wstring expectConfig = std::get<2>(test_case);

                if (testFolderExists)
                {
                    if (!std::filesystem::exists(folder))
                    {
                        std::filesystem::create_directories(folder);
                    }
                }
                else
                {
                    if (folder != rootFolder)
                    {
                        std::filesystem::remove_all(folder);
                    }
                }

                // Act.
                auto folderItem = PickerCommon::TryParseFolderItem(winrt::hstring{ folder });

                // Assert.
                std::wstring message;
                if (expectConfig != L"")
                {
                    message = L"Expected a valid folder item for: " + folder;
                    VERIFY_ARE_NOT_EQUAL(nullptr, folderItem, message.c_str());

                    wil::unique_cotaskmem_string resultFolderPath{};
                    folderItem->GetDisplayName(SIGDN_FILESYSPATH, resultFolderPath.put());
                    winrt::hstring resultFolderPathString(resultFolderPath.get());

                     // Do a case insensitive comparison for the folder path.
                    std::wstring expectConfigLower{ expectConfig };
                    std::wstring resultFolderPathLower{ resultFolderPathString };

                    std::transform(expectConfigLower.begin(), expectConfigLower.end(), expectConfigLower.begin(), ::towlower);
                    std::transform(resultFolderPathLower.begin(), resultFolderPathLower.end(), resultFolderPathLower.begin(), ::towlower);

                    message = L"Verify folder path of '" + folder + L"', expect: '" + expectConfigLower + L"', actual: '" + resultFolderPathLower + L"'";
                    VERIFY_ARE_EQUAL(resultFolderPathLower, expectConfigLower, message.c_str());
                }
                else
                {
                    message = L"This input should not return a valid folder item: '" + folder + L"'";
                    VERIFY_IS_NULL(folderItem.get(), message.c_str());
                }
                
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
                {L"validFileName.txt", true},           // Valid file name
                {s_embeddedNullString, false},        // embedded null
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

        
        TEST_METHOD(VerifyValidateSuggestedFolder)
        {
            // Arrange.
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);
            winrt::hstring folderNameTooLong = L"the_long_folder_name_that_exceeds_ntfs_maximum_length_of_a_folder_name_usually_255_characters_the_long_folder_name_that_exceeds_ntfs_maximum_length_of_a_folder_name_usually_255_characters_the_long_folder_name_that_exceeds_ntfs_maximum_length_of_name_usually_255";
            std::vector<std::tuple<winrt::hstring, bool>> ssfp_test_cases{
                {L"C:\\temp\\valid", true},     // Valid path
                {L"C:\\",            true},     // Valid path
                {L"",                true},     // Allow empty string
                {L".\\temp\\valid",  false},    // Reject relative path
                {L"1.txt",           false},    // A file name will be recognized as related path, and rejected.
                {s_embeddedNullFolder, false},  // Embedded null is invalid
                {
                    L"C:\\temp\\" + folderNameTooLong,
                    false                       // Reject folder name too long.
                },
                {L"C:\\>:di*r\\1.txt", false},  // Throw error on invalid characters
            };

            // Act & Assert
            for (const auto& test_case : ssfp_test_cases)
            {
                winrt::hstring suggestedFolder = std::get<0>(test_case);
                bool expectValid = std::get<1>(test_case);

                if (expectValid)
                {
                    picker.SuggestedFolder(suggestedFolder);
                    VERIFY_ARE_EQUAL(picker.SuggestedFolder(), suggestedFolder);
                }
                else
                {
                    try
                    {
                        picker.SuggestedFolder(suggestedFolder);
                        std::wstring errorMessage = L"Expected exception for invalid suggested folder: " + std::wstring(suggestedFolder);
                        VERIFY_FAIL(errorMessage.c_str());
                    }
                    catch (...)
                    {
                        // Expected exception for invalid suggested folder
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

    const wchar_t PickerCommonTests::s_rawStringWithNullFolder[] = L"C:\\in\0valid";
    const winrt::hstring PickerCommonTests::s_embeddedNullFolder{ std::wstring_view(s_rawStringWithNullFolder, 11) };

}
