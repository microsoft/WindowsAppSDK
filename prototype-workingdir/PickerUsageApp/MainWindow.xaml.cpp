#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <cwctype>
#include <string>
#include <shobjidl.h>
#include <microsoft.ui.xaml.window.h>
#include <winrt/Windows.UI.Popups.h>
#include <winrt/Windows.Data.Json.h>

#include <fstream>
#include <filesystem>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::Windows::Storage::Pickers;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PickerUsageApp::implementation
{
    // Helper Methods
    void MainWindow::LogResult(hstring const& message)
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;
        localtime_s(&localTime, &time);

        std::wstringstream timestamp;
        timestamp << L"[" << std::put_time(&localTime, L"%H:%M:%S") << L"] ";

        hstring currentText = ResultsTextBlock().Text();
        ResultsTextBlock().Text(timestamp.str() + message + L"\n" + currentText);
    }

    winrt::Windows::Storage::Pickers::PickerLocationId MainWindow::GetSelectedLocation()
    {
        int selectedIndex = StartLocationComboBox().SelectedIndex();
        switch (selectedIndex)
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
        case 9: return winrt::Windows::Storage::Pickers::PickerLocationId::Unspecified;
        default: throw hresult_invalid_argument(L"Invalid location selected");
        }
    }

    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId MainWindow::GetSelectedNewLocationId()
    {
        int selectedIndex = StartLocationComboBox().SelectedIndex();
        switch (selectedIndex)
        {
        case 0: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary;
        case 1: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::ComputerFolder;
        case 2: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Desktop;
        case 3: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Downloads;
        //case 4: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::HomeGroup;
        case 5: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::MusicLibrary;
        case 6: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::PicturesLibrary;
        case 7: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::VideosLibrary;
        case 8: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Objects3D;
        case 9: return winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Unspecified;
        default: throw hresult_invalid_argument(L"Invalid location selected");
        }
    }

    winrt::Windows::Storage::Pickers::PickerViewMode MainWindow::GetSelectedViewMode()
    {
        int selectedIndex = ViewModeComboBox().SelectedIndex();
        switch (selectedIndex)
        {
        case 0: return winrt::Windows::Storage::Pickers::PickerViewMode::List;
        case 1: return winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail;
        default: throw hresult_invalid_argument(L"Invalid view mode selected");
        }
    }

    winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode MainWindow::GetSelectedNewViewMode()
    {
        int selectedIndex = ViewModeComboBox().SelectedIndex();
        switch (selectedIndex)
        {
        case 0: return winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List;
        case 1: return winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail;
        default: throw hresult_invalid_argument(L"Invalid view mode selected");
        }
    }

    std::vector<hstring> MainWindow::GetFileFilters()
    {
        std::vector<hstring> filters;
        hstring input = FileTypeFilterInput().Text();
        
        if (input.empty())
        {
            filters.push_back(L"*");
            return filters;
        }

        std::wstring inputStr = input.c_str();
        std::wstringstream ss(inputStr);
        std::wstring filter;
        while (std::getline(ss, filter, L','))
        {
            if (!filter.empty())
            {
                // Trim whitespace
                filter.erase(0, filter.find_first_not_of(L' '));
                filter.erase(filter.find_last_not_of(L' ') + 1);
                if (!filter.empty())
                {
                    filters.push_back(filter.c_str());
                }
            }
        }

        return filters;
    }

    // FileOpenPicker Tests
    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickSingleFile_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
            // Initialize UWP picker
            auto hwnd = GetWindowHandle();
            auto initializeWithWindow = picker.as<IInitializeWithWindow>();
            initializeWithWindow->Initialize(hwnd);

            picker.FileTypeFilter().Clear();
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                auto filters = GetFileFilters();
                for (const auto& filter : filters)
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }
            else
            {
                picker.FileTypeFilter().Append(L"*");
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedLocation());
            }

            auto file = co_await picker.PickSingleFileAsync();
            if (file != nullptr)
            {
                std::wstringstream ss;
                ss << L"UWP FileOpenPicker - PickSingleFileAsync:\nFile: " << file.Name().c_str() 
                   << L"\nPath: " << file.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"UWP FileOpenPicker - PickSingleFileAsync: Operation cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in UWP FileOpenPicker: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickSingleFile_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            // Initialize new picker with AppWindow.Id
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker(this->AppWindow().Id());

            picker.FileTypeFilter().Clear();
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                auto filters = GetFileFilters();
                for (const auto& filter : filters)
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }
            else
            {
                picker.FileTypeFilter().Append(L"*");
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedNewViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedNewLocationId());
            }

            auto result = co_await picker.PickSingleFileAsync();
            if (result != nullptr)
            {
                std::wstringstream ss;
                ss << L"New FileOpenPicker - PickSingleFileAsync:\nFile: " 
                   << std::filesystem::path(result.Path().c_str()).filename().c_str()
                   << L"\nPath: " << result.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"New FileOpenPicker - PickSingleFileAsync: Operation cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in New FileOpenPicker: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickMultipleFiles_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
            // Initialize UWP picker
            auto hwnd = GetWindowHandle();
            auto initializeWithWindow = picker.as<IInitializeWithWindow>();
            initializeWithWindow->Initialize(hwnd);

            picker.FileTypeFilter().Clear();
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                auto filters = GetFileFilters();
                for (const auto& filter : filters)
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }
            else
            {
                picker.FileTypeFilter().Append(L"*");
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedLocation());
            }

            auto files = co_await picker.PickMultipleFilesAsync();
            if (files != nullptr && files.Size() > 0)
            {
                std::wstringstream ss;
                ss << L"UWP FileOpenPicker - PickMultipleFilesAsync: " << files.Size() << L" files\n";
                for (auto const& file : files)
                {
                    ss << L"- " << file.Name().c_str() << L": " << file.Path().c_str() << L"\n";
                }
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"UWP FileOpenPicker - PickMultipleFilesAsync: Operation cancelled or no files selected");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in UWP PickMultipleFilesAsync: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickMultipleFiles_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker(this->AppWindow().Id());
            
            picker.FileTypeFilter().Clear();
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                auto filters = GetFileFilters();
                for (const auto& filter : filters)
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }
            else
            {
                picker.FileTypeFilter().Append(L"*");
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedNewViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedNewLocationId());
            }

            auto results = co_await picker.PickMultipleFilesAsync();
            if (results != nullptr && results.Size() > 0)
            {
                std::wstringstream ss;
                ss << L"New FileOpenPicker - PickMultipleFilesAsync: " << results.Size() << L" files\n";
                for (auto const& result : results)
                {
                    ss << L"- " << std::filesystem::path(result.Path().c_str()).filename().c_str() 
                       << L": " << result.Path().c_str() << L"\n";
                }
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"New FileOpenPicker - PickMultipleFilesAsync: Operation cancelled or no files selected");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in New PickMultipleFilesAsync: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpFileTypeFilter_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
            auto hwnd = GetWindowHandle();
            auto initializeWithWindow = picker.as<IInitializeWithWindow>();
            initializeWithWindow->Initialize(hwnd);

            picker.FileTypeFilter().Clear();
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                auto filters = GetFileFilters();
                for (const auto& filter : filters)
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }
            else
            {
                picker.FileTypeFilter().Append(L"*");
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedLocation());
            }

            auto file = co_await picker.PickSingleFileAsync();
            if (file != nullptr)
            {
                std::wstringstream ss;
                ss << L"UWP FileOpenPicker with FileTypeFilter: ";
                
                auto filters = GetFileFilters();
                for (size_t i = 0; i < filters.size(); ++i) {
                    if (i > 0) ss << L", ";
                    ss << filters[i].c_str();
                }
                
                ss << L"\nFile: " << file.Name().c_str() << L"\nPath: " << file.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                std::wstringstream ss;
                ss << L"UWP FileOpenPicker with FileTypeFilter: ";
                
                auto filters = GetFileFilters();
                for (size_t i = 0; i < filters.size(); ++i) {
                    if (i > 0) ss << L", ";
                    ss << filters[i].c_str();
                }
                
                ss << L"\nOperation cancelled";
                LogResult(winrt::hstring{ss.str()});
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in UWP FileTypeFilter: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewFileTypeFilter_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker(this->AppWindow().Id());

            picker.FileTypeFilter().Clear();
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                auto filters = GetFileFilters();
                for (const auto& filter : filters)
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }
            else
            {
                picker.FileTypeFilter().Append(L"*");
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedNewViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedNewLocationId());
            }

            auto result = co_await picker.PickSingleFileAsync();
            if (result != nullptr)
            {
                std::wstringstream ss;
                ss << L"New FileOpenPicker with FileTypeFilter: ";
                
                auto filters = GetFileFilters();
                for (size_t i = 0; i < filters.size(); ++i) {
                    if (i > 0) ss << L", ";
                    ss << filters[i].c_str();
                }
                
                ss << L"\nFile: " << std::filesystem::path(result.Path().c_str()).filename().c_str() 
                   << L"\nPath: " << result.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                std::wstringstream ss;
                ss << L"New FileOpenPicker with FileTypeFilter: ";
                
                auto filters = GetFileFilters();
                for (size_t i = 0; i < filters.size(); ++i) {
                    if (i > 0) ss << L", ";
                    ss << filters[i].c_str();
                }
                
                ss << L"\nOperation cancelled";
                LogResult(winrt::hstring{ss.str()});
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in New FileTypeFilter: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    // FileSavePicker Tests
    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpFileTypeChoices_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Windows::Storage::Pickers::FileSavePicker();
            auto hwnd = GetWindowHandle();
            auto initializeWithWindow = picker.as<IInitializeWithWindow>();
            initializeWithWindow->Initialize(hwnd);

            if (SuggestedFileNameCheckBox().IsChecked().Value())
            {
                picker.SuggestedFileName(SuggestedFileNameInput().Text());
            }

            if (DefaultFileExtensionCheckBox().IsChecked().Value())
            {
                picker.DefaultFileExtension(DefaultFileExtensionInput().Text());
            }

            picker.FileTypeChoices().Clear();
            if (FileTypeChoicesCheckBox().IsChecked().Value())
            {
                hstring choicesJson = FileTypeChoicesInput().Text();
                if (!choicesJson.empty())
                {
                    try {
                        auto jsonValue = winrt::Windows::Data::Json::JsonObject::Parse(choicesJson);
                        for (auto const& pair : jsonValue)
                        {
                            auto key = pair.Key();
                            auto values = pair.Value().GetArray();
                            
                            winrt::Windows::Foundation::Collections::IVector<hstring> extensions = 
                                winrt::single_threaded_vector<hstring>();
                            

                            for (auto const& value : values)
                            {
                                extensions.Append(value.GetString());
                            }
                            
                            picker.FileTypeChoices().Insert(key, extensions);
                        }
                    }
                    catch (...) {
                        LogResult(L"Error parsing JSON file type choices");
                    }
                }
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedLocation());
            }

            auto file = co_await picker.PickSaveFileAsync();
            if (file != nullptr)
            {
                std::wstringstream ss;
                ss << L"UWP FileSavePicker with FileTypeChoices\nFile: " << file.Name().c_str() 
                   << L"\nPath: " << file.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"UWP FileSavePicker with FileTypeChoices\nOperation cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in UWP FileTypeChoices: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewFileTypeChoices_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker(this->AppWindow().Id());

            if (SuggestedFileNameCheckBox().IsChecked().Value())
            {
                picker.SuggestedFileName(SuggestedFileNameInput().Text());
            }

            if (DefaultFileExtensionCheckBox().IsChecked().Value())
            {
                picker.DefaultFileExtension(DefaultFileExtensionInput().Text());
            }

            picker.FileTypeChoices().Clear();
            if (FileTypeChoicesCheckBox().IsChecked().Value())
            {
                hstring choicesJson = FileTypeChoicesInput().Text();
                if (!choicesJson.empty())
                {
                    try {
                        auto jsonValue = winrt::Windows::Data::Json::JsonObject::Parse(choicesJson);
                        for (auto const& pair : jsonValue)
                        {
                            auto key = pair.Key();
                            auto values = pair.Value().GetArray();
                            
                            winrt::Windows::Foundation::Collections::IVector<hstring> extensions = 
                                winrt::single_threaded_vector<hstring>();
                            

                            for (auto const& value : values)
                            {
                                extensions.Append(value.GetString());
                            }
                            
                            picker.FileTypeChoices().Insert(key, extensions);
                        }
                    }
                    catch (...) {
                        LogResult(L"Error parsing JSON file type choices");
                    }
                }
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedNewLocationId());
            }

            auto result = co_await picker.PickSaveFileAsync();
            if (result != nullptr)
            {
                std::wstringstream ss;
                ss << L"New FileSavePicker with FileTypeChoices\nFile: " 
                   << std::filesystem::path(result.Path().c_str()).filename().c_str() 
                   << L"\nPath: " << result.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"New FileSavePicker with FileTypeChoices\nOperation cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in New FileTypeChoices: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    // FolderPicker Tests
    winrt::Windows::Foundation::IAsyncAction MainWindow::UwpPickFolder_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Windows::Storage::Pickers::FolderPicker();
            auto hwnd = GetWindowHandle();
            auto initializeWithWindow = picker.as<IInitializeWithWindow>();
            initializeWithWindow->Initialize(hwnd);

            picker.FileTypeFilter().Clear();
            if (FileTypeFilterCheckBox().IsChecked().Value())
            {
                auto filters = GetFileFilters();
                for (const auto& filter : filters)
                {
                    picker.FileTypeFilter().Append(filter);
                }
            }
            else
            {
                picker.FileTypeFilter().Append(L"*");
            }

            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedLocation());
            }

            auto folder = co_await picker.PickSingleFolderAsync();
            if (folder != nullptr)
            {
                std::wstringstream ss;
                ss << L"UWP FolderPicker - PickSingleFolderAsync:\nFolder: " << folder.Name().c_str() 
                   << L"\nPath: " << folder.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"UWP FolderPicker - PickSingleFolderAsync: Operation cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in UWP FolderPicker: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::NewPickFolder_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();
        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FolderPicker(this->AppWindow().Id());
            
            //picker.FileTypeFilter().Clear();
            //if (FileTypeFilterCheckBox().IsChecked().Value())
            //{
            //    auto filters = GetFileFilters();
            //    for (const auto& filter : filters)
            //    {
            //        picker.FileTypeFilter().Append(filter);
            //    }
            //}
            //else
            //{
            //    picker.FileTypeFilter().Append(L"*");
            //}
            
            if (CommitButtonCheckBox().IsChecked().Value())
            {
                picker.CommitButtonText(CommitButtonTextInput().Text());
            }

            if (ViewModeCheckBox().IsChecked().Value())
            {
                picker.ViewMode(GetSelectedNewViewMode());
            }

            if (SettingsIdCheckBox().IsChecked().Value())
            {
                picker.SettingsIdentifier(SettingsIdInput().Text());
            }

            if (SuggestedStartLocationCheckBox().IsChecked().Value())
            {
                picker.SuggestedStartLocation(GetSelectedNewLocationId());
            }

            auto result = co_await picker.PickSingleFolderAsync();
            if (result != nullptr)
            {
                std::wstringstream ss;
                ss << L"New FolderPicker - PickSingleFolderAsync:\nFolder: " 
                   << std::filesystem::path(result.Path().c_str()).filename().c_str() 
                   << L"\nPath: " << result.Path().c_str();
                LogResult(winrt::hstring{ss.str()});
            }
            else
            {
                LogResult(L"New FolderPicker - PickSingleFolderAsync: Operation cancelled");
            }
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in New FolderPicker: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }
    }

    // Test any code
    winrt::Windows::Foundation::IAsyncAction MainWindow::TestAnyCode_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto lifetime = get_strong();

        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker(this->AppWindow().Id());
            picker.TrySetSuggestedSaveFilePath(L"C:\\temp\\");
            auto result = co_await picker.PickSaveFileAsync();

            LogResult(L"Test code executed successfully");
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in test code: " << ex.message().c_str();
            LogResult(winrt::hstring{ ss.str() });
        }

        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker(this->AppWindow().Id());
            picker.TrySetSuggestedSaveFilePath(L"C:\\temp3\\MyFile.txt");
            auto result = co_await picker.PickSaveFileAsync();

            LogResult(L"Test code executed successfully");
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in test code: " << ex.message().c_str();
            LogResult(winrt::hstring{ss.str()});
        }

        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker(this->AppWindow().Id());
            picker.TrySetSuggestedSaveFilePath(L"illegal*%$^&-_folderpath\\MyFile.txt");
            auto result = co_await picker.PickSaveFileAsync();

            LogResult(L"Test code executed successfully");
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in test code: " << ex.message().c_str();
            LogResult(winrt::hstring{ ss.str() });
        }

        try
        {
            auto picker = winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker(this->AppWindow().Id());
            picker.TrySetSuggestedSaveFilePath(L"C:\\temp\\illegal*%$^&-_MyFile.txt");
            auto result = co_await picker.PickSaveFileAsync();

            LogResult(L"Test code executed successfully");
        }
        catch (hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"Error in test code: " << ex.message().c_str();
            LogResult(winrt::hstring{ ss.str() });
        }


        co_return;
    }

    // Helper function to get window handle
    HWND MainWindow::GetWindowHandle()
    {
        HWND hWnd = nullptr;
        // m_inner is the implementation's inner object, typically available in WinRT C++/WinUI3
        auto windowNative = this->m_inner.as<IWindowNative>();
        if (windowNative)
        {
            check_hresult(windowNative->get_WindowHandle(&hWnd));
        }
        return hWnd;
    }

}
