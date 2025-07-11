using WEX.Logging.Interop;
using WEX.TestExecution;
using WEX.TestExecution.Markup;
using Microsoft.Windows.Storage.Pickers;

namespace StoragePickerComponentTests;

[TestClass]
public class StoragePickersTest
{
    [AssemblyInitialize]
    // This attribute is used by GenerateHelixWorkItems.ps1 to control how it creates the work items.
    // The default is CreateWorkItemPerModule
    //[TestProperty("HelixWorkItemCreation", "CreateWorkItemPerTestClass")]
    //[TestProperty("CoreClrProfile", "net5")]
    //[TestProperty("CoreClrProfile", "TestNetv8.0")]

    [TestProperty("IsolationLevel", "Class")]
    [TestProperty("CoreClrProfile", "localDotNet")]
    public static void AssemblyInitialize(TestContext testContext)
    {
        Log.Comment("AssemblyInitialize");
    }

    [TestMethod]
    public void SimpleAPlusBTest()
    {
        var picker = new FileOpenPicker(default);
        Verify.AreEqual(2, 1 + 1);
        picker.PickSingleFileAsync().Wait();
    }
}
