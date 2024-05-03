using System.Drawing;
using System.Windows.Forms;

public class ProgressForm : Form
{
    private PictureBox spinner;
    private Label messageLabel;
    private FlowLayoutPanel layoutPanel;

    public ProgressForm()
    {
        InitializeComponent();
        TopMost = true; // Ensures it stays on top of the main application window
    }

    private void InitializeComponent()
    {
        spinner = new PictureBox();
        messageLabel = new Label();
        layoutPanel = new FlowLayoutPanel();

        ((System.ComponentModel.ISupportInitialize)(spinner)).BeginInit();

        // Panel setup
        layoutPanel.FlowDirection = FlowDirection.LeftToRight;
        layoutPanel.Dock = DockStyle.Fill;
        layoutPanel.Padding = new Padding(40, 20, 40, 20); // Increased padding

        // Spinner setup
        spinner.Image = Image.FromFile(@"C:\Users\shasnayak\WindowsAppSDK\dev\VSIX\Shared\spinner.gif");
        spinner.SizeMode = PictureBoxSizeMode.Zoom;
        spinner.Size = new Size(100, 100);
        spinner.Margin = new Padding(0, 0, 10, 0); // Adjusted margin for proper alignment

        // Message Label setup
        messageLabel.Font = new Font("Segoe UI", 10F, FontStyle.Regular);
        messageLabel.ForeColor = Color.Black;
        messageLabel.Text = "Installing NuGet packages to your project, please wait...";
        messageLabel.AutoSize = true;
        messageLabel.TextAlign = ContentAlignment.MiddleLeft;

        // Add controls to panel
        layoutPanel.Controls.Add(spinner);
        layoutPanel.Controls.Add(messageLabel);

        // Form setup
        ClientSize = new Size(600, 200); // Adjust size to better fit contents
        Controls.Add(layoutPanel);
        FormBorderStyle = FormBorderStyle.FixedDialog;
        StartPosition = FormStartPosition.CenterScreen;
        MaximizeBox = false;
        MinimizeBox = false;
        Name = "ProgressForm";
        ShowIcon = false;
        ShowInTaskbar = false;

        ((System.ComponentModel.ISupportInitialize)(spinner)).EndInit();
    }
}
