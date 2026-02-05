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
}
