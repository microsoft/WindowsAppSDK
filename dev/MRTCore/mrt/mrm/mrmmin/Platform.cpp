// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "mrm/common/Base.h"

// Platform specific implementations of common utility functions.

#ifdef DEF_RTL

#include <ntcsrmsg.h>
#include <base.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef FlagOn
#define FlagOn(_F, _SF) ((_F) & (_SF))
#endif

#ifndef FlagOff
#define FlagOff(_F, _SF) (!((_F) & (_SF)))
#endif

#ifndef BooleanFlagOn
#define BooleanFlagOn(F, SF) ((BOOLEAN)(((F) & (SF)) != 0))
#endif

#ifndef SetFlag
#define SetFlag(_F, _SF) ((_F) |= (_SF))
#endif

#ifndef ClearFlag
#define ClearFlag(_F, _SF) ((_F) &= ~(_SF))
#endif

    const UNICODE_STRING BaseConsoleInput = RTL_CONSTANT_STRING(L"CONIN$");
    const UNICODE_STRING BaseConsoleOutput = RTL_CONSTANT_STRING(L"CONOUT$");
    const UNICODE_STRING BaseConsoleGeneric = RTL_CONSTANT_STRING(L"CON");

    ULONG
    _DefVirtualQuery(__in_opt PVOID Address, __out PMEMORY_BASIC_INFORMATION Buffer, __in ULONG Length)
    {
        NTSTATUS Status;
        SIZE_T ReturnLength;

        Status = NtQueryVirtualMemory(
            NtCurrentProcess(), (LPVOID)Address, MemoryBasicInformation, (PMEMORY_BASIC_INFORMATION)Buffer, Length, &ReturnLength);
        if (NT_SUCCESS(Status))
        {
            return (ULONG)(ReturnLength);
        }
        else
        {
            return 0;
        }
    }

    ULONG
    _DefExpandEnvironmentStrings(_In_reads_(Size) PCWSTR Source, _Out_writes_opt_(Size) PWSTR Destination, __in ULONG Size)
    {
        NTSTATUS Status;
        SIZE_T Length;

        Length = 0;
        Status = RtlExpandEnvironmentStrings(nullptr, Source, Source ? wcslen(Source) : 0, Destination, Size, &Length);
        if (NT_SUCCESS(Status) || Status == STATUS_BUFFER_TOO_SMALL)
        {

            if (Length <= MAXULONG)
            {
                return (ULONG)Length;
            }

            Status = STATUS_UNSUCCESSFUL;
        }

        return 0;
    }

    void _DefCloseHandle(__in HANDLE handle) { NtClose(handle); }

    PCUNICODE_STRING
    _DefBaseIsThisAConsoleName(PCUNICODE_STRING FileNameString, DWORD dwDesiredAccess)
    {
        PCUNICODE_STRING FoundConsoleName;
        ULONG DeviceNameLength;
        ULONG DeviceNameOffset;
        UNICODE_STRING ConString;
        WCHAR sch, ech;

        FoundConsoleName = nullptr;
        if (FileNameString->Length)
        {
            sch = FileNameString->Buffer[0];
            ech = FileNameString->Buffer[(FileNameString->Length - 1) >> 1];

            //
            // if CON, CONOUT$, CONIN$, \\.\CON...
            //

            if (sch == (WCHAR)'c' || sch == (WCHAR)'C' || sch == (WCHAR)'\\' || ech == (WCHAR)'n' || ech == (WCHAR)'N' ||
                ech == (WCHAR)':' || ech == (WCHAR)'$')
            {

                ConString = *FileNameString;

                DeviceNameLength = RtlIsDosDeviceName_U(ConString.Buffer);
                if (DeviceNameLength)
                {

                    DeviceNameOffset = DeviceNameLength >> 16;
                    DeviceNameLength &= 0x0000ffff;

                    ConString.Buffer = (PWSTR)((PSZ)ConString.Buffer + DeviceNameOffset);
                    ConString.Length = (USHORT)DeviceNameLength;
                    ConString.MaximumLength = (USHORT)(DeviceNameLength + sizeof(UNICODE_NULL));
                }

                FoundConsoleName = nullptr;
                __try
                {

                    if (RtlEqualUnicodeString(&ConString, &BaseConsoleInput, TRUE))
                    {
                        FoundConsoleName = &BaseConsoleInput;
                    }
                    else if (RtlEqualUnicodeString(&ConString, &BaseConsoleOutput, TRUE))
                    {
                        FoundConsoleName = &BaseConsoleOutput;
                    }
                    else if (RtlEqualUnicodeString(&ConString, &BaseConsoleGeneric, TRUE))
                    {

                        if ((dwDesiredAccess & (GENERIC_READ | GENERIC_WRITE)) == GENERIC_READ)
                        {
                            FoundConsoleName = &BaseConsoleInput;
                        }
                        else if ((dwDesiredAccess & (GENERIC_READ | GENERIC_WRITE)) == GENERIC_WRITE)
                        {
                            FoundConsoleName = &BaseConsoleOutput;
                        }
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }
        }
        return FoundConsoleName;
    }

    HRESULT
    _DefCreateFile(
        __in LPCWSTR FileName,
        __in ULONG DesiredAccess,
        __in ULONG ShareMode,
        __in PSECURITY_ATTRIBUTES pSecurityAttributes,
        __in ULONG CreationFlags,
        __in ULONG FileAttributes,
        __out PHANDLE pHandle)
    {
        NTSTATUS Status;
        OBJECT_ATTRIBUTES Obja;
        HANDLE Handle = INVALID_HANDLE_VALUE;
        UNICODE_STRING FileNameStr;
        IO_STATUS_BLOCK IoStatusBlock;
        BOOLEAN TranslationStatus;
        RTL_RELATIVE_NAME_U RelativeName;
        PVOID FreeBuffer;
        ULONG CreateDisposition;
        ULONG CreateFlags;
        FILE_ALLOCATION_INFORMATION AllocationInfo;
        PCUNICODE_STRING lpConsoleName;
        BOOL EndsInSlash;
        DWORD SQOSFlags;
        SECURITY_QUALITY_OF_SERVICE SecurityQualityOfService;
        PVOID SecurityDescriptor = nullptr;

        switch (CreationFlags)
        {
        case CREATE_NEW:
            CreateDisposition = FILE_CREATE;
            break;
        case CREATE_ALWAYS:
            CreateDisposition = FILE_OVERWRITE_IF;
            break;
        case OPEN_EXISTING:
            CreateDisposition = FILE_OPEN;
            break;
        case OPEN_ALWAYS:
            CreateDisposition = FILE_OPEN_IF;
            break;
        case TRUNCATE_EXISTING:
            CreateDisposition = FILE_OPEN;
            if (DesiredAccess & GENERIC_WRITE)
            {
                return E_INVALIDARG;
            }
            break;
        default:
            return E_INVALIDARG;
        }

        //
        // temporary routing code
        //

        Status = RtlInitUnicodeStringEx(&FileNameStr, FileName);
        if (!NT_SUCCESS(Status))
        {
            return E_ABORT;
        }

        if (FileNameStr.Length > 1 && FileName[(FileNameStr.Length >> 1) - 1] == (WCHAR)'\\')
        {
            EndsInSlash = TRUE;
        }
        else
        {
            EndsInSlash = FALSE;
        }

        lpConsoleName = _DefBaseIsThisAConsoleName(&FileNameStr, DesiredAccess);
        if (!lpConsoleName)
        {
            return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
        }

        CreateFlags = 0;

        TranslationStatus = RtlDosPathNameToRelativeNtPathName_U(FileName, &FileNameStr, nullptr, &RelativeName);
        if (!TranslationStatus)
        {
            return HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND);
        }

        FreeBuffer = FileNameStr.Buffer;

        if (RelativeName.RelativeName.Length)
        {
            FileNameStr = RelativeName.RelativeName;
        }
        else
        {
            RelativeName.ContainingDirectory = nullptr;
        }

        InitializeObjectAttributes(
            &Obja,
            &FileNameStr,
            FileAttributes & FILE_FLAG_POSIX_SEMANTICS ? 0 : OBJ_CASE_INSENSITIVE,
            RelativeName.ContainingDirectory,
            nullptr);

        SQOSFlags = FlagOn(FileAttributes, SECURITY_VALID_SQOS_FLAGS);

        if (FlagOn(SQOSFlags, SECURITY_SQOS_PRESENT))
        {

            ClearFlag(SQOSFlags, SECURITY_SQOS_PRESENT);

            if (FlagOn(SQOSFlags, SECURITY_CONTEXT_TRACKING))
            {

                SecurityQualityOfService.ContextTrackingMode = (SECURITY_CONTEXT_TRACKING_MODE)TRUE;
                ClearFlag(SQOSFlags, SECURITY_CONTEXT_TRACKING);
            }
            else
            {
                SecurityQualityOfService.ContextTrackingMode = (SECURITY_CONTEXT_TRACKING_MODE)FALSE;
            }

            if (FlagOn(SQOSFlags, SECURITY_EFFECTIVE_ONLY))
            {

                SecurityQualityOfService.EffectiveOnly = TRUE;
                ClearFlag(SQOSFlags, SECURITY_EFFECTIVE_ONLY);
            }
            else
            {

                SecurityQualityOfService.EffectiveOnly = FALSE;
            }

            SecurityQualityOfService.ImpersonationLevel = (SECURITY_IMPERSONATION_LEVEL)(SQOSFlags >> 16);
        }
        else
        {

            SecurityQualityOfService.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
            SecurityQualityOfService.ImpersonationLevel = SecurityImpersonation;
            SecurityQualityOfService.EffectiveOnly = TRUE;
        }

        SecurityQualityOfService.Length = sizeof(SECURITY_QUALITY_OF_SERVICE);
        Obja.SecurityQualityOfService = &SecurityQualityOfService;

        if (ARGUMENT_PRESENT(pSecurityAttributes))
        {
            Obja.SecurityDescriptor = pSecurityAttributes->lpSecurityDescriptor;
            if (pSecurityAttributes->bInheritHandle)
            {
                SetFlag(Obja.Attributes, OBJ_INHERIT);
            }
        }

        //
        //  Translate from win32 flags to nt flags
        //

        if (FlagOn(FileAttributes, FILE_FLAG_NO_BUFFERING))
        {
            SetFlag(CreateFlags, FILE_NO_INTERMEDIATE_BUFFERING);
        }
        if (FlagOn(FileAttributes, FILE_FLAG_WRITE_THROUGH))
        {
            SetFlag(CreateFlags, FILE_WRITE_THROUGH);
        }
        if (!FlagOn(FileAttributes, FILE_FLAG_OVERLAPPED))
        {
            SetFlag(CreateFlags, FILE_SYNCHRONOUS_IO_NONALERT);
        }
        if (FlagOn(FileAttributes, FILE_FLAG_SEQUENTIAL_SCAN))
        {
            SetFlag(CreateFlags, FILE_SEQUENTIAL_ONLY);
        }
        if (FlagOn(FileAttributes, FILE_FLAG_RANDOM_ACCESS))
        {
            SetFlag(CreateFlags, FILE_RANDOM_ACCESS);
        }
        if (FlagOn(FileAttributes, FILE_FLAG_BACKUP_SEMANTICS))
        {
            SetFlag(CreateFlags, FILE_OPEN_FOR_BACKUP_INTENT);
        }
        if (FlagOn(FileAttributes, FILE_FLAG_DELETE_ON_CLOSE))
        {
            SetFlag(CreateFlags, FILE_DELETE_ON_CLOSE);
            SetFlag(DesiredAccess, DELETE);
        }
        if (FlagOn(FileAttributes, FILE_FLAG_OPEN_REPARSE_POINT))
        {
            SetFlag(CreateFlags, FILE_OPEN_REPARSE_POINT);
        }
        if (FlagOn(FileAttributes, FILE_FLAG_OPEN_NO_RECALL))
        {
            SetFlag(CreateFlags, FILE_OPEN_NO_RECALL);
        }

        //
        // Backup semantics allow directories to be opened
        //

        if (!FlagOn(FileAttributes, FILE_FLAG_BACKUP_SEMANTICS))
        {
            SetFlag(CreateFlags, FILE_NON_DIRECTORY_FILE);
        }
        else
        {

            //
            // Backup intent was specified... Now look to see if we are to allow
            // directory creation
            //

            if ((FlagOn(FileAttributes, FILE_ATTRIBUTE_DIRECTORY | FILE_FLAG_POSIX_SEMANTICS) ==
                 (FILE_ATTRIBUTE_DIRECTORY | FILE_FLAG_POSIX_SEMANTICS)) &&
                (CreateDisposition == FILE_CREATE))
            {

                SetFlag(CreateFlags, FILE_DIRECTORY_FILE);
            }
        }

        Status = NtCreateFile(
            &Handle,
            DesiredAccess | SYNCHRONIZE | FILE_READ_ATTRIBUTES,
            &Obja,
            &IoStatusBlock,
            nullptr,
            FileAttributes & (FILE_ATTRIBUTE_VALID_FLAGS & ~FILE_ATTRIBUTE_DIRECTORY),
            ShareMode,
            CreateDisposition,
            CreateFlags,
            nullptr,
            0);

        RtlFreeHeap(RtlProcessHeap(), 0, SecurityDescriptor);
        RtlReleaseRelativeName(&RelativeName);
        RtlFreeHeap(RtlProcessHeap(), 0, FreeBuffer);

        if (!NT_SUCCESS(Status))
        {
            // TODO - set global status here?
            return HRESULT_FROM_NT(Status);
        }

        //
        // if NT returns supersede/overwritten, it means that a create_always, openalways
        // found an existing copy of the file. In this case ERROR_ALREADY_EXISTS is returned
        //

        if ((CreationFlags == CREATE_ALWAYS && IoStatusBlock.Information == FILE_OVERWRITTEN) ||
            (CreationFlags == OPEN_ALWAYS && IoStatusBlock.Information == FILE_OPENED))
        {
            // TODO - set last error
        }
        else
        {
            // TODO - clear any error
        }

        //
        // Truncate the file if required
        //

        if (CreationFlags == TRUNCATE_EXISTING)
        {

            AllocationInfo.AllocationSize.QuadPart = 0;
            Status = NtSetInformationFile(Handle, &IoStatusBlock, &AllocationInfo, sizeof(AllocationInfo), FileAllocationInformation);

            if (!NT_SUCCESS(Status))
            {
                return HRESULT_FROM_NT(Status);
            }
        }

        *pHandle = Handle;
        return S_OK;
    }

    //
    // Helper function taken from base\win32\client\baseinit.c - used in BaseFormatObjectAttributes()
    // removed code that cached the opened directory object handle.  Added code taken from initialization
    // routine for a global variable BaseStaticServerData and made that into a local variable
    //
    NTSTATUS
    _DefBaseGetNamedObjectDirectory(PHANDLE pHandle)
    {
        OBJECT_ATTRIBUTES Obja;
        NTSTATUS Status, Status1;
        const static UNICODE_STRING RestrictedObjectDirectory = RTL_CONSTANT_STRING(L"Restricted");
        ACCESS_MASK DirAccess = DIRECTORY_QUERY | DIRECTORY_TRAVERSE | DIRECTORY_CREATE_OBJECT | DIRECTORY_CREATE_SUBDIRECTORY;
        HANDLE hRootNamedObject;
        HANDLE BaseHandle;
        HANDLE Token, NewToken;
        UNICODE_STRING TempStr;
        PBASE_STATIC_SERVER_DATA BaseStaticServerData;

        BaseStaticServerData = (PBASE_STATIC_SERVER_DATA)BASE_SHARED_SERVER_DATA;

        BASE_SERVER_STR_TO_LOCAL_STR(&TempStr, &BaseStaticServerData->NamedObjectDirectory);

        if (NtCurrentTeb()->IsImpersonating)
        {
            //
            // If we're impersonating, save the impersonation token, and
            // revert to self for the duration of the directory creation.
            //
            Status = NtOpenThreadToken(NtCurrentThread(), TOKEN_IMPERSONATE, TRUE, &Token);
            if (!NT_SUCCESS(Status))
            {
                return Status;
            }

            NewToken = nullptr;
            Status = NtSetInformationThread(NtCurrentThread(), ThreadImpersonationToken, (PVOID)&NewToken, (ULONG)sizeof(NewToken));
            if (!NT_SUCCESS(Status))
            {
                Status1 = NtClose(Token);
                //ASSERT (NT_SUCCESS (Status1));
                return Status;
            }
        }
        else
        {
            Token = nullptr;
        }

        InitializeObjectAttributes(&Obja, &TempStr, OBJ_CASE_INSENSITIVE, nullptr, nullptr);

        Status = NtOpenDirectoryObject(&BaseHandle, DirAccess, &Obja);

        // if the intial open failed, try again with just traverse, and
        // open the restricted subdirectory

        if (!NT_SUCCESS(Status))
        {
            Status = NtOpenDirectoryObject(&hRootNamedObject, DIRECTORY_TRAVERSE, &Obja);
            if (NT_SUCCESS(Status))
            {

                InitializeObjectAttributes(
                    &Obja, (PUNICODE_STRING)&RestrictedObjectDirectory, OBJ_CASE_INSENSITIVE, hRootNamedObject, nullptr);
                Status = NtOpenDirectoryObject(&BaseHandle, DirAccess, &Obja);
                Status1 = NtClose(hRootNamedObject);
            }
        }

        if (Token)
        {
            Status1 = NtSetInformationThread(NtCurrentThread(), ThreadImpersonationToken, &Token, sizeof(Token));

            Status1 = NtClose(Token);
        }

        *pHandle = BaseHandle;
        return Status;
    }

    NTSTATUS
    _DefBaseFormatObjectAttributes(
        OUT POBJECT_ATTRIBUTES ObjectAttributes,
        IN PSECURITY_ATTRIBUTES SecurityAttributes,
        IN PUNICODE_STRING ObjectName,
        OUT POBJECT_ATTRIBUTES* pObjectAttributes)
    {
        HANDLE RootDirectory;
        ULONG Attributes;
        PVOID SecurityDescriptor;
        NTSTATUS Status;

        if (ARGUMENT_PRESENT(SecurityAttributes) || ARGUMENT_PRESENT(ObjectName))
        {

            if (SecurityAttributes)
            {
                Attributes = (SecurityAttributes->bInheritHandle ? OBJ_INHERIT : 0);
                SecurityDescriptor = SecurityAttributes->lpSecurityDescriptor;
            }
            else
            {
                Attributes = 0;
                SecurityDescriptor = nullptr;
            }

            if (ARGUMENT_PRESENT(ObjectName))
            {
                Status = _DefBaseGetNamedObjectDirectory(&RootDirectory);

                if (!NT_SUCCESS(Status))
                {
                    return Status;
                }

                Attributes |= OBJ_OPENIF;
            }
            else
            {
                RootDirectory = nullptr;
            }

            InitializeObjectAttributes(ObjectAttributes, ObjectName, Attributes, RootDirectory, SecurityDescriptor);
            *pObjectAttributes = ObjectAttributes;
        }
        else
        {
            *pObjectAttributes = nullptr;
        }

        return STATUS_SUCCESS;
    }

    HRESULT
    _DefCreateFileMapping(
        __in HANDLE FileHandle,
        __in_opt LPSECURITY_ATTRIBUTES pSecurityAttributes,
        __in ULONG ProtectFlag,
        __in ULONG MaximumSizeHigh,
        __in ULONG MaximumSizeLow,
        __in_opt LPCWSTR pName,
        __out PHANDLE pMappingHandle)
    {
        HANDLE Section;
        NTSTATUS Status;
        LARGE_INTEGER SectionSizeData;
        PLARGE_INTEGER SectionSize;
        OBJECT_ATTRIBUTES Obja;
        POBJECT_ATTRIBUTES pObja;
        ACCESS_MASK DesiredAccess;
        UNICODE_STRING ObjectName;
        ULONG AllocationAttributes;

        DesiredAccess = STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ;
        AllocationAttributes = ProtectFlag & (SEC_FILE | SEC_IMAGE | SEC_RESERVE | SEC_COMMIT | SEC_NOCACHE | SEC_LARGE_PAGES);
        ProtectFlag ^= AllocationAttributes;
        if (AllocationAttributes == 0)
        {
            AllocationAttributes = SEC_COMMIT;
        }

        if (ProtectFlag == PAGE_READWRITE)
        {
            DesiredAccess |= (SECTION_MAP_READ | SECTION_MAP_WRITE);
        }
        else if (ProtectFlag == PAGE_EXECUTE_READWRITE)
        {
            DesiredAccess |= (SECTION_MAP_WRITE | SECTION_MAP_EXECUTE);
        }
        else if (ProtectFlag == PAGE_EXECUTE_READ)
        {
            DesiredAccess |= (SECTION_MAP_EXECUTE);
        }
        else if (ProtectFlag != PAGE_READONLY && ProtectFlag != PAGE_WRITECOPY)
        {
            // Invalid parameter
            return E_INVALIDARG;
        }

        if (ARGUMENT_PRESENT(pName))
        {
            RtlInitUnicodeString(&ObjectName, pName);
            Status = _DefBaseFormatObjectAttributes(&Obja, pSecurityAttributes, &ObjectName, &pObja);
        }
        else
        {
            Status = _DefBaseFormatObjectAttributes(&Obja, pSecurityAttributes, nullptr, &pObja);
        }

        if (!NT_SUCCESS(Status))
        {
            return HRESULT_FROM_NT(Status);
        }

        if (MaximumSizeLow || MaximumSizeHigh)
        {
            SectionSize = &SectionSizeData;
            SectionSize->LowPart = MaximumSizeLow;
            SectionSize->HighPart = MaximumSizeHigh;
        }
        else
        {
            SectionSize = nullptr;
        }

        if (FileHandle == INVALID_HANDLE_VALUE)
        {
            FileHandle = nullptr;
            if (!SectionSize)
            {
                return E_INVALIDARG;
            }
        }

        Status = NtCreateSection(&Section, DesiredAccess, pObja, SectionSize, ProtectFlag, AllocationAttributes, FileHandle);

        if (!NT_SUCCESS(Status) && Status != STATUS_OBJECT_NAME_EXISTS)
        {
            return HRESULT_FROM_NT(Status);
        }

        *pMappingHandle = Section;

        return S_OK;
    }

    HANDLE
    _DefGetCurrentProcess() { return NtCurrentProcess(); }

    HRESULT
    _DefGetFileSizeEx(__in HANDLE hFile, __out PLARGE_INTEGER pFileSize)
    {
        NTSTATUS Status;
        IO_STATUS_BLOCK IoStatusBlock;
        FILE_STANDARD_INFORMATION StandardInfo;

        Status = NtQueryInformationFile(hFile, &IoStatusBlock, &StandardInfo, sizeof(StandardInfo), FileStandardInformation);

        if (!NT_SUCCESS(Status))
        {
            return HRESULT_FROM_NT(Status);
        }

        *pFileSize = StandardInfo.EndOfFile;

        return S_OK;
    }

    DEFRESULT
    _DefGetLastError()
    {
        // TODO - need translation from NTSTATUS error codes to ART equivalents.
        return 0;
    }

    HRESULT
    _DefMapViewOfFile(
        __in HANDLE FileMapping,
        __in ULONG DesiredAccess,
        __in ULONG FileOffsetHigh,
        __in ULONG FileOffsetLow,
        __in size_t NumberOfBytesToMap,
        __out PPVOID pBaseAddress)
    {
        NTSTATUS Status;
        LARGE_INTEGER SectionOffset;
        SIZE_T ViewSize;
        PVOID ViewBase = nullptr;
        ULONG Protect;

        SectionOffset.LowPart = FileOffsetLow;
        SectionOffset.HighPart = FileOffsetHigh;
        ViewSize = NumberOfBytesToMap;

        if (DesiredAccess == FILE_MAP_COPY)
        {
            Protect = PAGE_WRITECOPY;
        }
        else if (DesiredAccess & FILE_MAP_WRITE)
        {

            if (DesiredAccess & FILE_MAP_EXECUTE)
            {
                Protect = PAGE_EXECUTE_READWRITE;
            }
            else
            {
                Protect = PAGE_READWRITE;
            }
        }
        else if (DesiredAccess & FILE_MAP_READ)
        {

            if (DesiredAccess & FILE_MAP_EXECUTE)
            {
                Protect = PAGE_EXECUTE_READ;
            }
            else
            {
                Protect = PAGE_READONLY;
            }
        }
        else
        {
            Protect = PAGE_NOACCESS;
        }

        Status = NtMapViewOfSection(FileMapping, NtCurrentProcess(), &ViewBase, 0L, 0L, &SectionOffset, &ViewSize, ViewShare, 0, Protect);
        if (!NT_SUCCESS(Status))
        {
            return HRESULT_FROM_NT(Status);
        }

        *pBaseAddress = ViewBase;
        return S_OK;
    }

    HRESULT
    _DefOpenFileMapping(__in ULONG DesiredAccess, __in BOOLEAN InheritHandle, __in LPCWSTR pName, __out PHANDLE pFileMappingHandle)
    {
        OBJECT_ATTRIBUTES Obja;
        UNICODE_STRING ObjectName;
        NTSTATUS Status;
        HANDLE Object, DirHandle;

        if (!pName)
        {
            return E_INVALIDARG;
        }

        if (!pFileMappingHandle)
        {
            return E_INVALIDARG;
        }

        RtlInitUnicodeString(&ObjectName, pName);

        Status = _DefBaseGetNamedObjectDirectory(&DirHandle);
        if (!NT_SUCCESS(Status))
        {
            return HRESULT_FROM_NT(Status);
        }

        InitializeObjectAttributes(&Obja, &ObjectName, (InheritHandle ? OBJ_INHERIT : 0), DirHandle, nullptr);

        if (DesiredAccess == FILE_MAP_COPY)
        {
            DesiredAccess = FILE_MAP_READ;
        }
        else if (DesiredAccess & FILE_MAP_EXECUTE)
        {
            DesiredAccess = (DesiredAccess | SECTION_MAP_EXECUTE) & ~FILE_MAP_EXECUTE;
        }

        Status = NtOpenSection(&Object, DesiredAccess, &Obja);

        if (!NT_SUCCESS(Status))
        {
            return HRESULT_FROM_NT(Status);
        }

        *pFileMappingHandle = Object;
        return S_OK;
    }

    HRESULT
    _DefReadFile(__in HANDLE Handle, __out PVOID pBuffer, __in ULONG BytesToRead, __out_opt ULONG* BytesRead)
    {
        NTSTATUS Status;
        IO_STATUS_BLOCK IoStatusBlock;
        PPEB Peb;

        if (pBuffer == nullptr)
        {
            return E_INVALIDARG;
        }

        if (ARGUMENT_PRESENT(BytesRead))
        {
            *BytesRead = 0;
        }

        Peb = NtCurrentPeb();

        //
        // kenhsu - support for stdio/console handle and overlapped operations removed
        //
        Status = NtReadFile(Handle, nullptr, nullptr, nullptr, &IoStatusBlock, pBuffer, BytesToRead, nullptr, nullptr);

        if (Status == STATUS_PENDING)
        {
            // Operation must complete before return & IoStatusBlock destroyed
            Status = NtWaitForSingleObject(Handle, FALSE, nullptr);
            if (NT_SUCCESS(Status))
            {
                Status = IoStatusBlock.Status;
            }
        }

        if (NT_SUCCESS(Status))
        {
            if (nullptr != BytesRead)
            {
                *BytesRead = (DWORD)IoStatusBlock.Information;
            }
            return S_OK;
        }
        else if (Status == STATUS_END_OF_FILE)
        {
            if (nullptr != BytesRead)
            {
                *BytesRead = 0;
            }
            return S_OK;
        }
        else
        {
            if (NT_WARNING(Status))
            {
                if (nullptr != BytesRead)
                {
                    *BytesRead = (DWORD)IoStatusBlock.Information;
                }
            }
            // TODO - set last status
            return HRESULT_FROM_NT(Status);
        }
    }

    BOOLEAN
    _DefUnmapViewOfFile(__in PVOID pBaseAddress)
    {
        NTSTATUS Status;

        Status = NtUnmapViewOfSection(NtCurrentProcess(), (PVOID)pBaseAddress);

        if (!NT_SUCCESS(Status))
        {
            if (Status == STATUS_INVALID_PAGE_PROTECTION)
            {

                //
                // Unlock any pages that were locked with MmSecureVirtualMemory.
                // This is useful for SANs.
                //

                if (RtlFlushSecureMemoryCache((PVOID)pBaseAddress, 0))
                {
                    Status = NtUnmapViewOfSection(NtCurrentProcess(), (PVOID)pBaseAddress);

                    if (NT_SUCCESS(Status))
                    {
                        return (TRUE);
                    }
                }
            }
            return FALSE;
        }

        return TRUE;
    }

    UINT _DefGetDriveTypeW(_In_opt_ PCWSTR rootPathName)
    {
        UNREFERENCED_PARAMETER(rootPathName);

        // Need to copy the implementation of GetDriveTypeW.
        DEF_ASSERT(FALSE);

        return DOSDEVICE_DRIVE_FIXED;
    }

    BOOLEAN _DefIsWellFormedTag(_In_ PCWSTR tag)
    {
        if (tag == nullptr || *tag == L'\0')
        {
            return FALSE;
        }

        BOOLEAN ok = TRUE;
        PCWSTR test = tag;

        while (ok && (*test != L'\0'))
        {
            // we accept letters, numbers, dash and semi-colon (as list separator)
            if (((*test >= L'0') && (*test <= L'9')) || ((*test >= L'a') && (*test <= L'z')) || ((*test >= L'A') && (*test <= L'Z')) ||
                (*test == L'-') || (*test == L';'))
            {
                test++;
            }
            else
            {
                ok = FALSE;
            }
        }

        return ok && ((test - tag) >= 2);
    }

    HRESULT _DefGetDistanceOfClosestLanguageInList(
        _In_ PCWSTR /* language */,
        _In_ PCWSTR /* languagesList */,
        _In_ wchar_t /* listDelimiter */,
        _Out_ double* closestDistance)
    {
        // Not implemented. Let caller handle
        *closestDistance = -1.0;

        return S_OK;
    }

#ifdef __cplusplus
}
#endif

