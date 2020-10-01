// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <winrt/base.h>
#include "ExecuteCommand.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class ExtensionContractHandler : public winrt::implements<ExtensionContractHandler, ExecuteCommand>
    {
        // IExecuteCommand
        IFACEMETHODIMP Execute();

    private:
    };

    class __declspec(uuid("FA2F222A-EC9D-437D-9760-2E2D73CB58EC")) ExtensionContractHandlerFactory :
        public winrt::implements<ExtensionContractHandlerFactory, IClassFactory>
    {
        IFACEMETHODIMP CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) noexcept override
        {
            try
            {
                return winrt::make<ExtensionContractHandler>()->QueryInterface(riid, ppvObject);
            }
            catch (...)
            {
                return winrt::to_hresult();
            }
        }

        IFACEMETHODIMP LockServer(BOOL fLock) noexcept override
        {
            // ...
            return S_OK;
        }

        // ...
    };
}
