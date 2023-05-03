// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <unknwn.h>
#include <appmodel.h>

#include <thread>
#include <mutex>

// Temporarily disable C4324 because WRL generates a false (well, irrelevant) warning
//   'Microsoft::WRL::Details::StaticStorage<Microsoft::WRL::Details::OutOfProcModuleBase<ModuleT>::GenericReleaseNotifier<T>,Microsoft::WRL::Details::StorageInstance::OutOfProcCallbackBuffer1,ModuleT>': structure was padded due to alignment specifier
#pragma warning(push)
#pragma warning(disable:4324)
#include <wrl.h>
#pragma warning(pop)

// Must appear before #include <wil/resource.h> to turn on wil::unique_wtsmem_ptr definition.
#include <wtsapi32.h>

#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/com.h>
#include <wil_kozani.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <WindowsAppRuntimeInsights.h>

#include "Logging.h"