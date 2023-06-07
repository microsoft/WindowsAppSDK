using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace AppAttachAPI.Utils
{
    public static class PrepareArguments
    {
        private static readonly Dictionary<string, string> ATTRIBUTE_CLASSNAME_MAP = new Dictionary<string, string>()
        {
            {AttrConsts.ACCESS_TOKEN, "AccessToken"},
            {AttrConsts.AZURE_APPLICATION_GROUP_NAME, "AzureApplicationGroupName"},
            {AttrConsts.AZURE_HOST_POOL_NAME, "AzureHostPoolName"},
            {AttrConsts.AZURE_RESOURCE_GROUP, "AzureResourceGroup"},
            {AttrConsts.AZURE_STORAGE_ACCOUNT, "AzureStorageAccount"},
            {AttrConsts.AZURE_STORAGE_FILE_SHARE, "AzureStorageFileShare"},
            {AttrConsts.AZURE_STORAGE_KEY, "AzureStorageKey"},
            {AttrConsts.AZURE_SUBSCRIPTION_ID, "AzureSubscriptionId"},
            {AttrConsts.AZURE_WORKSPACE, "AzureWorkspace"},
            {AttrConsts.CERTIFICATE_PASSWORD, "CertificatePassword"},
            {AttrConsts.CERTIFICATE_PATH, "CertificatePath"},
            {AttrConsts.CONFIGURATION, "Configuration"},
            {AttrConsts.PROJECT_FILE_PATH, "ProjectFilePath"},
            {AttrConsts.EMAIL_ID, "EmailId"},
            {AttrConsts.IS_PUBLISH_REQUIRED, "IsPublishRequired"},
            {AttrConsts.MSBUILD_PATH, "MsbuildPath"},
            {AttrConsts.MSIX_MANAGER_PATH, "MsixManagerPath"},
            {AttrConsts.PACKAGE_LOCATION, "PackageLocation"},
            {AttrConsts.PACKAGE_VERSION, "PackageVersion"},
            {AttrConsts.PLATFORM, "Platform"}
        };

        private static readonly Dictionary<string, IAttribute> ATTRIBUTE_OBJECT_MAP = new Dictionary<string, IAttribute>();

        public static Dictionary<string, IAttribute> prepare(string jsonObject)
        {
            ATTRIBUTE_OBJECT_MAP.Clear();
            Dictionary<string, string> jsonKeyValueMap = JsonConvert.DeserializeObject<Dictionary<string, string>>(jsonObject);

            string jsonNode = string.Empty;
            foreach (var jsonKeyValue in jsonKeyValueMap)
            {
                if (!ATTRIBUTE_CLASSNAME_MAP.TryGetValue(jsonKeyValue.Key, out jsonNode))
                {
                    continue;
                }
                jsonNode = jsonKeyValue.Key;
                IAttribute attributeInstance = AssemblyUtils.GetAttributeInstance(ATTRIBUTE_CLASSNAME_MAP[jsonNode]);
                attributeInstance.getAttributeName();
                attributeInstance.setAttributeValue(jsonKeyValue.Value);
                ATTRIBUTE_OBJECT_MAP.Add(jsonNode, attributeInstance);
            }

            return ATTRIBUTE_OBJECT_MAP;
        }
    }
}
