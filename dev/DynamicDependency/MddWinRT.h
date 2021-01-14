// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDWINRT_H)
#define MDDWINRT_H

#include <activationregistration.h>

namespace MddCore::WinRT
{
    enum class ThreadingModel
    {
        Unknown,
        Both,
        STA,
        MTA
    };

    static_assert(static_cast<int>(MddCore::WinRT::ThreadingModel::Both) == static_cast<int>(ABI::Windows::Foundation::ThreadingType::ThreadingType_BOTH) + 1);
    static_assert(static_cast<int>(MddCore::WinRT::ThreadingModel::STA) == static_cast<int>(ABI::Windows::Foundation::ThreadingType::ThreadingType_STA) + 1);
    static_assert(static_cast<int>(MddCore::WinRT::ThreadingModel::MTA) == static_cast<int>(ABI::Windows::Foundation::ThreadingType::ThreadingType_MTA) + 1);

    HRESULT ToThreadingType(
        MddCore::WinRT::ThreadingModel threadingModel,
        ABI::Windows::Foundation::ThreadingType& threadingType,
        HRESULT errorIfUnknown = REGDB_E_CLASSNOTREG);

    HRESULT GetThreadingModel(
        HSTRING activatableClassId,
        ABI::Windows::Foundation::ThreadingType& threading_model);

    HRESULT GetActivationFactory(
        HSTRING activatableClassId,
        REFIID iid,
        void** factory);
}

#endif // MDDWINRT_H
