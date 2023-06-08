// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <Windows.h>
#include <stdlib.h>

// Ensure the including PE file has an import reference to
// the WindowsAppSDK runtime DLL and thus gets loaded when
// the including PE file gets loaded.

STDAPI WindowsAppRuntime_EnsureIsLoaded();

namespace Microsoft::Windows::Foundation::UndockedRegFreeWinRT
{
    struct AutoInitialize
    {
        AutoInitialize()
        {
            // Load the Windows App SDK runtime DLL. The only reason this could fail
            // is if the loading application using WinAppSDK/SelfContained has a
            // damaged self-contained configuration of the Windows App SDK's runtime.

            // Define MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY
            // if Microsoft.WindowsAppRuntime.dll is DelayLoad'd and thus we need
            // to explicitly load the DLL at runtime. Otherwise we can implicitly
            // link the library and get an import reference causing Windows to
            // resolve our import at load-time.
#if defined(MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY)
            static HMODULE dll{ LoadLibraryExW(L"Microsoft.WindowsAppRuntime.dll", nullptr, 0) };
            if (!dll)
            {
                const auto lastError{ GetLastError() };
                DebugBreak();
                exit(HRESULT_FROM_WIN32(lastError));
            }
#else
            (void) WindowsAppRuntime_EnsureIsLoaded();
#endif
        }
    };
    static AutoInitialize g_autoInitialize;
}
