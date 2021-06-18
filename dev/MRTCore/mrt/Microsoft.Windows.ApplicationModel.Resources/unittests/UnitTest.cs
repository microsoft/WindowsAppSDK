// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.Windows.ApplicationModel.Resources;

namespace ManagedTest
{
    [TestClass]
    public class ResourceLoaderTest
    {
        [TestMethod]
        public void GetStringTest()
        {
            var resourceLoader = new ResourceLoader("resources.pri.standalone");
            var resource = resourceLoader.GetString("IDS_MANIFEST_MUSIC_APP_NAME");
            Assert.AreEqual(resource, "Groove Music");
        }

        [TestMethod]
        public void GetStringTest_NonDefaultNamespace()
        {
            var resourceLoader = new ResourceLoader("resources.pri.standalone", "Microsoft.UI.Xaml/Resources");
            var resource = resourceLoader.GetString("HelpTextMoreButton");
            Assert.AreEqual(resource, "Invoke to show or hide the text entry fields.");
        }

        [TestMethod]
        public void GetStringForUriTest()
        {
            var resourceLoader = new ResourceLoader("resources.pri.standalone");
            var resource = resourceLoader.GetStringForUri(new Uri("ms-resource://Microsoft.ZuneMusic/resources/IDS_MANIFEST_MUSIC_APP_NAME"));
            Assert.AreEqual(resource, "Groove Music");
        }

        [TestMethod]
        public void GetStringForUriTest_ImplicitRootNamespace()
        {
            var resourceLoader = new ResourceLoader("resources.pri.standalone");
            var resource = resourceLoader.GetStringForUri(new Uri("ms-resource:///resources/IDS_MANIFEST_MUSIC_APP_NAME"));
            Assert.AreEqual(resource, "Groove Music");
        }

        [TestMethod]
        public void GetDefaultResourceFilePathTest()
        {
            var filepath = ResourceLoader.GetDefaultResourceFilePath();
            Assert.AreNotEqual(filepath.IndexOf("resources.pri"), -1);
        }
    }

    [TestClass]
    public class ResourceManagerTest
    {
        [TestMethod]
        public void ValueAsStringTest_StringResource_Succeeds()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var stringResourceCandidate = resourceManager.MainResourceMap.GetValue("resources/IDS_MANIFEST_MUSIC_APP_NAME");
            Assert.AreEqual(stringResourceCandidate.ValueAsString, "Groove Music");
            var ex = Assert.ThrowsException<Exception>(() => stringResourceCandidate.ValueAsBytes);
            Assert.AreEqual((uint)ex.HResult, 0x80073b0d); // HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH)
            stringResourceCandidate = resourceManager.MainResourceMap.TryGetValue("resources/IDS_MANIFEST_MUSIC_APP_NAME");
            Assert.AreEqual(stringResourceCandidate.ValueAsString, "Groove Music");
        }

