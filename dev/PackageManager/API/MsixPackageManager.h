// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MSIXPACKAGEMANAGER_H)
#define MSIXPACKAGEMANAGER_H

/// MSIX Package Manager: Scanning for an applicable package
#define MSIXPACKAGEMANAGER_E_PACKAGE_SCAN           _HRESULT_TYPEDEF_(0x80040301L)

/// MSIX Package Manager: Found a package but doesn't match the criteria
#define MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH _HRESULT_TYPEDEF_(0x80040302L)

/// MSIX Package Manager: Found a package that does match the criteria
#define MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_MATCH     _HRESULT_TYPEDEF_(0x80040303L)

/// MSIX Package Manager: Found no applicable package matching the criteria
#define MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_FAILED    _HRESULT_TYPEDEF_(0x80040304L)

#endif // MSIXPACKAGEMANAGER_H
