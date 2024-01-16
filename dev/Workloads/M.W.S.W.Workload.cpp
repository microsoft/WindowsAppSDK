// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.W.Workload.h"
#include "Microsoft.Windows.System.Workloads.Workload.g.cpp"

#include <wil/winrt.h>

#include <WorkloadTelemetry.h>

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    Workload::Workload(hstring const& id, int32_t rank, hstring const& displayName, hstring const& workloadHandlerActivatableClassId, bool canRemove) :
        m_id(id),
        m_rank(rank),
        m_displayName(displayName),
        m_workloadHandlerActivatableClassId(workloadHandlerActivatableClassId),
        m_canRemove(canRemove)
    {
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> Workload::FindIds()
    {
        auto logTelemetry{ WorkloadTelemetry::FindIds::Start() };

        auto ids{ winrt::single_threaded_vector<hstring>() };

        //TODO wil::unique_cotaskmem_ptr<PWSTR[]> workloadIds;
        //TODO uint32_t workloadIdsCount{};
        //TODO THROW_IF_FAILED(FrameworkUDk.PackageManagementWorkloads_FindIds(&workloadIdsCount, wil::out_param(workloadIds)));
        //TODO for (uint32_t index=0; index < workloadIdsCount; ++index)
        //TODO {
        //TODO     const winrt::hstring id{ workloadIds[index] };
        //TODO     ids.Append(id);
        //TODO }

        return ids;
    }
    winrt::Microsoft::Windows::System::Workloads::Workload Workload::GetWorkload(hstring const& workloadId)
    {
        auto logTelemetry{ WorkloadTelemetry::GetWorkload::Start(workloadId) };

        //TODO winrt::Windows::Foundation::Collections::IPropertySet properties;
        //TODO THROW_IF_FAILED(FrameworkUDk.PackageManagementWorkloads_GetWorkload(workloadId.c_str(), wil::out_param(properties)));
        //TODO
        //TODO auto id{ properties.Lookup(L"Id").as<winrt::Windows::Foundation::IPropertyValue>() };
        //TODO THROW_HR_IF_NULL(E_UNEXPECTED, id);
        //TODO THROW_HR_IF(E_UNEXPECTED, id.Type() != winrt::Windows::Foundation::PropertyType::String);
        //TODO
        //TODO auto displayName{ properties.Lookup(L"DisplayName").as<winrt::Windows::Foundation::IPropertyValue>() };
        //TODO THROW_HR_IF_NULL(E_UNEXPECTED, displayName);
        //TODO THROW_HR_IF(E_UNEXPECTED, displayName.Type() != winrt::Windows::Foundation::PropertyType::String);
        //TODO
        //TODO winrt::hstring action_remove_activatableClassId;
        //TODO {
        //TODO     auto actions{ properties.Lookup(L"Actions").as<winrt::Windows::Foundation::IPropertyValue>() };
        //TODO     THROW_HR_IF_NULL(E_UNEXPECTED, actions);
        //TODO     THROW_HR_IF(E_UNEXPECTED, actions.Type() != winrt::Windows::Foundation::PropertyType::Inspectable);
        //TODO     auto actions_remove{ actions.Lookup(L"Actions").as<winrt::Windows::Foundation::IPropertyValue>() };
        //TODO     if (actions_remove)
        //TODO     {
        //TODO         THROW_HR_IF(E_UNEXPECTED, actions_remove.Type() != winrt::Windows::Foundation::PropertyType::Inspectable);
        //TODO         action_remove_activatableClassId = properties.Lookup(L"@ActivatableClassId").as<winrt::Windows::Foundation::IPropertyValue>() };
        //TODO         THROW_HR_IF_NULL(E_UNEXPECTED, action_remove_activatableClassId);
        //TODO         THROW_HR_IF(E_UNEXPECTED, action_remove_activatableClassId.Type() != winrt::Windows::Foundation::PropertyType::String);
        //TODO     }
        //TODO }
        //TODO
        //TODO return winrt::make<winrt::Microsoft::Windows::System::Workloads::implementation::Workload>(id.GetString(), displayName.GetString(), action_remove_activatableClassId.GetString());

        throw hresult_not_implemented();
    }
    hstring Workload::Id()
    {
        return m_id;
    }
    int32_t Workload::Rank()
    {
        return m_rank;
    }
    hstring Workload::DisplayName()
    {
        return m_displayName;
    }
    bool Workload::CanRemove()
    {
        return m_canRemove;
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::System::Workloads::WorkloadResult, winrt::Microsoft::Windows::System::Workloads::WorkloadProgress> Workload::RemoveWorkloadAsync()
    {
        auto logTelemetry{ WorkloadTelemetry::RemoveWorkloadAsync::Start(m_id, m_workloadHandlerActivatableClassId) };

        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), !m_canRemove, "Workload.Id=%ls", m_id.c_str());

        HSTRING_HEADER acidHeader{};
        HSTRING acid{};
        THROW_IF_FAILED(::WindowsCreateStringReference(m_workloadHandlerActivatableClassId.c_str(), m_workloadHandlerActivatableClassId.size(), &acidHeader, &acid));
        ::IInspectable* iinspectable{};
        THROW_IF_FAILED(RoActivateInstance(acid, &iinspectable));
        winrt::com_ptr<IInspectable> inspectable;
        winrt::copy_from_abi(inspectable, iinspectable);
        auto workloadHandler{ inspectable.as<winrt::Microsoft::Windows::System::Workloads::IWorkloadHandler>() };

        auto logHandler{ WorkloadTelemetry::RemoveWorkloadAsync_Handler::Start(m_id, m_workloadHandlerActivatableClassId) };
        auto result{ workloadHandler.RemoveWorkloadAsync() };
        logHandler.Stop();

        logTelemetry.Stop();
        return result;
    }
}
