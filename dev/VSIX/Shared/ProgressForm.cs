using System.Drawing;
using System.Windows.Forms;

public class ProgressForm : Form
{
    private PictureBox spinner;
    private Label messageLabel;
    private TableLayoutPanel tableLayoutPanel;

    public ProgressForm()
    {
        InitializeComponent();
        TopMost = true; // Ensures it stays on top of the main application window
    }

    private void InitializeComponent()
    {
        spinner = new PictureBox();
        messageLabel = new Label();
        tableLayoutPanel = new TableLayoutPanel();

        ((System.ComponentModel.ISupportInitialize)(spinner)).BeginInit();

        // TableLayoutPanel setup
        tableLayoutPanel.RowCount = 1; // One row
        tableLayoutPanel.ColumnCount = 2; // Two columns
        tableLayoutPanel.Dock = DockStyle.Fill;
        tableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 100F)); // Fixed size for spinner
        tableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F)); // Remaining space for text
        tableLayoutPanel.BackColor = Color.White;

        // Spinner setup
        spinner.Image = Image.FromFile(@"C:\Users\shasnayak\WindowsAppSDK\dev\VSIX\Shared\pacman.gif");
        spinner.SizeMode = PictureBoxSizeMode.Zoom;
        spinner.Size = new Size(100, 100);
        spinner.Anchor = AnchorStyles.None; // Center in table cell

        // Message Label setup
        messageLabel.Text = "Installing NuGet packages to your project, please wait...";
        messageLabel.Font = new Font("Segoe UI", 10F);
        messageLabel.Dock = DockStyle.Fill;
        messageLabel.TextAlign = ContentAlignment.MiddleLeft;
        messageLabel.AutoSize = true;

        // Add controls to the table
        tableLayoutPanel.Controls.Add(spinner, 0, 0);
        tableLayoutPanel.Controls.Add(messageLabel, 1, 0);

        // Form setup
        ClientSize = new Size(700, 150); // Increased width to prevent wrapping
        Controls.Add(tableLayoutPanel);
        FormBorderStyle = FormBorderStyle.FixedDialog;
        StartPosition = FormStartPosition.CenterScreen;
        MaximizeBox = false;
        MinimizeBox = false;
        Name = "ProgressForm";
        ShowIcon = false;
        ShowInTaskbar = false;
        BackColor = Color.White;

        ((System.ComponentModel.ISupportInitialize)(spinner)).EndInit();
    }
}
