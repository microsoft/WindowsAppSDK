// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.ApplicationModel.Resources;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace SampleLibrary
{
    public class SampleType
    {
        public string GetDefaultSampleString()
        {
            var resourceLoader = new ResourceLoader();
            return resourceLoader.GetString("SampleString");
        }
    }
}
