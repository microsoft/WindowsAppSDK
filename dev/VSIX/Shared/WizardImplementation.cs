// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using EnvDTE;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Imaging;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio.TemplateWizard;
using Microsoft.VisualStudio.Threading;
using NuGet.VisualStudio;

namespace WindowsAppSDK.TemplateUtilities
{
    public partial class NuGetPackageInstaller : IWizard
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
            _componentModel = ServiceProvider.GlobalProvider.GetService(typeof(SComponentModel)) as IComponentModel;
            if (_componentModel == null)
            {
                System.Diagnostics.Debug.WriteLine("Warning: Could not obtain IComponentModel service.");
            }
            
            _waitDialog = ServiceProvider.GlobalProvider.GetService(typeof(SVsThreadedWaitDialog)) as IVsThreadedWaitDialog2;
            if (_waitDialog == null)
            {
                System.Diagnostics.Debug.WriteLine("Warning: Could not obtain IVsThreadedWaitDialog2 service.");
            }
            
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
                int canceled = 0; // Initialize as not canceled

                // Start the package installation task but do not await it here
                var installationTask = StartInstallationAsync();

                // Start the threaded wait dialog
                if (_waitDialog != null)
                {
                    _waitDialog.StartWaitDialog(null, "Installing NuGet packages into project...", null, null, "Operation in progress...", 0, false, true);
                }

                // Now await the installation task to complete
                await installationTask;

                // Once the installation is complete, end the wait dialog
                if (_waitDialog != null)
                {
                    _waitDialog.EndWaitDialog(out canceled);
                }
                // If _waitDialog is null, canceled remains 0 (not canceled)

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
            if (_componentModel == null)
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                LogError("ComponentModel service is not available.");
                return;
            }

            IVsPackageInstaller installer = _componentModel.GetService<IVsPackageInstaller>();
            if (installer == null)
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                LogError("Could not obtain IVsPackageInstaller service.");
                return;
            }

            if (_project == null)
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                LogError("Project reference is null. Likely a ProjectGroup vstemplate.");
                return;
            }

            var failedPackages = new Dictionary<string, string>();

            // Process each package installation
            foreach (var packageId in _nuGetPackages)
            {
                try
                {
                    await Task.Run(() => installer.InstallPackage(null, _project, packageId, "", false));
                }
                catch (Exception ex)
                {
                    await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                    LogError($"Failed to install NuGet package: {packageId}. Error: {ex.Message}");
                    failedPackages[packageId] = ex.Message;
                }
            }

            if (failedPackages.Count > 0)
            {
                // Build error message in the requested format
                var errorDetails = string.Join(", ", failedPackages.Select(kvp => $"{kvp.Key} ({kvp.Value})"));
                var errorMessage = $"The following NuGet packages failed to install: {errorDetails}";
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                LogError(errorMessage);
                var infoBar = CreateNuGetInfoBar(errorMessage);
                var infoBar2 = TryCreateInfoBarUI(infoBar, out IVsInfoBarUIElement uiElement);
                uiElement.Advise(new NuGetInfoBarUIEvents(), out uint _);
                IVsShell shell = ServiceProvider.GlobalProvider.GetService(typeof(SVsShell)) as IVsShell;
                if (shell == null)
                {
                    return;
                }

                // Get the main window's InfoBar host using VSSPROPID_MainWindowInfoBarHost
                object infoBarHostObj;
                int hr = shell.GetProperty((int)__VSSPROPID7.VSSPROPID_MainWindowInfoBarHost, out infoBarHostObj);
                if (!(infoBarHostObj is IVsInfoBarHost infoBarHost))
                {
                    return;
                }

                infoBarHost.AddInfoBar(uiElement);
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

            // Normally, either InstallNuGetPackagesAsync is called from ProjectFinishedGenerating for VC++ projects (C++ templates)
            // while C# are called here. In the C++ wapproj template, InstallNuGetPackagesAsync would be called twice for the vcxproj,
            // once from each location. This causes NuGet to throw an InvalidOperationException because the package is already installed.
            // This check prevents that from happening. Since the check accesses _project, it must be done on the main thread.
            ThreadHelper.JoinableTaskFactory.Run(async delegate
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                Guid _projectGuid;
                Guid.TryParse(_project.Kind, out _projectGuid);
                if (_projectGuid.Equals(SolutionVCProjectGuid))
                {
                    return;
                }
                else
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
            });
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

        private bool TryCreateInfoBarUI(IVsInfoBar infoBar, out IVsInfoBarUIElement uiElement)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            IVsInfoBarUIFactory infoBarUIFactory = ServiceProvider.GlobalProvider.GetService(typeof(SVsInfoBarUIFactory)) as IVsInfoBarUIFactory;
            if (infoBarUIFactory == null)
            {
                uiElement = null;
                return false;
            }

            uiElement = infoBarUIFactory.CreateInfoBar(infoBar);
            return uiElement != null;
        }

        private IVsInfoBar CreateNuGetInfoBar(string message)
        {
            var infoBar = new InfoBarModel(
                textSpans: new[]
                {
                    new InfoBarTextSpan(message)
                },
                actionItems: new InfoBarActionItem[]
                {
                    new InfoBarHyperlink("Manage NuGet Packages")
                },
                image: KnownMonikers.NuGetNoColorError,
                isCloseButtonVisible: true);
            return infoBar;
        }

        private class NuGetInfoBarUIEvents : IVsInfoBarUIEvents
        {
            public void OnActionItemClicked(IVsInfoBarUIElement infoBarUIElement, IVsInfoBarActionItem actionItem)
            {
                ThreadHelper.ThrowIfNotOnUIThread();
                if (actionItem is InfoBarHyperlink hyperlink &&
                    hyperlink.Text == "Manage NuGet Packages")
                {
                    var dte = ServiceProvider.GlobalProvider.GetService(typeof(EnvDTE.DTE)) as EnvDTE.DTE;
                    dte?.ExecuteCommand("Project.ManageNuGetPackages");
                }
            }

            public void OnClosed(IVsInfoBarUIElement infoBarUIElement)
            {
                // Optional: handle InfoBar closed event if needed
            }
        }

        public bool ShouldAddProjectItem(string _)
        {
            return true;
        }
    }
}
