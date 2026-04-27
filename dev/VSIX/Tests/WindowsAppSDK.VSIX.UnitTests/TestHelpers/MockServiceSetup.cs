// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;
using System.Reflection;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Moq;
using NuGet.VisualStudio;

namespace WindowsAppSDK.VSIX.UnitTests.TestHelpers
{
    /// <summary>
    /// Configures mock VS services for testing NuGetPackageInstaller wizard.
    /// </summary>
    internal static class MockServiceSetup
    {
        /// <summary>
        /// Creates a mock IComponentModel that returns the given IVsPackageInstaller mock.
        /// </summary>
        public static Mock<IComponentModel> CreateComponentModel(
            Mock<IVsPackageInstaller> installerMock = null,
            Mock<IVsNuGetProjectUpdateEvents> updateEventsMock = null)
        {
            var componentModel = new Mock<IComponentModel>();

            if (installerMock is null)
            {
                installerMock = new Mock<IVsPackageInstaller>();
            }

            if (updateEventsMock is null)
            {
                updateEventsMock = new Mock<IVsNuGetProjectUpdateEvents>();
            }

            componentModel.Setup(cm => cm.GetService<IVsPackageInstaller>())
                .Returns(installerMock.Object);

            componentModel.Setup(cm => cm.GetService<IVsNuGetProjectUpdateEvents>())
                .Returns(updateEventsMock.Object);

            return componentModel;
        }

        /// <summary>
        /// Creates a mock EnvDTE.Project with the specified Kind GUID.
        /// </summary>
        public static Mock<EnvDTE.Project> CreateProject(string name, Guid projectKindGuid)
        {
            var project = new Mock<EnvDTE.Project>();
            project.Setup(p => p.Kind).Returns(projectKindGuid.ToString("B").ToUpperInvariant());
            project.Setup(p => p.Name).Returns(name);
            return project;
        }

        /// <summary>
        /// Creates a mock C# project (non-VC).
        /// </summary>
        public static Mock<EnvDTE.Project> CreateCSharpProject(string name = "TestCSharpApp")
        {
            // C# project GUID
            return CreateProject(name, new Guid("FAE04EC0-301F-11D3-BF4B-00C04F79EFBC"));
        }

        /// <summary>
        /// Creates a mock C++ (VC) project matching SolutionVCProjectGuid.
        /// </summary>
        public static Mock<EnvDTE.Project> CreateCppProject(string name = "TestCppApp")
        {
            // VC project GUID used by the wizard for C++ detection
            return CreateProject(name, new Guid("8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942"));
        }

        /// <summary>
        /// Creates a replacements dictionary as passed to RunStarted.
        /// </summary>
        public static Dictionary<string, string> CreateReplacementsDictionary(string nugetPackages)
        {
            return new Dictionary<string, string>
            {
                { "$NuGetPackages$", nugetPackages }
            };
        }

        /// <summary>
        /// Sets a private field on the wizard instance via reflection.
        /// </summary>
        public static void SetPrivateField(object instance, string fieldName, object value)
        {
            var field = instance.GetType().GetField(fieldName,
                BindingFlags.NonPublic | BindingFlags.Instance);
            if (field is null)
            {
                throw new InvalidOperationException($"Field '{fieldName}' not found on type '{instance.GetType().Name}'.");
            }

            field.SetValue(instance, value);
        }

        /// <summary>
        /// Gets a private field value from the wizard instance via reflection.
        /// </summary>
        public static T GetPrivateField<T>(object instance, string fieldName)
        {
            var field = instance.GetType().GetField(fieldName,
                BindingFlags.NonPublic | BindingFlags.Instance);
            if (field is null)
            {
                throw new InvalidOperationException($"Field '{fieldName}' not found on type '{instance.GetType().Name}'.");
            }

            return (T)field.GetValue(instance);
        }

        /// <summary>
        /// Invokes a private method on the wizard instance via reflection.
        /// </summary>
        public static object InvokePrivateMethod(object instance, string methodName, params object[] args)
        {
            var method = instance.GetType().GetMethod(methodName,
                BindingFlags.NonPublic | BindingFlags.Instance);
            if (method is null)
            {
                throw new InvalidOperationException($"Method '{methodName}' not found on type '{instance.GetType().Name}'.");
            }

            return method.Invoke(instance, args);
        }
    }
}
