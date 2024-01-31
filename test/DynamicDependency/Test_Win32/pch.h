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

#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/win32_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/filesystem.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.AppExtensions.h>
#include <winrt/Windows.Management.Core.h>
#include <winrt/Windows.Management.Deployment.h>

#include <filesystem>

#include <MsixDynamicDependency.h>

#include <MddBootstrap.h>
#include <MddBootstrapTest.h>

#include <appmodel_msixdynamicdependency.h>

#include <WexTestClass.h>

#include <appmodel.identity.h>
#include <appmodel.packagegraph.h>
#include <IsWindowsVersion.h>
#include <security.integritylevel.h>

#include "TestFilesystem.h"
#include "TestPackages.h"
#include <WindowsAppRuntime.Test.TAEF.h>

#include <winrt/Microsoft.Test.DynamicDependency.Widgets.h>

#endif //PCH_H
