// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef MICROSOFT_WINDOWSAPPSDK_ML_DISABLE_AUTOINITIALIZE

#include <Windows.h>

struct OrtApiBase;

extern "C" const OrtApiBase* __cdecl OrtGetApiBase() noexcept
{
    // Static local variable with guaranteed one-time initialization (C++11)
    static const OrtApiBase* s_ortApiBase = []() -> const OrtApiBase* {

        // In passthrough mode, onnxruntime.dll is expected to already be loaded in the process.
        // This approach is useful when the host application has already loaded onnxruntime.dll
        // and we just need to provide a passthrough implementation to satisfy linker requirements.

        // Get handle to onnxruntime.dll that should already be loaded in the current process
        HMODULE onnxruntimeModule = nullptr;
        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, L"onnxruntime.dll", &onnxruntimeModule))
        {
            // onnxruntime.dll is not loaded in the current process
            return nullptr;
        }

        // Get the OrtGetApiBase function from the already-loaded onnxruntime.dll
        using OrtGetApiBaseFunc = OrtApiBase* (*)();
        auto ortGetApiBase = reinterpret_cast<OrtGetApiBaseFunc>(GetProcAddress(onnxruntimeModule, "OrtGetApiBase"));
        if (ortGetApiBase)
        {
            // Call the real OrtGetApiBase function and return its result
            return ortGetApiBase();
        }

        return nullptr;
    }();

    return s_ortApiBase;
}

#endif // MICROSOFT_WINDOWSAPPSDK_ML_DISABLE_AUTOINITIALIZE
