using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WEX.Logging.Interop;
using WEX.TestExecution;
using WEX.TestExecution.Markup;

namespace ProjectReunion.TestCommon
{
    [TestClass]
    class TestAssembly
    {
        [AssemblyInitialize]
        // This attribute is used by GenerateHelixWorkItems.ps1 to control how it creates the work items.
        // The default is CreateWorkItemPerModule
        [TestProperty("HelixWorkItemCreation", "CreateWorkItemPerTestClass")]
        [TestProperty("CoreClrProfile", "net5")]
        [TestProperty("IsolationLevel", "Class")]
        public static void AssemblyInitialize(TestContext testContext)
        {
            Log.Comment("AssemblyInitialize");
        }
    }
}
