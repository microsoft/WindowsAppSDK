// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef PCH_H
#define PCH_H

#include <unknwn.h>

#include <ShObjIdl.h>

#include <wil/com.h>
#include <wil/cppwinrt.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Management.Deployment.h>

#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>
#include <winrt/Microsoft.Windows.Management.Deployment.h>

#include <WexTestClass.h>

#include <AppModel.Package.h>

#include <WindowsAppRuntime.Test.Diagnostics.h>
#include <WindowsAppRuntime.Test.AppModel.h>
#include <WindowsAppRuntime.Test.Package.h>
#include <WindowsAppRuntime.Test.Bootstrap.h>

#include "PackageManagerTests.Packages.h"

#include <windows.foundation.h>
#include <windows.foundation.collections.h>
#include <windows.management.deployment.h>
#if defined(NTDDI_WIN11_GE)
#   define TODO_UpdatedWindowsSDK_with_Windows_Management_Deployment_IRemovePackageOptions
#endif
#if !defined(TODO_UpdatedWindowsSDK_with_Windows_Management_Deployment_IRemovePackageOptions)
// Until we have access to the updated Windows SDK we can't use RemovePackageOptions
// but we need *something* to satisfy PackageManagement_RemovePackageByUriAsync() in the FrameworkUDK
// so we'll make a placeholder definition to satisfy the compiler enough to let us call
// PackageManagement_RemovePackageByUriAsync2(uri, nullptr). Remove this once the updated
// Windows SDK makes this unnecessary.
namespace ABI::Windows::Management::Deployment
{
    typedef void * IRemovePackageOptions;
}
#endif
//
#include <FrameworkUdk/PackageManagement.h>

#endif //PCH_H
