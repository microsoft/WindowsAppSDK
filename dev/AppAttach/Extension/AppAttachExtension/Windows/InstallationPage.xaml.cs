using AppAttachExtension.Contracts;
using AppAttachExtension.Validator;
using EnvDTE80;
using Microsoft.VisualStudio.Shell.Interop;
using Newtonsoft.Json;
using System.ComponentModel;
using System.Net;
using System.Security;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Navigation;

namespace AppAttachExtension
{
    /// <summary>
    /// Interaction logic for InstallationPageEdited.xaml
    /// </summary>
    public partial class InstallationPage : System.Windows.Controls.Page, INotifyPropertyChanged
    {
        private bool isCertificateAvailable = false;
        private bool isCertificateVerified = false;
        private string bindingOutputLocation = "";
        private string bindingInstallerLocation = "C:\\Program";
        private string bindingCertificateLocation;
        private string majorVersion = "1";
        private string minorVersion = "0";
        private string buildnumber = "0";
        private string revisionnumber = "0";
        public event PropertyChangedEventHandler PropertyChanged;

        public InstallationPage()
        {
            InitializeComponent();
            DataContext = this;
        }

        public ICommand CheckTextBoxCommand { get; set; }

        public bool IsCertificateAvailable
        {
            get => isCertificateAvailable;
            set
            {

                isCertificateAvailable = value;
                OnPropertyChanged(nameof(IsCertificateAvailable));

            }
        }

        public bool IsCertificateVerified
        {
            get => isCertificateVerified;
            set
            {

                isCertificateVerified = value;
                OnPropertyChanged(nameof(IsCertificateVerified));

            }
        }

        public string BindingOutputLocation
        {
            get
            {
                return bindingOutputLocation;
            }
            set
            {
                bindingOutputLocation = value;
                OnPropertyChanged(nameof(BindingOutputLocation));
            }
        }

        public string BindingInstallerLocation
        {
            get
            {
                return bindingInstallerLocation;
            }
            set
            {
                bindingInstallerLocation = value;
                OnPropertyChanged(nameof(BindingInstallerLocation));
            }
        }

        public string BindingCertificateLocation
        {
            get
            {
                return bindingCertificateLocation;
            }
            set
            {
                bindingCertificateLocation = value;
                OnPropertyChanged(nameof(BindingCertificateLocation));
            }
        }

        public string MajorVersion
        {
            get
            {
                return majorVersion;
            }
            set
            {
                majorVersion = value;
                OnPropertyChanged(nameof(MajorVersion));
            }
        }

        public string MinorVersion
        {
            get
            {
                return minorVersion;
            }
            set
            {
                minorVersion = value;
                OnPropertyChanged(nameof(MinorVersion));
            }
        }

        public string BuildNumber
        {
            get
            {
                return buildnumber;
            }
            set
            {
                buildnumber = value;
                OnPropertyChanged(nameof(BuildNumber));
            }
        }

        public string RevisionNumber
        {
            get
            {
                return revisionnumber;
            }
            set
            {
                revisionnumber = value;
                OnPropertyChanged(nameof(RevisionNumber));
            }
        }

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            ComboBoxItemList();
            _ = GetBinPathAsync();
        }

        private async Task GetBinPathAsync()
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();

            var _dte2 = await ServiceProvider.GetGlobalServiceAsync(typeof(SDTE)) as DTE2;
            var selectedItem = _dte2.SelectedItems.Item(1);
            var project = selectedItem.Project;

            if (project == null)
            {
                throw new Exception("No active project found.");
            }

            var activeConfig = project.ConfigurationManager?.ActiveConfiguration;

            if (activeConfig == null)
            {
                throw new Exception("No active configuration found.");
            }

