#pragma once

#include "MainWindow.g.h"
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cwctype>

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Windows.Data.Json.h>

#include <Windows.h>
#include <Shobjidl.h>
#include <microsoft.ui.xaml.window.h>

namespace winrt::PickerUsageApp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
        }
        
        // Helper Methods
        void LogResult(hstring const& message);
        winrt::Windows::Storage::Pickers::PickerLocationId GetSelectedLocation();
        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId GetSelectedNewLocationId();
        winrt::Windows::Storage::Pickers::PickerViewMode GetSelectedViewMode();
        winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode GetSelectedNewViewMode();
        std::vector<hstring> GetFileFilters();
        HWND MainWindow::GetWindowHandle();
        
        // FileOpenPicker Tests
        winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickSingleFile_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickSingleFile_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickMultipleFiles_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickMultipleFiles_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction MainWindow::UwpFileTypeFilter_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction MainWindow::NewFileTypeFilter_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        
        // FileSavePicker Tests
        winrt::Windows::Foundation::IAsyncAction MainWindow::UwpFileTypeChoices_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction MainWindow::NewFileTypeChoices_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        
        // FolderPicker Tests
        winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickFolder_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickFolder_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        
        // Test any code
        winrt::Windows::Foundation::IAsyncAction MainWindow::TestAnyCode_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    };
}

namespace winrt::PickerUsageApp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
