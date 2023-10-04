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
		IVsNuGetProjectUpdateEvents _nugetProjectUpdateEvents;
		public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
		{
			ThreadHelper.ThrowIfNotOnUIThread();

			if (replacementsDictionary.TryGetValue("$wizarddata$", out string wizardDataXml))
			{
				// Parse the XML
				XDocument xDoc = XDocument.Parse(wizardDataXml);

				// Extract the default namespace from the XML value
				XNamespace ns = xDoc.Root.GetDefaultNamespace();

				string packageId = xDoc.Descendants(ns + "package")
									  .Attributes("id")
									  .Select(attr => attr.Value)
									  .FirstOrDefault();

				// Check if the packageId is not null or empty
				if (!string.IsNullOrEmpty(packageId))
				{
					_packageId = packageId;
				}
			}

			_componentModel = (IComponentModel)Microsoft.VisualStudio.Shell.ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));

			_nugetProjectUpdateEvents = _componentModel.GetService<IVsNuGetProjectUpdateEvents>();
			_nugetProjectUpdateEvents.SolutionRestoreFinished += OnSolutionRestoreFinished;
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
			IVsPackageInstaller installer = _componentModel.GetService<IVsPackageInstaller>();
            if (string.IsNullOrEmpty(_packageId))
            {
                string message = "Failed to install the NuGet package. The package ID provided in the template configuration is either missing or invalid. Please ensure the template is correctly configured with a valid package ID.";

                // Use the Run method to synchronously switch to and execute on the UI thread
                ThreadHelper.JoinableTaskFactory.Run(async delegate
                {
                    await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();

                    VsShellUtilities.ShowMessageBox(
                        ServiceProvider.GlobalProvider,
                        message,
                        "Error",
                        OLEMSGICON.OLEMSGICON_CRITICAL,
                        OLEMSGBUTTON.OLEMSGBUTTON_OK,
                        OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST);
                });
                return Task.CompletedTask;
            }

            try
			{
				installer.InstallPackage(null, _project, _packageId, "", false);
			}
			catch (Exception ex)
			{

			}
			return Task.CompletedTask;
		}
		public bool ShouldAddProjectItem(string _)
		{
			return true;
		}
	}
}
