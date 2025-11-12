// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
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
    public enum ErrorMessageFormat
    {
        MessageBox,
        InfoBar
    }

    public partial class NuGetPackageInstaller : IWizard
    {
        internal static Guid SolutionVCProjectGuid = new Guid("8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942");
        private Project _project;
        private IComponentModel _componentModel;
        private IEnumerable<string> _nuGetPackages;
        private IVsNuGetProjectUpdateEvents _nugetProjectUpdateEvents;
        private IVsThreadedWaitDialog2 _waitDialog;
        private Dictionary<string, Exception> _failedPackageExceptions = new Dictionary<string, Exception>();
        private Resources _resources = new Resources();

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
            Guid _projectGuid = GetProjectGuid(project);
            if (_projectGuid.Equals(SolutionVCProjectGuid))
            {
                ThreadHelper.JoinableTaskFactory.Run(async () =>
                {
                    await InstallNuGetPackagesAsync();
                });
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
                    _waitDialog.StartWaitDialog(null, _resources.InstallingNuGetPackages, null, null, _resources.OperationInProgress, 0, false, true);
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
                    _failedPackageExceptions[packageId] = ex;
                }
            }

            if (_failedPackageExceptions.Count > 0)
            {
                // Build error message in the requested format
                var errorMessage = CreateErrorMessage(ErrorMessageFormat.InfoBar);
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                LogError(errorMessage);
                _ = DisplayInfoBarAsync(errorMessage);
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
            ThreadHelper.ThrowIfNotOnUIThread();
            Guid _projectGuid = GetProjectGuid(_project);
            if (_projectGuid.Equals(SolutionVCProjectGuid))
            {
                if (_failedPackageExceptions.Count > 0)
                {
                    var errorMessage = CreateErrorMessage(ErrorMessageFormat.MessageBox);
                    LogError(errorMessage);
                    
                    var result = MessageBox.Show(
                        errorMessage,
                        _resources.MissingPackageReferences,
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);
                    
                    // Show the Output window with the detailed errors
                    ShowOutputWindow(CreateDetailedErrorMessage());
                    return;
                }
                return;
            }
        }

        private void ShowOutputWindow(string errorMessage)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            OutputWindowHelper.ShowMessageInOutputWindow(errorMessage);
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
            ThreadHelper.JoinableTaskFactory.Run(async delegate
            {
                // Accessing _project requires the main thread
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();

                if (_project == null)
                {
                    return;
                }

                // Normally, either InstallNuGetPackagesAsync is called from ProjectFinishedGenerating
                // for VC++ projects (C++ templates) or from here for C# and wapproj projects. In the
                // C++ wapproj template, InstallNuGetPackagesAsync() was called twice for the vcxproj,
                // once from each location. This caused the NuGet install API to throw an
                // InvalidOperationException because the package was already installed.
                // This check prevents the double installation attempt.
                Guid _projectGuid = GetProjectGuid(_project);
                if (_projectGuid.Equals(SolutionVCProjectGuid))
                {
                    if (_failedPackageExceptions.Count > 0)
                    {
                        var errorMessage = CreateErrorMessage(ErrorMessageFormat.InfoBar);
                        LogError(errorMessage);
                        _ = DisplayInfoBarAsync(errorMessage);
                        return;
                    }
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

        private string CreateErrorMessage(ErrorMessageFormat format)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            var packageNames = string.Join(", ", _failedPackageExceptions.Keys);
            var separator = format == ErrorMessageFormat.MessageBox ? "\n\n" : " ";
            var projectName = _project?.Name ?? "Unknown Project";
            var errorMessage = format == ErrorMessageFormat.InfoBar ?
            _resources.Format(_resources.UnableToAddReferencesInfoBar, projectName, packageNames)
                : _resources.Format(_resources.UnableToAddReferencesMessageBox, projectName, packageNames);
            return errorMessage;
        }

        private string CreateDetailedErrorMessage()
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            var errorLines = new System.Text.StringBuilder();
            var projectName = _project?.Name ?? "Unknown Project";
            errorLines.AppendLine(_resources.Format(_resources.MissingPackageReferencesFor, projectName));
            
            foreach (var package in _failedPackageExceptions)
            {
                errorLines.AppendLine($"{package.Key} - {package.Value.GetType().FullName}: {package.Value.Message}");
            }
            
            errorLines.AppendLine();
            errorLines.Append(_resources.PleaseAddPackageReferences);

            return errorLines.ToString();
        }

        private Guid GetProjectGuid(Project project)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            Guid projectGuid;
            if (project != null && Guid.TryParse(project.Kind, out projectGuid))
            {
                return projectGuid;
            }
            return Guid.Empty;
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

        private async Task DisplayInfoBarAsync(string errorMessage)
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            var infoBar = CreateNuGetInfoBar(errorMessage);
            var infoBarUi = CreateInfoBarUI(infoBar);

            // Write detailed error message to output window
            var detailedErrorMessage = CreateDetailedErrorMessage();
            ShowOutputWindow(detailedErrorMessage);

            if (infoBarUi == null)
            {
                LogError("Could not create InfoBar UI element. Logged error message to output window.");
                return;
            }

            infoBarUi.Advise(new NuGetInfoBarUIEvents(detailedErrorMessage), out uint _);

            IVsShell shell = ServiceProvider.GlobalProvider.GetService(typeof(SVsShell)) as IVsShell;
            if (shell == null)
            {
                LogError("Could not obtain IVsShell service");
                return;
            }

            // Get the main window's InfoBar host using VSSPROPID_MainWindowInfoBarHost
            object infoBarHostObj;
            int hr = shell.GetProperty((int)__VSSPROPID7.VSSPROPID_MainWindowInfoBarHost, out infoBarHostObj);
            if (!(infoBarHostObj is IVsInfoBarHost infoBarHost))
            {
                LogError("Could not obtain IVsInfoBarHost service");
                return;
            }

            infoBarHost.AddInfoBar(infoBarUi);
        }

        private IVsInfoBarUIElement CreateInfoBarUI(IVsInfoBar infoBar)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            if (infoBar == null)
            {
                LogError("InfoBar model is null.");
                return null;
            }

            IVsInfoBarUIFactory infoBarUIFactory = ServiceProvider.GlobalProvider.GetService(typeof(SVsInfoBarUIFactory)) as IVsInfoBarUIFactory;
            if (infoBarUIFactory == null)
            {
                LogError("Could not obtain IVsInfoBarUIFactory service");
                return null;
            }

            return infoBarUIFactory.CreateInfoBar(infoBar);
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
                new InfoBarHyperlink(_resources.ManageNuGetPackages),
                new InfoBarHyperlink(_resources.SeeErrorDetails)
              },
               image: KnownMonikers.NuGetNoColorError,
               isCloseButtonVisible: true);
           return infoBar;
        }

        public bool ShouldAddProjectItem(string _)
        {
            return true;
        }
    }
}
