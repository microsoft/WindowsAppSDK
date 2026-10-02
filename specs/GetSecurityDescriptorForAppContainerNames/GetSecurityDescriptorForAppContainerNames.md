# Easing and streamlining named object sharing between packaged and Win32

This feature is a flat C API that takes a list of Package Family Names (PFNs) and access masks, and returns a security descriptor

# Background

Named objects (mutexes, events, waitable timers) must be ACLed during creation in order to be shared with packaged applications.

Currently, [our guidance](https://docs.microsoft.com/windows/uwp/communication/sharing-named-objects) for this scenario is to write a large amount of complex, cumbersome, and largely boilerplate code. ([See here for a taste](https://docs.microsoft.com/windows/win32/api/securityappcontainer/nf-securityappcontainer-getappcontainernamedobjectpath#examples)).

If we are to meet developers where they are, we need to reduce the friction of Win32 and UWP interop, and make it as easy as possible to share named objects.

# Description

Add a flat C API that takes an array of PFNs and access masks, and produces the needed `SECURITY_ATTRIBUTES` object.

# Examples
## Flat C
```c++
#include <wil/resource.h>

wil::unique_event CreateShareableEvent(PCWSTR name)
{
    wil::unique_hlocal_security_descriptor sd;
    AppContainerNameAndAccess access[1] =
      {{L"Contoso.Test.App_12345678",
        EVENT_MODIFY_STATE | SYNCHRONIZE}};

    THROW_IF_FAILED(GetSecurityDescriptorForAppContainerNames(
        1, access, nullptr, EVENT_MODIFY_STATE | SYNCHRONIZE, &sd, nullptr));

    SECURITY_ATTRIBUTES sa{};
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = sd.get();
    sa.bInheritHandle = FALSE;

    wil::unique_event result;
    result.create(wil::EventOptions::None, name, &sa);
    // aka, ::CreateEvent(&sa, FALSE, FALSE, name);
    return result;
}
```
## WinRT (C#)
```c#
EventWaitHandle CreateShareableEvent(String name)
{
    var access = new AppContainerNameAndAccess[]
    {
        new AppContainerNameAndAccess("Contoso.Test.App_12345678",
          (uint)(EventWaitHandleRights.Modify |
                 EventWaitHandleRights.Synchronize));
    };

    string sddl = SecurityDescriptorHelpers.GetSddlForAppContainerNames(
        access, "",
        (uint)(EventWaitHandleRights.Modify |
                 EventWaitHandleRights.Synchronize));

    var security = new EventWaitHandleSecurity();
    security.SetSecurityDescriptorSddlForm(sddl);

    Boolean created;
    return new EventWaitHandle(false,
      EventResetMode.AutoReset, name, out created, security);
}
```

# API Details
## Flat C
```c
struct AppContainerNameAndAccess
{
    PCWSTR appContainerName;
    UINT32 accessMask;
};

STDAPI GetSecurityDescriptorForAppContainerNames(
    UINT32 accessRequestCount,
    _In_reads_(accessRequestCount)
        const AppContainerNameAndAccess* accessRequests,
    _In_opt_ PSID principal,
    UINT32 principalAccessMask,
    _Outptr_ PSECURITY_DESCRIPTOR* securityDescriptor,
    _Out_opt_ UINT32* securityDescriptorSize
)
```

If the **principal** parameter is null, the principal of the current thread is used.

If the function succeds, the `SECURITY_DESCRIPTOR` returned in `securityDescriptor` must be freed by calling [LocalFree](https://docs.microsoft.com/windows/desktop/api/winbase/nf-winbase-localfree).

## WinRT
```c#
namespace Microsoft.Security.AccessControl
{
  runtimeclass AppContainerNameAndAccess
  {
    AppContainerNameAndAccess()
    AppContainerNameAndAccess(
      String appContainerNameArg,
      UInt32 accessMaskArg)

    String appContainerName;
    UInt32 accessMask;
  }

  static runtimeclass SecurityDescriptorHelpers
  {
    static String GetSddlForAppContainerNames(
      AppContainerNameAndAccess[] accessRequests,
      String principalStringSid,
      UInt32 principalAccessMask
    )

    static UInt8[] GetSecurityDescriptorBytesFromAppContainerNames(
      AppContainerNameAndAccess[] accessRequests,
      String principalStringSid,
      UInt32 principalAccessMask
    )
  }
}
```

The **principalStringSid** parameter is the [security identifier](https://docs.microsoft.com/windows/win32/secgloss/s-gly) (SID), in [string format](https://docs.microsoft.com/windows/win32/secauthz/sid-components), of the principal (See also: [ConvertSidToStringSid](https://docs.microsoft.com/windows/win32/api/sddl/nf-sddl-convertsidtostringsidw)). If this parameter is empty, the principal of the current thread is used.

# API Notes

Some alternative designs were considered.
- Single method, takes a list of permissions corresponding to the list of PFNs. (Current choice)
  - Pros
    - Handles both complicated case and simple case in a single call.
    - API is straightforward, no extra/optional/multimode parameters.
    - Only a single method to search/remember/code.
  - Cons
    - Simple case is not "optimally" simple - requires filling array with a single value.
- Single method, takes both a single permission as well as an optional array of permissions. The single permission is ignored if the array is non-null.
  - Pros
    - Handles both complicated case and simple case in a single call.
    - Only a single method to search/remember/code.
    - Provides a way to assign a single permission to all PFNs without filling an array.
  - Cons
    - Slightly more complicated API. Two parameters are conditionally used for the same purpose.
- Two methods, one that takes a list of permissions, and one that takes a single permission.
  - Pros
    - Each API is straightforward, no extra/optional/multimode parameters.
    - Dedicated APIs for assigning a single permission vs different permissions.
  - Cons
    - How to meaningfully name these two methods without unintentionally confusing or obfuscating?
    - Increased mental model tax - now have to search/remember/read two different, but similar APIs.
