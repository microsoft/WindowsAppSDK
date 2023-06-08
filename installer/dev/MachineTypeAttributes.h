// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "pch.h"

namespace MachineTypeAttributes
{
    // On systems running Windows 11, this inline function returns if given architecture is supported on the system in user mode.
    // On systems running down level Windows versions (ex: Windows 10), this inline function will return false, always.
    // NOTE: If in case, the GetMachineTypeAttributes API that is currently only available on Windows 11 get serviced to down level Windows versions as well,
    // then on systems running down level Windows versions (ex: Windows 10), this inline function will function the same as on Windows 11.
    inline bool IsWindows11_IsArchitectureSupportedInUserMode(USHORT architecture)
    {
        // GetMachineTypeAttributes() added to kernelbase.dll in NTDDI_WIN10_CO (aka Windows 11 21H2, the first market release version of Windows 11).
        // So, if that API is available, it indicates current system is running Windows 11.
        wil::unique_hmodule kernelbaseDll{ LoadLibraryExW(L"kernelbase.dll", nullptr, 0) };
        if (!kernelbaseDll)
        {
            const DWORD rcLoadLibraryError = GetLastError();
            THROW_HR_IF(HRESULT_FROM_WIN32(rcLoadLibraryError), rcLoadLibraryError != ERROR_MOD_NOT_FOUND);
            return false;
        }

        auto getMachineTypeAttributes{ GetProcAddressByFunctionDeclaration(kernelbaseDll.get(), GetMachineTypeAttributes) };
        if (!getMachineTypeAttributes)
        {
            const DWORD rcGetProcAddressError = GetLastError();
            THROW_HR_IF(HRESULT_FROM_WIN32(rcGetProcAddressError), rcGetProcAddressError != ERROR_PROC_NOT_FOUND);
            // If execution comes here, it means the current system is not running Windows 11.
            return false;
        }

        // If execution comes here, it means that the current system is running Windows 11
        // For defense against such possible future changes, also check explicitly if given architecture is supported on the current system.
        MACHINE_ATTRIBUTES machineAttributes{};
        THROW_IF_FAILED(getMachineTypeAttributes(architecture, &machineAttributes));
        return WI_IsFlagSet(machineAttributes, MACHINE_ATTRIBUTES::UserEnabled);
    }
}
