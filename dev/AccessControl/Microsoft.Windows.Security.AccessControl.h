// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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
