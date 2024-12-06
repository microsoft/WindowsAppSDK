// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "FileOpenPicker.h"
#include "Microsoft.Windows.Storage.Pickers.FileOpenPicker.g.cpp"
#include <windows.h>
#include <shobjidl.h> 
#include <wil/cppwinrt.h>
#include <wil/com.h>
#include <wil/resource.h>

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
	void FileOpenPicker::MyProperty(int32_t value)
	{
		throw hresult_not_implemented();
	}

    hstring FileOpenPicker::MyString()
    {
        throw hresult_not_implemented();
    }
    void FileOpenPicker::MyString(hstring const& value)
    {
        throw hresult_not_implemented();
    }

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> FileOpenPicker::PickSingleFileAsync()
	{
		winrt::apartment_context ui_thread;

		co_await winrt::resume_background();

        MyString();

		// Handle cancellation.
		auto cancellationToken = co_await winrt::get_cancellation_token();
		if (cancellationToken())
		{
			co_return nullptr;
		}

		// TODO: should we initialize COM?
		//wil::com_initialize_ex initializeCom{ COINIT_APARTMENTTHREADED };

		wil::com_ptr<IFileOpenDialog> fileOpenDialog;
		THROW_IF_FAILED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&fileOpenDialog)));

		HRESULT hr = fileOpenDialog->Show(nullptr);
		if (FAILED(hr) || cancellationToken())
		{
			co_return nullptr;
		}

		wil::com_ptr<IShellItem> shellItem;
		THROW_IF_FAILED(fileOpenDialog->GetResult(shellItem.put()));

		wil::unique_cotaskmem_string filePath;
		THROW_IF_FAILED(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath));

		// Convert the file path to a StorageFile.
		auto const& file = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(filePath.get());
		if (cancellationToken()) {
			co_return nullptr;
		}

		co_await ui_thread;
		if (cancellationToken()) {
			co_return nullptr;
		}

		co_return file;
	}
}
