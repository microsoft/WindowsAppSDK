// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

namespace WindowsAppSDK.TemplateUtilities
{
    public class NuGetInfoBarUIEvents : IVsInfoBarUIEvents
    {
        private readonly string _detailedErrorMessage;

        public NuGetInfoBarUIEvents(string detailedErrorMessage = null)
        {
            _detailedErrorMessage = detailedErrorMessage;
        }

        public void OnActionItemClicked(IVsInfoBarUIElement infoBarUIElement, IVsInfoBarActionItem actionItem)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            if (actionItem is InfoBarHyperlink hyperlink)
            {
                if (hyperlink.Text == "Manage NuGet Packages")
                {
                    var dte = ServiceProvider.GlobalProvider.GetService(typeof(EnvDTE.DTE)) as EnvDTE.DTE;
                    dte?.ExecuteCommand("Project.ManageNuGetPackages");
                }
                else if (hyperlink.Text == "See error details")
                {
                    ShowErrorDetails();
                }
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
