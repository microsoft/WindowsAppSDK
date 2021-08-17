// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace MrtCoreUnpackagedTests
{
    using System;
    using System.ComponentModel;
    using System.Data;
    using System.IO;
    using System.Reflection;
    using System.Runtime.InteropServices;
    using System.Security;
    using WEX.Common.Managed;
    using WEX.Logging.Interop;
    using WEX.TestExecution;
    using WEX.TestExecution.Markup;
    using Microsoft.ApplicationModel.Resources;

    #region Helper class for WinRT activation
    internal class ActivationContext : IDisposable
    {
        private IntPtr m_cookie = (IntPtr)0;
        private IntPtr m_ctx = (IntPtr)0;
        private bool m_activated = false;

        public ActivationContext()
        {
            Activate();
        }

        public void Activate()
        {
            if (!m_activated)
            {
                string assemblyPath = Assembly.GetExecutingAssembly().Location;
                ActivateContext(Path.Combine(Path.GetDirectoryName(assemblyPath), "app.manifest"));
                m_activated = true;
            }
        }

        public void Dispose()
        {
            if (m_activated)
            {
                NativeMethods.DeactivateActCtx(0, m_cookie);
                NativeMethods.ReleaseActCtx(m_ctx);
                m_cookie = (IntPtr)0;
                m_ctx = (IntPtr)0;
                m_activated = false;
            }
        }

        private void ActivateContext(string manifestPath)
        {
            var context = new NativeMethods.ACTCTX();
            context.cbSize = (uint)Marshal.SizeOf(typeof(NativeMethods.ACTCTX));
            context.lpSource = manifestPath;

            m_ctx = NativeMethods.CreateActCtx(ref context);
            if (m_ctx == (IntPtr)(-1))
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }

            if (!NativeMethods.ActivateActCtx(m_ctx, out m_cookie))
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }
    }

    [SuppressUnmanagedCodeSecurity]
    internal static class NativeMethods
    {
        [DllImport("kernel32.dll", SetLastError = true, EntryPoint = "CreateActCtxW")]
        internal static extern IntPtr CreateActCtx(ref ACTCTX pActctx);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool ActivateActCtx(IntPtr hActCtx, out IntPtr lpCookie);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool DeactivateActCtx(int dwFlags, IntPtr ulCookie);

        [DllImport("kernel32.dll")]
        internal static extern void ReleaseActCtx(IntPtr hActCtx);

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal struct ACTCTX
        {
            public UInt32 cbSize;
            public UInt32 dwFlags;
            public string lpSource;
            public UInt16 wProcessorArchitecture;
            public UInt16 wLangId;
            public string lpAssemblyDirectory;
            public string lpResourceName;
            public string lpApplicationName;
            public IntPtr hModule;
        }
    }
    #endregion

    [TestClass]
    public class TestClass
    {
        private ActivationContext m_context = new ActivationContext();
        private static string m_assemblyFolder = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
        private static string m_exeFolder = Path.GetDirectoryName(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName);
        private static bool m_rs5 = false;

        private static void Cleanup()
        {
            GC.Collect(); // Force any ResourceManager objects to be cleaned up.

            if (File.Exists(Path.Combine(m_exeFolder, "resources.pri")))
            {
                File.Delete(Path.Combine(m_exeFolder, "resources.pri"));
            }
            if (File.Exists(Path.Combine(m_exeFolder, "te.processhost.pri")))
            {
                File.Delete(Path.Combine(m_exeFolder, "te.processhost.pri"));
            }
            if (m_exeFolder != m_assemblyFolder)
            {
                if (File.Exists(Path.Combine(m_exeFolder, "resources.pri.standalone")))
                {
                    File.Delete(Path.Combine(m_exeFolder, "resources.pri.standalone"));
                }
            }
        }

        [AssemblyInitialize]
        public static void ModuleSetup(TestContext testContext)
        {
            // Clean up any left over files just in case
            File.Delete(Path.Combine(m_exeFolder, "resources.pri"));
            File.Delete(Path.Combine(m_exeFolder, "te.processhost.pri"));
            if (m_exeFolder != m_assemblyFolder)
            {
                File.Delete(Path.Combine(m_exeFolder, "resources.pri.standalone"));
            }
            m_rs5 = (System.Environment.OSVersion.Version.Build < 18362);
        }

        [AssemblyCleanup]
        public static void ModuleCleanup()
        {
            Cleanup();
        }

        [TestInitialize]
        public static void TestSetup()
        {
            Cleanup();
        }

        [TestCleanup]
        public static void TestCleanup()
        { 
            // There is random ACCESS_DENIED error during cleanup running in Helix.
            // Move cleanup to TestSetup and ModuleCleanup.
        }

        private void DefaultResourceManagerImpl()
        {
            var resourceManager = new ResourceManager();
            var resourceMap = resourceManager.MainResourceMap;
            var map = resourceMap.GetSubtree("resources");

            // No resource file is loaded
            Verify.AreEqual(map.ResourceCount, 0u);
            var ex = Verify.Throws<Exception>(() => map.GetValue("IDS_MANIFEST_MUSIC_APP_NAME"));
            Verify.AreEqual((uint)ex.HResult, 0x80070490); // HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
        }

        [TestMethod]
        public void DefaultResourceManager()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            DefaultResourceManagerImpl();
        }

        private void DefaultResourceManagerWithResourcePriImpl()
        {
            File.Copy(Path.Combine(m_assemblyFolder, "resources.pri.standalone"), Path.Combine(m_exeFolder, "resources.pri"));

            var resourceManager = new ResourceManager();
            var resourceMap = resourceManager.MainResourceMap;
            var map = resourceMap.GetSubtree("resources");
            Verify.AreNotEqual(map.ResourceCount, 0u);
            var resource = map.GetValue("IDS_MANIFEST_MUSIC_APP_NAME").ValueAsString;
            Verify.AreEqual(resource, "Groove Music");
        }

        [TestMethod]
        public void DefaultResourceManagerWithResourcePri()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            DefaultResourceManagerWithResourcePriImpl();
        }

        private void DefaultResourceManagerWithExePriImpl()
        {
            File.Copy(Path.Combine(m_assemblyFolder, "resources.pri.standalone"), Path.Combine(m_exeFolder, "te.processhost.pri"));

            var resourceManager = new ResourceManager();
            var resourceMap = resourceManager.MainResourceMap;
            var map = resourceMap.GetSubtree("resources");
            Verify.AreNotEqual(map.ResourceCount, 0u);
            var resource = map.GetValue("IDS_MANIFEST_MUSIC_APP_NAME").ValueAsString;
            Verify.AreEqual(resource, "Groove Music");
        }

        [TestMethod]
        public void DefaultResourceManagerWithExePri()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            DefaultResourceManagerWithExePriImpl();
        }

        private void ResourceManagerWithFileImpl()
        {
            if (m_exeFolder != m_assemblyFolder)
            {
                File.Copy(Path.Combine(m_assemblyFolder, "resources.pri.standalone"), Path.Combine(m_exeFolder, "resources.pri.standalone"));
            }

            var resourceManager = new ResourceManager("resources.pri.standalone");
            var resourceMap = resourceManager.MainResourceMap;
            var map = resourceMap.GetSubtree("resources");
            Verify.AreNotEqual(map.ResourceCount, 0u);
            var resource = map.GetValue("IDS_MANIFEST_MUSIC_APP_NAME").ValueAsString;
            Verify.AreEqual(resource, "Groove Music");
        }

        [TestMethod]
        public void ResourceManagerWithFile()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            ResourceManagerWithFileImpl();
        }
    }
}