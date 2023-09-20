// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using EnvDTE;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.TemplateWizard;
using Microsoft.VisualStudio.Threading;
using NuGet.VisualStudio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace WindowsAppSDK.Cs.Extension
{

    public class NuGetPackageInstaller : IWizard
    {
        private IVsPackageInstaller _packageInstaller;
        private string _packageId;
        private Project _project;
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

            var componentModel = (IComponentModel)Microsoft.VisualStudio.Shell.ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));
            IVsPackageInstaller installer = componentModel.GetService<IVsPackageInstaller>();
            _packageInstaller = installer;

            _nugetProjectUpdateEvents = componentModel.GetService<IVsNuGetProjectUpdateEvents>();
            _nugetProjectUpdateEvents.SolutionRestoreFinished += OnSolutionRestoreFinished;
        }

        public void ProjectFinishedGenerating(Project project)
        {
            _project = project;
        }

        public void BeforeOpeningFile(ProjectItem projectItem)
        {
        }

        public void ProjectItemFinishedGenerating(ProjectItem projectItem)
        {
        }

        public void RunFinished()
        {

        }

        private void OnSolutionRestoreFinished(IReadOnlyList<string> projects)
        {
            _nugetProjectUpdateEvents.SolutionRestoreFinished -= OnSolutionRestoreFinished;
            var joinableTaskFactory = new JoinableTaskFactory(ThreadHelper.JoinableTaskContext);
            joinableTaskFactory.RunAsync(InstallNuGetPackageAsync);

        }

        private Task InstallNuGetPackageAsync()
        {
            try
            {
                _packageInstaller.InstallPackage(null, _project, _packageId, "", false);
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
