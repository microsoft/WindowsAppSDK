// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using EnvDTE;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio.TemplateWizard;
using NuGet.VisualStudio;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using WindowsAppSDK.Cpp.Extension;

namespace WindowsAppSDK.TemplateUtilities.Cpp
{
    public class NuGetPackageInstaller : IWizard
    {
        private Project _project;
        private IComponentModel _componentModel;
        public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _componentModel = (IComponentModel)ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));
        }
        public void ProjectFinishedGenerating(Project project)
        {
            _project = project;

            // Ensure we're on the main thread, as required by the ProjectFinishedGenerating method and DTE operations
            ThreadHelper.JoinableTaskFactory.Run(async () =>
            {
                await InstallNuGetPackagesAsync(_project);
            });
        }
        private async Task InstallNuGetPackagesAsync(Project project)
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            foreach (var packageId in NuGetPackageList.Packages)
            {
                try
                {
                    // No version specified; it installs the latest stable version
                    await InstallNuGetPackageAsync(packageId);
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
        private async Task InstallNuGetPackageAsync(string packageId)
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            IVsPackageInstaller installer = _componentModel.GetService<IVsPackageInstaller>();
            if (installer == null)
            {
                LogError("Could not obtain IVsPackageInstaller service.");
                return;
            }

            try
            {
                installer.InstallPackage(null, _project, packageId, "", false);
            }
            catch (Exception ex)
            {
                LogError($"Error installing package {packageId}: {ex.Message}");
            }
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
