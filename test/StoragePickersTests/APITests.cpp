// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <FrameworkUdk/Containment.h>
#include "winrt/Microsoft.Windows.Storage.Pickers.h"
#include "TerminalVelocityFeatures-StoragePickers.h"

#include <thread>
#include <future>
#include <vector>
#include <mutex>

#include <winrt/Windows.Foundation.h>

using namespace std::chrono_literals;
using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

// #include <winrt/Windows.Storage.h>  // camera has this
// using namespace winrt::Windows::Storage; // camera has this

namespace StoragePickersTests
{
    // Timeout in milliseconds
    class APITests
    {
    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"StoragePickers-AppxManifest.xml")
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

        TEST_METHOD(VerifyFileOpenPickerOptionsAreReadCorrectly)
        {
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker picker(windowId);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);

            picker.SettingsIdentifier(L"id");
            VERIFY_ARE_EQUAL(picker.SettingsIdentifier(), L"id");

            picker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
            VERIFY_ARE_EQUAL(picker.SuggestedStartLocation(), winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

            picker.CommitButtonText(L"commit");
            VERIFY_ARE_EQUAL(picker.CommitButtonText(), L"commit");

            picker.FileTypeFilter().Append(L"*");
            VERIFY_ARE_EQUAL(picker.FileTypeFilter().GetAt(0), L"*");
        }

        TEST_METHOD(VerifyFileSavePickerOptionsAreReadCorrectly)
        {
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker picker(windowId);

            picker.SettingsIdentifier(L"id");
            VERIFY_ARE_EQUAL(picker.SettingsIdentifier(), L"id");

            picker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
            VERIFY_ARE_EQUAL(picker.SuggestedStartLocation(), winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

            picker.CommitButtonText(L"commit");
            VERIFY_ARE_EQUAL(picker.CommitButtonText(), L"commit");

            auto filters = winrt::single_threaded_vector<winrt::hstring>();
            filters.Append(L"*");
            picker.FileTypeChoices().Insert(L"All Files", filters);
            VERIFY_ARE_EQUAL(picker.FileTypeChoices().Lookup(L"All Files").GetAt(0), L"*");
        }

        TEST_METHOD(VerifyFolderPickerOptionsAreReadCorrectly)
        {
            auto parentWindow = ::GetForegroundWindow();
            winrt::Microsoft::UI::WindowId windowId{};
            winrt::Microsoft::Windows::Storage::Pickers::FolderPicker picker(windowId);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List);

            picker.ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
            VERIFY_ARE_EQUAL(picker.ViewMode(), winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail);

            picker.SettingsIdentifier(L"id");
            VERIFY_ARE_EQUAL(picker.SettingsIdentifier(), L"id");

            picker.SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
            VERIFY_ARE_EQUAL(picker.SuggestedStartLocation(), winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

            picker.CommitButtonText(L"commit");
            VERIFY_ARE_EQUAL(picker.CommitButtonText(), L"commit");

            picker.FileTypeFilter().Append(L"*");
            VERIFY_ARE_EQUAL(picker.FileTypeFilter().GetAt(0), L"*");
        }
    };
}
