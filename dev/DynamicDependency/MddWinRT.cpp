// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "MddWinRT.h"

#include "WinRTModuleManager.h"

HRESULT MddCore::WinRT::ToThreadingType(
    MddCore::WinRT::ThreadingModel threadingModel,
    ABI::Windows::Foundation::ThreadingType& threadingType,
    HRESULT errorIfUnknown) noexcept
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
    ABI::Windows::Foundation::ThreadingType& threadingType) noexcept try
{
    threadingType = MddCore::WinRTModuleManager::GetThreadingType(activatableClassId);
    return S_OK;
}
CATCH_RETURN();

HRESULT MddCore::WinRT::GetActivationFactory(
    HSTRING activatableClassId,
    REFIID iid,
    void** factory) noexcept try
{
    *factory = MddCore::WinRTModuleManager::GetActivationFactory(activatableClassId, iid);
    return S_OK;
}
CATCH_RETURN();
