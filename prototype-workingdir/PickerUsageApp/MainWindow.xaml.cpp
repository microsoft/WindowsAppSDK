#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <string>
#include <shobjidl.h>
#include <microsoft.ui.xaml.window.h>
#include <winrt/Windows.UI.Popups.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
//using namespace Windows::Foundation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PickerUsageApp::implementation
{
    Windows::Storage::Pickers::PickerViewMode Convert(Microsoft::Storage::Pickers::PickerViewMode viewMode)
    {
        switch (viewMode)
        {
        case winrt::Microsoft::Storage::Pickers::PickerViewMode::List:
            return Windows::Storage::Pickers::PickerViewMode::List;
        case winrt::Microsoft::Storage::Pickers::PickerViewMode::Thumbnail:
            return Windows::Storage::Pickers::PickerViewMode::Thumbnail;
        default:
            return Windows::Storage::Pickers::PickerViewMode::List;
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::SDKClick(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        labelBlock().Text(L"");
        hstring message{};
        try
        {
            switch (m_PickerTypeIndex)
            {
            case 0:
                message = co_await  OpenFileSDKClick(sender, args);
                break;
            case 1:
                message = co_await  SaveFileSDKClick();
                break;
            case 2:
                message = co_await  OpenFolderSDKClick();
                break;
            default:
                message = L"Unsupported Picker Type";
                break;
            }
        }
        catch (winrt::hresult_error const& ex_)
        {
            message = ex_.message();
        }
        labelBlock().Text(message);
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::UWPClick(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        labelBlock().Text(L"");
        hstring message{};
        try
        {
            switch (m_PickerTypeIndex)
            {
            case 0:
                message = co_await OpenFileUWPClick(sender, args);
                break;
            case 1:
                message = co_await SaveFileUWPClick();
                break;
            case 2:
                message = co_await OpenFolderUWPClick();
                break;

            default:
                message = L"Unsupported Picker Type";
                break;
            }
        }
        catch (winrt::hresult_error const& ex_)
        {
            message = ex_.message();
        }
        labelBlock().Text(message);
    }


    Windows::Foundation::IAsyncOperation<hstring> MainWindow::OpenFileUWPClick(IInspectable const&, RoutedEventArgs const&)
    {
        auto windowNative = this->m_inner.as<IWindowNative>();
        HWND hWnd = nullptr;
        check_hresult(windowNative->get_WindowHandle(&hWnd));

        winrt::Windows::Storage::Pickers::FileOpenPicker picker{};

        picker.as<::IInitializeWithWindow>()->Initialize(hWnd);
        SetOpenPickerOptions<winrt::Windows::Storage::Pickers::FileOpenPicker, winrt::Windows::Storage::Pickers::PickerLocationId>(picker);
        picker.ViewMode(Convert(m_ViewMode));

        if (!m_MultipleSelect)
        {
            auto& file = co_await picker.PickSingleFileAsync();
            if (file != nullptr)
            {
                co_return file.Path();
            }
        }
        else
        {
            auto& files = co_await picker.PickMultipleFilesAsync();
            winrt::hstring names = L"";
            for (auto& file : files)
            {
                names = names + file.Path() + L"\n";
            }
            co_return names;
        }
        co_return L"no selection";
    }

    Windows::Foundation::IAsyncOperation<hstring> MainWindow::SaveFileUWPClick()
    {
        auto windowNative = this->m_inner.as<IWindowNative>();
        HWND hWnd = nullptr;
        check_hresult(windowNative->get_WindowHandle(&hWnd));

        winrt::Windows::Storage::Pickers::FileSavePicker picker{};

        picker.as<::IInitializeWithWindow>()->Initialize(hWnd);
        SetSavePickerOptions<winrt::Windows::Storage::Pickers::FileSavePicker, winrt::Windows::Storage::Pickers::PickerLocationId>(picker);

        if (!m_MultipleSelect)
        {
            auto& file = co_await picker.PickSaveFileAsync();
            if (file != nullptr)
            {
                co_return file.Path();
            }
        }
        else
        {
            co_return L"File Save Picker does not support multi selection";
        }
        co_return L"no selection";
    }

    winrt::Windows::Foundation::IAsyncOperation<hstring> MainWindow::OpenFolderUWPClick()
    {
        auto windowNative = this->m_inner.as<IWindowNative>();
        HWND hWnd = nullptr;
        check_hresult(windowNative->get_WindowHandle(&hWnd));

        winrt::Windows::Storage::Pickers::FolderPicker picker{};

        picker.as<::IInitializeWithWindow>()->Initialize(hWnd);
        SetOpenPickerOptions<winrt::Windows::Storage::Pickers::FolderPicker, winrt::Windows::Storage::Pickers::PickerLocationId>(picker);
        picker.ViewMode(Convert(m_ViewMode));

        if (!m_MultipleSelect)
        {
            auto& folder = co_await picker.PickSingleFolderAsync();
            if (folder != nullptr)
            {
                co_return folder.Path();
            }
        }
        else
        {
            co_return L"Folder Picker does not support multi selection";
        }
        co_return L"no selection";
    }

    Windows::Foundation::IAsyncOperation<hstring> MainWindow::OpenFileSDKClick(IInspectable const&, RoutedEventArgs const&)
    {
        auto id = AppWindow().Id();
        winrt::Microsoft::Storage::Pickers::FileOpenPicker picker{ id };

        SetOpenPickerOptions<winrt::Microsoft::Storage::Pickers::FileOpenPicker, winrt::Microsoft::Storage::Pickers::PickerLocationId>(picker);
        picker.ViewMode(m_ViewMode);
        if (!m_MultipleSelect)
        {
            auto& file = co_await picker.PickSingleFileAsync();
            if (file != nullptr)
            {
                co_return file.Path();
            }
        }
        else
        {
            auto& files = co_await picker.PickMultipleFilesAsync();
            winrt::hstring names = L"";
            for (auto& file : files)
            {
                names = names + file.Path() + L"\n";
            }
            co_return names;
        }
        co_return L"no selection";
    }

    Windows::Foundation::IAsyncOperation<hstring> MainWindow::SaveFileSDKClick()
    {
        auto id = AppWindow().Id();
        winrt::Microsoft::Storage::Pickers::FileSavePicker picker{ id };

        SetSavePickerOptions<winrt::Microsoft::Storage::Pickers::FileSavePicker, winrt::Microsoft::Storage::Pickers::PickerLocationId>(picker);
        if (!m_MultipleSelect)
        {
            auto& file = co_await picker.PickSaveFileAsync();
            if (file != nullptr)
            {
                co_return file.Path();
            }
        }
        else
        {
            co_return L"FileSavePicker does not support multi selection";
        }
        co_return L"no selection";
    }

    winrt::Windows::Foundation::IAsyncOperation<hstring> MainWindow::OpenFolderSDKClick()
    {
        auto id = AppWindow().Id();
        winrt::Microsoft::Storage::Pickers::FolderPicker picker{ id };

        SetOpenPickerOptions<winrt::Microsoft::Storage::Pickers::FolderPicker, winrt::Microsoft::Storage::Pickers::PickerLocationId>(picker);
        picker.ViewMode(m_ViewMode);
        if (!m_MultipleSelect)
        {
            auto& folder = co_await picker.PickSingleFolderAsync();
            if (folder != nullptr)
            {
                co_return folder.Path();
            }
        }
        else
        {
            co_return L"Folder multiple selection is not supported";
        }
        co_return L"no selection";
    }
}


void winrt::PickerUsageApp::implementation::MainWindow::UIFronzenTestClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    counterBlock().Text(std::to_wstring(count));
    count++;
}


void winrt::PickerUsageApp::implementation::MainWindow::toggleCustomLableClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    m_isUseCustomLabel = !m_isUseCustomLabel;
    if (m_isUseCustomLabel)
    {
        useCustomLabelToggle().Content(box_value(L"Disable"));
        customLabelBox().Visibility(Visibility::Visible);
    }
    else
    {
        useCustomLabelToggle().Content(box_value(L"Enable"));
        customLabelBox().Visibility(Visibility::Collapsed);
    }
}


void winrt::PickerUsageApp::implementation::MainWindow::ViewModeSelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    auto radioButtons = sender.as<Microsoft::UI::Xaml::Controls::RadioButtons>();
    auto selectedIndex = radioButtons.SelectedIndex();
    switch (selectedIndex)
    {
    case 0:
        m_ViewMode = Microsoft::Storage::Pickers::PickerViewMode::List;
        break;
    case 1:
        m_ViewMode = Microsoft::Storage::Pickers::PickerViewMode::Thumbnail;
        break;
    default:
        break;
    }
}


void winrt::PickerUsageApp::implementation::MainWindow::FilterTypeSelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    auto radioButtons = sender.as<Microsoft::UI::Xaml::Controls::RadioButtons>();

    m_FilterTypeIndex = radioButtons.SelectedIndex();
}


void winrt::PickerUsageApp::implementation::MainWindow::SettingsIdentifierChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    auto radioButtons = sender.as<Microsoft::UI::Xaml::Controls::RadioButtons>();
    m_SettingsIdentifierIndex = radioButtons.SelectedIndex();
}

void winrt::PickerUsageApp::implementation::MainWindow::PickerLocationIdChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    auto radioButtons = sender.as<Microsoft::UI::Xaml::Controls::RadioButtons>();
    m_PickerLocationIdIndex = radioButtons.SelectedIndex();
}


void winrt::PickerUsageApp::implementation::MainWindow::MultiSelectToggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    m_MultipleSelect = sender.as<Microsoft::UI::Xaml::Controls::ToggleSwitch>().IsOn();
}

void winrt::PickerUsageApp::implementation::MainWindow::PickerTypeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    m_PickerTypeIndex = sender.as<Microsoft::UI::Xaml::Controls::RadioButtons>().SelectedIndex();
}
