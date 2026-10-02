// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System.Linq;
using Microsoft.Windows.Apps.Test.Foundation;
using Microsoft.Windows.Apps.Test.Foundation.Waiters;

using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Collections.Generic;

using WEX.Logging.Interop;
using WEX.TestExecution;
using WEX.TestExecution.Markup;

/*
    General Notes:
    - If you are onboarding a new Sample app, please look for instructions in the "Adding a new Sample app" section below.
    - This TAEF test attempts to verify that Sample apps on the Samples repo can be launched successfully given a newly built WASDK Foundation product
      (i.e., regression detection).
    - Currently, ~70 buildable and launchable Sample apps have been identified on the Samples repo.
    - Because there are different kinds of Sample apps, the extend to which the app launch can be verified varies from one app to another. The  
      basic permutations are: [ Packaged | Unpackaged ] x [ Windowed | Console | wpf ].
    - "Packaged + Windowed" is generally the most rigiously verified, while "Unpackaged + Console" is minimally verified. 
    - This TAEF test requires the environment variable SAMPLES_ROOT_PATH to be set to point to the root folder of the sample apps, under which folders 
      such as AppLifeCycle and ResourcesManagement can be found, e.g. "set SAMPLES_ROOT_PATH=C:\\myRepo\\WindowsAppSDK-Samples\\Samples". This approach
      seems to be more effective than spending time searching all logical drives the the machine for the samples root folder on each run of the test.  
    - The environment variable can be set in the pipeline or on a developer's local machine.    
    - The caller can optionally set environment variables Build_Platform and Build_Configuration to modify the paths to the target sample binaries.
      Build_Platform can be one of { x86 | x64 | arm64 }. By default, Build_Platform=x64.
      Build_Configuration can be one of { Debug | Release }. By default, Build_Configuration=Release.
    - Currently, not all Sample apps are being built for all permutations of { x86 | x64 | arm64 } X { Debug | Release }, with X64+Release being the
      greatest common denominator. When a test case exercises the Build_Platform + Build_Configuration which the corresponding Sample app isn't built
      for, that test is being skipped.
    - Not all Sample apps are working on all versions of Windows supported by WASDK. When a Sample app does not support a particular version of
      Windows, the corresponding test case is being skipped on that version of Windows.
    - The following information about each Sample app is currently hardcoded: relative path to executable/manifest, process name, window title, app 
      ID, package full/family names. The benefit of this hardcoding approach is simplicity. 
    - Test cases are intentionally "flat" structured, such that when any sample app test is failing, it is straight forward to diagnose and fix. 
      In case some of these per-app pieces are churning frequently enough in the future to create a maintenance burden, we can consider 
      investing into detection logic for populating most if not all of these pieces.
    - It is currently deemed non-critical to maximize the degree of verification for every app on the Samples repo, given the purpose of increasing 
      test coverage for nightly builds, as there likely is already redundance in the test cases. The ROI on including more sample apps in the future  
      is anticipated to diminish, unless a new feature or app activation mechansim needs to be verified.
*/

namespace WindowsAppSDK.Test.SampleTests
{
    [TestClass]
    public class WindowsAppSDKSampleAppTests
    {
        // 20-second timeout period for general shell commands.
        public const int TIMEOUT = 20000;
        
        public static TestContext TestContext { get; private set; }
        public static string SamplesRootPath = null;
        public static string BuildArch = null;
        public static string BuildConfig = null;
        public Process Process { get; private set; }

        private class ProcessComparer : IEqualityComparer<Process>
        {
            public bool Equals(Process x, Process y)
            {
                // NOTE: The following expression has been updated locally and is now out of sync with its source:
                // https://dev.azure.com/microsoft/WinUI/_search?action=history&type=code&text=def%3AProcessComparer&filters=ProjectFilters%7BWinUI%7DRepositoryFilters%7Bmicrosoft-ui-xaml-lift%7D&includeFacets=false&result=DefaultCollection/WinUI/microsoft-ui-xaml-lift/GBmain//controls/test/testinfra/MUXTestInfra/Infra/Application.cs.
                return (x == null && y == null) || ((x != null && y != null) && (x.Id == y.Id));
            }

            public int GetHashCode(Process obj)
            {
                return obj.GetHashCode();
            }
        }

        private int GetProcessIdFromAppWindow(string appWindowTitle)
        {
            var topWindowCondition = UICondition.CreateFromName(appWindowTitle);
            if (UIObject.Root.Children.TryFind(topWindowCondition, out UIObject topWindowObj))
            {
                Log.Comment("Found topWindowObj for #{0}...", topWindowCondition);
                return topWindowObj.ProcessId;
            }

            Log.Comment("topWindowObj _NOT FOUND_ for #{0}...", topWindowCondition);
            return -1;
        }

        private bool KillProcessAndWaitForExit(Process process)
        {
            Log.Comment($"Killing process {process.Id}");
            if (process.HasExited)
            {
                return true;
            }

            process.Kill();
            return process.WaitForExit(10000 /*milliseconds*/);
        }

