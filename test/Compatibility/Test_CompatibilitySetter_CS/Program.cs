// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;

class Program
{
    static void Main(string[] args)
    {
        // Note: This test app currently only tests that the compatibility properties specified in
        // the project file generates the ConfigureCompatibility() function and compiles successfully.
        Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Compatibility.AutoInitialize.ConfigureCompatibility();
        // Apps using the <WindowsAppSDKRuntimePatchMode*> or <WindowsAppSDKDisabledChanges> project properties should
        // NOT directly call the above function. This test calls it just to verify that the function is generated.

        Console.WriteLine("hello world");
        Environment.Exit(0);
    }
}
