// TODO: use better namespace, maybe anonymous namespace?
#pragma once
#include "pch.h"
#include "ShObjIdl.h"
#include "winrt/Microsoft.Storage.Pickers.h"

#pragma once

namespace PickerCommon {
	void ConfigureDialogCommon(
		winrt::com_ptr<IFileOpenDialog> dialog,
		winrt::hstring commitButtonText,
		winrt::hstring settingIdentifierId,
		winrt::Microsoft::Storage::Pickers::PickerLocationId pickerLocationId
	);

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> CreateStorageFileFromShellItem(winrt::com_ptr<IShellItem> shellItem);
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> CreateStorageFolderFromShellItem(winrt::com_ptr<IShellItem> shellItem);
}