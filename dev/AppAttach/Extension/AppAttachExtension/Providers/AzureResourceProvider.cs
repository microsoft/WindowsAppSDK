using AppAttachExtension.Models;
using Azure.Identity;
using Azure.ResourceManager;
using Azure.ResourceManager.DesktopVirtualization;
using Azure.ResourceManager.Resources;
using Azure.ResourceManager.Storage;
using System.Linq;

namespace AppAttachExtension.Providers
{
    public class AzureResourceProvider
    {
        private readonly ArmClient _client;
        private readonly PublishViewModel _publishViewModel;
        private readonly AzureResouceModel _resourceModel;
        private readonly IdentityProvider _identityProvider;

        public AzureResourceProvider(PublishViewModel publishViewModel, IdentityProvider identityProvider)
        {
            _client = new ArmClient(new DefaultAzureCredential());
            _publishViewModel = publishViewModel;
            _identityProvider = identityProvider;
            _resourceModel = new AzureResouceModel(publishViewModel);
        }

        /// <summary>
        /// Populate Subscriptions
        /// </summary>
        /// <returns></returns>
        public async Task PopulateSubscriptionsAsync()
        {
            var tenants = _client.GetTenants();
            SubscriptionCollection subscriptionResources = await Task.Run(() =>_client.GetSubscriptions());
            if (subscriptionResources != null)
            {
                _resourceModel.Subscriptions = subscriptionResources;
                 var subscription = await _client.GetDefaultSubscriptionAsync();
                if (subscription != null)
                {
                    _publishViewModel.SubscriptionName = subscription?.Data.SubscriptionId;
                }
            }
        }

        /// <summary>
        /// Populate Resource Group
        /// </summary>
        /// <param name="subscriptionName"></param>
        public void  PopulateResourceGroups(string subscriptionName)
        {
            var defaultSubscription = subscriptionName ?? _publishViewModel.SubscriptionName;
            if (!string.IsNullOrEmpty(defaultSubscription))
            {
                var subscription = _resourceModel.Subscriptions.FirstOrDefault(x => x.Data.SubscriptionId == defaultSubscription);
                var resourceGroups = subscription.GetResourceGroups();
                if (resourceGroups != null)
                {
                    _resourceModel.ResourceGroups = resourceGroups;
                    _publishViewModel.ResourceGroupName = resourceGroups.FirstOrDefault()?.Data?.Name;

                }
            } 
        }

        /// <summary>
        /// Populate Storage Accounts
        /// </summary>
        /// <param name="resourceGroupName"></param>
        public void PopulateStorageAccounts(string resourceGroupName)
        {
            var resourceGroupSelected = resourceGroupName ?? _publishViewModel.ResourceGroupName;
            if (!string.IsNullOrEmpty(resourceGroupSelected))
            {
                if (_resourceModel.ResourceGroups != null)
                {
                    var resourceGroup = _resourceModel.ResourceGroups.FirstOrDefault(x => x.Data.Name == resourceGroupSelected);
                    _resourceModel.StorageAccounts = resourceGroup.GetStorageAccounts();
                    _identityProvider.PopulateStorageConnectionString(_resourceModel.StorageAccounts.FirstOrDefault());
                    _publishViewModel.StorageAccountName = _resourceModel.StorageAccounts.FirstOrDefault()?.Data?.Name;

                }
            }
        }

        /// <summary>
        /// Populate File Shares
        /// </summary>
        /// <param name="storageAccountName"></param>
        public void PopulateFileShares(string storageAccountName)
        {
            var storageSelected = storageAccountName ?? _publishViewModel.StorageAccountName;
            if (!string.IsNullOrEmpty(storageSelected))
            {
                if (_resourceModel.StorageAccounts != null)
                {
                    var storageAccount = _resourceModel.StorageAccounts.FirstOrDefault(x => x.Data.Name == storageSelected);
                    _identityProvider.PopulateStorageConnectionString(storageAccount);
                    _resourceModel.FileShares = storageAccount.GetFileService()?.GetFileShares();
                    _publishViewModel.FileShareName = _resourceModel.FileShares.FirstOrDefault()?.Data?.Name;
                }
            } 
            else 
            {
                _publishViewModel.FileShareName = null;
            }
        }

        /// <summary>
        /// Populate Application Groups
        /// </summary>
        /// <param name="resourceGroupName"></param>
        public void PopulateApplicationGroups(string resourceGroupName)
        {
            var resourceGroupSelected = resourceGroupName ?? _publishViewModel.ResourceGroupName;
            if (!string.IsNullOrEmpty(resourceGroupSelected))
            {
                if (_resourceModel.ResourceGroups != null)
                {
                    var resourceGroup = _resourceModel.ResourceGroups.FirstOrDefault(x => x.Data.Name == resourceGroupSelected);
                    _resourceModel.VirtualApplications = resourceGroup.GetVirtualApplicationGroups();
                    _publishViewModel.ApplicationGroupName = _resourceModel.VirtualApplications.FirstOrDefault()?.Data?.Name; 
                }
            }
        }

        /// <summary>
        /// Populate host pools
        /// </summary>
        /// <param name="resourceGroupName"></param>
        public void PopulateHostPools(string resourceGroupName)
        {
            var resourceGroupSelected = resourceGroupName ?? _publishViewModel.ResourceGroupName;
            if (!string.IsNullOrEmpty(resourceGroupSelected))
            {
                if (_resourceModel.ResourceGroups != null)
                {
                    var resourceGroup = _resourceModel.ResourceGroups.FirstOrDefault(x => x.Data.Name == resourceGroupSelected);
                    _resourceModel.HostPools = resourceGroup.GetHostPools();
                    _publishViewModel.HostPoolName = _resourceModel.HostPools.FirstOrDefault()?.Data?.Name;
                }
            }
        }

        /// <summary>
        /// Populate  WorkSpaces
        /// </summary>
        /// <param name="resourceGroupName"></param>
        public void PopulateWorkspaces(string resourceGroupName)
        {
            var resourceGroupSelected = resourceGroupName ?? _publishViewModel.ResourceGroupName;
            if (!string.IsNullOrEmpty(resourceGroupSelected))
            {
                if (_resourceModel.ResourceGroups != null)
                {
                    var resourceGroup = _resourceModel.ResourceGroups.FirstOrDefault(x => x.Data.Name == resourceGroupSelected);
                    _resourceModel.VirtualWorkspaces = resourceGroup.GetVirtualWorkspaces();
                    _publishViewModel.WorkspaceName = _resourceModel.VirtualWorkspaces.FirstOrDefault()?.Data?.Name;
                }
            }
        }

        public PublishViewModel GetViewModel()
        {
            return _publishViewModel;
        }
    }
}