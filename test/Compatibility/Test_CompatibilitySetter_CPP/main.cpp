// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <windows.h>

namespace Microsoft::Windows::ApplicationModel::WindowsAppRuntime::Compatibility
{
    namespace AutoInitialize { void Initialize(); };
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    // Note: This test app currently only tests that the compatibility properties specified in
    // the project file generates the Initialize() function and compiles successfully.
    // ** THE CODE WILL NOT RUN SUCCESSFULLY ** since this test project does not have access to the real
    //                                          WindowsAppSDK package and is also not using the test
    //                                          Microsoft.WindowsAppRuntime.Framework package.
    Microsoft::Windows::ApplicationModel::WindowsAppRuntime::Compatibility::AutoInitialize::Initialize();
    // Apps using the <WindowsAppSDKRuntimePatchLevel*> or <WindowsAppSDKDisabledChanges> project properties should
    // NOT directly call the above function. This test calls it just to verify that the function is generated.
    
    return 0;
}
