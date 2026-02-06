// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <microsoft.ui.xaml.window.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::StoragePickersTestApp::implementation
{
    // ==========================================================================
    // Helper Methods
    // ==========================================================================

    void MainWindow::LogResult(hstring const& message)
    {
        // Add timestamp
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;
        localtime_s(&localTime, &time);

        std::wstringstream timestamp;
        timestamp << L"[" << std::put_time(&localTime, L"%H:%M:%S") << L"] ";

        hstring currentText = ResultsTextBlock().Text();
        ResultsTextBlock().Text(timestamp.str() + message + L"\n" + currentText);
    }

    HWND MainWindow::GetWindowHandle()
    {
        HWND hwnd = nullptr;
        auto windowNative = this->m_inner.as<IWindowNative>();
        if (windowNative)
        {
            check_hresult(windowNative->get_WindowHandle(&hwnd));
        }
        return hwnd;
    }

    winrt::Windows::Storage::Pickers::PickerLocationId MainWindow::GetUwpLocationId()
    {
        switch (StartLocationComboBox().SelectedIndex())
        {
        case 0: return winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary;
        case 1: return winrt::Windows::Storage::Pickers::PickerLocationId::ComputerFolder;
        case 2: return winrt::Windows::Storage::Pickers::PickerLocationId::Desktop;
        case 3: return winrt::Windows::Storage::Pickers::PickerLocationId::Downloads;
        case 4: return winrt::Windows::Storage::Pickers::PickerLocationId::HomeGroup;
        case 5: return winrt::Windows::Storage::Pickers::PickerLocationId::MusicLibrary;
        case 6: return winrt::Windows::Storage::Pickers::PickerLocationId::PicturesLibrary;
        case 7: return winrt::Windows::Storage::Pickers::PickerLocationId::VideosLibrary;
        case 8: return winrt::Windows::Storage::Pickers::PickerLocationId::Objects3D;
        default: return winrt::Windows::Storage::Pickers::PickerLocationId::Unspecified;
        }
    }

    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId MainWindow::GetNewLocationId()
    {
        switch (StartLocationComboBox().SelectedIndex())
        {
        case 0: return PickerLocationId::DocumentsLibrary;
        case 1: return PickerLocationId::ComputerFolder;
        case 2: return PickerLocationId::Desktop;
        case 3: return PickerLocationId::Downloads;
        // case 4: HomeGroup is not supported in new API - will throw at runtime
        case 5: return PickerLocationId::MusicLibrary;
        case 6: return PickerLocationId::PicturesLibrary;
        case 7: return PickerLocationId::VideosLibrary;
        case 8: return PickerLocationId::Objects3D;
        default: return PickerLocationId::Unspecified;
        }
    }

    winrt::Windows::Storage::Pickers::PickerViewMode MainWindow::GetUwpViewMode()
    {
        return ViewModeComboBox().SelectedIndex() == 0
            ? winrt::Windows::Storage::Pickers::PickerViewMode::List
            : winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail;
    }

    winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode MainWindow::GetNewViewMode()
    {
        return ViewModeComboBox().SelectedIndex() == 0
            ? PickerViewMode::List
            : PickerViewMode::Thumbnail;
    }

    std::vector<hstring> MainWindow::ParseFileTypeFilter()
    {
        std::vector<hstring> filters;
        hstring input = FileTypeFilterInput().Text();

        if (input.empty())
        {
            filters.push_back(L"*");
            return filters;
        }

        std::wstring inputStr{ input };
        std::wstringstream ss(inputStr);
        std::wstring filter;
        while (std::getline(ss, filter, L','))
        {
            // Trim whitespace
            filter.erase(0, filter.find_first_not_of(L' '));
            filter.erase(filter.find_last_not_of(L' ') + 1);
            if (!filter.empty())
            {
                filters.push_back(hstring{ filter });
            }
        }

        if (filters.empty())
        {
            filters.push_back(L"*");
        }
        return filters;
    }

    std::vector<std::pair<std::wstring, std::vector<std::wstring>>> MainWindow::ParseFileTypeChoices(hstring const& json)
    {
        std::vector<std::pair<std::wstring, std::vector<std::wstring>>> choices;
        if (json.empty()) return choices;

        std::wstring jsonStr{ json };

        // Find opening and closing braces
        size_t start = jsonStr.find(L'{');
        size_t end = jsonStr.rfind(L'}');
        if (start == std::wstring::npos || end == std::wstring::npos || start >= end)
            return choices;

        jsonStr = jsonStr.substr(start + 1, end - start - 1);

        // Parse key-value pairs (simple JSON parser)
        size_t pos = 0;
        int bracketDepth = 0;
        size_t lastPos = 0;

        auto processPair = [&](const std::wstring& pair) {
            size_t colonPos = pair.find(L':');
            if (colonPos == std::wstring::npos) return;

            std::wstring key = pair.substr(0, colonPos);
            std::wstring valueStr = pair.substr(colonPos + 1);

            // Clean key
            key.erase(0, key.find_first_not_of(L" \t\n\r\""));
            key.erase(key.find_last_not_of(L" \t\n\r\"") + 1);

            // Parse array
            std::vector<std::wstring> values;
            size_t arrStart = valueStr.find(L'[');
            size_t arrEnd = valueStr.rfind(L']');
            if (arrStart != std::wstring::npos && arrEnd != std::wstring::npos && arrStart < arrEnd)
            {
                std::wstring arrayContent = valueStr.substr(arrStart + 1, arrEnd - arrStart - 1);
                std::wstringstream ss(arrayContent);
                std::wstring item;
                while (std::getline(ss, item, L','))
                {
                    item.erase(0, item.find_first_not_of(L" \t\n\r\""));
                    item.erase(item.find_last_not_of(L" \t\n\r\"") + 1);
                    if (!item.empty())
                    {
                        values.push_back(item);
                    }
                }
            }

            if (!key.empty())
            {
                choices.emplace_back(key, values);
            }
        };

        while (pos < jsonStr.length())
        {
            wchar_t ch = jsonStr[pos];
            if (ch == L'[') bracketDepth++;
            else if (ch == L']') bracketDepth--;
            else if (ch == L',' && bracketDepth == 0)
            {
                processPair(jsonStr.substr(lastPos, pos - lastPos));
                lastPos = pos + 1;
            }
            pos++;
        }

        // Process last pair
        if (lastPos < jsonStr.length())
        {
            processPair(jsonStr.substr(lastPos));
        }

        return choices;
    }

    void MainWindow::ClearLog_Click(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        ResultsTextBlock().Text(L"");
    }

    // ==========================================================================
    // FileOpenPicker - UWP
    // ==========================================================================

    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickSingleFile_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            winrt::Windows::Storage::Pickers::FileOpenPicker picker;

            // Initialize with window handle (required for desktop apps)
            auto initializeWithWindow = picker.as<::IInitializeWithWindow>();
            initializeWithWindow->Initialize(GetWindowHandle());

            // Apply settings
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                for (const auto& filter : ParseFileTypeFilter())
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetUwpLocationId());
            if (ViewModeCheckBox().IsChecked().Value())
                picker.ViewMode(GetUwpViewMode());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());

            auto file = co_await picker.PickSingleFileAsync();

            if (file)
            {
                std::wstringstream ss;
                ss << L"[UWP] PickSingleFileAsync:\n  File: " << file.Name().c_str()
                   << L"\n  Path: " << file.Path().c_str();
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[UWP] PickSingleFileAsync: Cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[UWP] Error: " + ex.message());
        }
    }

    // ==========================================================================
    // FileOpenPicker - New API
    // ==========================================================================

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickSingleFile_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = FileOpenPicker{ this->AppWindow().Id() };

            // Apply settings
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                for (const auto& filter : ParseFileTypeFilter())
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }

            if (OpenPickerFileTypeChoicesCheckBox().IsChecked().Value())
            {
                auto choices = ParseFileTypeChoices(OpenPickerFileTypeChoicesInput().Text());
                for (const auto& choice : choices)
                {
                    auto extensions = winrt::single_threaded_vector<hstring>();
                    for (const auto& ext : choice.second)
                    {
                        extensions.Append(hstring{ ext });
                    }
                    picker.FileTypeChoices().Insert(hstring{ choice.first }, extensions);
                }
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetNewLocationId());
            if (ViewModeCheckBox().IsChecked().Value())
                picker.ViewMode(GetNewViewMode());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());
            if (TitleCheckBox().IsChecked().Value())
                picker.Title(TitleInput().Text());

            auto result = co_await picker.PickSingleFileAsync();

            if (result)
            {
                std::wstringstream ss;
                ss << L"[NEW] PickSingleFileAsync:\n  File: "
                   << std::filesystem::path(result.Path().c_str()).filename().c_str()
                   << L"\n  Path: " << result.Path().c_str();
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[NEW] PickSingleFileAsync: Cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[NEW] Error: " + ex.message());
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickMultipleFiles_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            winrt::Windows::Storage::Pickers::FileOpenPicker picker;
            auto initializeWithWindow = picker.as<::IInitializeWithWindow>();
            initializeWithWindow->Initialize(GetWindowHandle());

            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                for (const auto& filter : ParseFileTypeFilter())
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetUwpLocationId());
            if (ViewModeCheckBox().IsChecked().Value())
                picker.ViewMode(GetUwpViewMode());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());

            auto files = co_await picker.PickMultipleFilesAsync();

            if (files && files.Size() > 0)
            {
                std::wstringstream ss;
                ss << L"[UWP] PickMultipleFilesAsync: " << files.Size() << L" files\n";
                for (const auto& file : files)
                {
                    ss << L"  - " << file.Name().c_str() << L"\n";
                }
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[UWP] PickMultipleFilesAsync: Cancelled or no files");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[UWP] Error: " + ex.message());
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickMultipleFiles_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = FileOpenPicker{ this->AppWindow().Id() };

            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                for (const auto& filter : ParseFileTypeFilter())
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }

            if (OpenPickerFileTypeChoicesCheckBox().IsChecked().Value())
            {
                auto choices = ParseFileTypeChoices(OpenPickerFileTypeChoicesInput().Text());
                for (const auto& choice : choices)
                {
                    auto extensions = winrt::single_threaded_vector<hstring>();
                    for (const auto& ext : choice.second)
                    {
                        extensions.Append(hstring{ ext });
                    }
                    picker.FileTypeChoices().Insert(hstring{ choice.first }, extensions);
                }
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetNewLocationId());
            if (ViewModeCheckBox().IsChecked().Value())
                picker.ViewMode(GetNewViewMode());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());
            if (TitleCheckBox().IsChecked().Value())
                picker.Title(TitleInput().Text());

            auto results = co_await picker.PickMultipleFilesAsync();

            if (results && results.Size() > 0)
            {
                std::wstringstream ss;
                ss << L"[NEW] PickMultipleFilesAsync: " << results.Size() << L" files\n";
                for (const auto& result : results)
                {
                    ss << L"  - " << std::filesystem::path(result.Path().c_str()).filename().c_str() << L"\n";
                }
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[NEW] PickMultipleFilesAsync: Cancelled or no files");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[NEW] Error: " + ex.message());
        }
    }

    // ==========================================================================
    // FileSavePicker - UWP
    // ==========================================================================

    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickSaveFile_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            winrt::Windows::Storage::Pickers::FileSavePicker picker;
            auto initializeWithWindow = picker.as<::IInitializeWithWindow>();
            initializeWithWindow->Initialize(GetWindowHandle());

            if (SuggestedFileNameCheckBox().IsChecked().Value())
                picker.SuggestedFileName(SuggestedFileNameInput().Text());
            if (DefaultFileExtensionCheckBox().IsChecked().Value())
                picker.DefaultFileExtension(DefaultFileExtensionInput().Text());

            if (SavePickerFileTypeChoicesCheckBox().IsChecked().Value())
            {
                auto choices = ParseFileTypeChoices(SavePickerFileTypeChoicesInput().Text());
                for (const auto& choice : choices)
                {
                    auto extensions = winrt::single_threaded_vector<hstring>();
                    for (const auto& ext : choice.second)
                    {
                        extensions.Append(hstring{ ext });
                    }
                    picker.FileTypeChoices().Insert(hstring{ choice.first }, extensions);
                }
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetUwpLocationId());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());

            auto file = co_await picker.PickSaveFileAsync();

            if (file)
            {
                std::wstringstream ss;
                ss << L"[UWP] PickSaveFileAsync:\n  File: " << file.Name().c_str()
                   << L"\n  Path: " << file.Path().c_str();
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[UWP] PickSaveFileAsync: Cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[UWP] Error: " + ex.message());
        }
    }

    // ==========================================================================
    // FileSavePicker - New API
    // ==========================================================================

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickSaveFile_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = FileSavePicker{ this->AppWindow().Id() };

            if (SuggestedFileNameCheckBox().IsChecked().Value())
                picker.SuggestedFileName(SuggestedFileNameInput().Text());
            if (DefaultFileExtensionCheckBox().IsChecked().Value())
                picker.DefaultFileExtension(DefaultFileExtensionInput().Text());

            if (SavePickerFileTypeChoicesCheckBox().IsChecked().Value())
            {
                auto choices = ParseFileTypeChoices(SavePickerFileTypeChoicesInput().Text());
                for (const auto& choice : choices)
                {
                    auto extensions = winrt::single_threaded_vector<hstring>();
                    for (const auto& ext : choice.second)
                    {
                        extensions.Append(hstring{ ext });
                    }
                    picker.FileTypeChoices().Insert(hstring{ choice.first }, extensions);
                }
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetNewLocationId());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());
            if (TitleCheckBox().IsChecked().Value())
                picker.Title(TitleInput().Text());

            auto result = co_await picker.PickSaveFileAsync();

            if (result)
            {
                std::wstringstream ss;
                ss << L"[NEW] PickSaveFileAsync:\n  File: "
                   << std::filesystem::path(result.Path().c_str()).filename().c_str()
                   << L"\n  Path: " << result.Path().c_str();
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[NEW] PickSaveFileAsync: Cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[NEW] Error: " + ex.message());
        }
    }

    // ==========================================================================
    // FolderPicker - UWP
    // ==========================================================================

    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickFolder_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            winrt::Windows::Storage::Pickers::FolderPicker picker;
            auto initializeWithWindow = picker.as<::IInitializeWithWindow>();
            initializeWithWindow->Initialize(GetWindowHandle());

            // FolderPicker requires at least one filter
            picker.FileTypeFilter().Append(L"*");

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetUwpLocationId());
            if (ViewModeCheckBox().IsChecked().Value())
                picker.ViewMode(GetUwpViewMode());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());

            auto folder = co_await picker.PickSingleFolderAsync();

            if (folder)
            {
                std::wstringstream ss;
                ss << L"[UWP] PickSingleFolderAsync:\n  Folder: " << folder.Name().c_str()
                   << L"\n  Path: " << folder.Path().c_str();
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[UWP] PickSingleFolderAsync: Cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[UWP] Error: " + ex.message());
        }
    }

    // ==========================================================================
    // FolderPicker - New API
    // ==========================================================================

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickFolder_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = FolderPicker{ this->AppWindow().Id() };

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetNewLocationId());
            if (ViewModeCheckBox().IsChecked().Value())
                picker.ViewMode(GetNewViewMode());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());
            if (TitleCheckBox().IsChecked().Value())
                picker.Title(TitleInput().Text());

            auto result = co_await picker.PickSingleFolderAsync();

            if (result)
            {
                std::wstringstream ss;
                ss << L"[NEW] PickSingleFolderAsync:\n  Folder: "
                   << std::filesystem::path(result.Path().c_str()).filename().c_str()
                   << L"\n  Path: " << result.Path().c_str();
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[NEW] PickSingleFolderAsync: Cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[NEW] Error: " + ex.message());
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickMultipleFolders_Click(
        Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = FolderPicker{ this->AppWindow().Id() };

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
                picker.SuggestedStartLocation(GetNewLocationId());
            if (ViewModeCheckBox().IsChecked().Value())
                picker.ViewMode(GetNewViewMode());
            if (CommitButtonCheckBox().IsChecked().Value())
                picker.CommitButtonText(CommitButtonTextInput().Text());
            if (SettingsIdCheckBox().IsChecked().Value())
                picker.SettingsIdentifier(SettingsIdInput().Text());
            if (TitleCheckBox().IsChecked().Value())
                picker.Title(TitleInput().Text());

            auto results = co_await picker.PickMultipleFoldersAsync();

            if (results && results.Size() > 0)
            {
                std::wstringstream ss;
                ss << L"[NEW] PickMultipleFoldersAsync: " << results.Size() << L" folders\n";
                for (const auto& result : results)
                {
                    ss << L"  - " << std::filesystem::path(result.Path().c_str()).filename().c_str() << L"\n";
                }
                LogResult(hstring{ ss.str() });
            }
            else
            {
                LogResult(L"[NEW] PickMultipleFoldersAsync: Cancelled or no folders");
            }
        }
        catch (hresult_error const& ex)
        {
            LogResult(L"[NEW] Error: " + ex.message());
        }
    }
}