#else // !DEF_RTL

#ifdef __cplusplus
extern "C"
{
#endif

    void _DefCloseHandle(__in HANDLE handle) { CloseHandle(handle); }

    HRESULT
    _DefCreateFile(
        __in PCWSTR FileName,
        __in ULONG DesiredAccess,
        __in ULONG ShareMode,
        __in_opt PSECURITY_ATTRIBUTES pSecurityAttributes,
        __in ULONG CreationFlags,
        __in ULONG FileAttributes,
        __out PHANDLE pHandle)
    {
        if (pHandle == nullptr)
        {
            return E_INVALIDARG;
        }

        *pHandle = CreateFileW(FileName, DesiredAccess, ShareMode, pSecurityAttributes, CreationFlags, FileAttributes, nullptr);

        if (*pHandle == INVALID_HANDLE_VALUE)
        {
            HRESULT hr = HRESULT_FROM_WIN32(GetLastError());
            WRITE_MRMMIN_INIT_TRACE_ERROR_MEASURE_CHECK((FileName != nullptr) ? FileName : L"", hr);
            return hr;
        }

        return S_OK;
    }

    HRESULT
    _DefCreateFileMapping(
        __in HANDLE FileHandle,
        __in_opt PSECURITY_ATTRIBUTES pSecurityAttributes,
        __in ULONG ProtectFlag,
        __in ULONG MaximumSizeHigh,
        __in ULONG MaximumSizeLow,
        __in_opt PCWSTR pName,
        __out PHANDLE pMappingHandle)
    {
        if (pMappingHandle == nullptr)
        {
            return E_INVALIDARG;
        }

        *pMappingHandle = CreateFileMapping(FileHandle, pSecurityAttributes, ProtectFlag, MaximumSizeHigh, MaximumSizeLow, pName);
        if (*pMappingHandle == nullptr)
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        return S_OK;
    }

    HANDLE
    _DefGetCurrentProcess() { return GetCurrentProcess(); }

    HRESULT
    _DefGetFileSizeEx(__in HANDLE hFile, __out PLARGE_INTEGER pFileSize)
    {
        if (pFileSize == nullptr)
        {
            return E_INVALIDARG;
        }

        if (!GetFileSizeEx(hFile, pFileSize))
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        return S_OK;
    }

    DEFRESULT
    _DefGetLastError()
    {
        // TODO - need translation from Win32 error codes to ART equivalents.
        return (DEFRESULT)GetLastError();
    }

    HRESULT
    _DefMapViewOfFile(
        __in HANDLE FileMapping,
        __in ULONG DesiredAccess,
        __in ULONG FileOffsetHigh,
        __in ULONG FileOffsetLow,
        __in size_t NumberOfBytesToMap,
        __out PVOID* pBaseAddress)
    {
        if (pBaseAddress == nullptr)
        {
            return E_INVALIDARG;
        }

        *pBaseAddress = MapViewOfFile(FileMapping, DesiredAccess, FileOffsetHigh, FileOffsetLow, NumberOfBytesToMap);

        if (*pBaseAddress == nullptr)
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        return S_OK;
    }

    HRESULT
    _DefOpenFileMapping(__in ULONG DesiredAccess, __in BOOLEAN InheritHandle, __in PCWSTR pName, __out PHANDLE pFileMappingHandle)
    {
        if (pFileMappingHandle == nullptr)
        {
            return E_INVALIDARG;
        }

        *pFileMappingHandle = OpenFileMapping(DesiredAccess, InheritHandle, pName);

        if (*pFileMappingHandle == nullptr)
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        return S_OK;
    }

    HRESULT
    _DefReadFile(__in HANDLE Handle, __out_bcount(BytesToRead) PVOID pBuffer, __in ULONG BytesToRead, __out_opt ULONG* BytesRead)
    {
        if (pBuffer == nullptr)
        {
            return E_INVALIDARG;
        }

        if (!(ReadFile(Handle, pBuffer, BytesToRead, BytesRead,
                       nullptr))) // no support for overlapped at present
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        return S_OK;
    }

    BOOLEAN
    _DefUnmapViewOfFile(__in PVOID pBaseAddress) { return (BOOLEAN)UnmapViewOfFile(pBaseAddress); }

    ULONG
    _DefVirtualQuery(__in_opt PVOID Address, __out_bcount(Length) PMEMORY_BASIC_INFORMATION Buffer, __in ULONG Length)
    {
        return (ULONG)VirtualQuery(Address, Buffer, Length);
    }

    ULONG
    _DefExpandEnvironmentStrings(__in PCWSTR Source, __out_ecount_opt(Size) PWSTR Destination, __in ULONG Size)
    {
        ULONG rtrn = ExpandEnvironmentStrings(Source, Destination, Size);
        if ((rtrn == 0) && (Destination != nullptr) && (Size > 0))
        {
            *Destination = L'\0';
        }
        return rtrn;
    }

    /*
     * CRC-32 implementation (from RTL)
     */

    //
    // This is the precomputed data table for the CRC32 algorithm as specified
    // in IS0 3309. See RFC-1662 and RFC-1952 for implementation details and
    // references.
    //
    // To calculate this table, use the following function:
    //
    //  VOID
    //  PrintCrcTable(
    //      )
    //  {
    //    ULONG32 Val;
    //    ULONG i, k;
    //
    //      for (i = 0; i < 256; i++) {
    //         Val = (ULONG) i;
    //          for (k = 0; k < 8; k++) {
    //              if (Val & 1) {
    //                  Val = 0xedb88320L ^ (Val >> 1);
    //              } else {
    //                  Val = Val >> 1;
    //              }
    //          }
    //
    //          printf ("0x%08x, ", Val);
    //
    //          if ( (i+1) % 6 == 0) {
    //              printf ("\n");
    //          }
    //      }
    //  }
    //
    //

    const UINT32 gCrc32Table[] = {
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e,
        0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb,
        0xf4d4b551, 0x83d385c7, 0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5, 0x3b6e20c8,
        0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
        0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599,
        0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
        0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb,
        0x086d3d2d, 0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
        0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074,
        0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5,
        0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f, 0x5edef90e,
        0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27,
        0x7d079eb1, 0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0,
        0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1,
        0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
        0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92,
        0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
        0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4,
        0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777, 0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
        0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d,
        0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9, 0xbdbdf21c, 0xcabac28a,
        0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37,
        0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d};

    /*
 * Compute the CRC32 as specified in in IS0 3309. See RFC-1662 and RFC-1952
 * for implementation details and references.
 * Pre- and post-conditioning (one's complement) is done by this function, so
 * it should not be done by the caller. That is, do:
 *
 *     Crc = _DefComputeCrc32 ( 0, buffer, length );
 * instead of
 *
 *     Crc = _DefComputeCrc32 ( 0xffffffff, buffer, length );
 * or
 *     Crc = _DefComputeCrc32 ( 0xffffffff, buffer, length) ^ 0xffffffff;
 *
 * Arguments:
 * 
 *    PartialCrc - A partially calculated CRC32.
 *
 *    Buffer - The buffer you want to CRC.
 *
 *    Length - The length of the buffer in bytes.
 *
 * Return Value:
 *    The updated CRC32 value.
 *
 */

    UINT32
    _DefComputeCrc32(__in UINT32 partialCrc, __in_bcount(cbBuf) const BYTE* pBuf, __in UINT32 cbBuf)
    {
        UINT32 crc;
        UINT32 i;

        //
        // Compute the CRC32 checksum.
        //

        crc = partialCrc ^ 0xffffffffL;

        for (i = 0; i < cbBuf; i++)
        {
            crc = gCrc32Table[(crc ^ pBuf[i]) & 0xff] ^ (crc >> 8);
        }

        return (crc ^ 0xffffffffL);
    }

    UINT32
    _DefComputeStringCrc32(__in UINT32 partialCrc, __in BOOLEAN isCaseInsensitive, __in_ecount(cchStr) PCWSTR pStr, __in UINT32 cchStr)
    {
        UINT32 crc;
        UINT32 i;

        crc = partialCrc ^ 0xffffffffL;

        for (i = 0; i < cchStr; i++)
        {
            WCHAR ch = (isCaseInsensitive ? towlower(pStr[i]) : pStr[i]);
            crc = gCrc32Table[(crc ^ (ch & 0xff)) & 0xff] ^ (crc >> 8);
            crc = gCrc32Table[(crc ^ ((ch >> 8) & 0xff)) & 0xff] ^ (crc >> 8);
        }

        return (crc ^ 0xffffffffL);
    }

    UINT _DefGetDriveTypeW(_In_opt_ PCWSTR rootPathName) { return GetDriveTypeW(rootPathName); }

#include <stdbool.h>
    // We will just leak this. The module is shared as both functions will always be together.
    HMODULE g_bcp47 = (HMODULE)(-1);
    typedef bool(WINAPI* IsWellFormedTagFunc)(PCWSTR);
    typedef HRESULT(WINAPI* GetDistanceOfClosestLanguageInListFunc)(PCWSTR, PCWSTR, wchar_t, double*);

    HMODULE LoadBcp47ModuleFrom(_In_ PCWSTR moduleName)
    {
        HMODULE module = LoadLibraryExW(moduleName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (module != nullptr)
        {
            // All BCP47 APIs we are interested are always exported from the same dll together. So we just pick anyone for probe.
            IsWellFormedTagFunc func = (IsWellFormedTagFunc)(GetProcAddress(module, "IsWellFormedTag"));
            if (func != nullptr)
            {
                return module;
            }
            FreeLibrary(module);
        }

        return nullptr;
    }

    HMODULE LoadBcp47Module()
    {
        HMODULE module = LoadBcp47ModuleFrom(L"bcp47mrm.dll");
        if (module == nullptr)
        {
            // In downlevel OS, the API is exposed by bcp47langs.dll.
            module = LoadBcp47ModuleFrom(L"bcp47langs.dll");
        }

        return module;
    }

    void InitializeBcp47Module()
    {
        HMODULE comparand = (HMODULE)(-1);
        if (InterlockedCompareExchangePointer(reinterpret_cast<PVOID*>(&g_bcp47), comparand, comparand) == comparand)
        {
            HMODULE module = LoadBcp47Module();
            InterlockedExchangePointer(reinterpret_cast<PVOID*>(&g_bcp47), module);
        }
    }

    BOOLEAN _DefIsWellFormedTag(_In_ PCWSTR tag)
    {
        // Before new SDK is released, we need to use LoadLibrary/GetProcAddress
        InitializeBcp47Module();

        if (g_bcp47 == nullptr)
        {
            // Didn't find an implementation. Just return TRUE.
            return TRUE;
        }

        IsWellFormedTagFunc func = (IsWellFormedTagFunc)(GetProcAddress(g_bcp47, "IsWellFormedTag"));
        if (func != nullptr)
        {
            return func(tag);
        }

        // Should not reach here.
        return TRUE;
    }

    HRESULT _DefGetDistanceOfClosestLanguageInList(
        _In_ PCWSTR language,
        _In_ PCWSTR languagesList,
        _In_ wchar_t listDelimiter,
        _Out_ double* closestDistance)
    {
        // Before new SDK is released, we need to use LoadLibrary/GetProcAddress
        InitializeBcp47Module();

        if (g_bcp47 == nullptr)
        {
            // Didn't find an implementation. Just return -1.0 as distance, and caller would handle.
            *closestDistance = -1.0;
            return S_OK;
        }

        GetDistanceOfClosestLanguageInListFunc func =
            (GetDistanceOfClosestLanguageInListFunc)(GetProcAddress(g_bcp47, "GetDistanceOfClosestLanguageInList"));
        if (func != nullptr)
        {
            return func(language, languagesList, listDelimiter, closestDistance);
        }

        // Should not reach here.
        *closestDistance = -1.0;
        return S_OK;
    }

#ifdef __cplusplus
}
#endif

#endif // !DEF_RTL
