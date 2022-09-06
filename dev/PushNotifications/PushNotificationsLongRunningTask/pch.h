// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <unknwn.h>
#include <appmodel.h>

// Temporarily disable C4324 because WRL generates a false (well, irrelevant) warning
//   'Microsoft::WRL::Details::StaticStorage<Microsoft::WRL::Details::OutOfProcModuleBase<ModuleT>::GenericReleaseNotifier<T>,Microsoft::WRL::Details::StorageInstance::OutOfProcCallbackBuffer1,ModuleT>': structure was padded due to alignment specifier
#pragma warning(push)
#pragma warning(disable:4324)
#include <wrl.h>
#pragma warning(pop)

#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>
#include <winrt/Windows.Storage.h>
#include <wil/com.h>

// UDK/ProxyStub files
#define MIDL_NS_PREFIX
#include <FrameworkUdk/PushNotifications.h>
#include <FrameworkUdk/ToastNotifications.h>
#include <NotificationsLongRunningProcess_h.h>

// LRP files
#include "ForegroundSinkManager.h"
#include "PlatformLifetimeManager.h"
#include "NotificationListener.h"
#include "NotificationListenerManager.h"
