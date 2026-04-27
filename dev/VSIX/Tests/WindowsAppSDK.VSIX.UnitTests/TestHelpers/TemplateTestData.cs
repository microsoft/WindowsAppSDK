// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using System.Collections.Generic;

namespace WindowsAppSDK.VSIX.UnitTests.TestHelpers
{
    /// <summary>
    /// Provides template metadata for parameterized tests.
    /// Each entry represents a top-level project template shipped with the VSIX.
    /// </summary>
    internal static class TemplateTestData
    {
        /// <summary>
        /// NuGet packages specified by C# project templates.
        /// </summary>
        public const string CSharpStandardPackages = "Microsoft.WindowsAppSDK;Microsoft.Windows.SDK.BuildTools";

        /// <summary>
        /// NuGet packages specified by C# UnitTestApp template.
        /// </summary>
        public const string CSharpUnitTestPackages =
            "Microsoft.Windows.SDK.BuildTools;MSTest.TestAdapter;MSTest.TestFramework;Microsoft.TestPlatform.TestHost;Microsoft.WindowsAppSDK";

        /// <summary>
        /// NuGet packages specified by C++/WinRT project templates.
        /// </summary>
        public const string CppStandardPackages =
            "Microsoft.WindowsAppSDK;Microsoft.Windows.CppWinRT;Microsoft.Windows.SDK.BuildTools;Microsoft.Windows.ImplementationLibrary";

        /// <summary>
        /// Returns all top-level template definitions for iteration in tests.
        /// </summary>
        public static IEnumerable<TemplateInfo> AllTemplates
        {
            get
            {
                yield return CSharpSingleProjectPackagedApp;
                yield return CSharpClassLibrary;
                yield return CSharpUnitTestApp;
                yield return CSharpPackagedApp;
                yield return CppSingleProjectPackagedApp;
                yield return CppUnitTestApp;
                yield return CppPackagedApp;
                yield return CppRuntimeComponent;
            }
        }

        public static readonly TemplateInfo CSharpSingleProjectPackagedApp = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Desktop.Cs.SingleProjectPackagedApp",
            DisplayName = "C# SingleProjectPackagedApp",
            Language = TemplateLanguage.CSharp,
            Type = TemplateType.Project,
            NuGetPackages = CSharpStandardPackages,
            ExpectedOutputExtension = ".exe",
            RelativePath = @"Desktop\CSharp\SingleProjectPackagedApp"
        };

        public static readonly TemplateInfo CSharpClassLibrary = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Desktop.Cs.ClassLibrary",
            DisplayName = "C# ClassLibrary",
            Language = TemplateLanguage.CSharp,
            Type = TemplateType.Project,
            NuGetPackages = CSharpStandardPackages,
            ExpectedOutputExtension = ".dll",
            RelativePath = @"Desktop\CSharp\ClassLibrary"
        };

        public static readonly TemplateInfo CSharpUnitTestApp = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Desktop.Cs.UnitTestApp",
            DisplayName = "C# UnitTestApp",
            Language = TemplateLanguage.CSharp,
            Type = TemplateType.Project,
            NuGetPackages = CSharpUnitTestPackages,
            ExpectedOutputExtension = ".dll",
            RelativePath = @"Desktop\CSharp\UnitTestApp"
        };

        public static readonly TemplateInfo CSharpPackagedApp = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Desktop.Cs.PackagedApp",
            DisplayName = "C# PackagedApp",
            Language = TemplateLanguage.CSharp,
            Type = TemplateType.ProjectGroup,
            NuGetPackages = CSharpStandardPackages,
            ExpectedOutputExtension = ".exe",
            RelativePath = @"Desktop\CSharp\PackagedApp"
        };

        public static readonly TemplateInfo CppSingleProjectPackagedApp = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Desktop.CppWinRT.SingleProjectPackagedApp",
            DisplayName = "C++ SingleProjectPackagedApp",
            Language = TemplateLanguage.Cpp,
            Type = TemplateType.Project,
            NuGetPackages = CppStandardPackages,
            ExpectedOutputExtension = ".exe",
            RelativePath = @"Desktop\CppWinRT\SingleProjectPackagedApp"
        };

        public static readonly TemplateInfo CppUnitTestApp = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Desktop.CppWinRT.UnitTestApp",
            DisplayName = "C++ UnitTestApp",
            Language = TemplateLanguage.Cpp,
            Type = TemplateType.Project,
            NuGetPackages = CppStandardPackages,
            ExpectedOutputExtension = ".dll",
            RelativePath = @"Desktop\CppWinRT\UnitTestApp"
        };

        public static readonly TemplateInfo CppPackagedApp = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Desktop.CppWinRT.PackagedApp",
            DisplayName = "C++ PackagedApp",
            Language = TemplateLanguage.Cpp,
            Type = TemplateType.ProjectGroup,
            NuGetPackages = CppStandardPackages,
            ExpectedOutputExtension = ".exe",
            RelativePath = @"Desktop\CppWinRT\PackagedApp"
        };

        public static readonly TemplateInfo CppRuntimeComponent = new TemplateInfo
        {
            TemplateId = "Microsoft.WinUI.Neutral.CppWinRT.RuntimeComponent",
            DisplayName = "C++ RuntimeComponent",
            Language = TemplateLanguage.Cpp,
            Type = TemplateType.Project,
            NuGetPackages = CppStandardPackages,
            ExpectedOutputExtension = ".dll",
            ProducesWinMd = true,
            RelativePath = @"Neutral\CppWinRT\RuntimeComponent"
        };
    }

    internal enum TemplateLanguage
    {
        CSharp,
        Cpp
    }

    internal enum TemplateType
    {
        Project,
        ProjectGroup
    }

    internal class TemplateInfo
    {
        public string TemplateId { get; set; }
        public string DisplayName { get; set; }
        public TemplateLanguage Language { get; set; }
        public TemplateType Type { get; set; }
        public string NuGetPackages { get; set; }
        public string ExpectedOutputExtension { get; set; }
        public bool ProducesWinMd { get; set; }
        public string RelativePath { get; set; }

        /// <summary>
        /// True if this template uses the VC project GUID code path (immediate NuGet install).
        /// </summary>
        public bool IsCppProject => Language == TemplateLanguage.Cpp;

        public override string ToString() => DisplayName;
    }
}
