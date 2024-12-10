// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;

class Program
{
    static void Main(string[] args)
    {
        // Note: This test app currently only tests that the compatibility properties set in
        // the project file generates the ConfigureCompatibility() function and compiles successfully.
        Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Compatibility.AutoInitialize.ConfigureCompatibility();
        Console.WriteLine("hello world");
        Environment.Exit(0);
    }
}
