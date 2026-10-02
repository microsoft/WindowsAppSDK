// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WEX.Logging.Interop;
using WEX.TestExecution;
using WEX.TestExecution.Markup;

namespace WindowsAppSDK.Test.SampleTests
{
    [TestClass]
    class TestAssembly
    {
        [AssemblyInitialize]
        [TestProperty("CoreClrProfile", "net6")]
        [TestProperty("IsolationLevel", "Class")]
        public static void AssemblyInitialize(TestContext testContext)
        {
            Log.Comment("AssemblyInitialize");
            Log.Comment($" CurrentDirectory: {System.IO.Directory.GetCurrentDirectory()}");
            Log.Comment($"       Executable: {System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName}");
            Log.Comment($"    EntryAssembly: {EntryAssemblyLocation}");
            Log.Comment($"ExecutingAssembly: {System.Reflection.Assembly.GetExecutingAssembly().Location}");
            Log.Comment($"  CallingAssembly: {System.Reflection.Assembly.GetCallingAssembly().Location}");
        }

        private static string EntryAssemblyLocation
        {
            get
            {
                var assembly = System.Reflection.Assembly.GetEntryAssembly();
                return assembly == null ? "<null>" : assembly.Location;
            }
        }
    }
}
