// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef PCH_H
#define PCH_H
#endif //PCH_H

#include <unknwn.h>

#include <windows.h>
#include <sddl.h>
#include <appmodel.h>

#include <wil/result.h>
#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/resource.h>
#include <wil/filesystem.h>

#include <WexTestClass.h>

#include <string>

#include <wil/result_macros.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>
#include <winrt/Microsoft.Security.Authentication.OAuth.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h>
#include <winrt/Microsoft.Windows.ApplicationModel.Background.h>
#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>
#include <winrt/Microsoft.Windows.AppLifecycle.h>
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include <winrt/Microsoft.Windows.AppNotifications.Builder.h>
#include <winrt/Microsoft.Windows.BadgeNotifications.h>
#include <winrt/Microsoft.Windows.Management.Deployment.h>
#include <winrt/Microsoft.Windows.Media.Capture.h>
#include <winrt/Microsoft.Windows.PushNotifications.h>
#include <winrt/Microsoft.Windows.Security.AccessControl.h>
#include <winrt/Microsoft.Windows.Storage.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <winrt/Microsoft.Windows.System.h>
#include <winrt/Microsoft.Windows.System.Power.h>

// Component APIs - Resources, Foundation, Globalization
#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>
#include <winrt/Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.h>
#include <winrt/Microsoft.Windows.Foundation.h>
#include <winrt/Microsoft.Windows.Globalization.h>

// AI APIs
#include <winrt/Microsoft.Windows.AI.h>
#include <winrt/Microsoft.Windows.AI.ContentSafety.h>
#include <winrt/Microsoft.Windows.AI.Foundation.h>
#include <winrt/Microsoft.Windows.AI.Imaging.h>
#include <winrt/Microsoft.Windows.AI.Text.h>
#include <winrt/Microsoft.Graphics.Imaging.h>

// ML APIs
#include <winrt/Microsoft.Windows.AI.MachineLearning.h>

// Widgets APIs
#include <winrt/Microsoft.Windows.Widgets.Providers.h>
#include <winrt/Microsoft.Windows.Widgets.Feeds.Providers.h>
#include <winrt/Microsoft.Windows.Widgets.Notifications.h>

#include <MddBootstrap.h>
