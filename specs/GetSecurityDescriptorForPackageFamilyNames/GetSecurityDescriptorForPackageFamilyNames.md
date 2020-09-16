# Easing and streamlining named object sharing between packaged and Win32

This feature is a flat C API that takes a list of Package Family Names (PFNs) and access masks, and returns a security descriptor

# Background

Named objects (mutexes, events, waitable timers) must be ACLed during creation in order to be shared with packaged applications.

Currently, [our guidance](https://docs.microsoft.com/en-us/windows/uwp/communication/sharing-named-objects) for this scenario is to write a large amount of complex, cumbersome, and largely boilerplate code. ([See here for a taste](https://docs.microsoft.com/en-us/windows/win32/api/securityappcontainer/nf-securityappcontainer-getappcontainernamedobjectpath#examples)).

If we are to meet developers where they are, we need to reduce the friction of Win32 and UWP interop, and make it as easy as possible to share named objects.

# Description

Add a flat C API that takes an array of PFNs and access masks, and produces the needed `SECURITY_ATTRIBUTES` object.

# Examples

```c++
#include <wil/resource.h>

wil::unique_event CreateShareableEvent(PCWSTR name)
{
    wil::unique_hlocal_ptr sd;
    PCWSTR packageNames[1] = { L"Contoso.Test.App_12345678" };
    DWORD accessMasks[1] = { ACCESS_MODIFY_STATE };

    THROW_IF_FAILED(GetSecurityDescriptorForPackageFamilyNames(
        1, packageNames, accessMasks, &sd);

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = sd.get();
    sa.bInheritHandle = FALSE;

    wil::unique_event result;
    result.create(wil::EventOptions::None, name, &sa);
    return result;
}
```

# API Details

```c
STDAPI GetSecurityDescriptorForPackageFamilyNames(
    uint32_t                countOfPackageFamilyNames,
    _In_Reads_(countOfPackageFamilyNames)
      const PCWSTR*         listOfPackageFamilyNames,
    _In_Reads_(countOfPackageFamilyNames)
      const DWORD*          accessMask,
    _Outptr_ SECURITY_DESCRIPTOR** securityDescriptor
)
```
If the function succeds, the returned `SECURITY_DESCRIPTOR` must be freed by calling [LocalFree](https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-localfree).

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