// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using EnvDTE;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio.TemplateWizard;
using Microsoft.VisualStudio.Threading;
using NuGet.VisualStudio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace WindowsAppSDK.TemplateUtilities
{
	public class NuGetPackageInstaller : IWizard
	{
        private string _packageId;
        private Project _project;
        private IComponentModel _componentModel;
        private IVsNuGetProjectUpdateEvents _nugetProjectUpdateEvents;

        public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            _packageId = ExtractPackageId(replacementsDictionary);
            _componentModel = (IComponentModel)ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));
            _nugetProjectUpdateEvents = _componentModel.GetService<IVsNuGetProjectUpdateEvents>();
            _nugetProjectUpdateEvents.SolutionRestoreFinished += OnSolutionRestoreFinished;
        }
        private string ExtractPackageId(Dictionary<string, string> replacementsDictionary)
        {
            if (replacementsDictionary.TryGetValue("$wizarddata$", out string wizardDataXml))
            {
                XDocument xDoc = XDocument.Parse(wizardDataXml);
                XNamespace ns = xDoc.Root.GetDefaultNamespace();
                string packageId = xDoc.Descendants(ns + "package")
                                      .Attributes("id")
                                      .Select(attr => attr.Value)
                                      .FirstOrDefault();

                if (!string.IsNullOrEmpty(packageId))
                {
                    return packageId;
                }
            }
            return null;
        }
        public void ProjectFinishedGenerating(Project project)
		{
			_project = project;
		}
		public void BeforeOpeningFile(ProjectItem _)
		{
		}
		public void ProjectItemFinishedGenerating(ProjectItem _)
		{
		}
		public void RunFinished()
		{

		}
		private void OnSolutionRestoreFinished(IReadOnlyList<string> projects)
		{
			// Debouncing prevents multiple rapid executions of 'InstallNuGetPackageAsync'
			// during solution restore.
			_nugetProjectUpdateEvents.SolutionRestoreFinished -= OnSolutionRestoreFinished;
			var joinableTaskFactory = new JoinableTaskFactory(ThreadHelper.JoinableTaskContext);
			joinableTaskFactory.RunAsync(InstallNuGetPackageAsync);

		}
		private Task InstallNuGetPackageAsync()
		{
            if (string.IsNullOrEmpty(_packageId))
            {
                string message = "Failed to install the NuGet package. The package ID provided in the template configuration is either missing or invalid. Please ensure the template is correctly configured with a valid package ID.";
                DisplayMessageToUser(message, "Error", OLEMSGICON.OLEMSGICON_CRITICAL);
                LogError(message);
            }
            IVsPackageInstaller installer = _componentModel.GetService<IVsPackageInstaller>();
            try
            {
                installer.InstallPackage(null, _project, _packageId, "", false);
            }
            catch (Exception ex)
            {
                string errorMessage = "Failed to install the Microsoft.WindowsAppSDK package. You can try installing it manually from the following link: https://www.nuget.org/packages/Microsoft.WindowsAppSDK";
                DisplayMessageToUser(errorMessage, "Installation Error", OLEMSGICON.OLEMSGICON_CRITICAL);

                string logMessage = $"Failed to install Microsoft.WindowsAppSDK package. Exception details: \n" +
                                    $"Message: {ex.Message}\n" +
                                    $"Source: {ex.Source}\n" +
                                    $"Stack Trace: {ex.StackTrace}\n" +
                                    $"Target Site: {ex.TargetSite}\n";

                if (ex.InnerException != null)
                {
                    logMessage += $"Inner Exception Message: {ex.InnerException.Message}\n" +
                                  $"Inner Exception Stack Trace: {ex.InnerException.StackTrace}\n";
                }
                LogError(logMessage);
            }

            return Task.CompletedTask;
		}
        private void DisplayMessageToUser(string message, string title, OLEMSGICON icon)
        {
            ThreadHelper.JoinableTaskFactory.Run(async delegate
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                VsShellUtilities.ShowMessageBox(
                    ServiceProvider.GlobalProvider,
                    message,
                    title,
                    icon,
                    OLEMSGBUTTON.OLEMSGBUTTON_OK,
                    OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST);
            });
        }
        private void LogError(string message)
        {
            IVsActivityLog log = ServiceProvider.GlobalProvider.GetService(typeof(SVsActivityLog)) as IVsActivityLog;
            if (log != null)
            {
                log.LogEntry(
                    (UInt32)__ACTIVITYLOG_ENTRYTYPE.ALE_ERROR,
                    "WindowsAppSDK.TemplateUtilities",
                    message);
            }
        }
        public bool ShouldAddProjectItem(string _)
		{
			return true;
		}
	}
}
