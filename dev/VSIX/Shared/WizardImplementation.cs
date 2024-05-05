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
using System.Deployment.Internal;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsAppSDK.TemplateUtilities
{

    public class NuGetPackageInstaller : IWizard
    {
        internal static Guid SolutionVCProjectGuid = new Guid("8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942");
        private Project _project;
        private IComponentModel _componentModel;
        private IEnumerable<string> _nuGetPackages;
        private IVsNuGetProjectUpdateEvents _nugetProjectUpdateEvents;
        private IVsThreadedWaitDialog2 _waitDialog;

        public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _componentModel = (IComponentModel)ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));
            _waitDialog = ServiceProvider.GlobalProvider.GetService(typeof(SVsThreadedWaitDialog)) as IVsThreadedWaitDialog2;
            if (_componentModel != null)
            {
                _nugetProjectUpdateEvents = _componentModel.GetService<IVsNuGetProjectUpdateEvents>();
                if (_nugetProjectUpdateEvents != null)
                {
                    _nugetProjectUpdateEvents.SolutionRestoreFinished += OnSolutionRestoreFinished;
                }
            }
            // Assuming package list is passed via a custom parameter in the .vstemplate file
            if (replacementsDictionary.TryGetValue("$NuGetPackages$", out string packages))
            {
                _nuGetPackages = packages.Split(';').Where(p => !string.IsNullOrEmpty(p));
            }
        }        
        public void ProjectFinishedGenerating(Project project)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _project = project;
            Guid _projectGuid;
            if (project != null)
            {
                Guid.TryParse(project.Kind, out _projectGuid);

                if (_projectGuid.Equals(SolutionVCProjectGuid))
                {
                    ThreadHelper.JoinableTaskFactory.Run(async () =>
                    {
                        await InstallNuGetPackagesAsync();
                    });
                }
            }
        }
        private async Task InstallNuGetPackagesAsync()
        {

            await ThreadHelper.JoinableTaskFactory.RunAsync(async () =>
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                int canceled; // This variable will store the status after the dialog is closed

                // Start the package installation task but do not await it here
                var installationTask = StartInstallationAsync();

                // Start the threaded wait dialog
                _waitDialog.StartWaitDialog("Installing NuGet packages", "Please wait while NuGet packages are being installed to your project...", null, null, "Operation in progress...", 0, false, true);

                // Now await the installation task to complete
                await installationTask;

                // Once the installation is complete, end the wait dialog
                _waitDialog.EndWaitDialog(out canceled);
                // Check if the process was canceled before proceeding
                if (canceled == 0) // If not canceled, finalize the process
                {
                    await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                    SaveAllProjects();
                }
            });


        }

        private async Task StartInstallationAsync()
        {
            IVsPackageInstaller installer = _componentModel.GetService<IVsPackageInstaller>();
            if (installer == null)
            {
                LogError("Could not obtain IVsPackageInstaller service.");
                return;
            }

            foreach (var packageId in _nuGetPackages)
            {
                try
                {
                    await InstallNuGetPackageAsync(installer, packageId);
                }
                catch (Exception ex)
                {
                    LogError($"Failed to install NuGet package: {packageId}. Error: {ex.Message}");
                }
            }
        }

        private async Task InstallNuGetPackageAsync(IVsPackageInstaller installer, string packageId)
        {
            try
            {
                // Simulate or perform package installation, which might be CPU-bound
                await Task.Run(() => installer.InstallPackage(null, _project, packageId, "", false));
            }
            catch (Exception ex)
            {
                LogError($"Error installing package {packageId}: {ex.Message}");
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
        private void SaveAllProjects()
        {
            ThreadHelper.ThrowIfNotOnUIThread("SaveAllProjects must be called on the UI thread.");

            var dte = Package.GetGlobalService(typeof(DTE)) as DTE;
            if (dte != null && dte.Solution != null && dte.Solution.Projects != null)
            {
                foreach (Project project in dte.Solution.Projects)
                {
                    if (project != null)
                    {
                        project.Save();
                    }
                }
            }
        }
        private void OnSolutionRestoreFinished(IReadOnlyList<string> projects)
        {
            // Debouncing prevents multiple rapid executions of 'InstallNuGetPackageAsync'
            // during solution restore.
            if (_nugetProjectUpdateEvents == null)
            {
                return;
            }
            _nugetProjectUpdateEvents.SolutionRestoreFinished -= OnSolutionRestoreFinished;
            var joinableTaskFactory = new JoinableTaskFactory(ThreadHelper.JoinableTaskContext);
            _ = joinableTaskFactory.RunAsync(InstallNuGetPackagesAsync);
        }
        private void LogError(string message)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            ThreadHelper.JoinableTaskFactory.   Run(async delegate
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
