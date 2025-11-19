// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

namespace WindowsAppSDK.TemplateUtilities
{
    public class NuGetInfoBarUIEvents : IVsInfoBarUIEvents
    {
        private readonly string _detailedErrorMessage;

        public NuGetInfoBarUIEvents(string detailedErrorMessage)
        {
            _detailedErrorMessage = detailedErrorMessage;
        }

        // This method handles clicks for the InfoBarHyperlinks in WizardImplmentation.cs' CreateNuGetInfoBar()
        public void OnActionItemClicked(IVsInfoBarUIElement infoBarUIElement, IVsInfoBarActionItem actionItem)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (infoBarUIElement == null || actionItem == null)
            {
                OutputWindowHelper.ShowMessageInOutputWindow("Hyperlink not found");
                return;
            }

            if (actionItem is InfoBarHyperlink hyperlink)
            {
                // ActionContext can be any object, so we need to cast it to a string
                string actionContext = hyperlink.ActionContext as string;

                if (actionContext == "SeeErrorDetails")
                {
                    ShowErrorDetails();
                }
                else if (actionContext == "ManageNuGetPackages")
                {
                    OpenNuGetPackageManager();
                }
            }
        }

        private void OpenNuGetPackageManager()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            try
            {
                var dte = ServiceProvider.GlobalProvider.GetService(typeof(EnvDTE.DTE)) as EnvDTE.DTE;
                if (dte == null)
                {
                    OutputWindowHelper.ShowMessageInOutputWindow("Could not obtain DTE service to open NuGet Package Manager.");
                    return;
                }

                // Use the command GUID and ID instead of localized command name
                // This is the GUID for NuGet Package Manager commands
                // GUID: {25fd982b-8cae-4cbd-a440-e03ffccde106}
                // ID: 0x100 for Tools.ManageNuGetPackagesforSolution
                // https://devblogs.microsoft.com/dotnet/invoke-manage-nuget-packages-dialog-programmatically/
                var guidString = "{25fd982b-8cae-4cbd-a440-e03ffccde106}";
                var commandId = 0x100;

                object customIn = null;
                object customOut = null;
                dte.Commands.Raise(guidString, commandId, ref customIn, ref customOut);
            }
            catch (Exception ex)
            {
                OutputWindowHelper.ShowMessageInOutputWindow($"Failed to open NuGet Package Manager: {ex.Message}");
            }
        }

        private void ShowErrorDetails()
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            OutputWindowHelper.ShowMessageInOutputWindow(_detailedErrorMessage);
        }

        public void OnClosed(IVsInfoBarUIElement infoBarUIElement)
        {
        }
    }
}
