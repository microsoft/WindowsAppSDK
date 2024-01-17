// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.System.Workloads.Workload.g.h"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    struct Workload : WorkloadT<Workload>
    {
        Workload() = default;
        Workload(hstring const& id, int32_t rank, hstring const& displayName, hstring const& workloadHandlerActivatableClassId, bool canRemove);

        static winrt::Windows::Foundation::Collections::IVector<hstring> FindIds();
        static winrt::Microsoft::Windows::System::Workloads::Workload GetWorkload(hstring const& id);
        hstring Id();
        int32_t Rank();
        hstring DisplayName();
        bool CanRemove();
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::System::Workloads::WorkloadResult, winrt::Microsoft::Windows::System::Workloads::WorkloadProgress> RemoveWorkloadAsync();

    private:
        hstring m_id;
        int32_t m_rank{};
        hstring m_displayName;
        hstring m_workloadHandlerActivatableClassId;
        bool m_canRemove{};
    };
}
namespace winrt::Microsoft::Windows::System::Workloads::factory_implementation
{
    struct Workload : WorkloadT<Workload, implementation::Workload>
    {
    };
}
