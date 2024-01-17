// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.System.Workloads.Workload.g.h"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    struct Workload : WorkloadT<Workload>
    {
        Workload() = default;
        Workload(hstring const& id, hstring const& displayName, hstring const& workloadHandlerActivatableClassId);

        hstring Id();
        hstring DisplayName();
        hstring WorkloadHandlerActivatableClassId();
        winrt::Microsoft::Windows::System::Workloads::IWorkloadHandler WorkloadHandler();

    private:
        hstring m_id;
        hstring m_displayName;
        hstring m_workloadHandlerActivatableClassId;
        winrt::Microsoft::Windows::System::Workloads::IWorkloadHandler m_workloadHandler{};
    };
}
namespace winrt::Microsoft::Windows::System::Workloads::factory_implementation
{
    struct Workload : WorkloadT<Workload, implementation::Workload>
    {
    };
}
