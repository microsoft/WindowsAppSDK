// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.W.WorkloadManager.h"
#include "Microsoft.Windows.System.Workloads.WorkloadManager.g.cpp"

namespace winrt::Microsoft::Windows::System::Workloads::implementation
{
    winrt::Microsoft::Windows::System::Workloads::WorkloadManager WorkloadManager::GetDefault()
    {
        return winrt::make<winrt::Microsoft::Windows::System::Workloads::implementation::WorkloadManager>();
    }
    winrt::Microsoft::Windows::System::Workloads::Workload WorkloadManager::GetWorkload(hstring const& workloadId)
    {
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
    winrt::Windows::Foundation::Collections::IVector<hstring> WorkloadManager::FindIds()
    {
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
}
