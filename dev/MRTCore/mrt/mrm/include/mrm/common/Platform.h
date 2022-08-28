// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#ifdef DEF_RTL
#include "mrm/common/PlatformRtl.h"
#else
#include "mrm/common/PlatformWin32.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    // Common functions which should be implemented for all supported platforms.
    //
    // Using PVOID instead of various types so we'll compile properly

    ULONG DefExpandEnvironmentStrings(__in PCWSTR Source, __out_opt PWSTR Destination, __in ULONG Size);

    ULONG _DefVirtualQuery(__in_opt PVOID Address, __out PMEMORY_BASIC_INFORMATION Buffer, __in ULONG Length);

    void _DefCloseHandle(__in HANDLE handle);

    HRESULT _DefCreateFile(
        __in PCWSTR FileName,
        __in ULONG DesiredAccess,
        __in ULONG ShareMode,
        __in_opt PSECURITY_ATTRIBUTES pSecurityAttributes,
        __in ULONG CreationFlags,
        __in ULONG FileAttributes,
        __out PHANDLE pHandle);

    HRESULT _DefCreateFileMapping(
        __in HANDLE FileHandle,
        __in_opt PSECURITY_ATTRIBUTES pSecurityAttributes,
        __in ULONG ProtectFlag,
        __in ULONG MaximumSizeHigh,
        __in ULONG MaximumSizeLow,
        __in_opt PCWSTR pName,
        __out PHANDLE pMappingHandle);

    HANDLE _DefGetCurrentProcess();

    HRESULT _DefGetFileSizeEx(__in HANDLE hFile, __out PLARGE_INTEGER pFileSize);

    DEFRESULT _DefGetLastError();

    HRESULT _DefMapViewOfFile(
        __in HANDLE FileMapping,
        __in ULONG DesiredAccess,
        __in ULONG FileOffsetHigh,
        __in ULONG FileOffsetLow,
        __in size_t NumberOfBytesToMap,
        __out PVOID* pBaseAddress);

    HRESULT _DefOpenFileMapping(__in ULONG DesiredAccess, __in BOOLEAN InheritHandle, __in PCWSTR pName, __out PHANDLE pFileMappingHandle);

    HRESULT _DefReadFile(__in HANDLE Handle, __out PVOID pBuffer, __in ULONG BytesToRead, __out_opt ULONG* BytesRead);

    BOOLEAN _DefUnmapViewOfFile(__in PVOID pBaseAddress);

    UINT32 _DefComputeCrc32(__in UINT32 partialCrc, __in_bcount(cbBuf) const BYTE* pBuf, __in UINT32 cbBuf);

    UINT32
    _DefComputeStringCrc32(__in UINT32 partialCrc, __in BOOLEAN isCaseInsensitive, __in_ecount(cchStr) PCWSTR pStr, __in UINT32 cchStr);

    PWSTR _DefDuplicateString(__in PCWSTR Source);

    UINT _DefGetDriveTypeW(_In_opt_ PCWSTR rootPathName);

    BOOLEAN _DefIsWellFormedTag(_In_ PCWSTR tag);

    HRESULT _DefGetDistanceOfClosestLanguageInList(
        _In_ PCWSTR language,
        _In_ PCWSTR languagesList,
        _In_ wchar_t listDelimiter,
        _Out_ double* closestDistance);

#ifdef __cplusplus
}
#endif

#if DBG
#define DEF_ASSERT(a) \
    _Analysis_assume_(a); \
    DEF_PLATFORM_ASSERT(a)
#else
#define DEF_ASSERT(a) _Analysis_assume_(a)
#endif
