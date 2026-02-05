#pragma once

#include "MainWindow.g.h"
#include "StoragePickersActivation.h"

namespace winrt::StoragePickersTestApp::implementation
{
    // ==========================================================================
    // Storage Pickers API Wrappers
    // ==========================================================================
    // These wrappers allow using Storage Pickers APIs with normal syntax while
    // ensuring we load from the locally-built DLL (not the released version).
    //
    // Without the CreateFile*Picker methods in StoragePickersActivation, the
    // app would throw error "Class not registered" when trying to instantiate
    // the pickers.
    // ==========================================================================

    // Type aliases for enums - use directly without namespace prefix
    using PickerViewMode = winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode;
    using PickerLocationId = winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId;

    // Type aliases for result types - returned by picker async methods
    using PickFileResult = winrt::Microsoft::Windows::Storage::Pickers::PickFileResult;
    using PickFolderResult = winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult;

    // Picker wrapper classes - internally load from local DLL
    struct FileOpenPicker : winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker
    {
        FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId)
            : winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker(
                ::StoragePickersTestApp::StoragePickersActivation::CreateFileOpenPicker(windowId))
        {
        }
    };

    struct FileSavePicker : winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker
    {
        FileSavePicker(winrt::Microsoft::UI::WindowId const& windowId)
            : winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker(
                ::StoragePickersTestApp::StoragePickersActivation::CreateFileSavePicker(windowId))
        {
        }
    };

    struct FolderPicker : winrt::Microsoft::Windows::Storage::Pickers::FolderPicker
    {
        FolderPicker(winrt::Microsoft::UI::WindowId const& windowId)
            : winrt::Microsoft::Windows::Storage::Pickers::FolderPicker(
                ::StoragePickersTestApp::StoragePickersActivation::CreateFolderPicker(windowId))
        {
        }
    };

    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        winrt::Windows::Foundation::IAsyncAction OnPickFileClick(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        winrt::Windows::Foundation::IAsyncAction OnUWPPickFileClick(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::StoragePickersTestApp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
