// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test::DynamicDependency::COM
{
    void CoSuperInitialize(winrt::apartment_type const type)
    {
        // CoUninitialize() needs to be called as many times as CoInitialize()
        // Keep 'peeling the onion' until we're the 1st to initialize COM
        for (;;)
        {
            const HRESULT hr = WINRT_IMPL_CoInitializeEx(nullptr, static_cast<uint32_t>(type));
            if (hr == S_OK)
            {
                // COM was initialized successfully on this thread
                break;
            }
            else if (hr == S_FALSE)
            {
                // COM is already initialized the for thead
                // Undo the init we just did and the init we just detected
                WINRT_IMPL_CoUninitialize();
                WINRT_IMPL_CoUninitialize();
            }
            else if (hr == RPC_E_CHANGED_MODE)
            {
                // COM is already initialized for the thread as a different apartment type
                // This is an error so nothing to do. Undo the init we just detected
                WINRT_IMPL_CoUninitialize();
            }
            else
            {
                Assert::AreEqual(S_OK, hr, L"Error in CoInitializeEx()");
            }
        }
    }
}
