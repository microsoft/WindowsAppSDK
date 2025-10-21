using System;
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
            
            // Log detailed errors to Output window
            IVsOutputWindow outputWindow = ServiceProvider.GlobalProvider.GetService(typeof(SVsOutputWindow)) as IVsOutputWindow;
            if (outputWindow != null)
            {
                Guid guidGeneral = Microsoft.VisualStudio.VSConstants.GUID_OutWindowGeneralPane;
                IVsOutputWindowPane pane;
                int hr = outputWindow.GetPane(ref guidGeneral, out pane);
                
                // If the pane doesn't exist, create it
                if (hr != Microsoft.VisualStudio.VSConstants.S_OK || pane == null)
                {
                    outputWindow.CreatePane(ref guidGeneral, "General", 1, 1);
                    outputWindow.GetPane(ref guidGeneral, out pane);
                }
                
                if (pane != null)
                {
                    pane.Activate();
                    pane.Clear();
                    pane.OutputStringThreadSafe(_detailedErrorMessage ?? "No error details available.");
                    pane.OutputStringThreadSafe("\n");
                }
            }

            // Also show the Output window
            var dte = ServiceProvider.GlobalProvider.GetService(typeof(EnvDTE.DTE)) as EnvDTE.DTE;
            if (dte != null)
            {
                dte.ExecuteCommand("View.Output");
            }
        }

        public void OnClosed(IVsInfoBarUIElement infoBarUIElement)
        {
        }
    }
}
