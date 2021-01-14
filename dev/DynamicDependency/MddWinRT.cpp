// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "MddWinRT.h"

#include "PackageGraphManager.h"

HRESULT MddCore::WinRT::ToThreadingType(
    MddCore::WinRT::ThreadingModel threadingModel,
    ABI::Windows::Foundation::ThreadingType& threadingType,
    HRESULT errorIfUnknown)
{
    if (threadingModel == MddCore::WinRT::ThreadingModel::Both)
    {
        threadingType = ABI::Windows::Foundation::ThreadingType::ThreadingType_BOTH;
    }
    else if (threadingModel == MddCore::WinRT::ThreadingModel::STA)
    {
        threadingType = ABI::Windows::Foundation::ThreadingType::ThreadingType_STA;
    }
    else if (threadingModel == MddCore::WinRT::ThreadingModel::MTA)
    {
        threadingType = ABI::Windows::Foundation::ThreadingType::ThreadingType_MTA;
    }
    else
    {
        RETURN_HR_MSG(errorIfUnknown, "Unknown MddCore::WinRT::ThreadingModel %d", static_cast<int>(threadingModel));
    }
    return S_OK;
}

HRESULT MddCore::WinRT::GetThreadingModel(
    HSTRING activatableClassId,
    ABI::Windows::Foundation::ThreadingType& threading_model)
{
    auto threadingModel{ MddCore::WinRT::ThreadingModel::Unknown };
    RETURN_IF_FAILED(MddCore::PackageGraphManager::GetActivatableClassThreadingModel(activatableClassId, threadingModel));
    RETURN_HR_IF(REGDB_E_CLASSNOTREG, threadingModel == MddCore::WinRT::ThreadingModel::Unknown);
    RETURN_IF_FAILED(ToThreadingType(threadingModel, threading_model));
    return S_OK;
}

HRESULT MddCore::WinRT::GetActivationFactory(
    HSTRING /*activatableClassId*/,
    REFIID /*iid*/,
    void** /*factory*/)
{
    return E_NOTIMPL;
}
