// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ShObjIdl.h"

#include "winrt/base.h"
#include "winrt/Microsoft.Windows.Storage.Pickers.h"
#include "TerminalVelocityFeatures-StoragePickers.h"
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include "..\StoragePickersImpl\StoragePickersImpl.h"

namespace PickerCommon {
    winrt::hstring GetPathFromShellItem(winrt::com_ptr<IShellItem> shellItem);

    bool IsHStringNullOrEmpty(winrt::hstring value);

    void ConfigureDialog(winrt::com_ptr<IFileDialog> dialog, StoragePickersImpl::PickerParameters parameters, winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId pickerLocationId);
}
