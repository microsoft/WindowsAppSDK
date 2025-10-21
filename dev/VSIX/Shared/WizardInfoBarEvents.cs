using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

namespace WindowsAppSDK.TemplateUtilities
{
    public class NuGetInfoBarUIEvents : IVsInfoBarUIEvents
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
        }
    }
}
