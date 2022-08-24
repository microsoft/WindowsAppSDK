// Copyright (c) Microsoft Corporation. All rights reserved.
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
            THROW_LAST_ERROR();
        }
        else
        {
            auto getMachineTypeAttributes{ GetProcAddressByFunctionDeclaration(kernelbaseDll.get(), GetMachineTypeAttributes) };
            if (!getMachineTypeAttributes)
            {
                DWORD getProcAddressError = GetLastError();
                if (getProcAddressError != ERROR_PROC_NOT_FOUND)
                {
                    THROW_HR(HRESULT_FROM_WIN32(getProcAddressError));
                }
                // If execution comes here, it means the current system is not running Windows 11.
                return false;
            }
            else
            {
                // If execution entered this block, it means that the current system is running Windows 11
                // For defense against such possible future changes, also check explicitly if given architecture is supported on the current system.
                MACHINE_ATTRIBUTES machineAttributes{};
                THROW_IF_FAILED(getMachineTypeAttributes(architecture, &machineAttributes));
                return WI_IsFlagSet(machineAttributes, MACHINE_ATTRIBUTES::UserEnabled);
            }
        }
    }
}
