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

	Windows::Storage::Pickers::PickerViewMode Convert(Microsoft::Storage::Pickers::PickerViewMode viewMode) {
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

	Windows::Foundation::IAsyncAction MainWindow::OpenFileUWPClick(IInspectable const&, RoutedEventArgs const&)
	{
		hstring error_mesasge{};
		try {
			labelBlock().Text(L"");
			auto windowNative = this->m_inner.as<IWindowNative>();
			HWND hWnd = nullptr;
			check_hresult(windowNative->get_WindowHandle(&hWnd));

			winrt::Windows::Storage::Pickers::FileOpenPicker picker{};

			picker.as<::IInitializeWithWindow>()->Initialize(hWnd);
			SetPickerOptions<winrt::Windows::Storage::Pickers::FileOpenPicker, winrt::Windows::Storage::Pickers::PickerLocationId>(picker);
			//SetPickerOptions(picker);
			picker.ViewMode(Convert(m_ViewMode));

			if (!m_MultipleSelect) {
				auto& file = co_await picker.PickSingleFileAsync();
				if (file != nullptr) {
					labelBlock().Text(file.Path());
				}
			}
			else {
				auto& files = co_await picker.PickMultipleFilesAsync();
				winrt::hstring names = L"";
				for (auto& file : files)
				{
					names = names + file.Path() + L"\n";
				}
				labelBlock().Text(names);
			}

			co_return;
		}
		catch (winrt::hresult_error const& ex_)
		{
			error_mesasge = ex_.message();
		}
		if (!error_mesasge.empty())
		{
			winrt::Windows::UI::Popups::MessageDialog dialog(error_mesasge);
			co_await dialog.ShowAsync();
		}
	}

	Windows::Foundation::IAsyncAction MainWindow::OpenFileSDKClick(IInspectable const&, RoutedEventArgs const&)
	{
		hstring error_mesasge{};
		try {
			labelBlock().Text(L"");
			auto id = AppWindow().Id();
			winrt::Microsoft::Storage::Pickers::FileOpenPicker picker{ id };

			SetPickerOptions<winrt::Microsoft::Storage::Pickers::FileOpenPicker, winrt::Microsoft::Storage::Pickers::PickerLocationId>(picker);
			//SetPickerOptions(picker);
			picker.ViewMode(m_ViewMode);
			if (!m_MultipleSelect) {
				auto& file = co_await picker.PickSingleFileAsync();
				if (file != nullptr) {
					labelBlock().Text(file.Path());
				}
			}
			else {
				auto& files = co_await picker.PickMultipleFilesAsync();
				winrt::hstring names = L"";
				for (auto& file : files)
				{
					names = names + file.Path() + L"\n";
				}
				labelBlock().Text(names);
			}
			co_return;
		}
		catch (winrt::hresult_error const& ex_)
		{
			error_mesasge = ex_.message();
		}
		if (!error_mesasge.empty())
		{
			winrt::Windows::UI::Popups::MessageDialog dialog(error_mesasge);
			co_await dialog.ShowAsync();
		}
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
