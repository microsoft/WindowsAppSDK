using System;
using System.Windows;
using System.Text.Json;
using System.IO;

namespace MicroAppHostWPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            // Check if a file path was passed in the command line arguments
            if (e.Args.Length > 0)
            {
                // Get the file path from the command line arguments
                string filePath = e.Args[0];

                // Read the file contents into a string
                string fileContents = File.ReadAllText(filePath);
                Console.WriteLine(fileContents);

                // Parse the file string to a JsonDocument
                JsonDocument doc = JsonDocument.Parse(fileContents);
            }

        }
    }
}
