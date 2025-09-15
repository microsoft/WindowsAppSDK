using System.Runtime.InteropServices;
using System.Text;
using Microsoft.Windows.Storage.Pickers;
using WEX.Logging.Interop;
using WEX.TestExecution;
using WEX.TestExecution.Markup;

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


    //[TestProperty("RunAs", "UAP")]
    //[TestProperty("UAP:AppxManifest", "StoragePickerTest-AppxManifest.xml")]
    [TestProperty("IsolationLevel", "Class")]
    [TestProperty("CoreClrProfile", "localDotnet")]
    [TestProperty("ActivationContext", "taeftest.manifest")]
    public static void AssemblyInitialize(TestContext testContext)
    {
        Log.Comment("AssemblyInitialize");
    }

    List<IntPtr> foundDialogs = new List<IntPtr>();
    uint currentProcessId = 0;

    // Win32 APIs for auto-closing dialogs
    [DllImport("user32.dll", SetLastError = true)]
    static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

    [DllImport("user32.dll", SetLastError = true)]
    static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

    [DllImport("user32.dll", SetLastError = true)]
    static extern bool PostMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

    [DllImport("user32.dll", SetLastError = true)]
    static extern bool SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

    [DllImport("user32.dll", SetLastError = true)]
    static extern bool CloseWindow(IntPtr hWnd);

    [DllImport("user32.dll", SetLastError = true)]
    static extern bool IsWindow(IntPtr hWnd);

    [DllImport("user32.dll", SetLastError = true)]
    static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

    [DllImport("user32.dll", SetLastError = true)]
    static extern int GetClassName(IntPtr hWnd, StringBuilder lpClassName, int nMaxCount);

    delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

    [DllImport("user32.dll", SetLastError = true)]
    static extern bool EnumWindows(EnumWindowsProc lpEnumFunc, IntPtr lParam);

    [DllImport("user32.dll", SetLastError = true)]
    static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint lpdwProcessId);

    bool EnumWindowsCallback(IntPtr hWnd, IntPtr lParam)
    {
        if (!IsWindow(hWnd))
        {
            return true;
        }

        // Get window's process ID
        GetWindowThreadProcessId(hWnd, out uint processId);
        if (processId != currentProcessId)
        {
            return true;
        }

        // Get window class name and title
        StringBuilder className = new StringBuilder(256);
        StringBuilder windowTitle = new StringBuilder(256);
        GetClassName(hWnd, className, className.Capacity);
        GetWindowText(hWnd, windowTitle, windowTitle.Capacity);

        string classNameStr = className.ToString();
        string titleStr = windowTitle.ToString();

        // Look for common file picker dialog classes and titles
        if (classNameStr.Contains("#32770") || // Common dialog class
            classNameStr.Contains("FilePickerViewHost") ||
            titleStr.Contains("Open") ||
            titleStr.Contains("Save") ||
            titleStr.Contains("Browse") ||
            titleStr.Contains("Select"))
        {
            foundDialogs.Add(hWnd);
            Console.WriteLine($"Found dialog: Class={classNameStr}, Title={titleStr}, HWND={hWnd}");
        }

        return true; // Continue enumeration
    }

    // Constants for Windows messages
    const uint WM_CLOSE = 0x0010;
    const uint WM_COMMAND = 0x0111;
    const uint WM_KEYDOWN = 0x0100;
    const uint VK_ESCAPE = 0x1B;

    async Task CloseDialogsAfterDelay(int delayMs = 2000)
    {
        await Task.Delay(delayMs);

        foundDialogs.Clear();
        currentProcessId = (uint)Environment.ProcessId;

        // Find all dialogs belonging to our process
        EnumWindows(EnumWindowsCallback, IntPtr.Zero);

        // Close found dialogs
        foreach (var hWnd in foundDialogs)
        {
            if (IsWindow(hWnd))
            {
                Console.WriteLine($"Closing dialog with HWND: {hWnd}");

                // Try multiple methods to close the dialog
                // Method 1: Send WM_CLOSE message
                PostMessage(hWnd, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);

                // Method 2: Send Escape key (backup)
                await Task.Delay(100);
                if (IsWindow(hWnd))
                {
                    PostMessage(hWnd, WM_KEYDOWN, new IntPtr(VK_ESCAPE), IntPtr.Zero);
                }
            }
        }
    }

    [TestMethod]
    public async Task SimpleAPlusBTest()
    {
        var picker = new FileOpenPicker(default);
        Verify.AreEqual(2, 1 + 1);
        var task = CloseDialogsAfterDelay(2500);
        var file = await picker.PickSingleFileAsync();
        await task;
        // Trigger test failure for debugging
        Verify.IsNotNull(file);
    }
}
