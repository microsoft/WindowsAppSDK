// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <wil/cppwinrt.h>

#include <FrameworkUdk/Containment.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>

#include "..\..\dev\Interop\StoragePickers\PickerCommon.h"

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

        TEST_METHOD(VerifyFileSaveDialog_WhenSuggestedSaveFilePathTakesPrecedenceOverSuggestedFileName)
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
    };
}
