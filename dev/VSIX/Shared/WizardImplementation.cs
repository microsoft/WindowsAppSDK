// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Resources;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using EnvDTE;
using Microsoft.VisualStudio.ComponentModelHost;
using Microsoft.VisualStudio.Imaging;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio.TemplateWizard;
using Microsoft.VisualStudio.Threading;
using NuGet.VisualStudio;


// Although the strings are the same in the wizard for both extensions,
// they are included with both their respective VSPackages.
// Strings for both extensions can be found in {PathToWindowsAppSDK}\dev\VSIX\Extension\Cs\Common\VSPackage.resx
// Wizard strings are numbers 1044 and above.
#if CSHARP_EXTENSION
using Resources = WindowsAppSDK.Cs.Extension.Dev17.VSPackage;
#elif CPP_EXTENSION
using Resources = WindowsAppSDK.Cpp.Extension.Dev17.VSPackage;
#endif

namespace WindowsAppSDK.TemplateUtilities
{
    public enum ErrorMessageFormat
    {
        MessageBox,
        InfoBar
    }

    public partial class NuGetPackageInstaller : IWizard, IVsSolutionEvents
    {
        internal static Guid SolutionVCProjectGuid = new Guid("8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942");
        private Project _project;
        private IComponentModel _componentModel;
        private IEnumerable<string> _nuGetPackages;
        private IVsNuGetProjectUpdateEvents _nugetProjectUpdateEvents;
        private IVsThreadedWaitDialog2 _waitDialog;
        private IVsInfoBarUIFactory _infoBarUIFactory;
        private Dictionary<string, Exception> _failedPackageExceptions = new Dictionary<string, Exception>();
        private static BuildGuard s_buildGuard = new BuildGuard();
        private static volatile bool s_installationComplete;
        private IVsSolution _solution;
        private uint _solutionEventsCookie;
        private bool _packageRestoreEnabled = true;

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

            _infoBarUIFactory = ServiceProvider.GlobalProvider.GetService(typeof(SVsInfoBarUIFactory)) as IVsInfoBarUIFactory;
            if (_infoBarUIFactory == null)
            {
                System.Diagnostics.Debug.WriteLine("Warning: Could not obtain IVsInfoBarUIFactory service.");
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

            if (_nuGetPackages != null && _nuGetPackages.Any())
            {
                _packageRestoreEnabled = IsNuGetPackageRestoreEnabled();

                if (!_packageRestoreEnabled)
                {
                    LogError("NuGet package restore is disabled. Skipping automatic package installation.");
                    return;
                }

                if (s_installationComplete)
                {
                    s_buildGuard = new BuildGuard();
                    s_installationComplete = false;
                }

                s_buildGuard.SetReleaseCondition(() => s_installationComplete);

                _solution = ServiceProvider.GlobalProvider.GetService(typeof(SVsSolution)) as IVsSolution;
                if (_solution != null)
                {
                    _solution.AdviseSolutionEvents(this, out _solutionEventsCookie);
                }

                s_buildGuard.DisableBuilds();
            }
        }

        public void ProjectFinishedGenerating(Project project)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _project = project;
            Guid _projectGuid = GetProjectGuid(project);

            if (_nuGetPackages != null && _nuGetPackages.Any())
            {
                var projectName = _project?.Name ?? "Unknown Project";
                var packageNames = string.Join(", ", _nuGetPackages);
                s_buildGuard.SetInfoBarMessage(string.Format(Resources._1055, projectName, packageNames));
            }

            if (!_packageRestoreEnabled && _nuGetPackages != null && _nuGetPackages.Any())
            {
                // Write C# package references to the project so that auto-download can install packages
                // after project generation completes.
                if (!_projectGuid.Equals(SolutionVCProjectGuid))
                {
                    AddPackageReferencesToProject();
                }

                var projectName = _project?.Name ?? "Unknown Project";
                var packageNames = string.Join(", ", _nuGetPackages);
                _ = DisplayInfoBarAsync(string.Format(Resources._1056, projectName, packageNames));
                return;
            }

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

