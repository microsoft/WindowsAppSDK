// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.Shell.Interop;
using System.ComponentModel.Design;
using System.Linq;
using System.Xml.Linq;

namespace AppAttachExtension
{
    [Command(PackageIds.AppAttach)]
    internal sealed class AppAttach
    {
        private readonly AsyncPackage package;
        public const int CommandId = 0x0100;
        public const string commandGuid = "ac8bcc47-f5f3-4afa-8cc2-f0d697e04bb7";

        public static AppAttach Instance
        {
            get;
            private set;
        }

        public static readonly Guid CommandSet = new Guid(commandGuid);

        public static void Initialize(AsyncPackage package, IMenuCommandService commandService)
        {
            Instance = new AppAttach(package, commandService);
        }

        private AppAttach(AsyncPackage package, IMenuCommandService commandService)
        {
            this.package = package ?? throw new ArgumentNullException(nameof(package));
            commandService = commandService ?? throw new ArgumentNullException(nameof(commandService));

            var menuCommandID = new CommandID(CommandSet, CommandId);
            var menuItem = new OleMenuCommand(this.Execute, menuCommandID);
            menuItem.BeforeQueryStatus += new EventHandler(OnBeforeQueryStatusAsync);
            commandService.AddCommand(menuItem);
        }

        private async void OnBeforeQueryStatusAsync(object sender, EventArgs e)
        {
            var appAttachCommand = sender as OleMenuCommand;
            appAttachCommand.Visible = false;
            appAttachCommand.Enabled = false;
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            var _dte2 = await ServiceProvider.GetGlobalServiceAsync(typeof(SDTE)) as DTE2;
            var selectedItem = _dte2.SelectedItems.Item(1);
            var project = selectedItem.Project;
            if (project != null)
            {
                string projectPath = project.FullName;
                XDocument projectDoc = XDocument.Load(projectPath);
                XNamespace ns = projectDoc.Root.Name.Namespace;

                XElement useWinUIElement = projectDoc.Descendants(ns + "UseWinUI").FirstOrDefault();
                if (appAttachCommand != null)
                {
                    appAttachCommand.Visible = useWinUIElement.Value == "true";
                    appAttachCommand.Enabled = false;
                    if (_dte2.Solution.IsOpen && _dte2.Solution.SolutionBuild.BuildState != vsBuildState.vsBuildStateInProgress)
                    {
                        appAttachCommand.Enabled = true;
                    }
                }
            }

        }

        private void Execute(object sender, EventArgs e)
        {
            AppAttachWindow appAttachWindow = new AppAttachWindow();
            appAttachWindow.ShowModal();
        }

        public AsyncPackage Packageval()
        {
            return package;
        }

    }
}
