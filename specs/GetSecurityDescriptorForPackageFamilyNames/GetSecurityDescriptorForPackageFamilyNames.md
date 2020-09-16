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
    wil::unique_hlocal_ptr pSD;
    PCWSTR packageNames[1] = { L"Contoso.Test.App_12345678" };
    DWORD accessMasks[1] = { ACCESS_MODIFY_STATE };

    THROW_IF_FAILED(GetSecurityDescriptorForPackageFamilyNames(
        1, packageNames, accessMasks, &pSD);

    wil::unique_event result;
    result.create(wil::EventOptions::None, name, pSD.get());
    return result;
}
```

# API Details

```c
STDAPI GetSecurityDescriptorForPackageFamilyNames(
    DWORD                 cCountOfPackageFamilyNames,
    _In_Reads_(cCountOfPackageFamilyNames)
      const PCWSTR*         pListOfPackageFamilyNames,
    _In_Reads_(cCountOfPackageFamilyNames)
      const DWORD*          accessMask,
    _Outptr_ SECURITY_DESCRIPTOR** ppSD
)
```
If the function succeds, the returned `SECURITY_DESCRIPTOR` must be freed by calling [LocalFree](https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-localfree).
