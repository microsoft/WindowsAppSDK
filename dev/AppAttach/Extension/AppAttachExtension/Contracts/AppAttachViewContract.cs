// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using Newtonsoft.Json;

namespace AppAttachExtension.Contracts
{
    public class AppAttachViewContract
    {
        [JsonProperty(PropertyName = "emailId")]
        public string EmailId { get; set; }

        [JsonProperty(PropertyName = "accessToken")]
        public string AccessToken { get; set; }

        [JsonProperty(PropertyName = "packageLocation")]
        public string PackageLocation { get; set; }

        [JsonProperty(PropertyName = "projectFilePath")]
        public string ProjectFilePath { get; set; }

        [JsonProperty(PropertyName = "configuration")]
        public string Configuration { get; set; }

        [JsonProperty(PropertyName = "platform")]
        public string Platform { get; set; }

        [JsonProperty(PropertyName = "certificatePath")]
        public string CertificatePath { get; set; }

        [JsonProperty(PropertyName = "certificatePassword")]
        public string CertificatePassword { get; set; }

        [JsonProperty(PropertyName = "packageVersion")]
        public string PackageVersion { get; set; }

        [JsonProperty(PropertyName = "isPublishRequired")]
        public string IsPublishRequired { get; set; }

        [JsonProperty(PropertyName = "msbuildPath")]
        public string MsbuildPath { get; set; }

        [JsonProperty(PropertyName = "msixManagerPath")]
        public string MsixManagerPath { get; set; }

        [JsonProperty(PropertyName = "azureStorageKey")]
        public string AzureStorageKey { get; set; }

        [JsonProperty(PropertyName = "azureWorkspace")]
        public string AzureWorkspace { get; set; }

        [JsonProperty(PropertyName = "azureStorageFileShare")]
        public string AzureStorageFileShare { get; set; }

        [JsonProperty(PropertyName = "azureStorageAccount")]
        public string AzureStorageAccount { get; set; }

        [JsonProperty(PropertyName = "azureSubscriptionId")]
        public string AzureSubscriptionId { get; set; }

        [JsonProperty(PropertyName = "azureResourceGroup")]
        public string AzureResourceGroup { get; set; }

        [JsonProperty(PropertyName = "azureHostPoolName")]
        public string AzureHostPoolName { get; set; }

        [JsonProperty(PropertyName = "azureApplicationGroupName")]
        public string AzureApplicationGroupName { get; set; }


        public AppAttachViewContract()
        {
            AccessToken = "";
            EmailId = "";
            PackageLocation = "";
            PackageVersion = "";
            ProjectFilePath = "";
            Configuration = "";
            Platform = "";
            CertificatePath = "";
            CertificatePassword = "";
            IsPublishRequired = "";
            MsbuildPath = "";
            MsixManagerPath = "";
            AzureSubscriptionId = "";
            AzureResourceGroup = "";
            AzureStorageKey = "";
            AzureStorageAccount = "";
            AzureStorageFileShare = "";
            AzureApplicationGroupName = "";
            AzureWorkspace = "";
            AzureHostPoolName = "";
        }
    }
}
