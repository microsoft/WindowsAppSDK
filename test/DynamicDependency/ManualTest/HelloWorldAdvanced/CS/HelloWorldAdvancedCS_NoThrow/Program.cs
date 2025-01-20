// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using Microsoft.Windows.ApplicationModel.DynamicDependency;

namespace HelloWorldAdvancedCS_NoThrow
{
    class Program
    {
        static void Help()
        {
            var help = new string[]{
                "Usage: HelloWorldAdvancedCS_NoThrow.exe [options] <majorminor> [<tag> [<minversion>]]",
                "options:",
                "  --onerror:debugbreak                    = DebugBreak() if error",
                "  --onerror:debugbreak:ifdebuggerattached = DebugBreak() if error and IsDebuggerAttached()",
                "  --onerror:failfast                      = FailFast if error",
                "  --onnomatch:showui                      = Show UI if no match",
                "  --onpackageidentity:noop                = No error if process has package identity",
                "  -?, --help                              = Display help",
                "  --                                      = Stop processing options",
                "where:",
                "  majorminor = Windows App SDK release Major.Minor version (default=1.0)",
                "               Can be...",
                "                   0xMMMMNNNN (base-16)",
                "                   M[.N] (dot-notation)",
                "                   UInt32 (base-10)",
                "         tag = Project Reunion version Tag (default=experimental1)",
                "  minversion = Project Reunion minimum version (default=0)",
                "",
                "Examples:",
                "",
                "Use Windows App SDK 1.0-experimental1, minVersion=0.218.840.0",
                "  HelloWorldAdvancedCS_NoThrow.exe 1.0 experimental 0.218.840.0",
                "Use Windows App SDK 1.0 (stable), minVersion=0 (any)",
                "  HelloWorldAdvancedCS_NoThrow.exe 0x00010000 0\"\"",
                "Use Windows App SDK 1.1-experimental2, minVersion=0 (any)",
                "  HelloWorldAdvancedCS_NoThrow.exe 1.1 experimental2 0",
                "  or",
                "  HelloWorldAdvancedCS_NoThrow.exe 1.1 experimental"
            };
            Console.WriteLine(string.Join('\n', help));
            Environment.Exit(1);
        }

        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Help();
            }

            // Parse the command line
            uint majorMinorVersion = 0;
            Bootstrap.InitializeOptions options = Bootstrap.InitializeOptions.None;
            int argn = 0;
            string arg = null;
            while (argn < args.Length)
            {
                arg = args[argn];
                if (arg == "*")
                {
                    // Use the build-time value (our default value above)
                }
                else if (arg.Equals("-?") || arg.Equals("--help"))
                {
                    Help();
                }
                else if (arg.Equals("--onerror:debugbreak"))
                {
                    options |= Bootstrap.InitializeOptions.OnError_DebugBreak;
                }
                else if (arg.Equals("--onerror:debugbreak:ifdebuggerattached"))
                {
                    options |= Bootstrap.InitializeOptions.OnError_DebugBreak_IfDebuggerAttached;
                }
                else if (arg.Equals("--onerror:failfast"))
                {
                    options |= Bootstrap.InitializeOptions.OnError_FailFast;
                }
                else if (arg.Equals("--onnomatch:showui"))
                {
                    options |= Bootstrap.InitializeOptions.OnNoMatch_ShowUI;
                }
                else if (arg.Equals("--onpackageidentity:noop"))
                {
                    options |= Bootstrap.InitializeOptions.OnPackageIdentity_NOOP;
                }
                else if (arg.Equals("--"))
                {
                    break;
                }
                else if (arg.StartsWith("--"))
                {
                    // Unknown option
                    Help();
                }
                else
                {
                    break;
                }
                ++argn;
            }

            if (argn >= args.Length)
            {
                Help();
            }
            arg = args[argn++];
            if (arg.StartsWith("0x"))
            {
                majorMinorVersion = Convert.ToUInt32(arg.Substring(2), 16);
            }
            else
            {
                try
                {
                    var fields = arg.Split('.');
                    if (fields.Length == 2)
                    {
                        var major = Convert.ToUInt16(fields[0]);
                        var minor = Convert.ToUInt16(fields[1]);
                        majorMinorVersion = ((uint)major) << 16 | (uint)minor;
                    }
                    else
                    {
                        majorMinorVersion = Convert.ToUInt32(arg, 10);
                    }
                }
                catch (FormatException)
                {
                    Help();
                }
            }
            if (majorMinorVersion == 0)
            {
                Help();
            }

            string versionTag = "";
            if (argn < args.Length)
            {
                arg = args[argn++];
                versionTag = arg;
            }

            var minVersion = new PackageVersion();
            if (argn < args.Length)
            {
                arg = args[argn++];
                if (arg.StartsWith("0x"))
                {
                    var version = Convert.ToUInt64(arg);
                    minVersion = new PackageVersion(version);
                }
                else
                {
                    var fields = arg.Split('.');
                    if ((fields.Length >= 1) && (fields.Length <= 4))
                    {
                        var major = Convert.ToUInt16(fields[0]);
                        var minor = (fields.Length >= 2 ? Convert.ToUInt16(fields[1]) : (ushort)0);
                        var build = (fields.Length >= 2 ? Convert.ToUInt16(fields[2]) : (ushort)0);
                        var revision = (fields.Length >= 2 ? Convert.ToUInt16(fields[3]) : (ushort)0);
                        minVersion = new PackageVersion(major, minor, build, revision);
                    }
                    else
                    {
                        Console.WriteLine($"Invalid parameter {arg}");
                        Environment.Exit(1);
                    }
                }
            }

            // Initialize access to Windows App SDK
            Console.WriteLine($"Bootstrap_NoThrow.Initialize({majorMinorVersion:X08}, \"{versionTag}\", {minVersion.Major}.{minVersion.Minor}.{minVersion.Build}.{minVersion.Revision}, 0x{(int)options:X08})...");
            int hr;
            if (!Bootstrap.TryInitialize(majorMinorVersion, versionTag, minVersion, out hr))
            {
                Console.WriteLine($"Error 0x{hr:X08} in Bootstrap_NoThrow.Initialize(0x{majorMinorVersion:X08}, \"{versionTag}\", {minVersion.Major}.{minVersion.Minor}.{minVersion.Build}.{minVersion.Revision}, 0x{(int)options:X08})");
                Environment.Exit(hr);
            }

            // Do interesting stuff...
            Console.WriteLine("Hello World!");

            // Cleanup
            Bootstrap.Shutdown();
        }
    }
}
