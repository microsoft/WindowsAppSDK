#include <pch.h>
#include <wil/resource.h>
#include <wil/result.h>
#include <accctrl.h>
#include <aclapi.h>
#include <userenv.h>
#include "Security.AccessControl.h"
#include "SecurityDescriptorHelpers.h"
#include <vector>

using namespace std;

STDAPI GetSecurityDescriptorForAppContainerNames(
    uint32_t accessRequestCount,
    _In_reads_(accessRequestCount)
    const AppContainerNameAndAccess* accessRequests,
    _In_opt_ PSID principal,
    uint32_t principalAccessMask,
    _Outptr_ PSECURITY_DESCRIPTOR* securityDescriptor
)
{
    *securityDescriptor = nullptr;
    try
    {
        vector<EXPLICIT_ACCESS> ea;
        if (accessRequestCount == UINT32_MAX)
        {
            THROW_HR(E_OUTOFMEMORY);
        }
        ea.reserve(static_cast<size_t>(accessRequestCount) + 1);

        wil::unique_any_psid currentProcessSid;
        if (!principal)
        {
            currentProcessSid = Security::Descriptors::GetCurrentProcessSid();
            principal = currentProcessSid.get();
        }

        {
            EXPLICIT_ACCESS entry{};
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
            EXPLICIT_ACCESS entry{};
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

        auto result = wil::make_unique_hlocal<SECURITY_DESCRIPTOR>();
        THROW_IF_WIN32_BOOL_FALSE(::InitializeSecurityDescriptor(result.get(), SECURITY_DESCRIPTOR_REVISION));
        THROW_IF_WIN32_BOOL_FALSE(::SetSecurityDescriptorDacl(result.get(), TRUE, acl.get(), FALSE));

        *securityDescriptor = result.release();
        return S_OK;
    }
    CATCH_RETURN();
}
