using Microsoft.VisualStudio.PlatformUI;

namespace AppAttachExtension
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class AppAttachWindow : DialogWindow
    {


        public AppAttachWindow()
        {
            InitializeComponent();
            AVDFrame.Source = new Uri("InstallationPage.xaml", UriKind.Relative);
        }
    }
}
