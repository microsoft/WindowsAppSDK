// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;
using System.Reflection;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using WindowsAppSDK.TemplateUtilities;
using WindowsAppSDK.VSIX.UnitTests.TestHelpers;

namespace WindowsAppSDK.VSIX.UnitTests
{
    /// <summary>
    /// Tests for error message construction in NuGetPackageInstaller.
    /// Focuses on CreateErrorMessage and CreateDetailedErrorMessage private methods.
    /// </summary>
    [TestClass]
    public class ErrorMessageTests : VsTestBase
    {
        #region CreateErrorMessage Tests

        [TestMethod]
        public void CreateErrorMessage_InfoBar_SinglePackage_ContainsProjectAndPackageName()
        {
            // Arrange
            var wizard = CreateWizardWithFailedPackages(
                "TestProject",
                new Dictionary<string, Exception>
                {
                    { "Microsoft.WindowsAppSDK", new Exception("Not found") }
                });

            // Act
            var message = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateErrorMessage", ErrorMessageFormat.InfoBar);

            // Assert
            Assert.IsNotNull(message);
            Assert.IsTrue(message.Contains("TestProject"),
                "InfoBar error message should contain the project name.");
            Assert.IsTrue(message.Contains("Microsoft.WindowsAppSDK"),
                "InfoBar error message should contain the failed package name.");
        }

        [TestMethod]
        public void CreateErrorMessage_InfoBar_MultiplePackages_ContainsAllPackageNames()
        {
            // Arrange
            var wizard = CreateWizardWithFailedPackages(
                "MultiPkgProject",
                new Dictionary<string, Exception>
                {
                    { "Microsoft.WindowsAppSDK", new Exception("Error 1") },
                    { "Microsoft.Windows.SDK.BuildTools", new Exception("Error 2") }
                });

            // Act
            var message = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateErrorMessage", ErrorMessageFormat.InfoBar);

            // Assert
            Assert.IsTrue(message.Contains("Microsoft.WindowsAppSDK"));
            Assert.IsTrue(message.Contains("Microsoft.Windows.SDK.BuildTools"));
            Assert.IsTrue(message.Contains("MultiPkgProject"));
        }

        [TestMethod]
        public void CreateErrorMessage_MessageBox_ContainsProjectAndPackageName()
        {
            // Arrange
            var wizard = CreateWizardWithFailedPackages(
                "CppTestProject",
                new Dictionary<string, Exception>
                {
                    { "Microsoft.WindowsAppSDK", new Exception("Source error") }
                });

            // Act
            var message = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateErrorMessage", ErrorMessageFormat.MessageBox);

            // Assert
            Assert.IsNotNull(message);
            Assert.IsTrue(message.Contains("CppTestProject"),
                "MessageBox error message should contain the project name.");
            Assert.IsTrue(message.Contains("Microsoft.WindowsAppSDK"),
                "MessageBox error message should contain the failed package name.");
        }

        [TestMethod]
        public void CreateErrorMessage_InfoBarVsMessageBox_ProduceDifferentFormats()
        {
            // Arrange
            var wizard = CreateWizardWithFailedPackages(
                "FormatProject",
                new Dictionary<string, Exception>
                {
                    { "SomePackage", new Exception("Error") }
                });

            // Act
            var infoBarMessage = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateErrorMessage", ErrorMessageFormat.InfoBar);
            var messageBoxMessage = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateErrorMessage", ErrorMessageFormat.MessageBox);

            // Assert — the two formats should be different
            Assert.AreNotEqual(infoBarMessage, messageBoxMessage,
                "InfoBar and MessageBox formats should produce different messages.");
        }

        [TestMethod]
        public void CreateErrorMessage_NullProject_UsesUnknownProjectFallback()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            MockServiceSetup.SetPrivateField(wizard, "_project", null);

            var failedPackages = new Dictionary<string, Exception>
            {
                { "SomePackage", new Exception("Error") }
            };
            MockServiceSetup.SetPrivateField(wizard, "_failedPackageExceptions", failedPackages);

            // Act
            var message = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateErrorMessage", ErrorMessageFormat.InfoBar);

            // Assert — should use fallback name, not throw
            Assert.IsNotNull(message);
            Assert.IsTrue(message.Contains("SomePackage"));
        }

        #endregion

        #region CreateDetailedErrorMessage Tests

        [TestMethod]
        public void CreateDetailedErrorMessage_IncludesExceptionTypeAndMessage()
        {
            // Arrange
            var wizard = CreateWizardWithFailedPackages(
                "DetailedProject",
                new Dictionary<string, Exception>
                {
                    { "Microsoft.WindowsAppSDK", new InvalidOperationException("Package already installed") }
                });

            // Act
            var message = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateDetailedErrorMessage");

            // Assert
            Assert.IsTrue(message.Contains("DetailedProject"),
                "Detailed error should contain project name.");
            Assert.IsTrue(message.Contains("Microsoft.WindowsAppSDK"),
                "Detailed error should contain package name.");
            Assert.IsTrue(message.Contains("InvalidOperationException"),
                "Detailed error should contain exception type.");
            Assert.IsTrue(message.Contains("Package already installed"),
                "Detailed error should contain exception message.");
        }

        [TestMethod]
        public void CreateDetailedErrorMessage_MultiplePackages_ListsAll()
        {
            // Arrange
            var wizard = CreateWizardWithFailedPackages(
                "MultiDetailProject",
                new Dictionary<string, Exception>
                {
                    { "Package.A", new Exception("Error A") },
                    { "Package.B", new ArgumentException("Error B") },
                    { "Package.C", new TimeoutException("Error C") }
                });

            // Act
            var message = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateDetailedErrorMessage");

            // Assert
            Assert.IsTrue(message.Contains("Package.A"));
            Assert.IsTrue(message.Contains("Error A"));
            Assert.IsTrue(message.Contains("Package.B"));
            Assert.IsTrue(message.Contains("ArgumentException"));
            Assert.IsTrue(message.Contains("Package.C"));
            Assert.IsTrue(message.Contains("TimeoutException"));
        }

        [TestMethod]
        public void CreateDetailedErrorMessage_EndsWithManualInstallInstruction()
        {
            // Arrange
            var wizard = CreateWizardWithFailedPackages(
                "InstructionProject",
                new Dictionary<string, Exception>
                {
                    { "SomePackage", new Exception("Error") }
                });

            // Act
            var message = (string)MockServiceSetup.InvokePrivateMethod(
                wizard, "CreateDetailedErrorMessage");

            // Assert — message should end with the manual install instruction
            // Resource string _1052 = "Please manually add package references before building."
            Assert.IsTrue(
                message.Contains("manually") || message.Contains("package references"),
                "Detailed error should include manual install instruction.");
        }

        #endregion

        #region Helper Methods

        private NuGetPackageInstaller CreateWizardWithFailedPackages(
            string projectName,
            Dictionary<string, Exception> failedPackages)
        {
            var wizard = new NuGetPackageInstaller();
            var project = MockServiceSetup.CreateCSharpProject(projectName);

            MockServiceSetup.SetPrivateField(wizard, "_project", project.Object);
            MockServiceSetup.SetPrivateField(wizard, "_failedPackageExceptions", failedPackages);

            return wizard;
        }

        #endregion
    }
}
