// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <windows.h>
#include <wil/result.h>
#include <wil/cppwinrt.h>
#include <wil/resource.h>
#include <wil/token_helpers.h>
#include <wil/win32_helpers.h>
#include <wil/result_macros.h>

#include <string>
#include <sstream>
#include <filesystem>

#include <WexTestClass.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.System.h>

#endif //PCH_H
