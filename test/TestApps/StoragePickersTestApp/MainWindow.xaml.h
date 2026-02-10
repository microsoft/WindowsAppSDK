// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"
#include <winrt/Microsoft.Windows.Storage.Pickers.h>

#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <iomanip>

namespace winrt::StoragePickersTestApp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
        }
        
        void InitializeDefaults()
        {
            OpenPickerFileTypeChoicesInput().Text(LR"({"Documents": [".txt", ".doc"], "Images": [".png", ".jpg"]})");
            SavePickerFileTypeChoicesInput().Text(LR"({"Documents": [".txt", ".doc"], "All Files": ["*"]})");
        }

        // Helper methods
        void LogResult(hstring const& message);
        HWND GetWindowHandle();
        winrt::Windows::Storage::Pickers::PickerLocationId GetUwpLocationId();
        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId GetNewLocationId();
        winrt::Windows::Storage::Pickers::PickerViewMode GetUwpViewMode();
        winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode GetNewViewMode();
        std::vector<hstring> ParseFileTypeFilter();
        std::vector<std::pair<std::wstring, std::vector<std::wstring>>> ParseFileTypeChoices(hstring const& json);

        // FileOpenPicker handlers
        winrt::Windows::Foundation::IAsyncAction UwpPickSingleFile_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction NewPickSingleFile_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction UwpPickMultipleFiles_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction NewPickMultipleFiles_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        // FileSavePicker handlers
        winrt::Windows::Foundation::IAsyncAction UwpPickSaveFile_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction NewPickSaveFile_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        // FolderPicker handlers
        winrt::Windows::Foundation::IAsyncAction UwpPickFolder_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction NewPickFolder_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction NewPickMultipleFolders_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        // Utility handlers
        void ClearLog_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::StoragePickersTestApp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
