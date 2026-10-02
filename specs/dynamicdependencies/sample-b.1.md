# Sample B.1 - HelloWorld console app using the Boostrap API

At runtime, HelloWorld wants to use the Windows App SDK Framework 1.0-preview1 package, so it calls the Bootstrap API.

## Win32

```c++
#include <iostream>

#include <MddBootstrap.h>

int main()
{
    // Initialize access to Windows App SDK
    const uint32_t c_majorMinorVersion{ 0x00010000 };
    PCWSTR c_versionTag{ L"preview1" };
    const PACKAGE_VERSION c_minVersion{};
    wprintf(L"MddBootstrapInitialize(0x%08X, \"%s\", %hu.%hu.%hu.%hu)...\n",
            c_majorMinorVersion, c_versionTag, c_minVersion.Major, c_minVersion.Minor, c_minVersion.Build, c_minVersion.Revision);
    HRESULT hr{ MddBootstrapInitialize(c_majorMinorVersion, c_versionTag, c_minVersion) };
    if (FAILED(hr))
    {
        wprintf(L"Error 0x%X in MddBootstrapInitialize(0x%08X, \"%s\", %hu.%hu.%hu.%hu)\n",
                hr, c_majorMinorVersion, c_versionTag,
                c_minVersion.Major, c_minVersion.Minor, c_minVersion.Build, c_minVersion.Revision);
        return hr;
    }

    // Do interesting stuff...
    std::cout << "Hello World!\n";

    // Cleanup
    MddBootstrapShutdown();
    return 0;
}
```

## C# (Throw Exception on Error)

```c#
using System;
using Microsoft.Windows.ApplicationModel.DynamicDependency;

namespace HelloWorldCS
{
    class Program
    {
        static void Main(string[] args)
        {
            // Initialize access to Windows App SDK
            uint majorMinorVersion = 0x00010000;
            string versionTag = "preview1";
            var minVersion = new PackageVersion();
            try
            {
                Console.WriteLine($"Bootstrap.Initialize({majorMinorVersion:X08}, \"{versionTag}\", {minVersion.Major}.{minVersion.Minor}.{minVersion.Build}.{minVersion.Revision})...");
                Bootstrap.Initialize(majorMinorVersion, versionTag, minVersion);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                Environment.Exit(e.HResult);
            }

            // Do interesting stuff...
            Console.WriteLine("Hello World!");

            // Cleanup
            Bootstrap.Shutdown();
        }
    }
}
```

## C# (Return HRESULT on Error)

```c#
using System;
using Microsoft.Windows.ApplicationModel.DynamicDependency;

namespace HelloWorldCS_NoThrow
{
    class Program
    {
        static void Main(string[] args)
        {
            // Initialize access to Windows App SDK
            uint majorMinorVersion = 0x00010000;
            string versionTag = "preview1";
            var minVersion = new PackageVersion();
            Console.WriteLine($"Bootstrap_NoThrow.Initialize({majorMinorVersion:X08}, \"{versionTag}\", {minVersion.Major}.{minVersion.Minor}.{minVersion.Build}.{minVersion.Revision})...");
            int hr = 0;
            if (!Bootstrap.TryInitialize(majorMinorVersion, versionTag, minVersion,  out hr))
            {
                Console.WriteLine($"Error 0x{hr:X08} in Bootstrap_NoThrow.Initialize(0x{majorMinorVersion:X08}, \"{versionTag}\", {minVersion.Major}.{minVersion.Minor}.{minVersion.Build}.{minVersion.Revision})");
                Environment.Exit(hr);
            }

            // Do interesting stuff...
            Console.WriteLine("Hello World!");

            // Cleanup
            Bootstrap.Shutdown();
        }
    }
}
```
