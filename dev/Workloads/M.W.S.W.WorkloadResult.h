// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.System.Workloads.WorkloadResult.g.h"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    struct WorkloadResult : WorkloadResultT<WorkloadResult>
    {
        WorkloadResult() = default;
        WorkloadResult(winrt::Microsoft::Windows::System::Workloads::WorkloadStatus status, winrt::hresult const& error, winrt::hresult const& extendedError, hstring const& errorText) :
            m_status(status),
            m_error(error),
            m_extendedError(extendedError),
            m_errorText(errorText)
        {
        }

        winrt::Microsoft::Windows::System::Workloads::WorkloadStatus Status();
        winrt::hresult Error();
        winrt::hresult ExtendedError();
        hstring ErrorText();

    private:
        winrt::Microsoft::Windows::System::Workloads::WorkloadStatus m_status{};
        winrt::hresult m_error{};
        winrt::hresult m_extendedError{};
        winrt::hstring m_errorText{};
    };
}
