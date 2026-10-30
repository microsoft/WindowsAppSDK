// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using WEX.TestExecution;
using WEX.TestExecution.Markup;

namespace MrtCoreCsWinRTTests
{
    [TestClass]
    internal class TestAssembly
    {
        // TAEF loads CoreCLR from this subfolder next to the test DLL.
#if NET10_0_OR_GREATER
        private const string CoreClrProfile = "net10";
#else
        private const string CoreClrProfile = "net6";
#endif

        [AssemblyInitialize]
        [TestProperty("CoreClrProfile", CoreClrProfile)]
        public static void AssemblyInitialize(TestContext testContext)
        {
#if NET10_0_OR_GREATER
            // TAEF has no managed entry assembly; CsWinRT 3.0 finds its type maps through it.
            System.Reflection.Assembly.SetEntryAssembly(typeof(TestAssembly).Assembly);
#endif
        }
    }
}