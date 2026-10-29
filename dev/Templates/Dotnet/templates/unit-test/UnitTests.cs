using Microsoft.UI.Xaml.Controls;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.VisualStudio.TestTools.UnitTesting.AppContainer;

// WinUI tests share one application and UI dispatcher.
[assembly: DoNotParallelize]

// #if (TestRunner == "VSTest" && unpackaged)
[assembly: WinUITestTarget(typeof($safeprojectname$.VSTestApplication))]

// #endif
namespace $safeprojectname$;

[TestClass]
public partial class UnitTest1
{
#if (Fixture == AssemblyInitialize)
    [AssemblyInitialize]
    public static void AssemblyInit(TestContext context)
    {
    }

#endif
#if (Fixture == AssemblyCleanup)
    [AssemblyCleanup]
    public static void AssemblyCleanup()
    {
    }

#endif
#if (Fixture == ClassInitialize)
    [ClassInitialize]
    public static void ClassInit(TestContext context)
    {
    }

#endif
#if (Fixture == ClassCleanup)
    [ClassCleanup]
    public static void ClassCleanup()
    {
    }

#endif
#if (Fixture == TestInitialize)
    [TestInitialize]
    public void TestInit()
    {
    }

#endif
#if (Fixture == TestCleanup)
    [TestCleanup]
    public void TestCleanup()
    {
    }

#endif
    [TestMethod]
    public void TestMethod1()
    {
        Assert.AreEqual(0, 0);
    }

    // Use the UITestMethod attribute for tests that need to run on the UI thread.
    [UITestMethod]
    public void TestMethod2()
    {
        var grid = new Grid();
        Assert.IsTrue(grid.DispatcherQueue.HasThreadAccess);
        Assert.AreEqual(0, grid.MinWidth);
    }
}
