public class SimpleProgressDialog : Form
{
    private Label messageLabel;

    public SimpleProgressDialog()
    {
        messageLabel = new Label
        {
            Text = "Installing NuGet packages, please wait...",
            Dock = DockStyle.Fill,
            TextAlign = ContentAlignment.MiddleCenter,
            AutoSize = true
        };

        Controls.Add(messageLabel);
        AutoSize = true;
        AutoSizeMode = AutoSizeMode.GrowAndShrink;
        StartPosition = FormStartPosition.CenterScreen;
        Text = "Please Wait";
    }
}
