// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(APPMODEL_PACKAGEINFO_H)
#define APPMODEL_PACKAGEINFO_H

namespace appmodel
{
// GetPackageInfo2 requires >> 19H1 (not available on RS5). Anyone needing GetPackageInfo2
// should call this so as not to create an import reference to GetPackageInfo2 that can't
// be resolved on RS5. This is significant for as long as we support Windows <= RS5.
LONG GetPackageInfo2(
    PACKAGE_INFO_REFERENCE packageInfoReference,
    UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);
}

#endif // APPMODEL_PACKAGEINFO_H
