// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.ApplicationModel.Resources;

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
