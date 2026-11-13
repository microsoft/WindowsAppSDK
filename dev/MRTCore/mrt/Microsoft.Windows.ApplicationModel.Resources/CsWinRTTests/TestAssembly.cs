// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using WEX.TestExecution;
using WEX.TestExecution.Markup;

namespace MrtCoreCsWinRTTests
{
    [TestClass]
    internal class TestAssembly
    {
        [AssemblyInitialize]
        [TestProperty("CoreClrProfile", "net6")]
        public static void AssemblyInitialize(TestContext testContext)
        {
        }
    }
}
