// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;

class Program
{
    static void Main(string[] args)
    {
        // Note: This test app currently only tests that the compatibility properties specified in
        // the project file generates the ConfigureCompatibility() function and compiles successfully.
        // ** THE CODE WILL NOT RUN SUCCESSFULLY ** since this test project does not have access to the real
        //                                          WindowsAppSDK package and is also not using the test
        //                                          Microsoft.WindowsAppRuntime.Framework package.
        Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Compatibility.AutoInitialize.ConfigureRuntimeCompatibility();
        // Apps using the <WindowsAppSDKRuntimePatchLevel*> or <WindowsAppSDKDisabledChanges> project properties should
        // NOT directly call the above function. This test calls it just to verify that the function is generated.

        Console.WriteLine("hello world");
        Environment.Exit(0);
    }
}
