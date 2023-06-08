using AppAttachKernel;
using AppAttachExtension.Contracts;
using AppAttachExtension.Models;
using AppAttachExtension.Providers;
using AppAttachExtension.Utils;
using AppAttachExtension;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
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
            var dialog = UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Required Information..");
            try
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
            catch (Exception e)
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
        private void SubscriptionList_DropDownClosed(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox != null)
            {
                var subscriptionSelected = comboBox.SelectedItem as string;
                if (!string.IsNullOrEmpty(subscriptionSelected) && _publishViewModel.SubscriptionName != subscriptionSelected)
                {
                    var dialog = UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Requried Information..");
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
        private void ResourceGroupList_DropDownClosed(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox != null)
            {
                var resourceGroupSelected = comboBox.SelectedItem as string;
                if (!string.IsNullOrEmpty(resourceGroupSelected) && _publishViewModel.ResourceGroupName != resourceGroupSelected)
                {
                    var dialog = UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Required Information..");
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
        private void StorageAccountList_DropDownClosed(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox != null)
            {
                var selectedStorageAccount = comboBox.SelectedItem as string;
                if (!string.IsNullOrEmpty(selectedStorageAccount) && _publishViewModel.StorageAccountName != selectedStorageAccount)
                {
                    var dialog = UIShellUtils.OpenDialogBoxWithPageDisable(this, "AVD App Attach", "Gathering Required Information..");
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

            OutputCommandHandler();
            var parentWindow = Window.GetWindow(this);
            parentWindow.Close();

        }

        private void ExecutePublish(string dialogBoxTitle, string dialogBoxContent, string messageBoxTitle, string messageBoxContent, string jsonString)
        {
            var dialog = UIShellUtils.OpenDialogBoxWithPageDisable(this, dialogBoxContent, dialogBoxTitle);
            IAppAttachFlowResponse returnObj = null;
            try
            {
                returnObj = _appAttachKernel.execute(jsonString);
                UIShellUtils.CloseDialogWithPageEnable(this, dialog);
            }
            catch (Exception ex)
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

        private void OutputCommandHandler()
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            AsyncPackage pack = AppAttach.Instance.Packageval();
            System.IServiceProvider serviceProvider = pack as System.IServiceProvider;
            Guid paneGuid = new Guid();
            string paneName = "App-Attach Build";
            IVsOutputWindowPane pane;
            IVsOutputWindow output = (IVsOutputWindow)serviceProvider.GetService(typeof(SVsOutputWindow));
            int hr = output.CreatePane(ref paneGuid, paneName, Convert.ToInt32(true), Convert.ToInt32(false));
            ErrorHandler.ThrowOnFailure(hr);
            hr = output
                .GetPane(ref paneGuid, out pane);
            ErrorHandler.ThrowOnFailure(hr);

            string filePath = System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Temp", "AppAttach");
            string filepath = System.IO.Path.Combine(filePath, "AppAttachLog.log");
            var fileContents = System.IO.File.ReadAllText(filepath);
            pane.Activate();
            pane.OutputStringThreadSafe(fileContents);
            pane.FlushToTaskList();
        }
    }
}
