// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using System.Collections.Generic;
using System.Resources;
using System.Windows.Forms;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

#if CSHARP_EXTENSION
using Resources = WindowsAppSDK.Cs.Extension.Dev17.VSPackage;
#elif CPP_EXTENSION
using Resources = WindowsAppSDK.Cpp.Extension.Dev17.VSPackage;
#endif

namespace WindowsAppSDK.TemplateUtilities
{
    internal static class WizardErrorHelper
    {
        internal static string CreateErrorMessage(
            ErrorMessageFormat format,
            string projectName,
            Dictionary<string, Exception> failedPackageExceptions)
        {
            try
            {
                var packageNames = string.Join(", ", failedPackageExceptions.Keys);
                var errorMessage = format == ErrorMessageFormat.InfoBar ?
                    string.Format(Resources._1047, projectName, packageNames)
                    : string.Format(Resources._1048, projectName, packageNames);
                return errorMessage;
            }
            catch (MissingManifestResourceException ex)
            {
                ShowLocalizationErrorDialog(ex);
                var packageNames = string.Join(", ", failedPackageExceptions.Keys);
                return $"Unable to add package references to project: {packageNames}";
            }
        }

        internal static string CreateDetailedErrorMessage(
            string projectName,
            Dictionary<string, Exception> failedPackageExceptions)
        {
            try
            {
                var errorLines = new System.Text.StringBuilder();
                errorLines.AppendLine(string.Format(Resources._1051, projectName));

                foreach (var package in failedPackageExceptions)
                {
                    errorLines.AppendLine($"{package.Key} - {package.Value.GetType().FullName}: {package.Value.Message}");
                }

                errorLines.AppendLine();
                errorLines.Append(Resources._1052);

                return errorLines.ToString();
            }
            catch (MissingManifestResourceException ex)
            {
                ShowLocalizationErrorDialog(ex);
                var errorLines = new System.Text.StringBuilder();
                errorLines.AppendLine($"Missing package references for project: {projectName}");

                foreach (var package in failedPackageExceptions)
                {
                    errorLines.AppendLine($"{package.Key} - {package.Value.GetType().FullName}: {package.Value.Message}");
                }

                errorLines.AppendLine();
                errorLines.Append("Please add the package references manually using NuGet Package Manager.");

                return errorLines.ToString();
            }
        }

        internal static void LogError(string message)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            ThreadHelper.JoinableTaskFactory.Run(async delegate
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                IVsActivityLog log = ServiceProvider.GlobalProvider.GetService(typeof(SVsActivityLog)) as IVsActivityLog;
                if (log != null)
                {
                    log.LogEntry((uint)__ACTIVITYLOG_ENTRYTYPE.ALE_ERROR, nameof(NuGetPackageInstaller), message);
                }
            });
        }

        internal static void ShowLocalizationErrorDialog(MissingManifestResourceException ex)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            var errorMessage = $"A localization error occurred while loading the template wizard:\n\n{ex.Message}\n\n" +
                "The template may not have been installed correctly. Please reinstall the Windows App SDK extension.";

            MessageBox.Show(
                errorMessage,
                "Localization Error",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error);

            LogError($"Localization error: {ex.Message}");
            OutputWindowHelper.ShowMessageInOutputWindow($"Localization Error:\n{ex.Message}\n{ex.StackTrace}");
        }
    }
}