        // If an explicit appWindowsProcessId is prescribed then add the corresponding process name to a list of processes to try to kill.
        // Regardless of that, as long as a valid appProcessName is prescribed then we should be able to just add that name to the kill list.
        // Hopefully that would leave us with a list of process names, potentially with duplicates, to kill.
        // We then try to kill each unique process name, with verification.
        // If the target process is not found, it's unexpected, bubble up an issue.
        private void EnsureApplicationProcessHasExited(int appWindowsProcessId, string appProcessName)
        {
            const int MaxLaunchRetries = 4;
            for (int retries = 1; retries <= MaxLaunchRetries; ++retries)
            {
                var appProcesses = Process.GetProcessesByName(Path.GetFileNameWithoutExtension(appProcessName)).ToList();

                if (appWindowsProcessId != -1)
                {
                    try
                    {
                        appProcesses.Add(Process.GetProcessById(appWindowsProcessId));
                    }
                    catch (Exception)
                    {
                        // Ignore. GetProcessById throws if the process has already exited.
                    }
                }
 
                if (Process != null)
                {
                    appProcesses.Add(Process);
                }

                if (appProcesses.Count > 0)
                {
                    foreach (var proc in appProcesses.Distinct(new ProcessComparer()))
                    {
                        if (!proc.HasExited && !KillProcessAndWaitForExit(proc))
                        {
                            throw new Exception($"Unable to kill process: {proc}");
                        }
                    }
                    return;
                }

                // appWindowsProcessId==-1 means the caller did not wait for the app's window at launch; so in case we've got 
                // here too quickly, retry a couple of times to find the app's processes.
                if ((appWindowsProcessId != -1) || (retries >= MaxLaunchRetries))
                {
                    // http://task.ms/58006958. Preliminary investigation revealed that, when we can't detect the expected
                    // sample app process after the launch command has returned success, even with retries, is probably not
                    // because we don't wait long enough for the sampple app's process to be found, but is more likely 
                    // because the sample app process has naturally terminated so quickly that the test code doesn't catch 
                    // it soon enough. IOW, increasing the wait time for the app launch is unlikely to help, and the 
                    // intermittent sample app launch failures being reported recently are most likely noise (false positives).
                    // To unblock pipeline runs, we are making it a non-fatal situation when we hit this code path. Log a   
                    // warning message to maintain visibility to the "process not found" errors.
                    // When we can properly detect the "sample app terminates too quickly" situation in the future, we might  
                    // want to bring back the following commented out statement to make this code path a fatal problem again.
                    // Verify.Fail($"Couldn't find the expected process {appProcessName}, not good!");
                    Log.Warning($"[WARNING]: Couldn't find the expected process {appProcessName}, not good!");
                    return;
                }

                Log.Comment("Found no process related to {0} to terminate, trying again {1} after 2 sec.", appProcessName, retries);
                Thread.Sleep(TimeSpan.FromSeconds(2));
            }
            return;
        }

        // Try to launch an unpackaged app by its full exe path, with retries.
        // If a valid appWindowTitle is prescribed, then the launch isn't considered successful until the window with the expected 
        // title is found. Also verify that the expected process name is present, and then use that name to terminate the appp process.
        // Process termination is also verified.
        private void LaunchAndCloseUnpackagedApp(string unpackagedExeFullPath, string appWindowTitle, string appProcessName)
        {
            const int MaxLaunchRetries = 3;

            Log.Comment($"Using executable: {unpackagedExeFullPath}");
            if (!File.Exists(unpackagedExeFullPath))
            {
                Verify.Fail($"Executable not found at {unpackagedExeFullPath}!");
                return;
            }

            for (int retries = 1; retries <= MaxLaunchRetries; ++retries)
            {
                try
                {
                    Log.Comment("Attempting launch, try #{0}...", retries);

                    if (String.IsNullOrEmpty(appWindowTitle))
                    {                        
                        //Instead of launching the process directly it is invoked through explorer.exe, resulting in the process starting unelevated. 
                        ProcessStartInfo unelevatedProcessStartInfo = new ProcessStartInfo();
                        unelevatedProcessStartInfo.FileName = "C:\\Windows\\explorer.exe";
                        unelevatedProcessStartInfo.Arguments = unpackagedExeFullPath;

                        Process.Start(unelevatedProcessStartInfo);

                        // Unlike the case below, there is no window to wait for here. So, as long as we didn't hit an activation error, just
                        // wait a couple of seconds to give the app a chance to run, then proceed to kill it, at that point the presence of the
                        // expected process is verified.
                        Thread.Sleep(TimeSpan.FromSeconds(2));
                    }
                    else
                    {
                        // In this case we can verify the window with the expected title is present. We currently don't perform further checks such as the window type.
                        UICondition WindowCondition = UICondition.CreateFromName(appWindowTitle);

                        using (AppLaunchWaiter launchWaiter = new AppLaunchWaiter(WindowCondition))
                        {
                            // Instead of launching the process directly it is invoked through explorer.exe, resulting in the process starting unelevated. 
                            ProcessStartInfo unelevatedProcessStartInfo = new ProcessStartInfo();
                            unelevatedProcessStartInfo.FileName = "C:\\Windows\\explorer.exe";
                            unelevatedProcessStartInfo.Arguments = unpackagedExeFullPath;

                            Process.Start(unelevatedProcessStartInfo);

                            launchWaiter.Wait();
                        }
                    }

                    Log.Comment("Launch successful!");
                    break;
                }
                catch (Exception ex)
                {
                    Log.Comment("Failed to launch app. Exception: " + ex.ToString());

                    if (retries < MaxLaunchRetries)
                    {
                        Log.Comment("UAPApp.Launch might not have waited long enough, trying again {0}", retries);
                        Thread.Sleep(TimeSpan.FromSeconds(2));
                    }
                    else
                    {
                        Log.Error("Could not launch app {0} !", unpackagedExeFullPath);
                        throw;
                    }
                }
            }

            // If appWindowTitle is valid, use it to derive the target process ID to terminate. Otherwise, we fall back to 
            // using the appProcessName to derive the process ID.
            int appWindowsProcessId = -1;
            if (!String.IsNullOrEmpty(appWindowTitle))
            {
                appWindowsProcessId = GetProcessIdFromAppWindow(appWindowTitle);
                if (appWindowsProcessId < 0)
                {
                    throw new Exception($"Could not find window with title: {appWindowTitle}");
                }
            }

            EnsureApplicationProcessHasExited(appWindowsProcessId, appProcessName);

            if (Process != null)
            {
                Process.Dispose();
                Process = null;
            }
            return;
        }

        private static void UpdateBuildArchIfNeeded()
        {
            if (String.IsNullOrEmpty(BuildArch))
            {
                string getEnv = Environment.GetEnvironmentVariable("Build_Platform");
                if (String.IsNullOrEmpty(getEnv))
                {
                    BuildArch = "x64";
                }
                else 
                {
                    BuildArch = getEnv;
                }
                Log.Comment("BuildArch updated to: " + BuildArch);
            }
        }

        private static void UpdateBuildConfigIfNeeded()
        {
            if (String.IsNullOrEmpty(BuildConfig))
            {
                string getEnv = Environment.GetEnvironmentVariable("Build_Configuration");
                if (String.IsNullOrEmpty(getEnv))
                {
                    BuildConfig = "Release";
                }
                else
                {
                    BuildConfig = getEnv;
                }

                Log.Comment("BuildConfig updated to: " + BuildConfig);
            }
        }

