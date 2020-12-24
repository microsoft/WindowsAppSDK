// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <unknwn.h>

#include <appmodel.h>

#include <ShObjIdl_core.h>
#include <thread>
#include <mutex>
#include <list>
#include <stdexcept>

#include <filesystem>

#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/filesystem.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <NotificationActivationCallback.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>

#include <MsixDynamicDependency.h>
