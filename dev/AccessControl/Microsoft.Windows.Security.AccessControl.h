// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers.g.h"

namespace winrt::Microsoft::Windows::Security::AccessControl::implementation
{
    struct SecurityDescriptorHelpers
    {
        SecurityDescriptorHelpers() = default;

        static hstring GetSddlForAppContainerNames(
            array_view<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess const> accessRequests,
            hstring const& principalStringSid, uint32_t principalAccessMask);

        static com_array<uint8_t> GetSecurityDescriptorBytesFromAppContainerNames(
            array_view<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess const> accessRequests,
            hstring const& principalStringSid, uint32_t principalAccessMask);
    };
}
namespace winrt::Microsoft::Windows::Security::AccessControl::factory_implementation
{
    struct SecurityDescriptorHelpers : SecurityDescriptorHelpersT<SecurityDescriptorHelpers, implementation::SecurityDescriptorHelpers>
    {
    };
}
