// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef PCH_H
#define PCH_H

#include <unknwn.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <sddl.h>
#include <appmodel.h>

#include <vector>
#include <string>
#include <algorithm>
#include <wil/resource.h>
#include <wil/stl.h>
#include <wil/result.h>
#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wrl.h>
#include <WexTestClass.h>

#include <sstream>
#include <iomanip>

#include <wil/result_macros.h>
#include <wil/com.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.Networking.PushNotifications.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>
#include <WindowsAppRuntime.Test.Package.h>
#include <WindowsAppRuntime.Test.TAEF.h>
#include <WindowsAppRuntime.Test.Bootstrap.h>
#include <WindowsAppRuntime.VersionInfo.h>
#include <windows.applicationmodel.h>
#include <windows.applicationmodel.background.h>
#include <ShObjIdl_core.h>

#define VERIFY_THROWS_HR(expression, hr)        \
            VERIFY_THROWS_SPECIFIC(expression,          \
                winrt::hresult_error,                   \
                [&](winrt::hresult_error e) -> bool     \
                {                                       \
                    return (e.code() == hr);    \
                })

namespace TP = ::Test::Packages;
namespace TAEF = ::Test::TAEF;
#endif //PCH_H
