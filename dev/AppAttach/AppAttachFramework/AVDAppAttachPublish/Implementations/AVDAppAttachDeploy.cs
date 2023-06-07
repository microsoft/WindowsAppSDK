using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using AVDAppAttachPublish.Interfaces;
using System;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Implementations
{
    /// <summary>
    /// Implementation of the IAVDAppAttachDeploy interface that deploys an MSIX package to an Azure AVD host pool and application group.
    /// </summary>
    public class AVDAppAttachDeploy : IAVDAppAttachDeploy
    {
        private List<IAppAttachOutput> _errorList;
        private readonly string URI;
        private readonly string FILE_NAME;

        private static string formUri(string azureStorageAccount, string azureStorageFileShare, string packagePath)
        {
            return string.Format(@"\\{0}.file.core.windows.net\{1}\{2}", azureStorageAccount, azureStorageFileShare, FileUtils.extractFileNameWithExtension(packagePath));
        }

        /// <summary>
        /// Expands the given Msix Image and returns the details.
        /// Creates a new Msix Package in the specified Host Pool in Azure WVD.
        /// Creates a new WVD application with the given Azure Subscription ID, Azure Resource Group, Azure Application Group Name, and MSIX package information.
        /// </summary>
        /// <param name="azureSubscriptionId">The Azure Subscription ID.</param>
        /// <param name="azureResourceGroup">The name of the Azure Resource Group.</param>
        /// <param name="azureHostPoolName">The name of the Host Pool in which the Msix Image is to be expanded.</param>
        /// <param name="azureApplicationGroupName">The name of the Azure application group.</param>
        private void appAttachMsixImage(string azureSubscriptionId, string azureResourceGroup, string azureHostPoolName, string azureApplicationGroupName)
        {
            PowerShellUtils.ExecutePowerShellCommand(
                    "$response = (Expand-AzWvdMsixImage -HostPoolName \"{0}\" -ResourceGroupName \"{1}\" -SubscriptionId \"{2}\" -Uri \"{3}\")  \n New-AzWvdMsixPackage -HostPoolName \"{4}\" -ResourceGroupName \"{5}\" -SubscriptionId \"{6}\" -PackageAlias $response.PackageAlias -DisplayName \"{7}\" -ImagePath \"{8}\" -IsActive:$true \n New-AzWvdApplication -ResourceGroupName \"{9}\" -SubscriptionId \"{10}\" -Name \"{11}\" -ApplicationType MsixApplication -ApplicationGroupName \"{12}\" -MsixPackageFamilyName $response.PackageFamilyName -CommandLineSetting 0 -MsixPackageApplicationId $response.PackageApplication.AppId",
                    azureHostPoolName, azureResourceGroup, azureSubscriptionId, URI, azureHostPoolName, azureResourceGroup, azureSubscriptionId, FILE_NAME, URI, azureResourceGroup, azureSubscriptionId, FILE_NAME, azureApplicationGroupName
                );
        }

        /// <summary>
        /// Initializes errorList and forms URI, artifactName and imports PS module.
        /// </summary>
        /// <param name="azureStorageAccount">The name of the Azure Storage Account.</param>
        /// <param name="azureStorageFileShare">The name of the Azure Storage File Share.</param>
        /// <param name="packagePath">The path of the MSIX package.</param>
        public AVDAppAttachDeploy(string azureStorageAccount, string azureStorageFileShare, string packagePath)
        {
            _errorList = new List<IAppAttachOutput>();
            URI = formUri(azureStorageAccount, azureStorageFileShare, packagePath);
            FILE_NAME = FileUtils.extractFileNameWithoutExtension(packagePath);
        }

        /// <summary>
        /// Deploys the Msix Package to the specified Azure WVD Host Pool and Application Group.
        /// </summary>
        /// <param name="azureSubscriptionId">The Azure Subscription ID.</param>
        /// <param name="azureResourceGroup">The name of the Azure Resource Group.</param>
        /// <param name="azureHostPoolName">The name of the Host Pool in which the Msix Package is to be deployed.</param>
        /// <param name="azureApplicationGroupName">The name of the Application Group to which the Msix Package is to be added.</param>
        /// <returns>A list of errors encountered during deployment.</returns>
        public List<IAppAttachOutput> deploy(string azureSubscriptionId, string azureResourceGroup, string azureHostPoolName, string azureApplicationGroupName)
        {
            try
            {
                appAttachMsixImage(azureSubscriptionId, azureResourceGroup, azureHostPoolName, azureApplicationGroupName);
            }
            catch (Exception exception)
            {
                _errorList.Add(new AppAttachOutput(exception.Message, true));
            }
            return _errorList;
        }
    }
}
