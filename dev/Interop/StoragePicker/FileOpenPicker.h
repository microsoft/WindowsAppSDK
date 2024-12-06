// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Storage.Pickers.FileOpenPicker.g.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker>
    {
        FileOpenPicker() = default;

        hstring MyString();
        void MyString(hstring const& value);

        int32_t MyProperty();
        void MyProperty(int32_t value);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> PickSingleFileAsync();
    };
}
namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker, implementation::FileOpenPicker>
    {
    };
}
