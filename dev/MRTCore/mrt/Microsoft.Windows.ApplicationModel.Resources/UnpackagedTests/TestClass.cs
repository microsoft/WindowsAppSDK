// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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
    using Microsoft.Windows.ApplicationModel.Resources;

    [TestClass]
    public class TestClass
    {
        private static string m_assemblyFolder = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
        private static string m_exeFolder = Path.GetDirectoryName(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName);
        private static bool m_rs5 = false;

        private static void FileDeleteWithRetry(String filename)
        {
            if (File.Exists(filename))
            {
                for (int i = 0; i < 10; i++)
                {
                    try
                    {
                        File.Delete(filename);
                        break;
                    }
                    catch (Exception e)
                    {
                        System.Threading.Thread.Sleep(200);
                        if (i == 9)
                        {
                            throw e;
                        }
                    }
                }
            }
        }

        private static void Cleanup()
        {
            GC.Collect(); // Force any ResourceManager objects to be cleaned up.

            FileDeleteWithRetry(Path.Combine(m_exeFolder, "resources.pri"));

            FileDeleteWithRetry(Path.Combine(m_exeFolder, "te.processhost.pri"));

            if (m_exeFolder != m_assemblyFolder)
            {
                FileDeleteWithRetry(Path.Combine(m_exeFolder, "resources.pri.standalone"));
            }
        }

        [AssemblyInitialize]
        [TestProperty("ActivationContext", "app.manifest")]
        public static void ModuleSetup(TestContext testContext)
        {
            // Clean up any left over files just in case
            FileDeleteWithRetry(Path.Combine(m_exeFolder, "resources.pri"));
            FileDeleteWithRetry(Path.Combine(m_exeFolder, "te.processhost.pri"));
            if (m_exeFolder != m_assemblyFolder)
            {
                FileDeleteWithRetry(Path.Combine(m_exeFolder, "resources.pri.standalone"));
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

            if (m_exeFolder != m_assemblyFolder)
            {
                File.Copy(Path.Combine(m_assemblyFolder, "resources.pri.standalone"), Path.Combine(m_exeFolder, "resources.pri.standalone"));
            }
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

        [TestMethod]
        public void ResourceLoader_GetStringTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceLoaderTest.GetStringTest();
        }

        [TestMethod]
        public void ResourceLoader_GetStringTest_NonDefaultNamespace()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceLoaderTest.GetStringTest_NonDefaultNamespace();
        }

        [TestMethod]
        public void ResourceLoader_GetStringForUriTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceLoaderTest.GetStringForUriTest();
        }

        [TestMethod]
        public void ResourceLoader_GetStringForUriTest_ImplicitRootNamespace()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceLoaderTest.GetStringForUriTest_ImplicitRootNamespace();
        }

        [TestMethod]
        public void ResourceLoader_GetDefaultResourceFilePathTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceLoaderTest.GetDefaultResourceFilePathTest();
        }

        [TestMethod]
        public void ResourceLoader_ReturnSameResultAsResourceManager()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceLoaderTest.ReturnSameResultAsResourceManager();
        }

        [TestMethod]
        public void ResourceManager_ValueAsStringTest_StringResource_Succeeds()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.ValueAsStringTest_StringResource_Succeeds();
        }

        [TestMethod]
        public void ResourceManager_ValueAsStringTest_FileResource_Succeeds()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.ValueAsStringTest_FileResource_Succeeds();
        }

        [TestMethod]
        public void ResourceManager_ValueAsBlobTest_Succeeds()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.ValueAsBlobTest_Succeeds();
        }

        [TestMethod]
        public void ResourceManager_GetKindTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.GetKindTest();
        }

        [TestMethod]
        public void ResourceManager_GetSubtreeTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.GetSubtreeTest();
        }

        [TestMethod]
        public void ResourceManager_TryGetSubtreeTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.TryGetSubtreeTest();
        }

        [TestMethod]
        public void ResourceManager_SubtreeNotFoundTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.SubtreeNotFoundTest();
        }

        [TestMethod]
        public void ResourceManager_ResourceNotFoundTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.ResourceNotFoundTest();
        }

        [TestMethod]
        public void ResourceManager_NoResourceFileTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.NoResourceFileTest();
        }

        [TestMethod]
        public void ResourceManager_ResourceEnumTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.ResourceEnumTest();
        }

        [TestMethod]
        public void ResourceManager_GetValueFullUriTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.GetValueFullUriTest();
        }

        [TestMethod]
        public void ResourceManager_GetSubtreeFullUriTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceManagerTest.GetSubtreeFullUriTest();
        }

        [TestMethod]
        public void ResourceContext_LanguageContextTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceContextTest.LanguageContextTest();
        }

        [TestMethod]
        public void ResourceContext_NonLanguageContextTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceContextTest.NonLanguageContextTest();
        }

        [TestMethod]
        public void ResourceContext_ResourceEnumWithContextTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceContextTest.ResourceEnumWithContextTest();
        }

        [TestMethod]
        public void ResourceContext_ResourceNotFoundWithContextTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceContextTest.ResourceNotFoundWithContextTest();
        }

        [TestMethod]
        public void ResourceContext_NoResourceFileWithContextTest()
        {
            if (m_rs5)
            {
                // Test doesn't run before 19H1. Make it pass as skipped is treated as failure in Helix.
                return;
            }

            CommonTestCode.ResourceContextTest.NoResourceFileWithContextTest();
        }
    }
}