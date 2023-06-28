// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachMessenger;
using AppAttachMessenger.Interface;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AppAttachExtension.Implementation
{
    public class VSMessageHandler : IMessageHandler
    {
        IVsOutputWindowPane pane;
        public VSMessageHandler(IVsOutputWindowPane pane)
        {
            this.pane = pane;
        }
        public string HandleMessage(Message m)
        {
            this.pane.OutputString(m.Content);

            return m.Content;
        }
    }
}
