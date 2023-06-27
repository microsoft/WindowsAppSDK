using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AppAttachExtension.Notification
{
    public class OutputPane
    {
        private IVsOutputWindowPane pane;
        public IVsOutputWindowPane getPane()
        {
            return pane;
        }
        public async Task OutputPaneHandlerAsync()
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            AsyncPackage pack = AppAttach.Instance.Packageval();
            System.IServiceProvider serviceProvider = pack as System.IServiceProvider;
            Guid paneGuid = Guid.NewGuid();

            string paneName = "App-Attach";

            IVsOutputWindow output = (IVsOutputWindow)serviceProvider.GetService(typeof(SVsOutputWindow));
            int hr = output.CreatePane(ref paneGuid, paneName, Convert.ToInt32(true), Convert.ToInt32(false));
            ErrorHandler.ThrowOnFailure(hr);
            hr = output.GetPane(ref paneGuid, out pane);
            ErrorHandler.ThrowOnFailure(hr);
            pane.Activate();
        }
    }
}
