#pragma once

#include "MainWindow.g.h"
#include <functional>

namespace winrt::PickerUsageApp::implementation
{
	struct MainWindow : MainWindowT<MainWindow>
	{
		int count{ 0 };

		MainWindow()
		{
			// Xaml objects should not call InitializeComponent during construction.
			// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
		}

		winrt::Windows::Foundation::IAsyncAction OpenFileSDKClick(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
		winrt::Windows::Foundation::IAsyncAction OpenFileUWPClick(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

		void UIFronzenTestClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		void toggleCustomLableClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		void ViewModeSelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
		void FilterTypeSelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
		void SettingsIdentifierChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
		void PickerLocationIdChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
		void MultiSelectToggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
	private:
		bool m_isUseCustomLabel{ false };
		winrt::Microsoft::Storage::Pickers::PickerViewMode m_ViewMode{ Microsoft::Storage::Pickers::PickerViewMode::List };
		int m_FilterTypeIndex{ 0 };
		int m_SettingsIdentifierIndex{ 0 };
		int m_PickerLocationIdIndex{ 0 };
		bool m_MultipleSelect{ false };


		// using this template approach helps us ensure use same logic on compatible user facing API
		template<typename TPicker, typename TPickerLocationId> void SetPickerOptions(TPicker picker) {
			if (m_isUseCustomLabel)
			{
				picker.CommitButtonText(customLabelBox().Text());
			}
			switch (m_SettingsIdentifierIndex)
			{
			case 1:
				picker.SettingsIdentifier(L"Identifier1");
				break;
			case 2:
				picker.SettingsIdentifier(L"Identifier2");
				break;
			default:
				picker.SettingsIdentifier({});
				break;
			}
			switch (m_FilterTypeIndex)
			{
			case 1:
				picker.FileTypeFilter().Append(L".jpg");
				picker.FileTypeFilter().Append(L".png");
				break;
			case 2:
				picker.FileTypeFilter().Append(L".jpg");
				picker.FileTypeFilter().Append(L".png");
				picker.FileTypeFilter().Append(L".json");
				break;
			default:
				picker.FileTypeFilter().Append(L"*");
				break;
			}
			switch (m_PickerLocationIdIndex)
			{
			case 1:
				picker.SuggestedStartLocation(TPickerLocationId::DocumentsLibrary);
				break;
			case 2:
				picker.SuggestedStartLocation(TPickerLocationId::Desktop);
				break;
			default:
				break;
			}


		}

	};
}

namespace winrt::PickerUsageApp::factory_implementation
{
	struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
	{
	};
}