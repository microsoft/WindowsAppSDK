using AppAttachExtension.Contracts;
using AppAttachExtension.Models;
using Microsoft.IO;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AppAttachExtension.Utils
{
    public class JsonParserUtil
    {
        public static string ConvertJsonForPublish(PublishViewModel publishViewModel, IdentityViewModel identityViewModel, IDEResouceModel resourceModel, AppAttachViewContract contract)
        {
            bool localPublish = false;
            if (publishViewModel == null || identityViewModel == null || resourceModel == null)
            {
                localPublish = true;
            }
            if (publishViewModel != null && (string.IsNullOrEmpty(publishViewModel.SubscriptionName) || string.IsNullOrEmpty(publishViewModel.WorkspaceName) || string.IsNullOrEmpty(publishViewModel.FileShareName)
                || string.IsNullOrEmpty(publishViewModel.HostPoolName) || string.IsNullOrEmpty(publishViewModel.ResourceGroupName) || string.IsNullOrEmpty(publishViewModel.StorageAccountName)))
            {
                localPublish = true;
            }
            if (identityViewModel != null && (string.IsNullOrEmpty(identityViewModel.JwtToken) && (string.IsNullOrEmpty(identityViewModel.Upn) && string.IsNullOrEmpty(identityViewModel.UserName) && string.IsNullOrEmpty(identityViewModel.UserEmail))))
            {
                localPublish = true;
            }
            if (!localPublish)
            {
                contract.AzureApplicationGroupName = publishViewModel.ApplicationGroupName;
                contract.AzureSubscriptionId = publishViewModel.SubscriptionName;
                contract.AzureWorkspace = publishViewModel.WorkspaceName;
                contract.AzureStorageFileShare = publishViewModel.FileShareName;
                contract.AzureHostPoolName = publishViewModel.HostPoolName;
                contract.AzureResourceGroup = publishViewModel.ResourceGroupName;
                contract.AzureStorageAccount = publishViewModel.StorageAccountName;
                contract.EmailId = string.IsNullOrEmpty(identityViewModel.Upn) ? identityViewModel.UserEmail : identityViewModel.Upn;
                contract.MsbuildPath = resourceModel.BuildPath;
                contract.ProjectFilePath = resourceModel.ProjectPath;
                contract.AzureStorageKey = identityViewModel.StorageAccountConnectionString;
                contract.AccessToken = identityViewModel.JwtToken;
                contract.IsPublishRequired = bool.TrueString;
            }
            else
            {
                contract.IsPublishRequired = bool.FalseString;
            }
            contract.MsbuildPath = resourceModel.BuildPath;
            contract.ProjectFilePath = resourceModel.ProjectPath;
            var msixManagerPath = $"MSIXMGR\\x64\\msixmgr.exe";
            var assemblyPath = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), msixManagerPath);
            if (File.Exists(assemblyPath))
            {
                contract.MsixManagerPath = assemblyPath;
            }
            return JsonConvert.SerializeObject(contract);

        }
    }
}
