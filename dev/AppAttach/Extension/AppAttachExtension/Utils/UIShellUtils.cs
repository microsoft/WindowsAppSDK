// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachExtension.Enums;
using Microsoft.VisualStudio.Shell.Interop;
using System.Windows.Controls;

namespace AppAttachExtension.Utils
{
    public class UIShellUtils
    {
        public static IVsThreadedWaitDialog2 OpenDialogBoxWithPageDisable(Page page, string header, string content)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            IVsThreadedWaitDialog2 dialog = null;
            IVsThreadedWaitDialogFactory dlgFactory = Package.GetGlobalService(typeof(SVsThreadedWaitDialogFactory)) as IVsThreadedWaitDialogFactory;
            if (dlgFactory != null)
            {
                dlgFactory.CreateInstance(out dialog);
                page.IsEnabled = false;
                dialog?.StartWaitDialog(header, content, "", null, "", 0, false, true);
            }
            return dialog;
        }

        public static void CloseDialogWithPageEnable(Page page, IVsThreadedWaitDialog2 dialog)
        {
            page.IsEnabled = true;
            dialog?.EndWaitDialog();
        }

        public static int ShowMessageBox(string content, string header, MessageBoxTypeEnum messageBoxTypeEnum)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            IVsUIShell uiShell = (IVsUIShell)Package.GetGlobalService(typeof(SVsUIShell));
            string message = content;
            string title = header;
            Guid clsid = Guid.Empty;
            int result = 0;
            switch (messageBoxTypeEnum)
            {
                case MessageBoxTypeEnum.Info:
                    uiShell.ShowMessageBox(
                   0,
                   ref clsid,
                   title,
                   message,
                   string.Empty,
                   0,
                   OLEMSGBUTTON.OLEMSGBUTTON_OK,
                   OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST,
                   OLEMSGICON.OLEMSGICON_INFO,
                   0,        // false
                   out result);
                    break;

                case MessageBoxTypeEnum.Error:
                    uiShell.ShowMessageBox(
                    0,
                    ref clsid,
                    title,
                    message,
                    string.Empty,
                    0,
                    OLEMSGBUTTON.OLEMSGBUTTON_OK,
                    OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST,
                    OLEMSGICON.OLEMSGICON_CRITICAL,
                    0,        // false
                    out result);
                    break;

                case MessageBoxTypeEnum.InfoWithConfirmation:
                    uiShell.ShowMessageBox(
                    0,
                    ref clsid,
                    title,
                    message,
                    string.Empty,
                    0,
                    OLEMSGBUTTON.OLEMSGBUTTON_OKCANCEL,
                    OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST,
                    OLEMSGICON.OLEMSGICON_INFO,
                    0,        // false
                    out result);
                    break;
            }

            return result;
        }
    }
}
