// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef PCH_H
#define PCH_H

#include <unknwn.h>

#include <wil/cppwinrt.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include "winrt/Microsoft.Windows.Storage.Pickers.h"

#include <WexTestClass.h>

#include <WindowsAppRuntime.Test.AppModel.h>
#include <WindowsAppRuntime.Test.Package.h>
#include <WindowsAppRuntime.Test.Bootstrap.h>

#include <winrt/Windows.Storage.Streams.h>

#define VERIFY_THROWS_HR(expression, hr)        \
            VERIFY_THROWS_SPECIFIC(expression,          \
                winrt::hresult_error,                   \
                [&](winrt::hresult_error e) -> bool     \
                {                                       \
                    return (e.code() == hr);    \
                })

#endif //PCH_H
