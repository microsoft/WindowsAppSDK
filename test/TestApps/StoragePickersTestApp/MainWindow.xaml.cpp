// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::StoragePickersTestApp::implementation
{
    winrt::Windows::Foundation::IAsyncAction MainWindow::OnPickFileClick(
        Windows::Foundation::IInspectable const& /*sender*/, 
        RoutedEventArgs const& /*args*/)
    {

        try
        {
            // Create FileOpenPicker using our local WindowsAppRuntime DLL
            auto picker = ::StoragePickersTestApp::StoragePickersActivation::CreateFileOpenPicker(
                this->AppWindow().Id());
            
            picker.FileTypeFilter().Append(L"*");
            
            PickFileResult result = co_await picker.PickSingleFileAsync();
            
            if (result)
            {
                FilePathTextBox().Text(result.Path());
            }
            else
            {
                FilePathTextBox().Text(L"No file selected (cancelled)");
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            FilePathTextBox().Text(L"Error: " + ex.message());
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::OnUWPPickFileClick(
        Windows::Foundation::IInspectable const& /*sender*/,
        RoutedEventArgs const& /*args*/)
    {
        try
        {
            // Create FileOpenPicker using legacy UWP API
            winrt::Windows::Storage::Pickers::FileOpenPicker picker;
            
            // Get HWND from AppWindow and initialize the picker with it
            // (required for UWP pickers in desktop/WinUI3 apps)
            auto windowId = this->AppWindow().Id();
            HWND hwnd = winrt::Microsoft::UI::GetWindowFromWindowId(windowId);
            auto initializeWithWindow = picker.as<::IInitializeWithWindow>();
            initializeWithWindow->Initialize(hwnd);
            
            picker.FileTypeFilter().Append(L"*");
            auto file = co_await picker.PickSingleFileAsync();

            if (file)
            {
                FilePathTextBox().Text(file.Path());
            }
            else
            {
                FilePathTextBox().Text(L"No file selected (cancelled)");
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            FilePathTextBox().Text(L"Error: " + ex.message());
        }
    }
}
