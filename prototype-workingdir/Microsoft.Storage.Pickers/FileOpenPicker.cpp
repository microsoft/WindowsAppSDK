#include "pch.h"
#include "FileOpenPicker.h"
#include "FileOpenPicker.g.cpp"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <winrt/Microsoft.UI.Interop.h>
#include "PickerCommon.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{
	FileOpenPicker::FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId)
		: m_windowId(windowId)
	{
	}

	winrt::Microsoft::Storage::Pickers::PickerViewMode FileOpenPicker::ViewMode()
	{
		return m_ViewMode;
	}
	void FileOpenPicker::ViewMode(winrt::Microsoft::Storage::Pickers::PickerViewMode const& value)
	{
		m_ViewMode = value;
	}
	hstring FileOpenPicker::SettingsIdentifier()
	{
		return m_SettingsIdentifier;
	}
	void FileOpenPicker::SettingsIdentifier(hstring const& value)
	{
		m_SettingsIdentifier = value;
	}
	winrt::Microsoft::Storage::Pickers::PickerLocationId FileOpenPicker::SuggestedStartLocation()
	{
		return m_PickerLocationId;
	}
	void FileOpenPicker::SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value)
	{
		m_PickerLocationId = value;
	}
	winrt::hstring FileOpenPicker::CommitButtonText()
	{
		return m_commitButtonText;
	}
	void FileOpenPicker::CommitButtonText(winrt::hstring const& value)
	{
		m_commitButtonText = value;
	}
	winrt::Windows::Foundation::Collections::IVector<hstring> FileOpenPicker::FileTypeFilter()
	{
		return m_fileTypeFilter;
	}

	struct FileOpenPickerParameters {
		winrt::hstring CommitButtonText;
		winrt::hstring SettingsIdentifierId;
		PickerLocationId PickerLocationId;
		std::vector<winrt::hstring> FileTypeFilterData{};
		std::vector<COMDLG_FILTERSPEC> FileTypeFilterPara{};
		HWND HWnd;

		void ConfigureDialog(winrt::com_ptr<IFileOpenDialog> dialog) {
			PickerCommon::ConfigureDialogCommon(dialog, CommitButtonText, SettingsIdentifierId, PickerLocationId);
			check_hresult(dialog->SetFileTypes(FileTypeFilterPara.size(), FileTypeFilterPara.data()));
		}
	};

	void FileOpenPicker::CaptureParameters(FileOpenPickerParameters& parameters) {
		parameters.CommitButtonText = m_commitButtonText;
		parameters.SettingsIdentifierId = m_SettingsIdentifier;
		parameters.PickerLocationId = m_PickerLocationId;
		for (size_t i = 0; i < m_fileTypeFilter.Size(); i++)
		{
			parameters.FileTypeFilterData.push_back(m_fileTypeFilter.GetAt(i));
			parameters.FileTypeFilterPara.push_back({ L"", parameters.FileTypeFilterData[i].c_str() });
		}
		parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> FileOpenPicker::PickSingleFileAsync()
	{
		FileOpenPickerParameters parameters{};

		CaptureParameters(parameters);

		co_await winrt::resume_background();

		auto cancellationToken = co_await winrt::get_cancellation_token();
		if (cancellationToken())
		{
			co_return nullptr;
		}

		// TODO: should we initialize COM?
		// wil::com_initialize_ex initializeCom{ COINIT_APARTMENTTHREADED };

		auto dialog = create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CONTEXT_ALL);

		parameters.ConfigureDialog(dialog);

		auto hr = dialog->Show(parameters.HWnd);
		if (FAILED(hr) || cancellationToken())
		{
			co_return nullptr;
		}

		winrt::com_ptr<IShellItem> shellItem{};
		check_hresult(dialog->GetResult(shellItem.put()));

		auto& file = co_await PickerCommon::CreateStorageFileFromShellItem(shellItem);
		if (cancellationToken())
		{
			co_return nullptr;
		}

		co_return file;
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::StorageFile>> FileOpenPicker::PickMultipleFilesAsync()
	{
		FileOpenPickerParameters parameters{};

		CaptureParameters(parameters);

		co_await winrt::resume_background();

		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Storage::StorageFile> results{ winrt::single_threaded_vector<winrt::Windows::Storage::StorageFile>() };

		auto cancellationToken = co_await winrt::get_cancellation_token();
		if (cancellationToken())
		{
			co_return results.GetView();
		}

		auto dialog = create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CONTEXT_ALL);

		parameters.ConfigureDialog(dialog);

		auto pickerOptions = FOS_ALLOWMULTISELECT;
		check_hresult(dialog->SetOptions(pickerOptions));

		auto hr = dialog->Show(parameters.HWnd);
		if (FAILED(hr) || cancellationToken())
		{
			co_return results.GetView();
		}

		winrt::com_ptr<IShellItemArray> shellItems{};
		check_hresult(dialog->GetResults(shellItems.put()));

		DWORD itemCount = 0;
		check_hresult(shellItems->GetCount(&itemCount));

		winrt::com_ptr<IShellItem> shellItem{};
		for (auto i = 0; i < itemCount; i++) {
			check_hresult(shellItems->GetItemAt(i, shellItem.put()));
			auto& file = co_await PickerCommon::CreateStorageFileFromShellItem(shellItem);
			results.Append(file);
		}


		if (cancellationToken())
		{
			results.Clear();
			co_return results.GetView();
		}

		co_return results.GetView();
	}
}