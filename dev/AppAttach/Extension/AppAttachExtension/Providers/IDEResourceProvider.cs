// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachExtension.Models;
using EnvDTE80;
using Microsoft.VisualStudio.Setup.Configuration;
using Microsoft.VisualStudio.Shell.Interop;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AppAttachExtension.Providers
{
    public class IDEResourceProvider
    {
        private readonly IDEResouceModel _model;

        public IDEResourceProvider()
        {
            _model = new IDEResouceModel();
        }

        public async Task PopulateIDEModelAsync()
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            var _dte2 = await ServiceProvider.GetGlobalServiceAsync(typeof(SDTE)) as DTE2;
            var selectedItem = _dte2.SelectedItems.Item(1);
            _model.ProjectPath = selectedItem.Project.FullName;
            var vsVersion = _dte2.Version.Split('.')[0];
            var vsEdition = _dte2.Edition;
            var filePath = "";
            var query = new SetupConfiguration();
            var query2 = (ISetupConfiguration2)query;
            var e = query2.EnumAllInstances();

            var helper = (ISetupHelper)query;
            List<string> list = new List<string>();
            int fetched;
            var instances = new ISetupInstance[1];
            do
            {
                e.Next(1, instances, out fetched);
                if (fetched > 0)
                    list.Add(instances[0].GetInstallationPath());
            } while (fetched > 0);
            string version = vsVersion == "17" ? "2022" : "2019";
            filePath = list.Where(l => l.Contains(version) && (l.Contains(_dte2.Edition))).FirstOrDefault();
            filePath += "\\MSBuild\\Current\\Bin\\MSBuild.exe";

            if (File.Exists(filePath))
            {
                _model.BuildPath = filePath;
            }

        }

        public IDEResouceModel GetModel()
        {
            return _model;
        }
    }
}
