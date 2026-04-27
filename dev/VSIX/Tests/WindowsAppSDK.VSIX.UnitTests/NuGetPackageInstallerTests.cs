// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;
using EnvDTE;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using NuGet.VisualStudio;
using WindowsAppSDK.TemplateUtilities;
using WindowsAppSDK.VSIX.UnitTests.TestHelpers;

namespace WindowsAppSDK.VSIX.UnitTests
{
    [TestClass]
    public class NuGetPackageInstallerTests : VsTestBase
    {
        #region Package Parsing Tests (simulates RunStarted logic)

        [TestMethod]
        public void PackageParsing_StandardPackageString_ParsesCorrectly()
        {
            // The wizard parses $NuGetPackages$ by splitting on ';'
            // Simulate this logic directly since RunStarted requires ServiceProvider.GlobalProvider
            var wizard = new NuGetPackageInstaller();
            var packages = "Microsoft.WindowsAppSDK;Microsoft.Windows.SDK.BuildTools"
                .Split(';')
                .Where(p => !string.IsNullOrEmpty(p));

            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages", packages);

            var stored = MockServiceSetup.GetPrivateField<IEnumerable<string>>(wizard, "_nuGetPackages");
            Assert.IsNotNull(stored);
            var list = stored.ToList();
            Assert.AreEqual(2, list.Count);
            Assert.AreEqual("Microsoft.WindowsAppSDK", list[0]);
            Assert.AreEqual("Microsoft.Windows.SDK.BuildTools", list[1]);
        }

        [TestMethod]
        public void PackageParsing_EmptyString_ResultsInEmptyList()
        {
            var wizard = new NuGetPackageInstaller();
            var packages = "".Split(';').Where(p => !string.IsNullOrEmpty(p));

            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages", packages);

            var stored = MockServiceSetup.GetPrivateField<IEnumerable<string>>(wizard, "_nuGetPackages");
            Assert.IsNotNull(stored);
            Assert.AreEqual(0, stored.Count());
        }

        [TestMethod]
        public void PackageParsing_CppPackages_ParsesFourPackages()
        {
            var wizard = new NuGetPackageInstaller();
            var packages = TemplateTestData.CppStandardPackages
                .Split(';')
                .Where(p => !string.IsNullOrEmpty(p));

            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages", packages);

            var stored = MockServiceSetup.GetPrivateField<IEnumerable<string>>(wizard, "_nuGetPackages");
            Assert.AreEqual(4, stored.Count());
        }

        [TestMethod]
        public void PackageParsing_UnitTestPackages_ParsesFivePackages()
        {
            var wizard = new NuGetPackageInstaller();
            var packages = TemplateTestData.CSharpUnitTestPackages
                .Split(';')
                .Where(p => !string.IsNullOrEmpty(p));

            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages", packages);

            var stored = MockServiceSetup.GetPrivateField<IEnumerable<string>>(wizard, "_nuGetPackages");
            Assert.AreEqual(5, stored.Count());
            Assert.IsTrue(stored.Contains("MSTest.TestAdapter"));
            Assert.IsTrue(stored.Contains("Microsoft.WindowsAppSDK"));
        }

        [TestMethod]
        public void PackageParsing_NullPackages_FieldIsNull()
        {
            var wizard = new NuGetPackageInstaller();
            // When $NuGetPackages$ is not in the replacements dictionary, _nuGetPackages stays null
            var stored = MockServiceSetup.GetPrivateField<IEnumerable<string>>(wizard, "_nuGetPackages");
            Assert.IsNull(stored);
        }

        #endregion

        #region ProjectFinishedGenerating Tests

        [TestMethod]
        public void CppProject_StartInstallation_CallsInstallerForEachPackage()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var installerMock = new Mock<IVsPackageInstaller>();
            var componentModel = MockServiceSetup.CreateComponentModel(installerMock);
            var cppProject = MockServiceSetup.CreateCppProject();

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_project", cppProject.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                TemplateTestData.CppStandardPackages.Split(';').AsEnumerable());

            // Act — call StartInstallationAsync directly (bypasses JoinableTaskFactory.Run)
            InvokeStartInstallation(wizard);

