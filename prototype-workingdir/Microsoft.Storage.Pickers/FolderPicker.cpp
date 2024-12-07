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

	void FolderPicker::CaptureParameters(PickerCommon::PickerParameters& parameters) {
		parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
		parameters.CommitButtonText = m_commitButtonText;
		parameters.SettingsIdentifierId = m_SettingsIdentifier;
		parameters.PickerLocationId = m_PickerLocationId;
        parameters.FileTypeFilterPara = PickerCommon::CaptureFilterSpec(parameters.FileTypeFilterData, m_fileTypeFilter.GetView());
	}


	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> FolderPicker::PickSingleFolderAsync()
	{
		PickerCommon::PickerParameters parameters{};
		CaptureParameters(parameters);

		co_await winrt::resume_background();

		auto cancellationToken = co_await winrt::get_cancellation_token();
		if (cancellationToken())
		{
			co_return nullptr;
		}

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

		auto folder = co_await PickerCommon::CreateStorageFolderFromShellItem(shellItem);
		if (cancellationToken())
		{
			co_return nullptr;
		}

		co_return folder;
	}
}