        // The prescribed fileRelativePath is expected to be relative to the root of the samples folder. See example below.
        // Construct the full path by appending fileRelativePath to the samples root folder.
        // Verify existence of the resulting full path.
        // Similarly, use _optional_ environment variables to initialize build architecture and config.
        private static string GetFullFilePathFromRelativePath(string fileRelativePath)
        {
            if (String.IsNullOrEmpty(fileRelativePath))
            {
                Verify.Fail($"fileRelativePath cannot be null!");
                return null;
            }

            // Fetch the samples root folder from environment variable on demand.
            if (String.IsNullOrEmpty(SamplesRootPath))
            {
                string getEnv = Environment.GetEnvironmentVariable("SAMPLES_ROOT_PATH");
                if (String.IsNullOrEmpty(getEnv))
                {
                    Log.Error("**** Please set environment variable SAMPLES_ROOT_PATH before running this test ****");
                    Log.Error("SAMPLES_ROOT_PATH should point to a folder that contains sample folders such as AppLifecycle, PhotoEditor, ResourceManagement, etc.");
                    Verify.Fail($"e.g., set SAMPLES_ROOT_PATH=C:\\myRepo\\WindowsAppSDK-Samples\\Samples");
                    Log.Error("You can also optionally set Build_Platform to one of { x86 | x64 | arm64 }, the default is x64.");
                    Log.Error($"e.g., set Build_Platform=arm64");
                    Log.Error("You can also optionally set Build_Configuration to one of { Debug | Release }, the default is Release.");
                    Log.Error($"Build_Platform and Build_Configuration modifies the file path to the test binary targeted.");
                    return null;
                }

                if (!Directory.Exists(getEnv))
                {
                    Verify.Fail($"Path {getEnv} in SAMPLES_ROOT_PATH was not found!");
                    return null;
                }

                SamplesRootPath = getEnv;
                Log.Comment("SamplesRootPath updated to: " + SamplesRootPath);
            }

            UpdateBuildArchIfNeeded();
            UpdateBuildConfigIfNeeded();

            var fileFullPath1 = Path.Combine(SamplesRootPath, fileRelativePath);
            var fileFullPath2 = fileFullPath1.Replace("[BuildArch]", BuildArch);
            var fileFullPath3 = fileFullPath2.Replace("[BuildConfig]", BuildConfig);
            if (!File.Exists(fileFullPath3))
            {
                Verify.Fail($"File path {fileFullPath3} was not found!");
                return null;
            }

            return fileFullPath3;
        }

        private static class NativeMethods
        {
            public enum ActivateOptions
            {
                None = 0x00000000,  // No flags set
                DesignMode = 0x00000001,  // The application is being activated for design mode, and thus will not be able to
                                          // to create an immersive window. Window creation must be done by design tools which
                                          // load the necessary components by communicating with a designer-specified service on
                                          // the site chain established on the activation manager.  The splash screen normally
                                          // shown when an application is activated will also not appear.  Most activations
                                          // will not use this flag.
                NoErrorUI = 0x00000002,   // Do not show an error dialog if the app fails to activate.                                
                NoSplashScreen = 0x00000004,  // Do not show the splash screen when activating the app.
            }

            public const string CLSID_ApplicationActivationManager_String = "45ba127d-10a8-46ea-8ab7-56ea9078943c";
            public const string CLSID_IApplicationActivationManager_String = "2e941141-7f97-4756-ba1d-9decde894a3d";

            public static readonly Guid CLSID_ApplicationActivationManager = new Guid(CLSID_ApplicationActivationManager_String);
            public static readonly Guid CLSID_IApplicationActivationManager = new Guid(CLSID_IApplicationActivationManager_String);

            [ComImport, Guid(CLSID_IApplicationActivationManager_String), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
            public interface IApplicationActivationManager
            {
                // Activates the specified immersive application for the "Launch" contract, passing the provided arguments
                // string into the application.  Callers can obtain the process Id of the application instance fulfilling this contract.
                IntPtr ActivateApplication([In] String appUserModelId, [In] String arguments, [In] ActivateOptions options, [Out] out UInt32 processId);
                IntPtr ActivateForFile([In] String appUserModelId, [In] IntPtr /*IShellItemArray* */ itemArray, [In] String verb, [Out] out UInt32 processId);
                IntPtr ActivateForProtocol([In] String appUserModelId, [In] IntPtr /* IShellItemArray* */itemArray, [Out] out UInt32 processId);
            }

            [DllImport("api-ms-win-ntuser-ie-window-l1-1-0.dll", SetLastError = true)]
            public static extern bool SetForegroundWindow(IntPtr hWnd);

            [DllImport("ole32.dll", CharSet = CharSet.Unicode, ExactSpelling = true, PreserveSig = false)]
            public static extern UInt32 CoCreateInstance(
                [In, MarshalAs(UnmanagedType.LPStruct)] Guid rclsid,
                IntPtr pUnkOuter,
                CLSCTX dwClsContext,
                [In, MarshalAs(UnmanagedType.LPStruct)] Guid riid,
                [MarshalAs(UnmanagedType.IUnknown)] out object rReturnedComObject);

            [Flags]
            public enum CLSCTX : uint
            {
                CLSCTX_INPROC_SERVER = 0x1,
                CLSCTX_INPROC_HANDLER = 0x2,
                CLSCTX_LOCAL_SERVER = 0x4,
                CLSCTX_INPROC_SERVER16 = 0x8,
                CLSCTX_REMOTE_SERVER = 0x10,
                CLSCTX_INPROC_HANDLER16 = 0x20,
                CLSCTX_RESERVED1 = 0x40,
                CLSCTX_RESERVED2 = 0x80,
                CLSCTX_RESERVED3 = 0x100,
                CLSCTX_RESERVED4 = 0x200,
                CLSCTX_NO_CODE_DOWNLOAD = 0x400,
                CLSCTX_RESERVED5 = 0x800,
                CLSCTX_NO_CUSTOM_MARSHAL = 0x1000,
                CLSCTX_ENABLE_CODE_DOWNLOAD = 0x2000,
                CLSCTX_NO_FAILURE_LOG = 0x4000,
                CLSCTX_DISABLE_AAA = 0x8000,
                CLSCTX_ENABLE_AAA = 0x10000,
                CLSCTX_FROM_DEFAULT_CONTEXT = 0x20000,
                CLSCTX_ACTIVATE_32_BIT_SERVER = 0x40000,
                CLSCTX_ACTIVATE_64_BIT_SERVER = 0x80000,
                CLSCTX_INPROC = CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER,
                CLSCTX_SERVER = CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER,
                CLSCTX_ALL = CLSCTX_SERVER | CLSCTX_INPROC_HANDLER
            }
        }

