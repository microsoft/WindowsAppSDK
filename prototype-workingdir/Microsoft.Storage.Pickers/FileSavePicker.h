#pragma once
#include "FileSavePicker.g.h"
#include "PickerCommon.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{
	struct FileSavePickerParameters;

	struct FileSavePicker : FileSavePickerT<FileSavePicker>
	{
		FileSavePicker(winrt::Microsoft::UI::WindowId const& windowId);
		hstring SettingsIdentifier();
		void SettingsIdentifier(hstring const& value);
		winrt::Microsoft::Storage::Pickers::PickerLocationId SuggestedStartLocation();
		void SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value);
		hstring CommitButtonText();
		void CommitButtonText(hstring const& value);
		winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileTypeChoices();
		hstring DefaultFileExtension();
		void DefaultFileExtension(hstring const& value);
		winrt::Windows::Storage::StorageFile SuggestedSaveFile();
		void SuggestedSaveFile(winrt::Windows::Storage::StorageFile const& value);
		hstring SuggestedFileName();
		void SuggestedFileName(hstring const& value);
		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> PickSaveFileAsync();
	private:
		winrt::Microsoft::UI::WindowId m_windowId{};

		hstring m_SettingsIdentifier{};
		PickerLocationId m_PickerLocationId{ PickerLocationId::Unspecified };
		hstring m_commitButtonText{};
		hstring m_defaultFileExtension{};
		winrt::Windows::Storage::StorageFile m_suggestedSaveFile{ nullptr };
		hstring m_suggestedFileName{};
		winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> m_fileTypeChoices{ winrt::single_threaded_map<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>() };

		void CaptureParameters(PickerCommon::PickerParameters& parameters);
	};
}
namespace winrt::Microsoft::Storage::Pickers::factory_implementation
{
	struct FileSavePicker : FileSavePickerT<FileSavePicker, implementation::FileSavePicker>
	{
	};
}
