// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.System.Workloads.WorkloadResult.g.h"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    struct WorkloadResult : WorkloadResultT<WorkloadResult>
    {
        WorkloadResult() = default;

        winrt::Microsoft::Windows::System::Workloads::WorkloadStatus Status();
        winrt::hresult ExtendedError();

    private:
        winrt::Microsoft::Windows::System::Workloads::WorkloadStatus m_status{};
        winrt::hresult m_extendedError{};
    };
}
