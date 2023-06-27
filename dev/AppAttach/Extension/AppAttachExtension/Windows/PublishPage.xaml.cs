using AppAttachAPI.Response.Interfaces;
using AppAttachExtension.Contracts;
using AppAttachExtension.Enums;
using AppAttachExtension.Models;
using AppAttachExtension.Providers;
using AppAttachExtension.Utils;
using AppAttachKernel;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.Shell.Interop;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AppAttachAPI.Response.Interfaces;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio;
using AppAttachExtension.Enums;
using AppAttachExtension.Enums;
using AppAttachExtension.Models;
using AppAttachExtension.Providers;
using AppAttachExtension.Utils;
using AppAttachExtension;
using AppAttachExtension.Implementation;
using AppAttachExtension.Notification;
using AppAttachExtension.Helper;

namespace AppAttachExtension
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class PublishPage : Page
    {
        private readonly AzureResourceProvider resourceProvider;
        private readonly PublishViewModel _publishViewModel;
        private readonly IdentityProvider _identityProvider;
        private readonly IDEResourceProvider _ideResourceProvider;
        private AppAttachViewContract _contract;
        private AppAttachKernelController _appAttachKernel;

        public PublishPage()
        {
            InitializeComponent();
            PublishViewModel viewModel = (PublishViewModel)PublishViewGrid.DataContext;
            _publishViewModel = viewModel;
            _identityProvider = new IdentityProvider();
            _ideResourceProvider = new IDEResourceProvider();
            resourceProvider = new AzureResourceProvider(viewModel, _identityProvider);
            _appAttachKernel = new AppAttachKernelController();
        }

        public void NavigationService_LoadCompleted(object sender, NavigationEventArgs e)
        {
            if (e.ExtraData != null && e.ExtraData is AppAttachViewContract)
            {
                _contract = e.ExtraData as AppAttachViewContract;
            }
        }

        /// <summary>
        /// Page Loaded Trigger.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            _ = PopulateDataAsync();
        }

        /// <summary>
        /// Populates the data in the publish view model
        /// </summary>
        /// <returns></returns>
        private async Task PopulateDataAsync()
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
            var dialog = await Task.Run(() => UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Required Information..")); try
            {
                await _ideResourceProvider.PopulateIDEModelAsync();
                var isAuthenticated = await _identityProvider.PopulateUserIdentityAsync();
                if (isAuthenticated)
                {
                    await resourceProvider.PopulateSubscriptionsAsync();
                    await Task.Run(() => resourceProvider.PopulateResourceGroups(null));
                    var storageAccountTask = Task.Run(() => resourceProvider.PopulateStorageAccounts(null));
                    var applicationGroupTask = Task.Run(() => resourceProvider.PopulateApplicationGroups(null));
                    var workSpaceTask = Task.Run(() => resourceProvider.PopulateWorkspaces(null));
                    var hostpoolTask = Task.Run(() => resourceProvider.PopulateHostPools(null));
                    await Task.WhenAll(storageAccountTask, applicationGroupTask, workSpaceTask, hostpoolTask);
                    await Task.Run(() => resourceProvider.PopulateFileShares(null));
                }
                else
                {
                    //UIShellUtils.ShowMessageBox($"User is not authenticated", "AVD App Attach", Constants.MessageBoxTypeEnum.Error);
                }
            }
            catch (Exception)
            {
                //UIShellUtils.ShowMessageBox($"Error while getting the requried parameters{e.Message}", "AVD App Attach", Constants.MessageBoxTypeEnum.Error);
            }
            finally
            {
                UIShellUtils.CloseDialogWithPageEnable(this, dialog);
            }

        }

        /// <summary>
        /// When Subscription List is closed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void SubscriptionList_DropDownClosed(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox != null)
            {
                var subscriptionSelected = comboBox.SelectedItem as string;
                if (!string.IsNullOrEmpty(subscriptionSelected) && _publishViewModel.SubscriptionName != subscriptionSelected)
                {
                    var dialog = await Task.Run(() => UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Requried Information.."));
                    resourceProvider.PopulateResourceGroups(subscriptionSelected);
                    _publishViewModel.SubscriptionName = subscriptionSelected;
                    UIShellUtils.CloseDialogWithPageEnable(this, dialog);
                }
            }
        }

        /// <summary>
        /// When Resource group list is closed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void ResourceGroupList_DropDownClosed(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox != null)
            {
                var resourceGroupSelected = comboBox.SelectedItem as string;
                if (!string.IsNullOrEmpty(resourceGroupSelected) && _publishViewModel.ResourceGroupName != resourceGroupSelected)
                {
                    var dialog = await Task.Run(() => UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Required Information.."));
                    resourceProvider.PopulateStorageAccounts(resourceGroupSelected);
                    resourceProvider.PopulateFileShares(null);
                    resourceProvider.PopulateWorkspaces(resourceGroupSelected);
                    resourceProvider.PopulateApplicationGroups(resourceGroupSelected);
                    resourceProvider.PopulateHostPools(resourceGroupSelected);
                    _publishViewModel.ResourceGroupName = resourceGroupSelected;
                    UIShellUtils.CloseDialogWithPageEnable(this, dialog);
                }
            }
        }

        /// <summary>
        /// When Storage drop down is closed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void StorageAccountList_DropDownClosed(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox != null)
            {
                var selectedStorageAccount = comboBox.SelectedItem as string;
                if (!string.IsNullOrEmpty(selectedStorageAccount) && _publishViewModel.StorageAccountName != selectedStorageAccount)
                {
                    var dialog = await Task.Run(() => UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Required Information.."));
                    resourceProvider.PopulateFileShares(selectedStorageAccount);
                    _publishViewModel.StorageAccountName = selectedStorageAccount;
                    UIShellUtils.CloseDialogWithPageEnable(this, dialog);
                }
            }
        }

        private void PreviousBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new InstallationPage());
        }

        private void PublishBtn_Click(object sender, RoutedEventArgs e)
        {
            var publishViewModel = resourceProvider.GetViewModel();
            var identityModel = _identityProvider.GetModel();
            var ideResourceModel = _ideResourceProvider.GetModel();
            var jsonString = JsonParserUtil.ConvertJsonForPublish(publishViewModel, identityModel, ideResourceModel, _contract);
            if (_contract.IsPublishRequired == bool.FalseString)
            {
                var result = UIShellUtils.ShowMessageBox("The required parameters are empty for publish to AVD, progressing further would generate local installable", "AVD Publish", MessageBoxTypeEnum.InfoWithConfirmation);
                if (result == 1)
                {
                    ExecutePublish("Generating VHDX locally", "Local installable generation", "Local installable generation", "App Attach packages generated successfully in ", jsonString);
                }
            }
            else
            {
                ExecutePublish("Attaching to AVD", "AVD Publish", "AVD Publish", "Successfully published to AVD", jsonString);
            }

            var parentWindow = Window.GetWindow(this);
            parentWindow.Close();

        }

        private async void ExecutePublish(string dialogBoxTitle, string dialogBoxContent, string messageBoxTitle, string messageBoxContent, string jsonString)
        {
            ProjectHelper projectHelper = ProjectHelper.Instance;
            OutputPane outputPane = projectHelper.GetOutputPane();
            VSMessageHandler messageHandler = new VSMessageHandler(outputPane.getPane());
            var dialog = await Task.Run(() => UIShellUtils.OpenDialogBoxWithPageDisable(this, dialogBoxContent, dialogBoxTitle)); IAppAttachFlowResponse returnObj = null;
            try
            {
                returnObj = await Task.Run(() => _appAttachKernel.execute(jsonString, messageHandler));
                UIShellUtils.CloseDialogWithPageEnable(this, dialog);
            }
            catch (Exception)
            {
                UIShellUtils.CloseDialogWithPageEnable(this, dialog);
                UIShellUtils.ShowMessageBox("Error while processing request for detail error see the logs", messageBoxTitle, MessageBoxTypeEnum.Error);
            }
            if (returnObj != null && !returnObj.isError())
            {
                if (messageBoxContent.Contains("packages"))
                {
                    messageBoxContent += returnObj.getAppAttachArtifact().getVHDXPath();
                }
                UIShellUtils.ShowMessageBox(messageBoxContent, messageBoxTitle, MessageBoxTypeEnum.Info);
            }
            else if (returnObj != null)
            {
                var errorString = "";
                returnObj.getAppAttachOutputs().ForEach(output => { errorString += output.getMessage(); });
                if (!string.IsNullOrEmpty(errorString))
                {
                    UIShellUtils.ShowMessageBox("Error while processing request for detail error see the logs", messageBoxTitle, MessageBoxTypeEnum.Error);
                }
            }
        }

        private void CancelBtn_Click(object sender, RoutedEventArgs e)
        {
            var parentWindow = Window.GetWindow(this);
            parentWindow.Close();
        }
    }
}
