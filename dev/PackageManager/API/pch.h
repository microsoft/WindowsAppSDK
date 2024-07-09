// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Windows.h>

#include <unknwn.h>
#include <appmodel.h>
#include <sddl.h>

#include <filesystem>
#include <thread>
#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/winrt.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Management.Core.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.System.h>

#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>

#include <appmodel.identity.h>
#include <appmodel.package.h>
#include <security.user.h>

#include "MsixPackageManager.h"

#include <FrameworkUdk/PackageManagement.h>
#include <FrameworkUdk/UupStateRepository.h>
