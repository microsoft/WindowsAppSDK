// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Windows.h>

#include <unknwn.h>
#include <appmodel.h>
#include <MsixDynamicDependency.h>

#include <filesystem>
#include <thread>
#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
//TODO REMOVE #include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Management.Core.h>
#include <winrt/Windows.Management.Deployment.h>
//TODO REMOVE #include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>

#include <appmodel.identity.h>
#include <appmodel.package.h>
