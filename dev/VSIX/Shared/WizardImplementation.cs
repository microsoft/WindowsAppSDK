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

        
        public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _componentModel = (IComponentModel)ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));
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
        private async Task InstallNuGetPackageAsync(IVsPackageInstaller installer, string packageId)
        {
            await Task.Run(() =>
            {
                try
                {
                    installer.InstallPackage(null, _project, packageId, "", false);
                    // If there's any CPU-bound work, it will be done on the background thread.
                }
                catch (Exception ex)
                {
                    LogError($"Error installing package {packageId}: {ex.Message}");
                }
            });
        }
        // InstallNuGetPackagesAsync iterates over the package list and installs each
        private async Task InstallNuGetPackagesAsync()
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            DTE dte = ServiceProvider.GlobalProvider.GetService(typeof(DTE)) as DTE;
            IntPtr mainWindowHandle = new IntPtr((int)dte.MainWindow.HWnd);
            Form mainVsWindow = Control.FromHandle(mainWindowHandle) as Form;

            using (var progressDialog = new ProgressForm())
            {
                // Start the installation asynchronously
                var installationTask = StartInstallationAsync(progressDialog);

                // Show the dialog modally, which will block until progressDialog.Close() is called
                progressDialog.ShowDialog(mainVsWindow);
            }
        }

        private async Task StartInstallationAsync(ProgressForm progressDialog)
        {
            try
            {
                IVsPackageInstaller installer = _componentModel.GetService<IVsPackageInstaller>();
                if (installer == null)
                {
                    LogError("Could not obtain IVsPackageInstaller service.");
                    progressDialog.Invoke(new Action(progressDialog.Close));  // Close on error
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

                // Once all packages are installed, close the dialog on the UI thread
                progressDialog.Invoke(new Action(progressDialog.Close));
            }
            finally
            {
                if (progressDialog.Visible)
                {
                    // Ensure the dialog is closed if still open for any reason
                    progressDialog.Invoke(new Action(progressDialog.Close));
                }

                // Ensure the UI thread is used to save all projects after the dialog is closed
                await ThreadHelper.JoinableTaskFactory.RunAsync(async () =>
                {
                    await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                    SaveAllProjects();
                });
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
