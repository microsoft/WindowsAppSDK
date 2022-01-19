#include <pch.h>
#include "Microsoft.Windows.Security.AccessControl.h"
#include "Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers.g.cpp"

namespace winrt::Microsoft::Windows::Security::AccessControl::implementation
{
    hstring SecurityDescriptorHelpers::GetSddlForAppContainerNames(array_view<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess const> accessRequests, hstring const& principalStringSid, uint32_t principalAccessMask)
    {
        throw hresult_not_implemented();
    }
    com_array<uint8_t> SecurityDescriptorHelpers::GetSecurityDescriptorBytesFromAppContainerNames(array_view<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess const> accessRequests, hstring const& principalStringSid, uint32_t principalAccessMask)
    {
        throw hresult_not_implemented();
    }
}
