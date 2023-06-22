// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

global using Community.VisualStudio.Toolkit;
global using Microsoft.VisualStudio.Shell;
global using System;
global using Task = System.Threading.Tasks.Task;
using Microsoft.VisualStudio.Shell.Interop;
using System.ComponentModel.Design;
using System.Runtime.InteropServices;
using System.Threading;

namespace AppAttachExtension
{
    [PackageRegistration(UseManagedResourcesOnly = true, AllowsBackgroundLoading = true)]
    [InstalledProductRegistration(Vsix.Name, Vsix.Description, Vsix.Version)]
    [ProvideMenuResource("Menus.ctmenu", 1)]
    [ProvideAutoLoad(UIContextGuids.SolutionExists, PackageAutoLoadFlags.BackgroundLoad)]
    [Guid(PackageGuids.guidAppAttachExtensionString)]
    public sealed class AppAttachExtensionPackage : AsyncPackage
    {
        protected override async Task InitializeAsync(CancellationToken cancellationToken, IProgress<ServiceProgressData> progress)
        {
            var commandService = await GetServiceAsync((typeof(IMenuCommandService))) as IMenuCommandService;

            AppAttach.Initialize(this, commandService);
        }
    }
}