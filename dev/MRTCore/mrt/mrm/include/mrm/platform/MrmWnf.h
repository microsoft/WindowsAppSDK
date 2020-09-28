// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

__declspec(selectany) extern const int MrmWnf_DefaultMaxPayloadSizeInChars = 256;

__declspec(selectany) extern const int MrmWnf_MergeSystemPriFiles_PayloadSizeInChars = 64;
__declspec(selectany) extern PCWSTR const MrmWnf_MergeSystemPriFiles_StartFormat = L"start %I64u";
__declspec(selectany) extern PCWSTR const MrmWnf_MergeSystemPriFiles_DoneFormat = L"done %I64u %I64u";

__declspec(selectany) extern const int MrmWnf_SystemPriMerge_PayloadSizeInChars = 256;
__declspec(selectany) extern PCWSTR const MrmWnf_SystemPriMerge_StartFormat = L"start %I64u %s";
__declspec(selectany) extern PCWSTR const MrmWnf_SystemPriMerge_ExistsFormat = L"exists %d %I64u %I64u %s";
__declspec(selectany) extern PCWSTR const MrmWnf_SystemPriMerge_DoneFormat = L"done %d %I64u %I64u %s";

__declspec(selectany) extern const int MrmWnf_PersistentQualifierChangedEvent_PayloadSizeInChars = 256;
__declspec(selectany) extern PCWSTR const MrmWnf_PersistentQualifierChangedEvent_PayloadFormat = L"%s@%s";