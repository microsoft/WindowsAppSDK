// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// This is a mocked PickderLocalization head file for test purpose.

#pragma once
#include "pch.h"


namespace PickerLocalization
{
    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key);
    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key, winrt::hstring fallbackContent);
}