        [TestMethod]
        public void ValueAsStringTest_FileResource_Succeeds()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var fileResourceCandidate = resourceManager.MainResourceMap.GetValue("Files/Assets/AppList.png");
            var fileResourceString = fileResourceCandidate.ValueAsString;
            Assert.AreNotEqual(fileResourceString.IndexOf(@"\AppList."), -1);
            fileResourceString = resourceManager.MainResourceMap.TryGetValue("Files/Assets/AppList.png").ValueAsString;
            Assert.AreNotEqual(fileResourceString.IndexOf(@"\AppList."), -1);
        }

        [TestMethod]
        public void ValueAsBlobTest_Succeeds()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var resourceCandidate = resourceManager.MainResourceMap.GetValue("Files/Controls/AlbumBasicInfoControl.xbf");
            var resourceData = resourceCandidate.ValueAsBytes;
            Assert.AreEqual(resourceData.Length, 15002);
            var ex = Assert.ThrowsException<Exception>(() => resourceCandidate.ValueAsString);
            Assert.AreEqual((uint)ex.HResult, 0x80073b0d); // HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH)
            resourceData = resourceManager.MainResourceMap.TryGetValue("Files/Controls/AlbumBasicInfoControl.xbf").ValueAsBytes;
            Assert.AreEqual(resourceData.Length, 15002);
        }

        [TestMethod]
        public void GetKindTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");

            var stringResourceCandidate = resourceManager.MainResourceMap.GetValue("resources/IDS_MANIFEST_MUSIC_APP_NAME");
            Assert.AreEqual(stringResourceCandidate.Kind, ResourceCandidateKind.String);
            stringResourceCandidate = resourceManager.MainResourceMap.TryGetValue("resources/IDS_MANIFEST_MUSIC_APP_NAME");
            Assert.AreEqual(stringResourceCandidate.Kind, ResourceCandidateKind.String);

            var fileResourceCandidate = resourceManager.MainResourceMap.GetValue("Files/Assets/AppList.png");
            Assert.AreEqual(fileResourceCandidate.Kind, ResourceCandidateKind.FilePath);
            fileResourceCandidate = resourceManager.MainResourceMap.TryGetValue("Files/Assets/AppList.png");
            Assert.AreEqual(fileResourceCandidate.Kind, ResourceCandidateKind.FilePath);

            var blobResourceCandidate = resourceManager.MainResourceMap.GetValue("Files/Controls/AlbumBasicInfoControl.xbf");
            Assert.AreEqual(blobResourceCandidate.Kind, ResourceCandidateKind.EmbeddedData);
            blobResourceCandidate = resourceManager.MainResourceMap.TryGetValue("Files/Controls/AlbumBasicInfoControl.xbf");
            Assert.AreEqual(blobResourceCandidate.Kind, ResourceCandidateKind.EmbeddedData);
        }

        [TestMethod]
        public void GetSubtreeTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var resourceMap = resourceManager.MainResourceMap.GetSubtree("resources");
            var resourceCandidate = resourceMap.GetValue("IDS_MANIFEST_MUSIC_APP_NAME");
            var resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "Groove Music");

            var ex = Assert.ThrowsException<Exception>(() => resourceMap.GetValue("abc"));
            Assert.AreEqual((uint)ex.HResult, 0x80073b17); // HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND)
            resourceCandidate = resourceMap.TryGetValue("abc");
            Assert.IsNull(resourceCandidate);
        }

        [TestMethod]
        public void ResourceNotFoundTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            resourceManager.ResourceNotFound += (sender, args) =>
            {
                if (args.Name == "abc")
                {
                    var candidate = new ResourceCandidate(ResourceCandidateKind.String, "abcValue");
                    args.SetResolvedCandidate(candidate);
                }
            };
            var resourceMap = resourceManager.MainResourceMap.GetSubtree("resources");
            var resourceCandidate = resourceMap.GetValue("abc");
            var resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "abcValue");
            resource = resourceMap.TryGetValue("abc").ValueAsString;
            Assert.AreEqual(resource, "abcValue");

            var ex = Assert.ThrowsException<Exception>(() => resourceMap.GetValue("xyz"));
            Assert.AreEqual((uint)ex.HResult, 0x80073b17); // HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND)
            resourceCandidate = resourceMap.TryGetValue("xyz");
            Assert.IsNull(resourceCandidate);
        }

        [TestMethod]
        public void DefaultResourceManagerTest()
        {
            var resourceManager = new ResourceManager();
            var resourceMap = resourceManager.MainResourceMap;
            var resourceChildMap = resourceMap.GetSubtree("Files");
            var resourceChildChildMap = resourceChildMap.GetSubtree("Assets");
            var resourceCandidate = resourceChildChildMap.GetValue("LockScreenLogo.png");
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.FilePath);
            Assert.AreNotEqual(resourceCandidate.ValueAsString.IndexOf(@"Assets\LockScreenLogo.scale-200.png"), -1);
            resourceCandidate = resourceChildChildMap.TryGetValue("LockScreenLogo.png");
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.FilePath);
            Assert.AreNotEqual(resourceCandidate.ValueAsString.IndexOf(@"Assets\LockScreenLogo.scale-200.png"), -1);
        }

        [TestMethod]
        public void NoResourceFileTest()
        {
            var resourceManager = new ResourceManager("NoSuchFile.pri");
            var resourceMap = resourceManager.MainResourceMap;
            var resourceChildMap = resourceMap.GetSubtree("anyname");
            var resourceContext = resourceManager.CreateResourceContext();
            Assert.IsTrue(resourceContext.QualifierValues.ContainsKey(KnownResourceQualifierName.Language));

            // No resource file, and not handled by fallback 
            var ex = Assert.ThrowsException<Exception>(() => resourceMap.GetValue("abc"));
            Assert.AreEqual((uint)ex.HResult, 0x80070490); // HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
            var resourceCandidate = resourceMap.TryGetValue("abc");
            Assert.IsNull(resourceCandidate);

            // add fallback handler
            resourceManager.ResourceNotFound += (sender, args) =>
            {
                if (args.Name == "abc")
                {
                    var candidate = new ResourceCandidate(ResourceCandidateKind.String, "abcValue");
                    args.SetResolvedCandidate(candidate);
                }
            };

            resourceCandidate = resourceMap.GetValue("abc");
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(resourceCandidate.ValueAsString, "abcValue");

            resourceCandidate = resourceMap.TryGetValue("abc");
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(resourceCandidate.ValueAsString, "abcValue");

            ex = Assert.ThrowsException<Exception>(() => resourceMap.GetValue("xyz"));
            Assert.AreEqual((uint)ex.HResult, 0x80070490); // HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
            resourceCandidate = resourceMap.TryGetValue("xyz");
            Assert.IsNull(resourceCandidate);
        }

        [TestMethod]
        public void ResourceEnumTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var resourceMapXaml = resourceManager.MainResourceMap.GetSubtree("Microsoft.UI.Xaml");
            var resourceMapResources = resourceMapXaml.GetSubtree("Resources");

            var count = resourceMapResources.ResourceCount;
            Assert.AreEqual(count, 78u);

            // first resource under the resource map
            var value = resourceMapResources.GetValueByIndex(0);
            Assert.AreEqual(value.Key, "AutomationNameAlphaSlider");
            var candidate = value.Value;
            Assert.AreEqual(candidate.ValueAsString, "Opacity");
            Assert.AreEqual(candidate.Kind, ResourceCandidateKind.String);

            // last resource under the resource map
            value = resourceMapResources.GetValueByIndex(77);
            Assert.AreEqual(value.Key, "ValueStringValueSliderWithoutColorName");
            candidate = value.Value;
            Assert.AreEqual(candidate.ValueAsString, "%1!u!");
            Assert.AreEqual(candidate.Kind, ResourceCandidateKind.String);
        }
    }

    [TestClass]
    public class ResourceContextTest
    {
        [TestMethod]
        public void LanguageContextTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var resourceContext = resourceManager.CreateResourceContext();
            var qualifierValues = resourceContext.QualifierValues;

            var resourceCandidate = resourceManager.MainResourceMap.GetValue("resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", resourceContext);
            var resource = resourceCandidate.ValueAsString;
            if ((qualifierValues[KnownResourceQualifierName.Language].IndexOf("en-US") != -1) || (qualifierValues[KnownResourceQualifierName.Language].IndexOf("en") == -1))
            {
                // en-US or non-en which will match default
                Assert.AreEqual(resource, "Equalizer");
            }

            Assert.AreEqual(qualifierValues[KnownResourceQualifierName.Scale], "");

            qualifierValues[KnownResourceQualifierName.Language] = "en-GB";
            resourceCandidate = resourceManager.MainResourceMap.GetValue("resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", resourceContext);
            resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "Equaliser");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "EN-GB");
            Assert.IsFalse(resourceCandidate.QualifierValues.ContainsKey(KnownResourceQualifierName.Scale));

            resourceCandidate = resourceManager.MainResourceMap.TryGetValue("resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", resourceContext);
            resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "Equaliser");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "EN-GB");
            Assert.IsFalse(resourceCandidate.QualifierValues.ContainsKey(KnownResourceQualifierName.Scale));

            qualifierValues[KnownResourceQualifierName.Language] = "en-AU";
            resourceCandidate = resourceManager.MainResourceMap.GetValue("resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", resourceContext);
            resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "Equaliser");
            // Candidate for en-GB is selected
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "EN-GB");
        }

        [TestMethod]
        public void NonLanguageContextTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var resourceContext = resourceManager.CreateResourceContext();
            Assert.AreEqual(resourceContext.QualifierValues[KnownResourceQualifierName.Contrast], "");
            Assert.AreEqual(resourceContext.QualifierValues[KnownResourceQualifierName.TargetSize], "");
            Assert.AreEqual(resourceContext.QualifierValues["AlternateForm"], "");

            resourceContext.QualifierValues[KnownResourceQualifierName.Contrast] = "White";
            resourceContext.QualifierValues[KnownResourceQualifierName.TargetSize] = "96";
            var resourceCandidate = resourceManager.MainResourceMap.GetValue("Files/Assets/AppList.png", resourceContext);
            var resource = resourceCandidate.ValueAsString;
            Assert.AreNotEqual(resource.IndexOf(@"Assets\contrast-white\AppList.targetsize-96_contrast-white.png"), -1);
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Contrast], "WHITE");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.TargetSize], "96");

            resourceContext.QualifierValues[KnownResourceQualifierName.Contrast] = "Black";
            resourceContext.QualifierValues[KnownResourceQualifierName.TargetSize] = "72";
            resourceContext.QualifierValues["AlternateForm"] = "UNPLATED";
            resourceCandidate = resourceManager.MainResourceMap.GetValue("Files/Assets/AppList.png", resourceContext);
            resource = resourceCandidate.ValueAsString;
            Assert.AreNotEqual(resource.IndexOf(@"Assets\contrast-black\AppList.targetsize-72_altform-unplated_contrast-black.png"), -1);
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Contrast], "BLACK");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.TargetSize], "72");
            Assert.AreEqual(resourceCandidate.QualifierValues["AlternateForm"], "UNPLATED");
        }

        [TestMethod]
        public void ResourceEnumWithContextTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var resourceMap = resourceManager.MainResourceMap.GetSubtree("Resources");
            var resourceContext = resourceManager.CreateResourceContext();

            var count = resourceMap.ResourceCount;
            Assert.AreEqual(count, 1269u);

            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "en-US";

            // first resource under the resource map
            var value = resourceMap.GetValueByIndex(0, resourceContext);
            Assert.AreEqual(value.Key, "000D1359");
            var candidate = value.Value;
            Assert.AreEqual(candidate.ValueAsString, "This song is available only when you buy the whole album.");
            Assert.AreEqual(candidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(candidate.QualifierValues[KnownResourceQualifierName.Language], "EN-US");

            // second to last resource under the resource map
            value = resourceMap.GetValueByIndex(1267, resourceContext);
            Assert.AreEqual(value.Key, "IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE");
            candidate = value.Value;
            Assert.AreEqual(candidate.ValueAsString, "Equalizer");
            Assert.AreEqual(candidate.Kind, ResourceCandidateKind.String);

            // Change language context
            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "en-GB";

            // first resource under the resource map
            value = resourceMap.GetValueByIndex(0, resourceContext);
            Assert.AreEqual(value.Key, "000D1359");
            candidate = value.Value;
            Assert.AreEqual(candidate.ValueAsString, "This song is available only when you buy the whole album.");
            Assert.AreEqual(candidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(candidate.QualifierValues[KnownResourceQualifierName.Language], "EN-GB");

            // second to last resource under the resource map
            value = resourceMap.GetValueByIndex(1267, resourceContext);
            Assert.AreEqual(value.Key, "IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE");
            candidate = value.Value;
            Assert.AreEqual(candidate.ValueAsString, "Equaliser");
            Assert.AreEqual(candidate.Kind, ResourceCandidateKind.String);
        }

        [TestMethod]
        public void ResourceNotFoundWithContextTest()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            resourceManager.ResourceNotFound += (sender, args) =>
            {
                if (args.Name == "abc")
                {
                    String value;
                    if (args.Context.QualifierValues[KnownResourceQualifierName.Language].StartsWith("en-US"))
                    {
                        value = "USValue";
                    }
                    else if (args.Context.QualifierValues[KnownResourceQualifierName.Language].StartsWith("en-GB"))
                    {
                        value = "GBValue";
                    }
                    else
                    {
                        value = "OtherValue";
                    }
                    var candidate = new ResourceCandidate(ResourceCandidateKind.String, value);
                    args.SetResolvedCandidate(candidate);
                }
            };

            var resourceContext = resourceManager.CreateResourceContext();
            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "en-US";
            var resourceMap = resourceManager.MainResourceMap.GetSubtree("resources");
            var resourceCandidate = resourceMap.GetValue("abc", resourceContext);
            var resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "USValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "en-US");

            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "en-GB";
            resourceCandidate = resourceMap.GetValue("abc", resourceContext);
            resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "GBValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "en-GB");

            resourceCandidate = resourceMap.TryGetValue("abc", resourceContext);
            resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "GBValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "en-GB");

            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "fr-FR";
            resourceCandidate = resourceMap.GetValue("abc", resourceContext);
            resource = resourceCandidate.ValueAsString;
            Assert.AreEqual(resource, "OtherValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "fr-FR");

            var ex = Assert.ThrowsException<Exception>(() => resourceMap.GetValue("xyz", resourceContext));
            Assert.AreEqual((uint)ex.HResult, 0x80073b17); // HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND)

            resourceCandidate = resourceMap.TryGetValue("xyz", resourceContext);
            Assert.IsNull(resourceCandidate);
        }

        [TestMethod]
        public void NoResourceFileWithContextTest()
        {
            var resourceManager = new ResourceManager("NoSuchFile.pri");
            var resourceMap = resourceManager.MainResourceMap;
            var resourceChildMap = resourceMap.GetSubtree("anyname");
            var resourceContext = resourceManager.CreateResourceContext();
            Assert.IsTrue(resourceContext.QualifierValues.ContainsKey(KnownResourceQualifierName.Language));

            // No resource file, and not handled by fallback 
            var ex = Assert.ThrowsException<Exception>(() => resourceMap.GetValue("abc"));
            Assert.AreEqual((uint)ex.HResult, 0x80070490); // HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
            var resourceCandidate = resourceMap.TryGetValue("abc");
            Assert.IsNull(resourceCandidate);

            // add fallback handler
            resourceManager.ResourceNotFound += (sender, args) =>
            {
                if (args.Name == "abc")
                {
                    String value;
                    if (args.Context.QualifierValues.ContainsKey(KnownResourceQualifierName.Language))
                    {
                        if (args.Context.QualifierValues[KnownResourceQualifierName.Language].StartsWith("en-US"))
                        {
                            value = "USValue";
                        }
                        else if (args.Context.QualifierValues[KnownResourceQualifierName.Language].StartsWith("en-GB"))
                        {
                            value = "GBValue";
                        }
                        else
                        {
                            value = "OtherValue";
                        }
                    }
                    else
                    {
                        value = "UnknownValue";
                    }
                    var candidate = new ResourceCandidate(ResourceCandidateKind.String, value);
                    args.SetResolvedCandidate(candidate);
                }
            };

            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "en-US";
            resourceCandidate = resourceMap.GetValue("abc", resourceContext);
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(resourceCandidate.ValueAsString, "USValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "en-US");

            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "en-GB";
            resourceCandidate = resourceMap.GetValue("abc", resourceContext);
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(resourceCandidate.ValueAsString, "GBValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "en-GB");

            resourceContext.QualifierValues[KnownResourceQualifierName.Language] = "fr-FR";
            resourceCandidate = resourceMap.GetValue("abc", resourceContext);
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(resourceCandidate.ValueAsString, "OtherValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "fr-FR");

            resourceCandidate = resourceMap.TryGetValue("abc", resourceContext);
            Assert.AreEqual(resourceCandidate.Kind, ResourceCandidateKind.String);
            Assert.AreEqual(resourceCandidate.ValueAsString, "OtherValue");
            Assert.AreEqual(resourceCandidate.QualifierValues[KnownResourceQualifierName.Language], "fr-FR");

            ex = Assert.ThrowsException<Exception>(() => resourceMap.GetValue("xyz", resourceContext));
            Assert.AreEqual((uint)ex.HResult, 0x80070490); // HRESULT_FROM_WIN32(ERROR_NOT_FOUND)

            resourceCandidate = resourceMap.TryGetValue("xyz", resourceContext);
            Assert.IsNull(resourceCandidate);
        }
    }
}