        // Verify that process creation of the prescribed exe by full path hits no error.
        // Generally, there isn't much else we can verify in this basic scenario.
        private void LaunchUnpackagedConsoleApp(string unpackagedExeFullPath)
        {
            Log.Comment($"Using executable: {unpackagedExeFullPath}");
            try
            {
                if (!File.Exists(unpackagedExeFullPath))
                {
                    Verify.Fail($"Executable not found at {unpackagedExeFullPath}!");
                    return;
                }

                ProcessStartInfo unelevatedProcessStartInfo = new ProcessStartInfo();
                unelevatedProcessStartInfo.FileName = unpackagedExeFullPath;
                unelevatedProcessStartInfo.Arguments = "";

                Process.Start(unelevatedProcessStartInfo);

                Log.Comment("Launch successful!");
            }
            catch (Exception ex)
            {
                Log.Comment("Failed to launch app. Exception: " + ex.ToString());
                Log.Error("Could not launch app {0} !", unpackagedExeFullPath);
                throw;
            }

            return;
        }

        // Use the Activation Manager to launch a packaged app by appName (app ID). When a valid appWindowTitle is prescribed,
        // the launch isn't deemed finish until a window with expected title appWindowTitle is found. Verify that a process
        // with expected name appProcessName can be found, and then the corresponding process is terminated by process ID.
        // Termination of the process is also verified.
        private void LaunchAndClosePackagedApp(string appName, string appWindowTitle, string appProcessName)
        {
            const int MaxLaunchRetries = 3;

            Log.Comment($"Using NonUWPApp: {appName}");

            for (int retries = 1; retries <= MaxLaunchRetries; ++retries)
            {
                try
                {
                    Log.Comment("Attempting launch, try #{0}...", retries);

                    if (NativeMethods.CoCreateInstance(
                        NativeMethods.CLSID_ApplicationActivationManager,
                        IntPtr.Zero,
                        NativeMethods.CLSCTX.CLSCTX_LOCAL_SERVER,
                        NativeMethods.CLSID_IApplicationActivationManager,
                        out object applicationActivationManagerAsObject) != 0)
                    {
                        throw new Exception("Failed to create ApplicationActivationManager!");
                    }

                    if (String.IsNullOrEmpty(appWindowTitle))
                    {
                        var applicationActivationManager = (NativeMethods.IApplicationActivationManager)applicationActivationManagerAsObject;
                        applicationActivationManager.ActivateApplication(appName, null, NativeMethods.ActivateOptions.None, out uint processId);

                        // Unlike the case below, there is no window to wait for here. So, as long as we didn't hit an activation error, just
                        // wait a couple of seconds to give the app a chance to run, proceed to kill it.
                        Thread.Sleep(TimeSpan.FromSeconds(2));
                    }
                    else
                    {
                        UICondition WindowCondition = UICondition.CreateFromName(appWindowTitle);
                        UIObject window;
                        using (AppLaunchWaiter launchWaiter = new AppLaunchWaiter(WindowCondition))
                        {
                            var applicationActivationManager = (NativeMethods.IApplicationActivationManager)applicationActivationManagerAsObject;
                            applicationActivationManager.ActivateApplication(appName, null, NativeMethods.ActivateOptions.None, out uint processId);

                            launchWaiter.Wait();
                            window = launchWaiter.Source;
                        }

                        NativeMethods.SetForegroundWindow(window.NativeWindowHandle);
                    }

                    Log.Comment("Launch successful!");
                    break;
                }
                catch (Exception ex)
                {
                    Log.Comment("Failed to launch app. Exception: " + ex.ToString());

                    if (retries < MaxLaunchRetries)
                    {
                        Log.Comment("UAPApp.Launch might not have waited long enough, trying again {0}", retries);
                        Thread.Sleep(TimeSpan.FromSeconds(2));
                    }
                    else
                    {
                        Log.Error("Could not launch app {0} !", appName);
                        throw;
                    }
                }
            }

            int appWindowsProcessId = -1;
            if (!String.IsNullOrEmpty(appWindowTitle))
            {
                // appWindowTitle being valid means we would have waited for the app's window with the expected title at launch above.
                // Hence, putting the logic below in a retry loop probably won't help.
                appWindowsProcessId = GetProcessIdFromAppWindow(appWindowTitle);
                if (appWindowsProcessId < 0)
                {
                    throw new Exception($"Could not find window with title: {appWindowTitle}");
                }
            }

            EnsureApplicationProcessHasExited(appWindowsProcessId, appProcessName);

            if (Process != null)
            {
                Process.Dispose();
                Process = null;
            }
            return;
        }

        // Invoke CreateProcess to run exeName with arguments. Wiat for completion.
        // Verify no error is returned.
        private static void RunCommand(string exeName, string arguments)
        {
            Log.Comment("Running the following command line: " + exeName + " " + arguments);

            Process process = new Process();
            ProcessStartInfo psi = new ProcessStartInfo();

            psi.FileName = exeName;
            if (arguments != null)
            {
                psi.Arguments = arguments;
            }
            psi.UseShellExecute = false;
            psi.RedirectStandardOutput = true;
            psi.RedirectStandardError = true;

            process.StartInfo = psi;
            process.Start();
            string stdout = process.StandardOutput.ReadToEnd();
            string stderr = process.StandardError.ReadToEnd();

            // Ensure things went smoothly
            Verify.IsTrue(process.WaitForExit(TIMEOUT), "Waiting for " + exeName + " to finish");
            Log.Comment("Tool std output: " + stdout);
            Log.Comment("Tool error output: " + stderr);

            // Ensure we dont fail for any commands
            Verify.IsTrue((process.ExitCode == 0), "Expected an exit code of 0, and got back " + process.ExitCode);
            process.Dispose();
        }

        private static void RunPowerShellCommand(string arguments)
        {
            RunCommand("powershell.exe ", arguments);
        }