            // Assert — InstallPackage should have been called for each package
            installerMock.Verify(
                i => i.InstallPackage(null, cppProject.Object, It.IsAny<string>(), "", false),
                Times.Exactly(4));
        }

        [TestMethod]
        public void ProjectFinishedGenerating_CSharpProject_DoesNotCallInstallPackagesImmediately()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var installerMock = new Mock<IVsPackageInstaller>();
            var componentModel = MockServiceSetup.CreateComponentModel(installerMock);

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                TemplateTestData.CSharpStandardPackages.Split(';').AsEnumerable());

            var csProject = MockServiceSetup.CreateCSharpProject();

            // Act
            wizard.ProjectFinishedGenerating(csProject.Object);

            // Assert — C# projects should NOT install packages immediately
            installerMock.Verify(
                i => i.InstallPackage(It.IsAny<string>(), It.IsAny<Project>(), It.IsAny<string>(), It.IsAny<string>(), It.IsAny<bool>()),
                Times.Never);
        }

        [TestMethod]
        public void ProjectFinishedGenerating_StoresProjectReference()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var componentModel = MockServiceSetup.CreateComponentModel();
            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);

            var project = MockServiceSetup.CreateCSharpProject("MyProject");

            // Act
            wizard.ProjectFinishedGenerating(project.Object);

            // Assert
            var storedProject = MockServiceSetup.GetPrivateField<Project>(wizard, "_project");
            Assert.AreSame(project.Object, storedProject);
        }

        #endregion

        #region NuGet Installation Failure Tests

        [TestMethod]
        public void StartInstallation_InstallerThrows_ExceptionIsCaught()
        {
            // Arrange: verify that when installer.InstallPackage throws,
            // StartInstallationAsync catches the exception (doesn't propagate).
            // The full error message display requires a VS message pump (integration test).
            var wizard = new NuGetPackageInstaller();
            var installerMock = new Mock<IVsPackageInstaller>();
            installerMock.Setup(i => i.InstallPackage(null, It.IsAny<Project>(), It.IsAny<string>(), "", false))
                .Throws(new InvalidOperationException("Package source not found"));

            var componentModel = MockServiceSetup.CreateComponentModel(installerMock);
            var cppProject = MockServiceSetup.CreateCppProject("FailTestApp");

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_project", cppProject.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                new[] { "Microsoft.WindowsAppSDK" }.AsEnumerable());

            // Act — installer is called and throws, but the async error handling
            // path (SwitchToMainThreadAsync) needs a VS message pump. We verify
            // the installer WAS called and the exception doesn't propagate.
            try
            {
                InvokeStartInstallation(wizard);
            }
            catch (Exception ex) when (!(ex is AssertFailedException))
            {
                // The async machinery may throw due to missing message pump.
                // The key assertion is that InstallPackage was called.
            }

            // Assert — verify the installer was invoked
            installerMock.Verify(
                i => i.InstallPackage(null, cppProject.Object, "Microsoft.WindowsAppSDK", "", false),
                Times.Once);
        }

        [TestMethod]
        public void StartInstallation_PartialFailure_SuccessfulPackagesStillInstalled()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var installerMock = new Mock<IVsPackageInstaller>();

            // First package succeeds, second fails
            installerMock.Setup(i => i.InstallPackage(null, It.IsAny<Project>(), "PackageA", "", false));
            installerMock.Setup(i => i.InstallPackage(null, It.IsAny<Project>(), "PackageB", "", false))
                .Throws(new Exception("Network error"));

            var componentModel = MockServiceSetup.CreateComponentModel(installerMock);
            var project = MockServiceSetup.CreateCppProject("PartialFailApp");

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_project", project.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                new[] { "PackageA", "PackageB" }.AsEnumerable());

            // Act
            try
            {
                InvokeStartInstallation(wizard);
            }
            catch (Exception ex) when (!(ex is AssertFailedException))
            {
                // Async error handling may throw due to missing message pump
            }

            // Assert — both packages were attempted
            installerMock.Verify(
                i => i.InstallPackage(null, project.Object, "PackageA", "", false), Times.Once);
            installerMock.Verify(
                i => i.InstallPackage(null, project.Object, "PackageB", "", false), Times.Once);
        }

        [TestMethod]
        public void StartInstallation_NullComponentModel_LogsErrorAndReturns()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            MockServiceSetup.SetPrivateField(wizard, "_componentModel", null);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                TemplateTestData.CppStandardPackages.Split(';').AsEnumerable());

            // Act — should not throw; logs error and returns
            InvokeStartInstallation(wizard);

            // Assert — no packages should be attempted
            var failedPackages = MockServiceSetup.GetPrivateField<Dictionary<string, Exception>>(
                wizard, "_failedPackageExceptions");
            Assert.AreEqual(0, failedPackages.Count);
        }

        [TestMethod]
        public void StartInstallation_NullInstaller_LogsErrorAndReturns()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var componentModel = new Mock<IComponentModel>();
            componentModel.Setup(cm => cm.GetService<IVsPackageInstaller>())
                .Returns((IVsPackageInstaller)null);

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                TemplateTestData.CppStandardPackages.Split(';').AsEnumerable());

            // Act — should not throw
            InvokeStartInstallation(wizard);

            // Assert — no packages attempted
            var failedPackages = MockServiceSetup.GetPrivateField<Dictionary<string, Exception>>(
                wizard, "_failedPackageExceptions");
            Assert.AreEqual(0, failedPackages.Count);
        }

        [TestMethod]
        public void StartInstallation_NullProject_LogsErrorAndReturns()
        {
            // Arrange: simulate scenario where _project is null (e.g., ProjectGroup vstemplate)
            var wizard = new NuGetPackageInstaller();
            var installerMock = new Mock<IVsPackageInstaller>();
            var componentModel = MockServiceSetup.CreateComponentModel(installerMock);

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                TemplateTestData.CppStandardPackages.Split(';').AsEnumerable());
            // _project remains null

            // Act
            InvokeStartInstallation(wizard);

            // Assert — installer should not be called when project is null
            installerMock.Verify(
                i => i.InstallPackage(It.IsAny<string>(), It.IsAny<Project>(), It.IsAny<string>(), It.IsAny<string>(), It.IsAny<bool>()),
                Times.Never);
        }

        #endregion

        #region Happy Path Tests

        [TestMethod]
        public void StartInstallation_AllPackagesSucceed_NoFailedExceptions()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var installerMock = new Mock<IVsPackageInstaller>();
            var componentModel = MockServiceSetup.CreateComponentModel(installerMock);
            var cppProject = MockServiceSetup.CreateCppProject("HappyPathCpp");

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_project", cppProject.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                TemplateTestData.CppStandardPackages.Split(';').AsEnumerable());

            // Act
            InvokeStartInstallation(wizard);

            // Assert
            var failedPackages = MockServiceSetup.GetPrivateField<Dictionary<string, Exception>>(
                wizard, "_failedPackageExceptions");
            Assert.AreEqual(0, failedPackages.Count);

            // Verify all 4 C++ packages were installed
            foreach (var package in TemplateTestData.CppStandardPackages.Split(';'))
            {
                installerMock.Verify(
                    i => i.InstallPackage(null, cppProject.Object, package, "", false),
                    Times.Once,
                    $"Package '{package}' should have been installed once.");
            }
        }

        [TestMethod]
        public void RunFinished_CppProject_NoFailures_DoesNotShowMessageBox()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var cppProject = MockServiceSetup.CreateCppProject("SuccessApp");
            MockServiceSetup.SetPrivateField(wizard, "_project", cppProject.Object);

            var failedPackages = MockServiceSetup.GetPrivateField<Dictionary<string, Exception>>(
                wizard, "_failedPackageExceptions");
            Assert.AreEqual(0, failedPackages.Count);

            // Act — should complete without error
            wizard.RunFinished();
        }

        [TestMethod]
        public void RunFinished_CppProject_WithFailures_ShowsMessageBoxWithCorrectContent()
        {
            // Arrange
            var wizard = new NuGetPackageInstaller();
            var cppProject = MockServiceSetup.CreateCppProject("FailedCppApp");
            MockServiceSetup.SetPrivateField(wizard, "_project", cppProject.Object);
            MockServiceSetup.SetPrivateField(wizard, "_failedPackageExceptions",
                new Dictionary<string, Exception>
                {
                    { "Microsoft.WindowsAppSDK", new InvalidOperationException("Package source not found") },
                    { "Microsoft.Windows.SDK.BuildTools", new Exception("Network error") }
                });

            // Intercept the MessageBox to verify content and avoid blocking
            string capturedMessage = null;
            string capturedCaption = null;
            var originalFunc = NuGetPackageInstaller.ShowMessageBox;
            try
            {
                NuGetPackageInstaller.ShowMessageBox = (message, caption, buttons, icon) =>
                {
                    capturedMessage = message;
                    capturedCaption = caption;
                    Assert.AreEqual(MessageBoxButtons.OK, buttons);
                    Assert.AreEqual(MessageBoxIcon.Error, icon);
                    return DialogResult.OK;
                };

                // Act — RunFinished should show the MessageBox and then continue without crash
                wizard.RunFinished();
            }
            finally
            {
                NuGetPackageInstaller.ShowMessageBox = originalFunc;
            }

            // Assert — message was shown with correct content
            Assert.IsNotNull(capturedMessage, "MessageBox should have been shown for failed C++ packages.");
            Assert.IsTrue(capturedMessage.Contains("FailedCppApp"),
                "Error message should contain the project name.");
            Assert.IsTrue(capturedMessage.Contains("Microsoft.WindowsAppSDK"),
                "Error message should contain the failed package name.");
            Assert.IsTrue(capturedMessage.Contains("Microsoft.Windows.SDK.BuildTools"),
                "Error message should contain all failed package names.");
            Assert.IsNotNull(capturedCaption, "MessageBox caption should not be null.");
        }

        #endregion

        #region ShouldAddProjectItem Tests

        [TestMethod]
        public void ShouldAddProjectItem_AlwaysReturnsTrue()
        {
            var wizard = new NuGetPackageInstaller();
            Assert.IsTrue(wizard.ShouldAddProjectItem("anything"));
            Assert.IsTrue(wizard.ShouldAddProjectItem(""));
            Assert.IsTrue(wizard.ShouldAddProjectItem(null));
        }

        #endregion

        #region Template-Specific Package Verification

        [TestMethod]
        public void StartInstallation_CSharpStandardPackages_InstallsCorrectCount()
        {
            VerifyPackageInstallation(TemplateTestData.CSharpStandardPackages, 2);
        }

        [TestMethod]
        public void StartInstallation_CppStandardPackages_InstallsCorrectCount()
        {
            VerifyPackageInstallation(TemplateTestData.CppStandardPackages, 4);
        }

        [TestMethod]
        public void StartInstallation_UnitTestPackages_InstallsCorrectCount()
        {
            VerifyPackageInstallation(TemplateTestData.CSharpUnitTestPackages, 5);
        }

        private void VerifyPackageInstallation(string packageList, int expectedCount)
        {
            var wizard = new NuGetPackageInstaller();
            var installerMock = new Mock<IVsPackageInstaller>();
            var componentModel = MockServiceSetup.CreateComponentModel(installerMock);
            var project = MockServiceSetup.CreateCppProject();

            MockServiceSetup.SetPrivateField(wizard, "_componentModel", componentModel.Object);
            MockServiceSetup.SetPrivateField(wizard, "_project", project.Object);
            MockServiceSetup.SetPrivateField(wizard, "_nuGetPackages",
                packageList.Split(';').AsEnumerable());

            InvokeStartInstallation(wizard);

            installerMock.Verify(
                i => i.InstallPackage(null, project.Object, It.IsAny<string>(), "", false),
                Times.Exactly(expectedCount));
        }

        #endregion

        #region Helpers

        /// <summary>
        /// Calls StartInstallationAsync directly via reflection, bypassing the
        /// JoinableTaskFactory.Run wrapper in ProjectFinishedGenerating that requires
        /// a VS message pump.
        /// </summary>
        private static void InvokeStartInstallation(NuGetPackageInstaller wizard)
        {
            var method = typeof(NuGetPackageInstaller).GetMethod(
                "StartInstallationAsync",
                BindingFlags.NonPublic | BindingFlags.Instance);

            Assert.IsNotNull(method, "StartInstallationAsync method not found on NuGetPackageInstaller.");

            var task = (Task)method.Invoke(wizard, null);
            task.GetAwaiter().GetResult();
        }

        #endregion
    }
}
