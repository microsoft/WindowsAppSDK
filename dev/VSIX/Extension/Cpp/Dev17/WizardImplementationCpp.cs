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

namespace WindowsAppSDK.TemplateUtilities.Cpp
{
    public class NuGetPackageInstaller : IWizard
    {
        private Project _project;
        private IComponentModel _componentModel;
        private IEnumerable<string> _nuGetPackages;
        private IVsNuGetProjectUpdateEvents _nugetProjectUpdateEvents;
        
        public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _componentModel = (IComponentModel)ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));
            _nugetProjectUpdateEvents = _componentModel.GetService<IVsNuGetProjectUpdateEvents>();
            _nugetProjectUpdateEvents.SolutionRestoreFinished += OnSolutionRestoreFinished;
            // Assuming package list is passed via a custom parameter in the .vstemplate file
            if (replacementsDictionary.TryGetValue("$NuGetPackages$", out string packages))
            {
                _nuGetPackages = packages.Split(';').Where(p => !string.IsNullOrEmpty(p));
            }
        }        
        public void ProjectFinishedGenerating(Project project)
        {
            _project = project;
        }        
        // InstallNuGetPackagesAsync iterates over the package list and installs each
        private async Task InstallNuGetPackagesAsync()
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            var installer = _componentModel.GetService<IVsPackageInstaller>();

            foreach (var packageId in _nuGetPackages)
            {
                try
                {
                    // Install the latest stable version of each package
                    installer.InstallPackage(null, _project, packageId, version: "", ignoreDependencies: false);
                }
                catch (Exception ex)
                {
                    LogError($"Failed to install NuGet package: {packageId}. Error: {ex.Message}");
                }
            }
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
            _ = joinableTaskFactory.RunAsync(InstallNuGetPackagesAsync);
        }
        private void LogError(string message)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            ThreadHelper.JoinableTaskFactory.Run(async delegate
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                IVsActivityLog log = ServiceProvider.GlobalProvider.GetService(typeof(SVsActivityLog)) as IVsActivityLog;
                if (log != null)
                {
                    int hr = log.LogEntry((uint)__ACTIVITYLOG_ENTRYTYPE.ALE_ERROR, ToString(), message);
                }
            });
        }
        public bool ShouldAddProjectItem(string _)
        {
            return true;
        }
    }
}
