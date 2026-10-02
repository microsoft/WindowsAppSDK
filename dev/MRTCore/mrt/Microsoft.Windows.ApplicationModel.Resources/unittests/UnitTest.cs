// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using Microsoft.Windows.ApplicationModel.Resources;
using WEX.Common.Managed;
using WEX.Logging.Interop;
using WEX.TestExecution;
using WEX.TestExecution.Markup;

namespace ManagedTest
{
    [TestClass]
    public class ResourceLoaderTest
    {
        [TestMethod]
        public void GetStringTest()
        {
            CommonTestCode.ResourceLoaderTest.GetStringTest();
        }

        [TestMethod]
        public void GetStringTest_NonDefaultNamespace()
        {
            CommonTestCode.ResourceLoaderTest.GetStringTest_NonDefaultNamespace();
        }

        [TestMethod]
        public void GetStringForUriTest()
        {
            CommonTestCode.ResourceLoaderTest.GetStringForUriTest();
        }

        [TestMethod]
        public void GetStringForUriTest_ImplicitRootNamespace()
        {
            CommonTestCode.ResourceLoaderTest.GetStringForUriTest_ImplicitRootNamespace();
        }

        [TestMethod]
        public void GetDefaultResourceFilePathTest()
        {
            CommonTestCode.ResourceLoaderTest.GetDefaultResourceFilePathTest();
        }

        [TestMethod]
        public void ReturnSameResultAsResourceManager()
        {
            CommonTestCode.ResourceLoaderTest.ReturnSameResultAsResourceManager();
        }
    }

    [TestClass]
    public class ResourceManagerTest
    {
        [TestMethod]
        public void ValueAsStringTest_StringResource_Succeeds()
        {
            CommonTestCode.ResourceManagerTest.ValueAsStringTest_StringResource_Succeeds();
        }

        [TestMethod]
        public void ValueAsStringTest_FileResource_Succeeds()
        {
            CommonTestCode.ResourceManagerTest.ValueAsStringTest_FileResource_Succeeds();
        }

        [TestMethod]
        public void ValueAsBlobTest_Succeeds()
        {
            CommonTestCode.ResourceManagerTest.ValueAsBlobTest_Succeeds();
        }

        [TestMethod]
        public void GetKindTest()
        {
            CommonTestCode.ResourceManagerTest.GetKindTest();
        }

        [TestMethod]
        public void GetSubtreeTest()
        {
            CommonTestCode.ResourceManagerTest.GetSubtreeTest();
        }

        [TestMethod]
        public void TryGetSubtreeTest()
        {
            CommonTestCode.ResourceManagerTest.TryGetSubtreeTest();
        }

        [TestMethod]
        public void SubtreeNotFoundTest()
        {
            CommonTestCode.ResourceManagerTest.SubtreeNotFoundTest();
        }

        [TestMethod]
        public void ResourceNotFoundTest()
        {
            CommonTestCode.ResourceManagerTest.ResourceNotFoundTest();
        }

        [TestMethod]
        public void DefaultResourceManagerTest()
        {
            CommonTestCode.ResourceManagerTest.DefaultResourceManagerTest();
        }

        [TestMethod]
        public void NoResourceFileTest()
        {
            CommonTestCode.ResourceManagerTest.NoResourceFileTest();
         }

        [TestMethod]
        public void ResourceEnumTest()
        {
            CommonTestCode.ResourceManagerTest.ResourceEnumTest();
        }

        [TestMethod]
        public void GetValueFullUriTest()
        {
            CommonTestCode.ResourceManagerTest.GetValueFullUriTest();
        }

        [TestMethod]
        public void GetSubtreeFullUriTest()
        {
            CommonTestCode.ResourceManagerTest.GetSubtreeFullUriTest();
        }
    }

    [TestClass]
    public class ResourceContextTest
    {
        [TestMethod]
        public void LanguageContextTest()
        {
            CommonTestCode.ResourceContextTest.LanguageContextTest();
        }

        [TestMethod]
        public void NonLanguageContextTest()
        {
            CommonTestCode.ResourceContextTest.NonLanguageContextTest();
        }

        [TestMethod]
        public void ResourceEnumWithContextTest()
        {
            CommonTestCode.ResourceContextTest.ResourceEnumWithContextTest();
        }

        [TestMethod]
        public void ResourceNotFoundWithContextTest()
        {
            CommonTestCode.ResourceContextTest.ResourceNotFoundWithContextTest();
        }

        [TestMethod]
        public void NoResourceFileWithContextTest()
        {
            CommonTestCode.ResourceContextTest.NoResourceFileWithContextTest();
        }
    }
}
