// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachExtension.Notification;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AppAttachExtension.Helper
{
    public class ProjectHelper
    {
        private OutputPane outputPane;
        public static ProjectHelper Instance { get; } = new ProjectHelper();

        private ProjectHelper() { }

        public async Task CreateOutputPaneAsync()
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            outputPane = new OutputPane();
            await outputPane.OutputPaneHandlerAsync();
            outputPane.getPane().Clear();
        }

        public OutputPane GetOutputPane()
        {
            return outputPane;
        }
    }
}