        private static void RemoveAppxPackage(string packageFullNameTempalte)
        {
            var packageFullName = packageFullNameTempalte.Replace("[BuildArch]", BuildArch);
            RunPowerShellCommand("remove-appxpackage " + packageFullName);
        }

        private static void RegisterAppxPackage(string manifestRelativePath)
        {
            var manifestFullPath = GetFullFilePathFromRelativePath(manifestRelativePath);

            // Powershell needs single quotes around the path in order to cope with spaces in the path.
            var manifestFullPathQuoted = "\'" + manifestFullPath + "\'";

            Log.Comment("manifestFullPathQuoted: " + manifestFullPathQuoted);
            RunPowerShellCommand("add-appxpackage " + "-register " + manifestFullPathQuoted);
        }

        private bool IsArchX86()
        {
            UpdateBuildArchIfNeeded();
            return ((BuildArch == "x86") || (BuildArch == "X86"));
        }

        private bool IsArchX64()
        {
            UpdateBuildArchIfNeeded();
            return ((BuildArch == "x64") || (BuildArch == "X64"));
        }

        private bool IsBuildConfigDebug()
        {
            UpdateBuildConfigIfNeeded();
            return ((BuildConfig == "debug") || (BuildConfig == "Debug"));
        }

        [ClassInitialize]
        [TestProperty("RunAs", "User")]
        public static void ClassInitialize(TestContext testContext)
        {
            return;
        }

        [TestCleanup]
        public void TestCleanup()
        {
            return;
        }

        [ClassCleanupAttribute]
        public static void ClassCleanup()
        {
            return;
        }

/*
                            Adding a new Sample app

- If you are adding a new Sample app to an existing feature area, please find the existing feature area below and add it there.
- Sections are marked by banners that look like "**** XYZ sample apps ***".
- If you are adding a new feature area, please start a new section using existing feature areas, such as "SelfContainedDeployment", 
  as example. Add new test cses for the Sample apps in the new section.
- Feature areas that currently only have 1 Sample app are grouped at the end in the "Other" section. Feel free to start a new 
  section if a feature area there is getting more than 1 sample app.
- There is typically one test method per Sample app. Please use the feature area as the prefix of the name of the new test method, 
  followed by the name/ID of the Sample app. Please see examples below.
- Currently, no Sample apps are being built in the pipeline for x86, hence, your sample app test method typically will have a "if 
  IsArchX86() then skip the test" check at top. You should be able to find examples below.
- If your Sample app does not support arm64, you might want to use a "if (!IsArchX64()) then skip the test" check at top. Again, 
  there are examples below.
- If your Sample app is "release only", then you might want to have a "if (IsBuildConfigDebug()) then skip the test" check.
- If your Sample app does not support older Windows version, please use Environment.OSVersion.Version.* to skip your test as needed.
  Examples are below.
- Please keep in mind that this TAEF test might be run manually on a local machine, so configuration permutations currently not
  being exercised in the pipeline can happen, and your test method should handle that.
- If your Sample app is a _unpackaged_ 
  - console app (i.e., no UI), please use LaunchUnpackagedConsoleApp(<exePath>) to verify its launch, where <exePath> is the relative 
    path to the .exe with your feature area as the root. Please see examples below.
  - app that pops a window, please use LaunchAndCloseUnpackagedApp(<exePath>, <windowTitle>, <processName>) to verify its launch. 
    Please see examples below.
  - app that does not pop a window but a process is still expected to be running after launch, please use LaunchAndCloseUnpackagedApp(
    <exePath>, null, <processName>) to verify its launch. Please see examples below.
- If your Sample app is a _packaged_ app
  - that pops a window, please use LaunchAndClosePackagedApp(<appName>, <windowTitle>, <processName>) to verify its launch. 
    - The packaged app should be explicitly registered using RegisterAppxPackage(<manifestPath>) and removed using RemoveAppxPackage(
      <packageFullName>). Please see examples below. 
  - that does not pop a window, please use LaunchAndClosePackagedApp(<appName>, null, <processName>) to verify its launch. 
- Even if for whatever reason a packaged sample app cannot be verified for launch, there is still merit to automate verification of 
  the Register and Remove of the package. Please see examples below.
- Please strive to maximize the degree of verification for your Sample app. Add runtime checks for your app after launch if applicable.

*/

        /**** SelfContainedDeployment sample apps ****/

        // For unpackaged console apps, generally we verify that launch of the app by full path to the exe does not return an error.
        [TestMethod]
        public void SelfContainedDeploymentCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("SelfContainedDeployment\\cpp\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\SelfContainedDeployment.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        [TestProperty("Ignore", "True")]    // Temporarily skipping this due to http://task.ms/56699769 
        public void SelfContainedDeploymentCsConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("SelfContainedDeployment\\cs\\cs-console-unpackaged\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\win-[BuildArch]\\SelfContainedDeployment.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        [TestProperty("Ignore", "True")]    // Temporarily skipping this due to http://task.ms/56699769 
        public void SelfContainedDeploymentCsWpfUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("SelfContainedDeployment\\cs\\cs-wpf-unpackaged\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.17763.0\\win-[BuildArch]\\SelfContainedDeployment.exe");
            LaunchAndCloseUnpackagedApp(exePath, "MainWindow", "SelfContainedDeployment.exe");
            return;
        }

        /**** AppLifecycle sample apps ****/

        [TestMethod]
        public void AppLifecycleActivationCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Activation\\cpp\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinRtConsoleActivation.exe");

            // TODO: Even when launched in VS, this app is hitting "Error 0x80070491 in MddBootstrapInitialize(0x00010000, , 0.0.0.0)".
            // Therefore, resorting to minimal verification for now, improve on this in the future.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        // TODO: This sample app quickly exits after launch, with message: "CsConsoleActivation.exe (process 11628) exited with code 0.", hence not much verification is
        // being done currently. Consider improving on that. Same for the next few apps.
        [TestMethod]
        public void AppLifecycleActivationCsConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Activation\\cs\\cs-console-unpackaged\\CsConsoleActivation\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsConsoleActivation.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleActivationCppWin32Unpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Activation\\cpp\\cpp-win32-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinMainActivation.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleActivationCsWinformsUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Activation\\cs\\cs-winforms-unpackaged\\CsWinFormsActivation\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsWinFormsActivation.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleActivationCsWpfUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Activation\\cs\\cs-wpf-unpackaged\\CsWpfActivation\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsWpfActivation.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        // For unpackaged apps that does not put up a window, generally we verify that
        // 1) launch of the app by full path to the exe does not return an error,
        // 2) a process with the expected name is present,
        // 3) processes associated with the app can be terminated.
        // TODO: Missing WASDK 1.2 is blocking WinCppWinRtConsoleEnv.exe from activating the app's main window? Temporarily skip looking for the app's main 
        // window, but still look for the expected process name to terminate. Same for the next 2 sample apps.
        [TestMethod]
        public void AppLifecycleEnvironmentVariablesCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\EnvironmentVariables\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinRtConsoleEnv.exe");
            LaunchAndCloseUnpackagedApp(exePath, null, "CppWinRtConsoleEnv.exe");
            return;
        }

