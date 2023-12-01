// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.W.Workload.h"
#include "Microsoft.Windows.System.Workloads.Workload.g.cpp"

#include <wil/winrt.h>

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    Workload::Workload(hstring const& id, hstring const& displayName, hstring const& workloadHandlerActivatableClassId) :
        m_id(id),
        m_displayName(displayName),
        m_workloadHandlerActivatableClassId(m_workloadHandlerActivatableClassId)
    {
    }
    hstring Workload::Id()
    {
        return m_id;
    }
    hstring Workload::DisplayName()
    {
        return m_displayName;
    }
    hstring Workload::WorkloadHandlerActivatableClassId()
    {
        return m_workloadHandlerActivatableClassId;
    }
    winrt::Microsoft::Windows::System::Workloads::IWorkloadHandler Workload::WorkloadHandler()
    {
        if (!m_workloadHandler)
        {
            //TODO
        }
        return m_workloadHandler;
    }
}
