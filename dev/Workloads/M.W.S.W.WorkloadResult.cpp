// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.W.WorkloadResult.h"
#include "Microsoft.Windows.System.Workloads.WorkloadResult.g.cpp"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    winrt::Microsoft::Windows::System::Workloads::WorkloadStatus WorkloadResult::Status()
    {
        return m_status;
    }
    winrt::hresult WorkloadResult::ExtendedError()
    {
        return m_extendedError;
    }
}
