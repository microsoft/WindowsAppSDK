// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

/*
 * Platform header files:
 * 1) Include any necessary headers
 */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NTSTRSAFE_NO_CB_FUNCTIONS
#define NTSTRSAFE_NO_CB_FUNCTIONS
#endif

#include <nt.h>
#include <ntrtl.h>
#include <nturtl.h>
#include <ntassert.h>

#include <wtypesbase.h>
#include <winerror.h>
#include <errno.h>
#include <ntstrsafe.h>
#include <ntintsafe.h>
#include <stdlib.h>

#ifdef __cplusplus
#include <new>
extern "C"
{
#endif

    HRESULT ErrnoToHResult(_In_ errno_t err);

#ifdef __cplusplus
}
#endif

#define Def_ErrnoFailed(WHAT, WHO, STATUS) Def_Check(((WHAT) != 0), TO_S(WHO), ErrnoToHResult(WHAT), (STATUS))

#define Def_HrFailed(WHAT, WHO, STATUS) Def_Check(FAILED(WHAT), TO_S(WHO), (WHAT), (STATUS))

typedef unsigned long _DEF_PLATFORM_RESULT_TYPE;
typedef float FLOAT;
typedef BOOLEAN __BOOL;

/*
 * Define platform-specific assert
 */
#define DEF_PLATFORM_ASSERT(WHAT) NT_ASSERT((WHAT))

// Kill output functions for rtl
#define wprintf

// Platform allocators
#define _DefPlatformAlloc(SZ) RtlAllocateHeap(RtlProcessHeap(), 0, (SZ))
#define _DefPlatformAllocZeroed(SZ) RtlAllocateHeap(RtlProcessHeap(), HEAP_ZERO_MEMORY, (SZ))
#define _DefPlatformFree(PTR) RtlFreeHeap(RtlProcessHeap(), 0, (PTR))

// Memory manipulation
#define _DefZeroMemory RtlSecureZeroMemory

// Intsafe functions
#define _DefSizeTToInt RtlSizeTToInt
#define _DefSizeTMult RtlSizeTMult

// Strsafe functions
#define _DEF_STRSAFE_MAX_CCH NTSTRSAFE_UNICODE_STRING_MAX_CCH
#define _DefStringCchLength RtlStringCchLengthW
#define _DefStringCchCopy RtlStringCchCopyW
#define _DefStringCchCat RtlStringCchCatW
#define _DefStringCchCatEx RtlStringCchCatExW
#define _DefStringCchPrintf RtlStringCchPrintfW

// Use RTL SRWLOCK

#define _DEF_SRWLOCK RTL_SRWLOCK

#define _DefInitializeSRWLock RtlInitializeSRWLock
#define _DefAcquireSRWLockExclusive RtlAcquireSRWLockExclusive
#define _DefAcquireSRWLockShared RtlAcquireSRWLockShared
#define _DefReleaseSRWLockExclusive RtlReleaseSRWLockExclusive
#define _DefReleaseSRWLockShared RtlReleaseSRWLockShared

//no message notification at rtl level
#define _DefSendNotifyMessage(A, B, C, D)
#define _DefRegisterWindowMessage(A) 0

// No ETW at RTL level yet

#define WRITE_MRMMIN_INIT_TRACE_INFO(msg, hr)
#define WRITE_MRMMIN_INIT_TRACE_INFO_CHECK(msg, hr)
#define WRITE_MRMMIN_INIT_TRACE_ERROR(msg, hr)
#define WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(msg, hr)
#define WRITE_MRMMIN_INIT_TRACE_ERROR_MEASURE(msg, hr)
#define WRITE_MRMMIN_INIT_TRACE_ERROR_MEASURE_CHECK(msg, hr)

#define WRITE_MRMMIN_TRACE_INFO(msg, msg2, hr)
#define WRITE_MRMMIN_TRACE_WARNING(msg, msg2, hr)
#define WRITE_MRMMIN_TRACE_WARNING_CHECK(msg, msg2, hr)
#define WRITE_MRMMIN_TRACE_ERROR(msg, msg2, hr)
#define WRITE_MRMMIN_TRACE_ERROR_CHECK(msg, msg2, hr)
#define WRITE_MRMMIN_TRACE_ERROR_MEASURE(msg, msg2, hr)
#define WRITE_MRMMIN_TRACE_ERROR_MEASURE_CHECK(msg, msg2, hr)

#define WRITE_MRMMIN_PRI_MERGE_INFO(mergeState, mergeInfo, result)
#define WRITE_MRMMIN_PRI_MERGE_ERROR(mergeState, mergeInfo, result)

#define WRITE_MRMMIN_UNABLE_TO_OPEN_OVERLAY_FILE(overlayFileName, result)

#define WRITE_ETW(etw)
