using Azure.ResourceManager.DesktopVirtualization;
using Azure.ResourceManager.Resources;
using Azure.ResourceManager.Storage;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AppAttachExtension.Models
{ 
    public class AzureResouceModel
    {
        private PublishViewModel _publishViewModel;
        private SubscriptionResource _subscriptionResource;
        private SubscriptionCollection _subscriptions;
        private ResourceGroupCollection _resourceGroups;
        private ResourceGroupResource _resourceGroupResource;
        private StorageAccountCollection _storageAccounts;
        private StorageAccountResource _storageAccount;
        private FileShareCollection _fileShares;
        private VirtualApplicationGroupCollection _virtualApplications;
        private HostPoolCollection _hostPools;
        private VirtualWorkspaceCollection _virtualWorkspaces;

        public AzureResouceModel(PublishViewModel publishViewModel) 
        { 
            _publishViewModel = publishViewModel;
            _subscriptionResource = null;
            _subscriptions = null;
            _resourceGroups = null;
            _resourceGroupResource = null;
            _storageAccounts = null;
            _storageAccount = null;
            _fileShares = null;
            _virtualApplications = null;
            _hostPools = null;
            _virtualWorkspaces = null;
        }

        public SubscriptionResource SubscriptionResource {
            get 
            { 
                return _subscriptionResource;
            }
            set 
            { 
                if (value != _subscriptionResource)
                {
                    _subscriptionResource = value;
                    _publishViewModel.SubscriptionName = value.Data.SubscriptionId;
                }
               
            }
        }

        public SubscriptionCollection Subscriptions { 
            get 
            {
                return _subscriptions;
            }  
            set 
            { 
                if (_subscriptions != value)
                {
                    _subscriptions = value;
                    _publishViewModel.SubscriptionsList = new ObservableCollection<string>(_subscriptions?.Select(x => x.Data?.SubscriptionId));
                }
            }
        }

        public ResourceGroupCollection ResourceGroups {
            get 
            {
                return _resourceGroups;
            } 
            set
            {
                if (_resourceGroups != value)
                {
                    _resourceGroups = value;
                    _publishViewModel.ResourceGroupLists = new ObservableCollection<string>(_resourceGroups?.Select(x => x.Data?.Name));
                }
            }
        }

        public ResourceGroupResource ResourceGroupResource
        {
            get
            {
                return _resourceGroupResource;
            }
            set
            {
                if (_resourceGroupResource != value)
                {
                    _resourceGroupResource = value;
                    _publishViewModel.ResourceGroupName = value?.Data.Name;
                }
            }
        }

        public StorageAccountCollection StorageAccounts { 
            get 
            { 
                return _storageAccounts; 
            } 
            set 
            { 
                if (_storageAccounts != value)
                {
                    _storageAccounts = value;
                    _publishViewModel.StorageAccountList = new ObservableCollection<string>(_storageAccounts?.Select(x => x.Data?.Name));
                }
            }
        }
        public StorageAccountResource StorageAccount { 
            get 
            { 
                return _storageAccount; 
            } 
            set 
            { 
                if (_storageAccount != value)
                {
                    _storageAccount = value;
                    _publishViewModel.StorageAccountName = value?.Data?.Name;
                }
            }
        }

        public FileShareCollection FileShares { 
            get { 
                return _fileShares; 
            } 
            set 
            { 
                if (_fileShares != value)
                {
                    _fileShares = value; 
                    _publishViewModel.FileShareList = new ObservableCollection<string>(_fileShares?.Select(x => x.Data?.Name));
                }
            }
        }

        public VirtualApplicationGroupCollection VirtualApplications {
            get 
            { 
                return _virtualApplications; 
            } set 
            { 
                if (_virtualApplications != value)
                {
                    _virtualApplications = value;
                    _publishViewModel.ApplicationGroupList = new ObservableCollection<string>(_virtualApplications?.Select(x => x.Data?.Name));
                }
            }
        }
        public HostPoolCollection HostPools { 
            get 
            { 
                return _hostPools; 
            } 
            set 
            {
                if (_hostPools != value)
                {
                    _hostPools = value; 
                    _publishViewModel.HostPoolList = new ObservableCollection<string>(_hostPools?.Select(x => x.Data?.Name));
                }
            } 

        }
        public VirtualWorkspaceCollection VirtualWorkspaces
        {
            get
            {
                return _virtualWorkspaces;
            }
            set
            {
                if (_virtualWorkspaces != value)
                {
                    _virtualWorkspaces = value;
                    _publishViewModel.WorkspaceList = new ObservableCollection<string>(_virtualWorkspaces?.Select(x => x.Data?.Name));
                }
            }
        }
    }
}
