#include "pch.h"
#include "FileSavePicker.h"
#include "FileSavePicker.g.cpp"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <KnownFolders.h>
#include <wil/cppwinrt.h>
#include <wil/com.h>
#include <wil/resource.h>
#include <Microsoft.Ui.Xaml.Window.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "PickerCommon.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{

	FileSavePicker::FileSavePicker(winrt::Microsoft::UI::WindowId const& windowId)
		: m_windowId(windowId)
	{
	}
	hstring FileSavePicker::SettingsIdentifier()
	{
		return m_SettingsIdentifier;
	}
	void FileSavePicker::SettingsIdentifier(hstring const& value)
	{
		m_SettingsIdentifier = value;
	}
	winrt::Microsoft::Storage::Pickers::PickerLocationId FileSavePicker::SuggestedStartLocation()
	{
		return m_PickerLocationId;
	}
	void FileSavePicker::SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value)
	{
		m_PickerLocationId = value;
	}
	hstring FileSavePicker::CommitButtonText()
	{
		return m_commitButtonText;
	}
	void FileSavePicker::CommitButtonText(hstring const& value)
	{
		m_commitButtonText = value;
	}
	winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileSavePicker::FileTypeChoices()
	{
		return m_fileTypeChoices;
	}
	hstring FileSavePicker::DefaultFileExtension()
	{
		return m_defaultFileExtension;
	}
	void FileSavePicker::DefaultFileExtension(hstring const& value)
	{
		m_defaultFileExtension = value;
	}
	winrt::Windows::Storage::StorageFile FileSavePicker::SuggestedSaveFile()
	{
		return m_suggestedSaveFile;
	}
	void FileSavePicker::SuggestedSaveFile(winrt::Windows::Storage::StorageFile const& value)
	{
		m_suggestedSaveFile = value;
	}
	hstring FileSavePicker::SuggestedFileName()
	{
		return m_suggestedFileName;
	}
	void FileSavePicker::SuggestedFileName(hstring const& value)
	{
		m_suggestedFileName = value;
	}

	struct FileOpenPickerParameters {
		HWND HWnd;
		winrt::hstring CommitButtonText;
		winrt::hstring SettingsIdentifierId;
		PickerLocationId PickerLocationId;

		void ConfigureDialog(winrt::com_ptr<IFileOpenDialog> dialog) {
			PickerCommon::ConfigureDialogCommon(dialog, CommitButtonText, SettingsIdentifierId, PickerLocationId);
		}
	};

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> FileSavePicker::PickSaveFileAsync()
	{
		throw hresult_not_implemented();
	}
}
