using EnvDTE;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Shell;
using NuGet.VisualStudio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TemplateWizard;
using Microsoft.VisualStudio.Shell.Interop;

namespace WindowsAppSDK.TemplateUtilities
{
    public class NuGetPackageInstaller : IWizard
    {
        private Project _project;
        private IComponentModel _componentModel;
        private IEnumerable<string> _nuGetPackages;

        // RunStarted initializes _componentModel and extracts the NuGet package list
        public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _componentModel = (IComponentModel)ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel));

            // Assuming package list is passed via a custom parameter in the .vstemplate file
            if (replacementsDictionary.TryGetValue("NuGetPackages", out string packages))
            {
                _nuGetPackages = packages.Split(';').Where(p => !string.IsNullOrEmpty(p));
            }
        }

        // ProjectFinishedGenerating triggers asynchronous package installation
        public void ProjectFinishedGenerating(Project project)
        {
            _project = project;
            ThreadHelper.JoinableTaskFactory.Run(async () => await InstallNuGetPackagesAsync());
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
        public void BeforeOpeningFile(ProjectItem projectItem) { }
        public void ProjectItemFinishedGenerating(ProjectItem projectItem) { }
        public void RunFinished() { }
        public bool ShouldAddProjectItem(string filePath) => true;
    }
}
