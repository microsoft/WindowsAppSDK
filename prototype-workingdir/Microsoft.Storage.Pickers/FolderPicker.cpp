#include "pch.h"
#include "FolderPicker.h"
#include "FolderPicker.g.cpp"
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <winrt/Microsoft.UI.Interop.h>
#include "PickerCommon.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{
	FolderPicker::FolderPicker(winrt::Microsoft::UI::WindowId const& windowId)
		: m_windowId(windowId)
	{
	}
	winrt::Microsoft::Storage::Pickers::PickerViewMode FolderPicker::ViewMode()
	{
		return m_ViewMode;
	}
	void FolderPicker::ViewMode(winrt::Microsoft::Storage::Pickers::PickerViewMode const& value)
	{
		m_ViewMode = value;
	}
	hstring FolderPicker::SettingsIdentifier()
	{
		return m_SettingsIdentifier;
	}
	void FolderPicker::SettingsIdentifier(hstring const& value)
	{
		m_SettingsIdentifier = value;
	}
	winrt::Microsoft::Storage::Pickers::PickerLocationId FolderPicker::SuggestedStartLocation()
	{
		return m_PickerLocationId;
	}
	void FolderPicker::SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value)
	{
		m_PickerLocationId = value;
	}
	hstring FolderPicker::CommitButtonText()
	{
		return m_commitButtonText;
	}
	void FolderPicker::CommitButtonText(hstring const& value)
	{
		m_commitButtonText = value;
	}
	winrt::Windows::Foundation::Collections::IVector<hstring> FolderPicker::FileTypeFilter()
	{
		return m_fileTypeFilter;

	}

	struct FolderPickerParameters {
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

	void FolderPicker::CaptureParameters(FolderPickerParameters& parameters) {
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


	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> FolderPicker::PickSingleFolderAsync()
	{
		FolderPickerParameters parameters{};

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
		dialog->SetOptions(FOS_PICKFOLDERS);

		auto hr = dialog->Show(parameters.HWnd);
		if (FAILED(hr) || cancellationToken())
		{
			co_return nullptr;
		}

		winrt::com_ptr<IShellItem> shellItem{};
		check_hresult(dialog->GetResult(shellItem.put()));

		auto& folder = co_await PickerCommon::CreateStorageFolderFromShellItem(shellItem);
		if (cancellationToken())
		{
			co_return nullptr;
		}

		co_return folder;
	}
}