                try
                {
                    // Start the package installation task but do not await it here
                    var installationTask = StartInstallationAsync();

                    // Start the threaded wait dialog
                    if (_waitDialog != null)
                    {
                        _waitDialog.StartWaitDialog(null, Resources._1044, null, null, Resources._1045, 0, false, true);
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
                }
                finally
                {
                    s_installationComplete = true;
                    await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                    UnadviseSolutionEvents();
                    s_buildGuard.EnableBuilds();
                }
            });
        }

        private async Task StartInstallationAsync()
        {
            if (!_packageRestoreEnabled)
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                LogError("NuGet package restore is disabled. Skipping package installation.");
                var packageNames = string.Join(", ", _nuGetPackages);
                _failedPackageExceptions[packageNames] = new InvalidOperationException("NuGet package restore is disabled.");
                return;
            }

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

                    if (IsNuGetRestoreDisabledException(ex))
                    {
                        LogError($"NuGet restore is disabled. Error: {ex.Message}");
                        AddPackageReferencesToProject();
                        var projectName = _project?.Name ?? "Unknown Project";
                        var packageNames = string.Join(", ", _nuGetPackages);
                        _ = DisplayInfoBarAsync(string.Format(Resources._1056, projectName, packageNames));
                        return;
                    }

                    LogError($"Failed to install NuGet package: {packageId}. Error: {ex.Message}");
                    _failedPackageExceptions[packageId] = ex;
                }
            }

            if (_failedPackageExceptions.Count > 0)
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();

                bool isRestoreDisabled = _failedPackageExceptions.Values
                    .Any(e => IsNuGetRestoreDisabledException(e));

                if (isRestoreDisabled)
                {
                    AddPackageReferencesToProject();
                    var projectName = _project?.Name ?? "Unknown Project";
                    var packageNames = string.Join(", ", _nuGetPackages);
                    _ = DisplayInfoBarAsync(string.Format(Resources._1056, projectName, packageNames));
                }
                else
                {
                    // Build error message in the requested format
                    var errorMessage = CreateErrorMessage(ErrorMessageFormat.InfoBar);
                    LogError(errorMessage);
                    _ = DisplayInfoBarAsync(errorMessage);
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
            ThreadHelper.ThrowIfNotOnUIThread();
            Guid _projectGuid = GetProjectGuid(_project);
            if (_projectGuid.Equals(SolutionVCProjectGuid))
            {
                // For C++ projects, installation is synchronous so builds are already
                // re-enabled by the finally block. Dispose as a safety net.
                UnadviseSolutionEvents();
                s_buildGuard.Dispose();

                if (_failedPackageExceptions.Count > 0)
                {
                    bool isRestoreDisabled = _failedPackageExceptions.Values
                        .Any(ex => IsNuGetRestoreDisabledException(ex));

                    if (isRestoreDisabled)
                    {
                        var projectName = _project?.Name ?? "Unknown Project";
                        var packageNames = string.Join(", ", _nuGetPackages);
                        _ = DisplayInfoBarAsync(string.Format(Resources._1056, projectName, packageNames));
                        ShowOutputWindow(CreateDetailedErrorMessage());
                        return;
                    }

                    var errorMessage = CreateErrorMessage(ErrorMessageFormat.MessageBox);
                    LogError(errorMessage);

                    var result = MessageBox.Show(
                    errorMessage,
                    Resources._1046,
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

        private void AddPackageReferencesToProject()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            try
            {
                if (_project == null || _nuGetPackages == null)
                {
                    return;
                }

                string projectPath = _project.FullName;
                if (!File.Exists(projectPath))
                {
                    return;
                }

                var doc = XDocument.Load(projectPath);
                XNamespace ns = doc.Root.GetDefaultNamespace();

                var itemGroup = doc.Root.Elements(ns + "ItemGroup")
                    .FirstOrDefault(ig => ig.Elements(ns + "PackageReference").Any());

                if (itemGroup == null)
                {
                    itemGroup = new XElement(ns + "ItemGroup");
                    doc.Root.Add(itemGroup);
                }

                foreach (var packageId in _nuGetPackages)
                {
                    bool alreadyExists = itemGroup.Elements(ns + "PackageReference")
                        .Any(e => string.Equals(
                            (string)e.Attribute("Include"), packageId, StringComparison.OrdinalIgnoreCase));

                    if (!alreadyExists)
                    {
                        itemGroup.Add(new XElement(ns + "PackageReference",
                            new XAttribute("Include", packageId),
                            new XAttribute("Version", "*")));
                    }
                }

                doc.Save(projectPath);
            }
            catch (Exception ex)
            {
                LogError($"Failed to add package references to project file: {ex.Message}");
            }
        }

        // NuGet package restore is enabled by default, so only return false if we can confirm it is disabled in
        // the user's config.
        private static bool IsNuGetPackageRestoreEnabled()
        {
            try
            {
                string configPath = Path.Combine(
                    Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                    "NuGet",
                    "NuGet.Config");

                // If no NuGet.config is provided, package restore is enabled by default
                if (!File.Exists(configPath))
                {
                    System.Diagnostics.Debug.WriteLine($"NuGet.Config not found at: {configPath}. Assuming package restore is enabled.");
                    return true;
                }

                // If package restore is not disabled, then it is enabled by default
                var doc = XDocument.Load(configPath);
                var packageRestore = doc.Descendants("packageRestore").FirstOrDefault();
                if (packageRestore == null)
                {
                    System.Diagnostics.Debug.WriteLine("No packageRestore section found in NuGet.Config. Assuming enabled.");
                    return true;
                }

                var enabledElement = packageRestore.Elements("add")
                    .FirstOrDefault(e => string.Equals(
                        (string)e.Attribute("key"), "enabled", StringComparison.OrdinalIgnoreCase));

                if (enabledElement != null)
                {
                    string value = (string)enabledElement.Attribute("value");

                    // Only explicit disabling of package restore should return false.
                    if (string.Equals(value, "False", StringComparison.OrdinalIgnoreCase))
                    {
                        System.Diagnostics.Debug.WriteLine("NuGet package restore is explicitly disabled in NuGet.Config.");
                        return false;
                    }
                }

                System.Diagnostics.Debug.WriteLine("NuGet package restore is enabled (no explicit disable found).");
                return true;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Error reading NuGet.Config: {ex.Message}. Assuming package restore is enabled.");
                return true;
            }
        }

        private static bool IsNuGetRestoreDisabledException(Exception ex)
        {
            for (var current = ex; current != null; current = current.InnerException)
            {
                if (current.Message != null &&
                    (current.Message.IndexOf("NuGet restore is currently disabled", StringComparison.OrdinalIgnoreCase) >= 0 ||
                     current.Message.IndexOf("package restore is disabled", StringComparison.OrdinalIgnoreCase) >= 0 ||
                     current.Message.IndexOf("EnableNuGetPackageRestore", StringComparison.OrdinalIgnoreCase) >= 0))
                {
                    return true;
                }
            }

            return false;
        }

        private void UnadviseSolutionEvents()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_solution != null && _solutionEventsCookie != 0)
            {
                _solution.UnadviseSolutionEvents(_solutionEventsCookie);
                _solutionEventsCookie = 0;
            }
        }

        public int OnAfterOpenProject(IVsHierarchy pHierarchy, int fAdded)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            s_buildGuard.DisableBuilds();
            if (s_buildGuard.IsBlocking)
            {
                UnadviseSolutionEvents();
            }
            return VSConstants.S_OK;
        }

        public int OnQueryCloseProject(IVsHierarchy pHierarchy, int fRemoving, ref int pfCancel)
        {
            return VSConstants.S_OK;
        }

        public int OnBeforeCloseProject(IVsHierarchy pHierarchy, int fRemoved)
        {
            return VSConstants.S_OK;
        }

        public int OnAfterLoadProject(IVsHierarchy pStubHierarchy, IVsHierarchy pRealHierarchy)
        {
            return VSConstants.S_OK;
        }

        public int OnQueryUnloadProject(IVsHierarchy pRealHierarchy, ref int pfCancel)
        {
            return VSConstants.S_OK;
        }

        public int OnBeforeUnloadProject(IVsHierarchy pRealHierarchy, IVsHierarchy pStubHierarchy)
        {
            return VSConstants.S_OK;
        }

        public int OnAfterOpenSolution(object pUnkReserved, int fNewSolution)
        {
            return VSConstants.S_OK;
        }

        public int OnQueryCloseSolution(object pUnkReserved, ref int pfCancel)
        {
            return VSConstants.S_OK;
        }

        public int OnBeforeCloseSolution(object pUnkReserved)
        {
            return VSConstants.S_OK;
        }

        public int OnAfterCloseSolution(object pUnkReserved)
        {
            return VSConstants.S_OK;
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

            try
            {
                var packageNames = string.Join(", ", _failedPackageExceptions.Keys);
                var separator = format == ErrorMessageFormat.MessageBox ? "\n\n" : " ";
                var projectName = _project?.Name ?? "Unknown Project";
                var errorMessage = format == ErrorMessageFormat.InfoBar ?
                string.Format(Resources._1047, projectName, packageNames)
                : string.Format(Resources._1048, projectName, packageNames);
                return errorMessage;
            }
            catch (MissingManifestResourceException ex)
            {
                ShowLocalizationErrorDialog(ex);
                // Return a fallback message
                var packageNames = string.Join(", ", _failedPackageExceptions.Keys);
                return $"Unable to add package references to project: {packageNames}";
            }
        }

        private string CreateDetailedErrorMessage()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            try
            {
                var errorLines = new System.Text.StringBuilder();
                var projectName = _project?.Name ?? "Unknown Project";
                errorLines.AppendLine(string.Format(Resources._1051, projectName));

                foreach (var package in _failedPackageExceptions)
                {
                    errorLines.AppendLine($"{package.Key} - {package.Value.GetType().FullName}: {package.Value.Message}");
                }

                errorLines.AppendLine();
                errorLines.Append(Resources._1052);

                return errorLines.ToString();
            }
            catch (MissingManifestResourceException ex)
            {
                ShowLocalizationErrorDialog(ex);
                // Return a fallback message
                var errorLines = new System.Text.StringBuilder();
                var projectName = _project?.Name ?? "Unknown Project";
                errorLines.AppendLine($"Missing package references for project: {projectName}");

                foreach (var package in _failedPackageExceptions)
                {
                    errorLines.AppendLine($"{package.Key} - {package.Value.GetType().FullName}: {package.Value.Message}");
                }

                errorLines.AppendLine();
                errorLines.Append("Please add the package references manually using NuGet Package Manager.");

                return errorLines.ToString();
            }
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

        private void ShowAutomaticPackageDownloadNotEnabledErrorDialog()
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            var errorMessage = "Automatic NuGet package download is not enabled. The required packages for this project template cannot be installed automatically.\n\n" +
                "To enable automatic package download, go to Tools > Options > NuGet Package Manager and check 'Allow NuGet to download missing packages'.\n\n" +
                "After enabling this option, please close and reopen the solution, then the packages will be installed automatically.";
            MessageBox.Show(
                errorMessage,
                "Automatic Package Download Disabled",
                MessageBoxButtons.OK,
                MessageBoxIcon.Warning);
            // Also log to activity log
            LogError("Automatic NuGet package download is disabled. User prompted to enable it.");
            // Show in output window
            ShowOutputWindow($"Automatic NuGet package download is disabled. User prompted to enable it.\n{errorMessage}");
        }

        private void ShowLocalizationErrorDialog(MissingManifestResourceException ex)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            var errorMessage = $"A localization error occurred while loading the template wizard:\n\n{ex.Message}\n\n" +
            "The template may not have been installed correctly. Please reinstall the Windows App SDK extension.";

            MessageBox.Show(
                errorMessage,
                "Localization Error",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error);

            // Also log to activity log
            LogError($"Localization error: {ex.Message}");

            // Show in output window
            ShowOutputWindow($"Localization Error:\n{ex.Message}\n{ex.StackTrace}");
        }

        private async Task DisplayInfoBarAsync(string errorMessage)
        {
            try
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                var infoBar = CreateNuGetInfoBar(errorMessage);
                var infoBarUi = CreateInfoBarUI(infoBar);

                // Write detailed error message to output window
                var detailedErrorMessage = CreateDetailedErrorMessage();
                ShowOutputWindow(detailedErrorMessage);

                if (infoBarUi == null)
                {
                    ShowOutputWindow("[InfoBar] Failed: Could not create InfoBar UI element.");
                    return;
                }

                infoBarUi.Advise(new NuGetInfoBarUIEvents(detailedErrorMessage), out uint _);

                IVsShell shell = ServiceProvider.GlobalProvider.GetService(typeof(SVsShell)) as IVsShell;
                if (shell == null)
                {
                    ShowOutputWindow("[InfoBar] Failed: Could not obtain IVsShell service.");
                    return;
                }

                // The main window InfoBar host may not be available immediately
                // during template wizard execution while the main window initializes.
                IVsInfoBarHost infoBarHost = null;
                for (int retry = 0; retry < 5; retry++)
                {
                    shell.GetProperty((int)__VSSPROPID7.VSSPROPID_MainWindowInfoBarHost, out object infoBarHostObj);
                    if (infoBarHostObj is IVsInfoBarHost host)
                    {
                        infoBarHost = host;
                        break;
                    }

                    await Task.Delay(1000);
                    await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                }

                if (infoBarHost != null)
                {
                    infoBarHost.AddInfoBar(infoBarUi);
                }
                else
                {
                    ShowOutputWindow("[InfoBar] Failed: Main window InfoBar host not available after retries.");
                }
            }
            catch (Exception ex)
            {
                ShowOutputWindow($"[InfoBar] Exception: {ex.Message}");
            }
        }

        private IVsInfoBarUIElement CreateInfoBarUI(IVsInfoBar infoBar)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            if (infoBar == null)
            {
                LogError("InfoBar model is null.");
                return null;
            }

            if (_infoBarUIFactory == null)
            {
                LogError("Could not obtain IVsInfoBarUIFactory service");
                return null;
            }

            return _infoBarUIFactory.CreateInfoBar(infoBar);
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
                new InfoBarHyperlink(Resources._1049, "ManageNuGetPackages"),
                new InfoBarHyperlink(Resources._1050, "SeeErrorDetails")
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