            string outputPath = activeConfig.Properties.Item("OutputPath").Value.ToString();
            string projectDir = System.IO.Path.GetDirectoryName(project.FullName);
            string path = System.IO.Path.Combine(projectDir, outputPath);
            int endIndex = path.IndexOf("bin\\") + 4;
            string binPath = path.Substring(0, endIndex);
            BindingOutputLocation = binPath;
        }


        public void ComboBoxItemList()
        {
            //  ArchitectureCombo.ItemsSource = new List<string>() { "Debug x86", "Debug x64", "Release x86", "Release x64", "ARM 64" };
        }

        private void BrowseButtonClick(object sender, RoutedEventArgs e)
        {
            FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
            DialogResult result = folderBrowserDialog.ShowDialog();
            if (!string.IsNullOrWhiteSpace(folderBrowserDialog.SelectedPath))
            {
                OutputLocation.Text = folderBrowserDialog.SelectedPath;
            }
        }



        private void LoadCertificate(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "Text Files (*.pfx)|*.pfx|All Files (*.*)|*.*";
            bool? result = openFileDialog.ShowDialog();
            if (result == true)
            {
                string filePath = openFileDialog.FileName;
                CertificatePathTextBox.Text = filePath;
                IsCertificateAvailable = true;
            }
        }

        private void VerifyCertificatePasswordButton_Click(object sender, RoutedEventArgs e)
        {
            string certificatePath = CertificatePathTextBox.Text;
            SecureString securePassword = PasswordBox.SecurePassword;
            string password = new NetworkCredential(string.Empty, securePassword).Password;
            string certVerify = CommonValidator.CertificateVerify(certificatePath, password);

            if (!string.IsNullOrEmpty(certVerify))
            {
                PasswordError.Style = FindResource("labelstyle") as Style;
                PasswordError.Content = certVerify;
                IsCertificateVerified = true;
            }
            else
            {
                PasswordError.Style = FindResource("redlabelstyle") as Style;
                PasswordError.Content = "Password is incorrrect";
                IsCertificateVerified = false;
            }
        }

        private void NextPage(object sender, RoutedEventArgs e)
        {
            string version = MajorVersionTextBox.Text + "." + MinorVersionTextBox.Text + "." + BuildNumberTextBox.Text + "." + RevisionNumberTextBox.Text;
            SecureString securePassword = PasswordBox.SecurePassword;
            string password = new NetworkCredential(string.Empty, securePassword).Password;

            string configuration = "";
            foreach (System.Windows.Controls.RadioButton radioButton in ConfigurationRadioButton.Children)
            {
                if (radioButton.IsChecked == true)
                {
                    configuration = radioButton.Content.ToString();
                    break;
                }
            }

            string platform = "";
            foreach (System.Windows.Controls.RadioButton radioButton in PlatformRadioButton.Children)
            {
                if (radioButton.IsChecked == true)
                {
                    platform = radioButton.Content.ToString();
                    break;
                }
            }
            AppAttachViewContract obj = new AppAttachViewContract() { PackageLocation = OutputLocation.Text, Configuration = configuration, Platform = platform, PackageVersion = version, CertificatePath = CertificatePathTextBox.Text, CertificatePassword = password };
            string json = JsonConvert.SerializeObject(obj);
            PublishPage pg = new PublishPage();
            NavigationService.LoadCompleted += pg.NavigationService_LoadCompleted;
            NavigationService.Navigate(pg, obj);

        }

        private void TextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.TextBox textBox = sender as System.Windows.Controls.TextBox;
            BindingExpression bindingExpr = textBox.GetBindingExpression(System.Windows.Controls.TextBox.TextProperty);
            bindingExpr.UpdateSource();

        }

        private void TextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.TextBox textBox = sender as System.Windows.Controls.TextBox;
            Validation.ClearInvalid(textBox.GetBindingExpression(System.Windows.Controls.TextBox.TextProperty));
            textBox.Style = FindResource("textboxstyle") as Style;
        }

        private void Close_Cancel(object sender, RoutedEventArgs e)
        {
            var parentWindow = System.Windows.Window.GetWindow(this); parentWindow.Close();
        }

        private void Validation_Error(object sender, ValidationErrorEventArgs e)
        {
            if (e.Action == ValidationErrorEventAction.Added)
            {
                System.Windows.Controls.ToolTipService.SetShowOnDisabled(OutputLocation, true);
            }
            else if (e.Action == ValidationErrorEventAction.Removed)
            {
                System.Windows.Controls.ToolTipService.SetShowOnDisabled(OutputLocation, false);
            }
        }

    }
}
