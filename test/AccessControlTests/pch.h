// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <unknwn.h>
#include <Windows.h>
#include <sddl.h>

#include <wil/result.h>
#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/resource.h>
#include <WexTestClass.h>

#include <string>

#include <wil/result_macros.h>
#include <wil/com.h>

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <WindowsAppRuntime.Test.Package.h>
#include <WindowsAppRuntime.Test.TAEF.h>
#include <WindowsAppRuntime.Test.Bootstrap.h>
#include <ShObjIdl_core.h>

#endif //PCH_H
