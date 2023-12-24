// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.W.WorkloadProgress.h"
#include "Microsoft.Windows.System.Workloads.WorkloadProgress.g.cpp"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    winrt::Microsoft::Windows::System::Workloads::WorkloadProgressStatus WorkloadProgress::status()
    {
        return m_status;
    }
    void WorkloadProgress::status(winrt::Microsoft::Windows::System::Workloads::WorkloadProgressStatus const& value)
    {
        m_status = value;
    }
    double WorkloadProgress::percentage()
    {
        return m_percentage;
    }
    void WorkloadProgress::percentage(double value)
    {
        m_percentage = value;
    }
}
