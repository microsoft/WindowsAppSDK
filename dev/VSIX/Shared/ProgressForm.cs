using System.Drawing;
using System.Windows.Forms;

public class ProgressForm : Form
{
    private PictureBox spinner;

    public ProgressForm()
    {
        InitializeComponent();
        TopMost = true;  // Ensures it stays on top
    }

    private void InitializeComponent()
    {
        spinner = new System.Windows.Forms.PictureBox();
        ((System.ComponentModel.ISupportInitialize)(spinner)).BeginInit();

        // Spinner setup
        spinner.Dock = System.Windows.Forms.DockStyle.Fill;
        spinner.Image = Image.FromFile(@"C:\Users\shasnayak\WindowsAppSDK\dev\VSIX\Shared\loading-buffering.gif");
        // Ensure the path points to a valid spinner GIF
        spinner.Location = new System.Drawing.Point(0, 0);
        spinner.Name = "spinner";
        spinner.Size = new System.Drawing.Size(284, 262);
        spinner.SizeMode = PictureBoxSizeMode.CenterImage;
        Controls.Add(spinner);

        // Form setup
        AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        ClientSize = new System.Drawing.Size(284, 262);
        FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
        StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
        MaximizeBox = false;
        MinimizeBox = false;
        Name = "ProgressForm";
        ShowIcon = false;
        ShowInTaskbar = false;
        Text = "Processing...";

        ((System.ComponentModel.ISupportInitialize)(spinner)).EndInit();
    }
}
