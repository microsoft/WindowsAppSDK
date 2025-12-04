// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

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
    internal static class OutputWindowHelper
    {
        /// <summary>
        /// Writes a message to the Visual Studio Output window and activates it.
        /// </summary>
        /// <param name="message">The message to write to the output window.</param>
        /// <param name="clearPane">Whether to clear the pane before writing the message.</param>
        public static void ShowMessageInOutputWindow(string message, bool clearPane = true)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            // Log to Output window
            IVsOutputWindow outputWindow = ServiceProvider.GlobalProvider.GetService(typeof(SVsOutputWindow)) as IVsOutputWindow;
            if (outputWindow != null)
            {
                Guid guidGeneral = Microsoft.VisualStudio.VSConstants.GUID_OutWindowGeneralPane;
                IVsOutputWindowPane pane;
                int hr = outputWindow.GetPane(ref guidGeneral, out pane);

                // Create pane if it doesn't exist
                if (pane == null)
                {
                    var generalWindowTitle = Resources._1053;
                    hr = outputWindow.CreatePane(ref guidGeneral, generalWindowTitle, 1, 1);
                    if (hr == Microsoft.VisualStudio.VSConstants.S_OK)
                    {
                        outputWindow.GetPane(ref guidGeneral, out pane);
                    }
                }

                if (pane != null)
                {
                    pane.Activate();
                    if (clearPane)
                    {
                        pane.Clear();
                    }
                    var noOutputString = Resources._1054;
                    pane.OutputStringThreadSafe(message ?? noOutputString);
                    pane.OutputStringThreadSafe("\n");
                }
            }

            // Show the Output window
            var dte = ServiceProvider.GlobalProvider.GetService(typeof(EnvDTE.DTE)) as EnvDTE.DTE;
            if (dte != null)
            {
                dte.ExecuteCommand("View.Output");
            }
        }
    }
}
