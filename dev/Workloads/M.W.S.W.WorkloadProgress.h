// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.System.Workloads.WorkloadProgress.g.h"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    struct WorkloadProgress : WorkloadProgressT<WorkloadProgress>
    {
        WorkloadProgress() = default;

        winrt::Microsoft::Windows::System::Workloads::WorkloadProgressStatus status();
        void status(winrt::Microsoft::Windows::System::Workloads::WorkloadProgressStatus const& value);
        double percentage();
        void percentage(double value);

    private:
        winrt::Microsoft::Windows::System::Workloads::WorkloadProgressStatus m_status{};
        double m_percentage{};
    };
}
