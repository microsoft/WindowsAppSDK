// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <accctrl.h>
#include <aclapi.h>
#include <userenv.h>
#include <vector>
#include "Security.AccessControl.h"
#include "SecurityDescriptorHelpers.h"

using namespace std;

STDAPI GetSecurityDescriptorForAppContainerNames(
    UINT32 accessRequestCount,
    _In_reads_(accessRequestCount) const AppContainerNameAndAccess* accessRequests,
    _In_opt_ PSID principal,
    UINT32 principalAccessMask,
    _Outptr_ PSECURITY_DESCRIPTOR* securityDescriptor,
    _Out_opt_ UINT32* securityDescriptorLength
) try
{
    *securityDescriptor = nullptr;
    if (securityDescriptorLength)
    {
        *securityDescriptorLength = 0;
    }

    THROW_HR_IF(E_INVALIDARG, accessRequestCount == UINT32_MAX);

    wil::unique_any_psid currentProcessSid;
    if (!principal)
    {
        currentProcessSid = Security::Descriptors::GetCurrentProcessSid();
        principal = currentProcessSid.get();
    }

    vector<EXPLICIT_ACCESS_W> ea;
    ea.reserve(accessRequestCount + 1);
    {
        EXPLICIT_ACCESS_W entry{};
        entry.grfAccessMode = GRANT_ACCESS;
        entry.grfAccessPermissions = principalAccessMask;
        entry.grfInheritance = NO_INHERITANCE;
        entry.Trustee.TrusteeForm = TRUSTEE_IS_SID;
        entry.Trustee.TrusteeType = TRUSTEE_IS_USER;
        entry.Trustee.ptstrName = static_cast<PWSTR>(principal);
        ea.push_back(entry);
    }

    vector<wil::unique_sid> appSids;
    appSids.reserve(accessRequestCount);
    for (auto const end = accessRequests + accessRequestCount; accessRequests < end; ++accessRequests)
    {
        EXPLICIT_ACCESS_W entry{};
        wil::unique_sid sid;
        THROW_IF_FAILED(::DeriveAppContainerSidFromAppContainerName(accessRequests->appContainerName, &sid));
        entry.grfAccessMode = GRANT_ACCESS;
        entry.grfAccessPermissions = accessRequests->accessMask;
        entry.grfInheritance = NO_INHERITANCE;
        entry.Trustee.TrusteeForm = TRUSTEE_IS_SID;
        entry.Trustee.TrusteeType = TRUSTEE_IS_USER;
        entry.Trustee.ptstrName = static_cast<PWSTR>(sid.get());
        appSids.push_back(std::move(sid));
        ea.push_back(entry);
    }

    wil::unique_any<PACL, decltype(&::LocalFree), ::LocalFree> acl;
    THROW_IF_WIN32_ERROR(::SetEntriesInAclW(static_cast<uint32_t>(ea.size()), ea.data(), nullptr, &acl));

    auto absoluteSD = wil::make_unique_hlocal<SECURITY_DESCRIPTOR>();
    THROW_IF_WIN32_BOOL_FALSE(::InitializeSecurityDescriptor(absoluteSD.get(), SECURITY_DESCRIPTOR_REVISION));
    THROW_IF_WIN32_BOOL_FALSE(::SetSecurityDescriptorDacl(absoluteSD.get(), TRUE, acl.get(), FALSE));

    DWORD sdLength = 0;

    if (!::MakeSelfRelativeSD(absoluteSD.get(), nullptr, &sdLength))
    {
        auto err = ::GetLastError();
        if (err != ERROR_INSUFFICIENT_BUFFER)
        {
            THROW_WIN32(err);
        }
    }
    wil::unique_hlocal_security_descriptor selfRelativeSD{ ::LocalAlloc(LMEM_FIXED, sdLength) };
    THROW_IF_WIN32_BOOL_FALSE(::MakeSelfRelativeSD(absoluteSD.get(), selfRelativeSD.get(), &sdLength));

    *securityDescriptor = selfRelativeSD.release();
    if (securityDescriptorLength)
    {
        *securityDescriptorLength = sdLength;
    }
    return S_OK;
}
CATCH_RETURN()
