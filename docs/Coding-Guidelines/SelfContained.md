# Self-Contained

## What is 'Self-Contained'?

Windows App SDK can be deployed via MSIX or self-contained, aka WinAppSDK/MSIX and WinAppSDK/SelfContained.

See the [Self-Contained spec](https://github.com/microsoft/WindowsAppSDK/pull/1202) for more details.

## How to detect if Windows App SDK is deployed Self-Contained?

If necessary, use `WindowsAppRuntime::SelfContained::IsSelfContained()` to detect if the
current process is using WindowsAppSDK deployed via SelfContained (vs MSIX).

**NOTE:** The implementation assumes Windows App SDK is in use. Failure to detect
WindowsAppSDK/MSIX is thus assumed to be WindowsAppSDK/SelfContained.

```c++
#include <WindowsAppRuntime.SelfContained.h>

void JustDoIt()
{
    if (::WindowsAppRuntime::SelfContained::IsSelfContained())
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
MSIX packages) need to call `::WindowsAppRuntime::VersionInfo::TestInitialize()` with a nonexistent
alternative (test) framework package family name **BEFORE** calling `IsSelfContained()` to simulate
running in a self-contained deployment.

```c++
#include "pch.h"

#include <WindowsAppRuntime.SelfContained.h>
#include <WindowsAppRuntime.VersionInfo.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::MyFeature
{
    class MyFeatureTests
    {
    public:
        BEGIN_TEST_CLASS(SelfContainedTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::SetupPackages();
            ::TB::SetupBootstrap();
            const auto c_testFrameworkPackageFamilyName{ L"Test.Framework.PackageFamilyName_1234567890abc" };
            ::WindowsAppRuntime::VersionInfo::TestInitialize(c_testFrameworkPackageFamilyName);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::WindowsAppRuntime::VersionInfo::TestShutdown();
            ::TB::CleanupBootstrap();
            ::TB::CleanupPackages();
            return true;
        }

        TEST_METHOD(TestThis)
        {
            ...insert your test code here...
        }
...
```

Alternatively, replace

```
::WindowsAppRuntime::VersionInfo::TestInitialize(c_testFrameworkPackageFamilyName);
```

with
```
::WindowsAppRuntime::VersionInfo::TestInitialize(::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);
```

to simulate running in a non-self-contained environment (i.e. Windows App SDK via MSIX packages).

See `test\common\Test_SelfContained.cpp` for more examples using `IsSelfContained()`.