        [TestMethod]
        public void AppLifecycleEnvironmentVariablesCppWin32Unpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\EnvironmentVariables\\cpp-win32-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinMainEnv.exe");
            LaunchAndCloseUnpackagedApp(exePath, null, "CppWinMainEnv.exe");
            return;
        }

        [TestMethod]
        public void AppLifecycleEnvironmentVariablesCsWinfromsUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            if (!IsArchX64())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, 
                    "This Sample app is currently failing to launch on arm64fre builds due to MSVCP140.dll NOT FOUND error.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\EnvironmentVariables\\cs-winforms-unpackaged\\CsWinFormsEnv\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsWinFormsEnv.exe");
            LaunchAndCloseUnpackagedApp(exePath, null, "CsWinFormsEnv.exe");
            return;
        }

        [TestMethod]
        public void AppLifecycleInstancingCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Instancing\\cpp\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinRtConsoleInstancing.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleInstancingCsConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Instancing\\cs\\cs-console-unpackaged\\CsConsoleInstancing\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsConsoleInstancing.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleInstancingCppWin32Unpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Instancing\\cpp\\cpp-win32-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinMainInstancing.exe");

            // This sample app seems to behave like a console app.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleInstancingCsWinformsUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Instancing\\cs\\cs-winforms-unpackaged\\CsWinFormsInstancing\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsWinFormsInstancing.exe");

            // This sample app seems to behave like a console app.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleInstancingCsWpfUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\Instancing\\cs\\cs-wpf-unpackaged\\CsWpfInstancing\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsWpfInstancing.exe");

            // This sample app seems to behave like a console app.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleStateNotificationsCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\StateNotifications\\cpp\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinRtConsoleState.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleStateNotificationsCsConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\StateNotifications\\cs\\cs-console-unpackaged\\CsConsoleState\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsConsoleState.exe");
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleStateNotificationsCppWin32Unpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\StateNotifications\\cpp\\cpp-win32-unpackaged\\[BuildArch]\\[BuildConfig]\\CppWinMainState.exe");

            // This sample app seems to behave like a console app.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleStateNotificationsCsWinformsUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\StateNotifications\\cs\\cs-winforms-unpackaged\\CsWinFormsState\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsWinFormsState.exe");

            // This sample app seems to behave like a console app.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void AppLifecycleStateNotificationsCsWpfUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("AppLifecycle\\StateNotifications\\cs\\cs-wpf-unpackaged\\CsWpfState\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\CsWpfState.exe");

            // This sample app seems to behave like a console app.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        // [TestMethod]
        // public void AppLifecycleInstancingCppWin32Packaged()
        // {
        //     if (IsArchX86() || IsBuildConfigDebug())
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
        //         return;
        //     }

        //     Log.Comment($"OSVersion {Environment.OSVersion.Version.Major}.{Environment.OSVersion.Version.Minor}.{Environment.OSVersion.Version.Build}");
        //     if ((Environment.OSVersion.Version.Major < 10) || ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Build < 19041)))
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This test requires Win 10 Build 19041 or higher.");
        //         return;
        //     }

        //     if ((Environment.OSVersion.Version.Major == 10) && ((Environment.OSVersion.Version.Build == 19044) || (Environment.OSVersion.Version.Build == 19045)))
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "Skipping this test on LTSC 2021 (19044) and 22h2 (19045) until b#53993352 is fixed.");
        //         return;
        //     }

        //     RegisterAppxPackage("AppLifecycle\\Instancing\\cpp\\cpp-win32-packaged\\CppWinMainInstancingPkg\\bin\\[BuildArch]\\[BuildConfig]\\AppxManifest.xml");
        //     LaunchAndClosePackagedApp("d9bcd10a-b42d-4e1e-9656-a2284d39e12d_s9y1p3hwd5qda!App", "CppWinMainInstancing", "CppWinMainInstancing.exe");
        //     RemoveAppxPackage("d9bcd10a-b42d-4e1e-9656-a2284d39e12d_1.0.0.0_[BuildArch]__s9y1p3hwd5qda");
        //     return;
        // }

        [TestMethod]
        public void AppLifecycleInstancingCsWpfPackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            Log.Comment($"OSVersion {Environment.OSVersion.Version.Major}.{Environment.OSVersion.Version.Minor}.{Environment.OSVersion.Version.Build}");
            if ((Environment.OSVersion.Version.Major < 10) || ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Build < 19041)))
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This test requires Win 10 Build 19041 or higher.");
                return;
            }

            if ((Environment.OSVersion.Version.Major == 10) && ((Environment.OSVersion.Version.Build == 19044) || (Environment.OSVersion.Version.Build == 19045)))
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "Skipping this test on LTSC 2021 (19044) and 22h2 (19045) until b#53993352 is fixed.");
                return;
            }

            RegisterAppxPackage("AppLifecycle\\Instancing\\cs1\\cs-wpf-packaged\\CsWpfInstancingPkg\\bin\\[BuildArch]\\[BuildConfig]\\AppxManifest.xml");
            LaunchAndClosePackagedApp("1b900d33-3e06-4f3e-9797-2fc2ffebb6f1_s9y1p3hwd5qda!App", "CsWpfInstancingPkg", "CsWpfInstancing.exe");
            RemoveAppxPackage("1b900d33-3e06-4f3e-9797-2fc2ffebb6f1_1.0.0.0_[BuildArch]__s9y1p3hwd5qda");
            return;
        }

        // [TestMethod]
        // public void AppLifecycleStateNotificationsCppWin32Packaged()
        // {
        //     if (IsArchX86() || IsBuildConfigDebug())
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
        //         return;
        //     }

        //     Log.Comment($"OSVersion {Environment.OSVersion.Version.Major}.{Environment.OSVersion.Version.Minor}.{Environment.OSVersion.Version.Build}");
        //     if ((Environment.OSVersion.Version.Major < 10) || ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Build < 19041)))
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This test requires Win 10 Build 19041 or higher.");
        //         return;
        //     }

        //     if ((Environment.OSVersion.Version.Major == 10) && ((Environment.OSVersion.Version.Build == 19044) || (Environment.OSVersion.Version.Build == 19045)))
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "Skipping this test on LTSC 2021 (19044) and 22h2 (19045) until b#53993352 is fixed.");
        //         return;
        //     }

        //     RegisterAppxPackage("AppLifecycle\\StateNotifications\\cpp\\cpp-win32-packaged\\CppWinMainStatePkg\\bin\\[BuildArch]\\[BuildConfig]\\AppxManifest.xml");
        //     LaunchAndClosePackagedApp("e0d8ad55-f3f2-4d7f-9182-3ee6905208a8_s9y1p3hwd5qda!App", "CppWinMainState", "CppWinMainState.exe");
        //     RemoveAppxPackage("e0d8ad55-f3f2-4d7f-9182-3ee6905208a8_1.0.0.0_[BuildArch]__s9y1p3hwd5qda");
        //     return;
        // }

        [TestMethod]
        public void AppLifecycleStateNotificationsCsWpfPackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            Log.Comment($"OSVersion {Environment.OSVersion.Version.Major}.{Environment.OSVersion.Version.Minor}.{Environment.OSVersion.Version.Build}");
            if ((Environment.OSVersion.Version.Major < 10) || ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Build < 19041)))
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This test requires Win 10 Build 19041 or higher.");
                return;
            }

            if ((Environment.OSVersion.Version.Major == 10) && ((Environment.OSVersion.Version.Build == 19044) || (Environment.OSVersion.Version.Build == 19045)))
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "Skipping this test on LTSC 2021 (19044) and 22h2 (19045) until b#53993352 is fixed.");
                return;
            }

            RegisterAppxPackage("AppLifecycle\\StateNotifications\\cs1\\cs-wpf-packaged\\CsWpfStatePkg\\bin\\[BuildArch]\\[BuildConfig]\\AppxManifest.xml");
            LaunchAndClosePackagedApp("7718eec3-5345-4d4e-815f-97df705dc89c_s9y1p3hwd5qda!App", "C# WPF Activation", "CsWpfState.exe");
            RemoveAppxPackage("7718eec3-5345-4d4e-815f-97df705dc89c_1.0.0.0_[BuildArch]__s9y1p3hwd5qda");
            return;
        }

        /**** ResourceManagement sample apps ****/

        // TODO: Missing WASDK 1.2 is blocking Unpackaged.exe from activating? Skip looking for the app's main window, but still
        // look for the expected process name to terminate. Same for the next app.
        [TestMethod]
        public void ResourceManagementCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("ResourceManagement\\cpp\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\console_unpackaged_app.exe");

            Log.Comment($"OSVersion {Environment.OSVersion.Version.Major}.{Environment.OSVersion.Version.Minor}.{Environment.OSVersion.Version.Build}");
            if ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Build == 22000))
            {
                Log.Comment("This test is currently failing on the 21h2 Enterprise Multi-Session OS image seemingly because a Welcome to MS Teams! window is on top. Doing minimal activation checking until this is resolved.");
                LaunchUnpackagedConsoleApp(exePath);
                return;
            }

            LaunchAndCloseUnpackagedApp(exePath, null, "console_unpackaged_app.exe");
            return;
        }

        [TestMethod]
        public void ResourceManagementCsWinformsUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            if (!IsArchX64())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, 
                    "This Sample app is currently failing to launch on arm64fre builds due to MSVCP140.dll NOT FOUND error.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("ResourceManagement\\cs\\cs-winforms-unpackaged\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\winforms_unpackaged_app.exe");
            LaunchAndCloseUnpackagedApp(exePath, null, "winforms_unpackaged_app.exe");
            return;
        }

        [TestMethod]
        public void ResourceManagementCsWpfPackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            if ((Environment.OSVersion.Version.Major == 10) && ((Environment.OSVersion.Version.Build == 19044) || (Environment.OSVersion.Version.Build == 19045)))
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "Skipping this test on LTSC 2021 (19044) and 22h2 (19045) until b#53993352 is fixed.");
                return;
            }

            RegisterAppxPackage("ResourceManagement\\cs1\\cs-wpf\\wpf_packaged_app (Package)\\bin\\[BuildArch]\\[BuildConfig]\\AppxManifest.xml");
            LaunchAndClosePackagedApp("25dee5b5-8e25-431f-a644-e75d98163029_s9y1p3hwd5qda!App", "MRT Core WPF sample", "wpf_packaged_app.exe");
            RemoveAppxPackage("25dee5b5-8e25-431f-a644-e75d98163029_1.0.0.0_[BuildArch]__s9y1p3hwd5qda");
            return;
        }

        /**** Windowing sample apps ****/

        [TestMethod]
        public void WindowingCsWinformsUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            if (!IsArchX64())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, 
                    "This Sample app is currently failing to launch on arm64fre builds due to MSVCP140.dll NOT FOUND error.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Windowing\\cs\\cs-winforms-unpackaged\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\winforms_unpackaged_app.exe");

            // TODO: Missing WASDK 1.2 is blocking winforms_unpackaged_app.exe from activating the app's main window? Temporarily skip looking for the app's main 
            // window, but still look for the expected process name to terminate.
            LaunchAndCloseUnpackagedApp(exePath, null, "winforms_unpackaged_app.exe");
            return;
        }

        [TestMethod]
        public void WindowingCppWin32Unpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Windowing\\cpp\\cpp-win32\\[BuildArch]\\[BuildConfig]\\Windowing.exe");

            // TODO: Missing WASDK 1.2 is blocking Windowing.exe from activating the app's main window? Temporarily skip looking for the app's main 
            // window, but still look for the expected process name to terminate.
            LaunchAndCloseUnpackagedApp(exePath, null, "Windowing.exe");
            return;
        }

        /**** Unpackaged sample apps ****/

        // TODO: Missing WASDK 1.2 is blocking Unpackaged.exe from activating? Skip looking for the app's main window, but still
        // look for the expected process name to terminate. Same for the next app.
        [TestMethod]
        public void UnpackagedCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Unpackaged\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\Unpackaged.exe");
            Log.Comment($"OSVersion {Environment.OSVersion.Version.Major}.{Environment.OSVersion.Version.Minor}.{Environment.OSVersion.Version.Build}");
            if ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Build == 22000))
            {
                Log.Comment("This test is currently failing on the 21h2 Enterprise Multi-Session OS image seemingly because a Welcome to MS Teams! window is on top. Doing minimal activation checking until this is resolved.");
                LaunchUnpackagedConsoleApp(exePath);
                return;
            }

            LaunchAndCloseUnpackagedApp(exePath, null, "Unpackaged.exe");
            return;
        }

        [TestMethod]
        public void UnpackagedCsConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Unpackaged\\cs-console-unpackaged\\bin\\[BuildArch]\\[BuildConfig]\\net8.0-windows10.0.19041.0\\Unpackaged.exe");
            LaunchUnpackagedConsoleApp(exePath);

            // TODO: The following stronger verification seems to work fine on a local machine but not in the Azure pipeline. Try harder to enable it.
            // LaunchAndCloseUnpackagedApp(exePath, null, "Unpackaged.exe");
            return;
        }

        /**** Notifications sample apps ****/

        [TestMethod]
        public void NotificationsPushCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Notifications\\Push\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\cpp-console-unpackaged.exe");

            // TODO: Missing WASDK 1.2 is blocking CppUnpackagedAppNotifications.exe from activating? Skip looking for the app's main window, but still
            // look for the expected process name to terminate. Same for the next app.
            LaunchAndCloseUnpackagedApp(exePath, null, "cpp-console-unpackaged.exe");
            return;
        }

        // For packaged console apps which does not put up a window, generally we verify that
        // 1) deployment of the app's package is successful,
        // 2) launch of the app by appName (appID) does not return an error,
        // 3) a process with the expected name is present,
        // 4) processes associated with the app can be terminated.
        // 5) the app's package can be successfully removed.
        // [TestMethod]
        // public void NotificationsPushCppConsolePackaged()
        // {
        //     if (IsArchX86() || IsBuildConfigDebug())
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
        //         return;
        //     }

        //     if ((Environment.OSVersion.Version.Major == 10) && ((Environment.OSVersion.Version.Build == 19044) || (Environment.OSVersion.Version.Build == 19045)))
        //     {
        //         WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "Skipping this test on LTSC 2021 (19044) and 22h2 (19045) until b#53993352 is fixed.");
        //         return;
        //     }
        //     if ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Minor == 0) && ((Environment.OSVersion.Version.Build == 17763)))
        //     {
        //         // https://task.ms/54900647 
        //         Log.Comment("This test is currently failing on the Win 10 Server 2019 OS image. Skipping this launch test to unblock exercising of the image until b#54900647 is fixed.");
        //         return;
        //     }
            
        //     RegisterAppxPackage("Notifications\\Push\\cpp-console-packaged\\cpp-console-package\\bin\\[BuildArch]\\[BuildConfig]\\AppxManifest.xml");

        //     // Upon launch, the app throws the following error message, which looks expected:
        //     //   There was an error obtaining the WNS Channel URI
        //     //   The remoteId has not been set.Refer to the readme file accompanying this sample
        //     //   for the instructions on how to obtain and setup a remote id
        //     //   Press 'Enter' at any time to exit App.
        //     //
        //     // Therefore, for this app we won't wait for a window with a specific title. Just proceed to look
        //     // for the expected process name to terminate.
        //     //
        //     // TODO: consider automating the above setup steps so that we can verify the main app window is present.
        //     LaunchAndClosePackagedApp("PushNotificationsSample_ph1m9x8skttmg!App", null, "cpp-console.exe");

        //     RemoveAppxPackage("PushNotificationsSample_1.0.0.0_[BuildArch]__ph1m9x8skttmg");
        //     return;
        // }

        /**** Other sample apps ****/

        [TestMethod]
        public void InstallerCppConsoleUnpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Installer\\cpp-console-unpackaged\\[BuildArch]\\[BuildConfig]\\LaunchInstaller.exe");
            Log.Comment($"OSVersion {Environment.OSVersion.Version.Major}.{Environment.OSVersion.Version.Minor}.{Environment.OSVersion.Version.Build}");
            if ((Environment.OSVersion.Version.Major == 10) && (Environment.OSVersion.Version.Build == 22000))
            {
                Log.Comment("This test is currently failing on the 21h2 Enterprise Multi-Session OS image seemingly because a Welcome to MS Teams! window is on top. Doing minimal activation checking until this is resolved.");
                LaunchUnpackagedConsoleApp(exePath);
                return;
            }

            LaunchAndCloseUnpackagedApp(exePath, null, "LaunchInstaller.exe");
            return;
        }

        [TestMethod]
        public void InsightsCppWin32Unpackaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Insights\\cpp-win32\\[BuildArch]\\[BuildConfig]\\Insights.exe");

            // This sample app seems to behave like a console app.
            LaunchUnpackagedConsoleApp(exePath);
            return;
        }

        [TestMethod]
        public void MicaCppWin32Packaged()
        {
            if (IsArchX86() || IsBuildConfigDebug())
            {
                WEX.Logging.Interop.Log.Result(WEX.Logging.Interop.TestResult.Skipped, "This Sample app is currently not being tested when platform=x86 or config=Debug.");
                return;
            }

            var exePath = GetFullFilePathFromRelativePath("Mica\\cpp-win32\\[BuildArch]\\[BuildConfig]\\WinAppSDKMicaSample.exe");

            // TODO: Missing WASDK 1.2 is blocking cpp-console-unpackaged.exe from activating? Skip looking for the app's main window, but still
            // look for the expected process name to terminate.
            LaunchAndCloseUnpackagedApp(exePath, null, "WinAppSDKMicaSample.exe");
            return;
        }
    }
}
