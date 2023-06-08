using System.Collections.ObjectModel;
using System.ComponentModel;

namespace AppAttachExtension.Models
{
    public class PublishViewModel : INotifyPropertyChanged
    {
        private ObservableCollection<string> _subscriptionsList;
        private string _subscriptionName;
        private ObservableCollection<string> _resourceGroupList;
        private string _resourceGroupName;
        private ObservableCollection<string> _storageAccountList;
        private string _storageAccountName;
        private ObservableCollection<string> _fileShareList;
        private string _fileShareName;
        private ObservableCollection<string> _applicationGroupsList;
        private string _applicationGroupName;
        private ObservableCollection<string> _hostPoolsList;
        private string _hostPoolName;
        private ObservableCollection<string> _workspacesList;
        private string _workspaceName;


        public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<string> SubscriptionsList { 
            get { 
                return _subscriptionsList;
            } 
            set {
                if (_subscriptionsList != value)
                {
                    _subscriptionsList = value;
                    OnPropertyChanged(nameof(SubscriptionsList));
                }
            } 
        }

        public string SubscriptionName { 
            get {
                return _subscriptionName;
            } 
            set { 
                if (_subscriptionName != value)
                {
                    _subscriptionName = value;
                    OnPropertyChanged(nameof(SubscriptionName));
                }
            } 
        }

        public ObservableCollection<string> ResourceGroupLists
        {
            get
            {
                return _resourceGroupList;
            }
            set
            {
                if (_resourceGroupList != value)
                {
                    _resourceGroupList = value;
                    OnPropertyChanged(nameof(ResourceGroupLists));
                }
            }
        }

        public string ResourceGroupName
        {
            get
            {
                return _resourceGroupName;
            }
            set
            {
                if (_resourceGroupName != value)
                {
                    _resourceGroupName = value;
                    OnPropertyChanged(nameof(ResourceGroupName));
                }
            }
        }

        public string StorageAccountName
        {
            get
            {
                return _storageAccountName;
            }
            set
            {
                if (_storageAccountName != value)
                {
                    _storageAccountName = value;
                    OnPropertyChanged(nameof(StorageAccountName));
                }
            }
        }

        public ObservableCollection<string> StorageAccountList
        {
            get
            {
                return _storageAccountList;
            }
            set
            {
                if (_storageAccountList != value)
                {
                    _storageAccountList = value;
                    OnPropertyChanged(nameof(StorageAccountList));
                }
            }
        }

        public ObservableCollection<string> FileShareList
        {
            get
            {
                return _fileShareList;
            }
            set
            {
                if (_fileShareList != value)
                {
                    _fileShareList = value;
                    OnPropertyChanged(nameof(FileShareList));
                }
            }
        }

        public string FileShareName
        {
            get
            {
                return _fileShareName;
            }
            set
            {
                if (_fileShareName != value)
                {
                    _fileShareName = value;
                    OnPropertyChanged(nameof(FileShareName));
                }
            }
        }

        public ObservableCollection<string> ApplicationGroupList
        {
            get
            {
                return _applicationGroupsList;
            }
            set
            {
                if (_applicationGroupsList != value)
                {
                    _applicationGroupsList = value;
                    OnPropertyChanged(nameof(ApplicationGroupList));
                }
            }
        }


        public string ApplicationGroupName
        {
            get
            {
                return _applicationGroupName;
            }
            set
            {
                if (_applicationGroupName != value)
                {
                    _applicationGroupName = value;
                    OnPropertyChanged(nameof(ApplicationGroupName));
                }
            }
        }

        public ObservableCollection<string> HostPoolList
        {
            get
            {
                return _hostPoolsList;
            }
            set
            {
                if (_hostPoolsList != value)
                {
                    _hostPoolsList = value;
                    OnPropertyChanged(nameof(HostPoolList));
                }
            }
        }

        public string HostPoolName
        {
            get
            {
                return _hostPoolName;
            }
            set
            {
                if (_hostPoolName != value)
                {
                    _hostPoolName = value;
                    OnPropertyChanged(nameof(HostPoolName));
                }
            }
        }

        public ObservableCollection<string> WorkspaceList
        {
            get
            {
                return _workspacesList;
            }
            set
            {
                if (_workspacesList != value)
                {
                    _workspacesList = value;
                    OnPropertyChanged(nameof(WorkspaceList));
                }
            }
        }

        public string WorkspaceName
        {
            get
            {
                return _workspaceName;
            }
            set
            {
                if (_workspaceName != value)
                {
                    _workspaceName = value;
                    OnPropertyChanged(nameof(WorkspaceName));
                }
            }
        }

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
