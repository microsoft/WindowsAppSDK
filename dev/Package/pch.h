// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Windows.h>

#include <unknwn.h>
#include <appmodel.h>

#include <filesystem>
#include <thread>
#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/filesystem.h>
#include <wil/registry.h>
#include <wil/stl.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/token_helpers.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>

#include <FrameworkUdk/Containment.h>

#include <appmodel.identity.h>
#include <appmodel.package.h>
#include <microsoft.foundation.string.h>

// 62800606: [2.x Servicing][WASDK] Add new 'GetPackage[Graph]File` APIs
#define WINAPPSDK_CHANGEID_62800606 62800606
