// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.System.Workloads.WorkloadManager.g.h"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    struct WorkloadManager : WorkloadManagerT<WorkloadManager>
    {
        WorkloadManager() = default;

        static winrt::Microsoft::Windows::System::Workloads::WorkloadManager GetDefault();
        winrt::Microsoft::Windows::System::Workloads::Workload GetWorkload(hstring const& id);
        winrt::Windows::Foundation::Collections::IVector<hstring> FindIds();
    };
}
namespace winrt::Microsoft::Windows::System::Workloads::factory_implementation
{
    struct WorkloadManager : WorkloadManagerT<WorkloadManager, implementation::WorkloadManager>
    {
    };
}
