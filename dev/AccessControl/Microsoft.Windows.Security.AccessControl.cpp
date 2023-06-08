// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include "Microsoft.Windows.Security.AccessControl.h"
#include "Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers.g.cpp"
#include "Security.AccessControl.h"
#include <sddl.h>

namespace winrt::Microsoft::Windows::Security::AccessControl::implementation
{
    wil::unique_hlocal_security_descriptor GetSecurityDescriptor(
        array_view<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess const> accessRequests,
        hstring const& principalStringSid, uint32_t principalAccessMask, uint32_t* sdLength)
    {
        wil::unique_any_psid sid;
        if (!principalStringSid.empty())
        {
            winrt::check_hresult(::ConvertStringSidToSidW(principalStringSid.data(), &sid));
        }

        std::vector<::AppContainerNameAndAccess> rawAccessRequests;
        rawAccessRequests.reserve(accessRequests.size());
        for (auto&& request : accessRequests)
        {
            rawAccessRequests.push_back({ request.appContainerName.data(), request.accessMask });
        }
        wil::unique_hlocal_security_descriptor sd;

        winrt::check_hresult(
            GetSecurityDescriptorForAppContainerNames(
                static_cast<uint32_t>(rawAccessRequests.size()), rawAccessRequests.data(), sid.get(), principalAccessMask, &sd, sdLength));
        return sd;
    }

    hstring SecurityDescriptorHelpers::GetSddlForAppContainerNames(
        array_view<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess const> accessRequests,
        hstring const& principalStringSid, uint32_t principalAccessMask)
    {
        auto sd = GetSecurityDescriptor(accessRequests, principalStringSid, principalAccessMask, nullptr);

        wil::unique_hlocal_string resultStr;
        DWORD resultLen = 0;
        winrt::check_bool(
            ::ConvertSecurityDescriptorToStringSecurityDescriptorW(
                sd.get(), SDDL_REVISION_1,
                OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION,
                &resultStr, &resultLen));
        return { resultStr.get(), resultLen };
    }

    com_array<uint8_t> SecurityDescriptorHelpers::GetSecurityDescriptorBytesFromAppContainerNames(
        array_view<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess const> accessRequests,
        hstring const& principalStringSid, uint32_t principalAccessMask)
    {
        uint32_t sdLength = 0;
        auto sd = GetSecurityDescriptor(accessRequests, principalStringSid, principalAccessMask, &sdLength);
        auto begin = static_cast<uint8_t*>(sd.get());
        return { begin, begin + sdLength };
    }
}
