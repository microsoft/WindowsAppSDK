#pragma once
#include "FileOpenPicker.g.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{
	struct FileOpenPickerParameters;

	struct FileOpenPicker : FileOpenPickerT<FileOpenPicker>
	{
		FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId);

		winrt::Microsoft::Storage::Pickers::PickerViewMode ViewMode();
		void ViewMode(winrt::Microsoft::Storage::Pickers::PickerViewMode const& value);
		hstring SettingsIdentifier();
		void SettingsIdentifier(hstring const& value);
		winrt::Microsoft::Storage::Pickers::PickerLocationId SuggestedStartLocation();
		void SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value);
		winrt::hstring CommitButtonText();
		void CommitButtonText(winrt::hstring const& value);

		winrt::Windows::Foundation::Collections::IVector<hstring> FileTypeFilter();

		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> PickSingleFileAsync();
		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::StorageFile>> PickMultipleFilesAsync();

	private:
		winrt::Microsoft::UI::WindowId m_windowId{};
		winrt::hstring m_SettingsIdentifier{};
		PickerLocationId m_PickerLocationId{ PickerLocationId::Unspecified };
		winrt::hstring m_commitButtonText{};

		PickerViewMode m_ViewMode{ PickerViewMode::List };

		winrt::Windows::Foundation::Collections::IVector<hstring> m_fileTypeFilter{ winrt::single_threaded_vector<hstring>() };

		void CaptureParameters(FileOpenPickerParameters& parameters);
	};
}
namespace winrt::Microsoft::Storage::Pickers::factory_implementation
{
	struct FileOpenPicker : FileOpenPickerT<FileOpenPicker, implementation::FileOpenPicker>
	{
	};
}