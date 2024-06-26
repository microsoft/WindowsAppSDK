// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
bool IsResourceNotFound(HRESULT hr);
HRESULT GetDefaultPriFile(winrt::hstring& path);
bool IsWellFormedLanguageTag(const wchar_t* languageTag);
