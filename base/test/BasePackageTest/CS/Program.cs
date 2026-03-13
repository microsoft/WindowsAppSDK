// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Validates Base package binplacement behavior for different configurations.
// EXPECT_NO_BOOTSTRAP: Only app DLLs expected, no bootstrap.
// EXPECT_BOOTSTRAP: Bootstrap DLLs MUST be present.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

var exeDir = AppContext.BaseDirectory;
Console.WriteLine($"BasePackageTest output dir: {exeDir}");

var allDlls = Directory.GetFiles(exeDir, "*.dll")
    .Select(Path.GetFileName)
    .OrderBy(x => x, StringComparer.OrdinalIgnoreCase)
    .ToList()!;

Console.WriteLine($"DLLs found: {allDlls.Count}");
foreach (var dll in allDlls)
{
    Console.WriteLine($"  {dll}");
}

int exitCode = 0;

#if EXPECT_NO_BOOTSTRAP
Console.WriteLine("\n[Expecting: no bootstrap DLLs]");
var allowedDlls = new HashSet<string>(StringComparer.OrdinalIgnoreCase)
{
    "BasePackageTest.dll",
    "Microsoft.Windows.SDK.NET.dll",
    "WinRT.Runtime.dll"
};

var unexpected = allDlls.Where(d => !allowedDlls.Contains(d!)).ToList();
if (unexpected.Count > 0)
{
    Console.Error.WriteLine("FAIL: Unexpected DLLs found:");
    foreach (var dll in unexpected)
        Console.Error.WriteLine($"  {dll}");
    exitCode = 1;
}
else
{
    Console.WriteLine("PASS: Only expected DLLs present (no bootstrap).");
}

#elif EXPECT_BOOTSTRAP
Console.WriteLine("\n[Expecting: bootstrap DLLs present]");
var requiredBootstrapDlls = new[]
{
    "Microsoft.WindowsAppRuntime.Bootstrap.dll",
    "Microsoft.WindowsAppRuntime.Bootstrap.Net.dll"
};

var missingBootstrap = requiredBootstrapDlls
    .Where(r => !allDlls.Any(d => string.Equals(d, r, StringComparison.OrdinalIgnoreCase)))
    .ToList();

if (missingBootstrap.Count > 0)
{
    Console.Error.WriteLine("FAIL: Expected bootstrap DLLs not found:");
    foreach (var dll in missingBootstrap)
        Console.Error.WriteLine($"  {dll}");
    exitCode = 1;
}
else
{
    Console.WriteLine("PASS: Bootstrap DLLs are present as expected.");
}
#endif

return exitCode;
