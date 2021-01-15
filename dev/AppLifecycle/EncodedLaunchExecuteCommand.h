// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ExecuteCommandBase.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class EncodedLaunchExecuteCommand : public winrt::implements<EncodedLaunchExecuteCommand,
        ExecuteCommandBase>
    {
    public:
        IFACEMETHOD(Execute)() noexcept;

    private:
        static std::wstring ResolveUriTarget(std::wstring uri, std::wstring appUserModelId);
    };

    class __declspec(uuid("8B7A213D-BFFC-456F-B4B9-E3C5B5F1097D")) EncodedLaunchExecuteCommandFactory
        : public winrt::implements<EncodedLaunchExecuteCommandFactory, IClassFactory>
    {
        IFACEMETHODIMP CreateInstance(IUnknown* outer, GUID const& iid, void** result) noexcept final
        {
            *result = nullptr;

            if (outer)
            {
                return CLASS_E_NOAGGREGATION;
            }

            return make<EncodedLaunchExecuteCommand>()->QueryInterface(iid, result);
        }

        IFACEMETHODIMP LockServer(BOOL) noexcept final
        {
            return S_OK;
        }
    };
}
