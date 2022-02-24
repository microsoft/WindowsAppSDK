# Self-Contained

## What is 'Self-Contained'?

Windows App SDK can be deployed via MSIX or self-contained, aka WinAppSDK/MSIX and WinAppSDK/SelfContained.

See the [Self-Contained spec](https://github.com/microsoft/WindowsAppSDK/pull/1202) for more details.

## How to detect if Windows App SDK is deployed Self-Contained?

If necessary, use `Microsoft::WindowsAppSDK::SelfContained::IsSelfContained()` to detect if the
current process is using WindowsAppSDK deployed via SelfContained (vs MSIX).

**NOTE:** The implementation assumes Windows App SDK is in use. Failure to detect
WindowsAppSDK/MSIX is thus assumed to be WindowsAppSDK/SelfContained.

```c++
#include <Microsoft.WindowsAppSDK.SelfContained.h>

void JustDoIt()
{
    if (::Microsoft::WindowsAppSDK::SelfContained::IsSelfContained())
    {
        printf("WindowsAppSDK/SelfContained");
    }
    else
    {
        printf("WindowsAppSDK/MSIX");
    }
}
```

### Unit and Functional Testing

Unit and Functional Tests using alternative test packages (not Integration Tests using the real
MSIX packages) need to define the alternative framework package's family name **BEFORE**
`#include`'ing the SelfContained header. This will alter the detection algorithm to look for the
alternative (test) package rather than the product (real) package.

```c++
#define WINDOWSAPPSDK_SELFCONTAINED_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W L"Microsoft.WindowsAppRuntime.Framework_8wekyb3d8bbwe"
#include <Microsoft.WindowsAppSDK.SelfContained.h>
...
```

See `test\common\Test_SelfContained.cpp` for examples using `IsSelfContained()`.
