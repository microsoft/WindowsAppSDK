using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Windows.Storage;
using Windows.Storage.Pickers;
using Microsoft.UI.Windowing;
using WinRT;

namespace FilePickersAppWithUnpackagedProj
{
    public sealed partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();
            Title = "File Pickers Comparison Test App";
        }
        
        #region Helper Methods
        
        private void LogResult(string message)
        {
            ResultsTextBlock.Text = $"[{DateTime.Now:HH:mm:ss}] {message}\n{ResultsTextBlock.Text}";
        }
        
        private Windows.Storage.Pickers.PickerLocationId GetSelectedLocation()
        {
            switch(StartLocationComboBox.SelectedIndex)
            {
                case 0: return PickerLocationId.Desktop;
                case 1: return PickerLocationId.DocumentsLibrary;
                case 2: return PickerLocationId.Downloads;
                case 3: return PickerLocationId.MusicLibrary;
                case 4: return PickerLocationId.PicturesLibrary;
                case 5: return PickerLocationId.VideosLibrary;
                default: return PickerLocationId.Unspecified;
            }
        }

        private Microsoft.Windows.Storage.Pickers.PickerLocationId GetSelectedNewLocationId()
        {
            switch (StartLocationComboBox.SelectedIndex)
            {
                case 0: return Microsoft.Windows.Storage.Pickers.PickerLocationId.Desktop;
                case 1: return Microsoft.Windows.Storage.Pickers.PickerLocationId.DocumentsLibrary;
                case 2: return Microsoft.Windows.Storage.Pickers.PickerLocationId.Downloads;
                case 3: return Microsoft.Windows.Storage.Pickers.PickerLocationId.MusicLibrary;
                case 4: return Microsoft.Windows.Storage.Pickers.PickerLocationId.PicturesLibrary;
                case 5: return Microsoft.Windows.Storage.Pickers.PickerLocationId.VideosLibrary;
                default: return Microsoft.Windows.Storage.Pickers.PickerLocationId.Unspecified;
            }
        }
        
        private string[] GetFileFilters()
        {
            string input = FileTypeFilterInput.Text?.Trim() ?? "";
            if (string.IsNullOrEmpty(input))
                return new string[] { "*" };
                
            return input.Split(new char[] { ',', ';' }, StringSplitOptions.RemoveEmptyEntries)
                        .Select(s => s.Trim())
                        .ToArray();
        }
        
        #endregion
        
        #region FileOpenPicker Tests
        
        private async void UwpPickSingleFile_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                // Initialize UWP picker
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                
                var file = await picker.PickSingleFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileOpenPicker - PickSingleFileAsync:\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult("UWP FileOpenPicker - PickSingleFileAsync: Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP FileOpenPicker: {ex.Message}");
            }
        }
        
        private async void NewPickSingleFile_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // Initialize new picker with AppWindow.Id
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);
                
                var result = await picker.PickSingleFileAsync();
                if (result != null)
                {
                    LogResult($"New FileOpenPicker - PickSingleFileAsync:\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult("New FileOpenPicker - PickSingleFileAsync: Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New FileOpenPicker: {ex.Message}");
            }
        }
        
        private async void UwpPickMultipleFiles_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                // Initialize UWP picker
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                
                var files = await picker.PickMultipleFilesAsync();
                if (files != null && files.Count > 0)
                {
                    var sb = new StringBuilder($"UWP FileOpenPicker - PickMultipleFilesAsync: {files.Count} files\n");
                    foreach (var file in files)
                    {
                        sb.AppendLine($"- {file.Name}: {file.Path}");
                    }
                    LogResult(sb.ToString());
                }
                else
                {
                    LogResult("UWP FileOpenPicker - PickMultipleFilesAsync: Operation cancelled or no files selected");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP PickMultipleFilesAsync: {ex.Message}");
            }
        }
        
        private async void NewPickMultipleFiles_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);
                
                var results = await picker.PickMultipleFilesAsync();
                if (results != null && results.Count > 0)
                {
                    var sb = new StringBuilder($"New FileOpenPicker - PickMultipleFilesAsync: {results.Count} files\n");
                    foreach (var result in results)
                    {
                        sb.AppendLine($"- {System.IO.Path.GetFileName(result.Path)}: {result.Path}");
                    }
                    LogResult(sb.ToString());
                }
                else
                {
                    LogResult("New FileOpenPicker - PickMultipleFilesAsync: Operation cancelled or no files selected");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New PickMultipleFilesAsync: {ex.Message}");
            }
        }
        
        private async void UwpFileTypeFilter_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                // Clear default filters and add user-specified filters
                picker.FileTypeFilter.Clear();
                foreach (var filter in GetFileFilters())
                {
                    picker.FileTypeFilter.Add(filter);
                }
                
                var file = await picker.PickSingleFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileOpenPicker with FileTypeFilter: {string.Join(", ", GetFileFilters())}\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult($"UWP FileOpenPicker with FileTypeFilter: {string.Join(", ", GetFileFilters())}\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP FileTypeFilter: {ex.Message}");
            }
        }
        
        private async void NewFileTypeFilter_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);
                
                // Clear default filters and add user-specified filters
                picker.FileTypeFilter.Clear();
                foreach (var filter in GetFileFilters())
                {
                    picker.FileTypeFilter.Add(filter);
                }
                
                var result = await picker.PickSingleFileAsync();
                if (result != null)
                {
                    LogResult($"New FileOpenPicker with FileTypeFilter: {string.Join(", ", GetFileFilters())}\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult($"New FileOpenPicker with FileTypeFilter: {string.Join(", ", GetFileFilters())}\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New FileTypeFilter: {ex.Message}");
            }
        }
        
        private async void UwpCommitButtonText_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                picker.CommitButtonText = CommitButtonTextInput.Text;
                
                var file = await picker.PickSingleFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileOpenPicker with CommitButtonText: '{CommitButtonTextInput.Text}'\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult($"UWP FileOpenPicker with CommitButtonText: '{CommitButtonTextInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP CommitButtonText: {ex.Message}");
            }
        }
        
        private async void NewCommitButtonText_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);

                picker.CommitButtonText = CommitButtonTextInput.Text;
                
                var result = await picker.PickSingleFileAsync();
                if (result != null)
                {
                    LogResult($"New FileOpenPicker with CommitButtonText: '{CommitButtonTextInput.Text}'\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult($"New FileOpenPicker with CommitButtonText: '{CommitButtonTextInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New CommitButtonText: {ex.Message}");
            }
        }
        
        private async void UwpStartLocation_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                picker.SuggestedStartLocation = GetSelectedLocation();
                
                var file = await picker.PickSingleFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileOpenPicker with SuggestedStartLocation: {GetSelectedLocation()}\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult($"UWP FileOpenPicker with SuggestedStartLocation: {GetSelectedLocation()}\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP SuggestedStartLocation: {ex.Message}");
            }
        }
        
        private async void NewStartLocation_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);

                picker.SuggestedStartLocation = GetSelectedNewLocationId();
                
                var result = await picker.PickSingleFileAsync();
                if (result != null)
                {
                    LogResult($"New FileOpenPicker with SuggestedStartLocation: {GetSelectedNewLocationId()}\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult($"New FileOpenPicker with SuggestedStartLocation: {GetSelectedNewLocationId()}\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New SuggestedStartLocation: {ex.Message}");
            }
        }
        
        private async void UwpSettingsId_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                picker.SettingsIdentifier = SettingsIdInput.Text;
                
                var file = await picker.PickSingleFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileOpenPicker with SettingsIdentifier: '{SettingsIdInput.Text}'\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult($"UWP FileOpenPicker with SettingsIdentifier: '{SettingsIdInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP SettingsIdentifier: {ex.Message}");
            }
        }
        
        private async void NewSettingsId_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);
                
                picker.SettingsIdentifier = SettingsIdInput.Text;
                
                var result = await picker.PickSingleFileAsync();
                if (result != null)
                {
                    LogResult($"New FileOpenPicker with SettingsIdentifier: '{SettingsIdInput.Text}'\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult($"New FileOpenPicker with SettingsIdentifier: '{SettingsIdInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New SettingsIdentifier: {ex.Message}");
            }
        }
        
        private async void UwpListView_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                picker.ViewMode = PickerViewMode.List;
                
                var file = await picker.PickSingleFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileOpenPicker with ViewMode: List\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult("UWP FileOpenPicker with ViewMode: List\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP ViewMode List: {ex.Message}");
            }
        }
        
        private async void UwpThumbnailView_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileOpenPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                picker.ViewMode = PickerViewMode.Thumbnail;
                
                var file = await picker.PickSingleFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileOpenPicker with ViewMode: Thumbnail\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult("UWP FileOpenPicker with ViewMode: Thumbnail\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP ViewMode Thumbnail: {ex.Message}");
            }
        }
        
        private async void NewListView_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);
                
                picker.ViewMode = Microsoft.Windows.Storage.Pickers.PickerViewMode.List;
                
                var result = await picker.PickSingleFileAsync();
                if (result != null)
                {
                    LogResult($"New FileOpenPicker with ViewMode: List\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult("New FileOpenPicker with ViewMode: List\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New ViewMode List: {ex.Message}");
            }
        }
        
        private async void NewThumbnailView_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);
                
                picker.ViewMode = Microsoft.Windows.Storage.Pickers.PickerViewMode.Thumbnail;
                
                var result = await picker.PickSingleFileAsync();
                if (result != null)
                {
                    LogResult($"New FileOpenPicker with ViewMode: Thumbnail\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult("New FileOpenPicker with ViewMode: Thumbnail\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New ViewMode Thumbnail: {ex.Message}");
            }
        }
        
        #endregion
        
        #region FileSavePicker Tests
        
        private async void UwpSaveFile_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileSavePicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.SuggestedFileName = "NewDocument";
                picker.FileTypeChoices.Add("Text Document", new List<string>() { ".txt" });
                
                var file = await picker.PickSaveFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileSavePicker - PickSaveFileAsync:\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult("UWP FileSavePicker - PickSaveFileAsync: Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP FileSavePicker: {ex.Message}");
            }
        }
        
        private async void NewSaveFile_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindow.Id);
                
                picker.SuggestedFileName = "NewDocument";
                picker.FileTypeChoices.Add("Text Document", new List<string>() { ".txt" });
                
                var result = await picker.PickSaveFileAsync();
                if (result != null)
                {
                    LogResult($"New FileSavePicker - PickSaveFileAsync:\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult("New FileSavePicker - PickSaveFileAsync: Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New FileSavePicker: {ex.Message}");
            }
        }
        
        private async void UwpSuggestedFileName_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileSavePicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.SuggestedFileName = SuggestedFileNameInput.Text;
                picker.FileTypeChoices.Add("Text Document", new List<string>() { ".txt" });
                
                var file = await picker.PickSaveFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileSavePicker with SuggestedFileName: '{SuggestedFileNameInput.Text}'\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult($"UWP FileSavePicker with SuggestedFileName: '{SuggestedFileNameInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP SuggestedFileName: {ex.Message}");
            }
        }
        
        private async void NewSuggestedFileName_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindow.Id);
                
                picker.SuggestedFileName = SuggestedFileNameInput.Text;
                picker.FileTypeChoices.Add("Text Document", new List<string>() { ".txt" });
                
                var result = await picker.PickSaveFileAsync();
                if (result != null)
                {
                    LogResult($"New FileSavePicker with SuggestedFileName: '{SuggestedFileNameInput.Text}'\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult($"New FileSavePicker with SuggestedFileName: '{SuggestedFileNameInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New SuggestedFileName: {ex.Message}");
            }
        }
        
        private async void UwpDefaultFileExtension_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileSavePicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.SuggestedFileName = "NewDocument";
                picker.DefaultFileExtension = DefaultFileExtensionInput.Text;
                picker.FileTypeChoices.Add("Custom Document", new List<string>() { DefaultFileExtensionInput.Text });
                
                var file = await picker.PickSaveFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileSavePicker with DefaultFileExtension: '{DefaultFileExtensionInput.Text}'\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult($"UWP FileSavePicker with DefaultFileExtension: '{DefaultFileExtensionInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP DefaultFileExtension: {ex.Message}");
            }
        }
        
        private async void NewDefaultFileExtension_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindow.Id);
                
                picker.SuggestedFileName = "NewDocument";
                picker.DefaultFileExtension = DefaultFileExtensionInput.Text;
                picker.FileTypeChoices.Add("Custom Document", new List<string>() { DefaultFileExtensionInput.Text });
                
                var result = await picker.PickSaveFileAsync();
                if (result != null)
                {
                    LogResult($"New FileSavePicker with DefaultFileExtension: '{DefaultFileExtensionInput.Text}'\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult($"New FileSavePicker with DefaultFileExtension: '{DefaultFileExtensionInput.Text}'\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New DefaultFileExtension: {ex.Message}");
            }
        }
        
        private async void UwpFileTypeChoices_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileSavePicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.SuggestedFileName = "Document";
                picker.FileTypeChoices.Clear();
                picker.FileTypeChoices.Add("Text Document", new List<string>() { ".txt" });
                picker.FileTypeChoices.Add("Rich Text Document", new List<string>() { ".rtf" });
                picker.FileTypeChoices.Add("Web Page", new List<string>() { ".html", ".htm" });
                
                var file = await picker.PickSaveFileAsync();
                if (file != null)
                {
                    LogResult($"UWP FileSavePicker with FileTypeChoices\nFile: {file.Name}\nPath: {file.Path}");
                }
                else
                {
                    LogResult("UWP FileSavePicker with FileTypeChoices\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP FileTypeChoices: {ex.Message}");
            }
        }
        
        private async void NewFileTypeChoices_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindow.Id);
                
                picker.SuggestedFileName = "Document";
                picker.FileTypeChoices.Clear();
                picker.FileTypeChoices.Add("Text Document", new List<string>() { ".txt" });
                picker.FileTypeChoices.Add("Rich Text Document", new List<string>() { ".rtf" });
                picker.FileTypeChoices.Add("Web Page", new List<string>() { ".html", ".htm" });
                
                var result = await picker.PickSaveFileAsync();
                if (result != null)
                {
                    LogResult($"New FileSavePicker with FileTypeChoices\nFile: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult("New FileSavePicker with FileTypeChoices\nOperation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New FileTypeChoices: {ex.Message}");
            }
        }
        
        #endregion
        
        #region FolderPicker Tests
        
        private async void UwpPickFolder_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FolderPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Add("*");
                
                var folder = await picker.PickSingleFolderAsync();
                if (folder != null)
                {
                    LogResult($"UWP FolderPicker - PickSingleFolderAsync:\nFolder: {folder.Name}\nPath: {folder.Path}");
                }
                else
                {
                    LogResult("UWP FolderPicker - PickSingleFolderAsync: Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP FolderPicker: {ex.Message}");
            }
        }
        
        private async void NewPickFolder_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FolderPicker(this.AppWindow.Id);
                
                var result = await picker.PickSingleFolderAsync();
                if (result != null)
                {
                    LogResult($"New FolderPicker - PickSingleFolderAsync:\nFolder: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult("New FolderPicker - PickSingleFolderAsync: Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New FolderPicker: {ex.Message}");
            }
        }
        
        private async void UwpFolderFileTypeFilter_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FolderPicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
                
                picker.FileTypeFilter.Clear();
                picker.FileTypeFilter.Add(".txt");
                picker.FileTypeFilter.Add(".docx");
                
                var folder = await picker.PickSingleFolderAsync();
                if (folder != null)
                {
                    LogResult($"UWP FolderPicker with FileTypeFilter (.txt, .docx):\nFolder: {folder.Name}\nPath: {folder.Path}");
                }
                else
                {
                    LogResult("UWP FolderPicker with FileTypeFilter (.txt, .docx): Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in UWP FolderPicker FileTypeFilter: {ex.Message}");
            }
        }
        
        private async void NewFolderFileTypeFilter_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Microsoft.Windows.Storage.Pickers.FolderPicker(this.AppWindow.Id);
                
                picker.FileTypeFilter.Clear();
                picker.FileTypeFilter.Add(".txt");
                picker.FileTypeFilter.Add(".docx");
                
                var result = await picker.PickSingleFolderAsync();
                if (result != null)
                {
                    LogResult($"New FolderPicker with FileTypeFilter (.txt, .docx):\nFolder: {System.IO.Path.GetFileName(result.Path)}\nPath: {result.Path}");
                }
                else
                {
                    LogResult("New FolderPicker with FileTypeFilter (.txt, .docx): Operation cancelled");
                }
            }
            catch (Exception ex)
            {
                LogResult($"Error in New FolderPicker FileTypeFilter: {ex.Message}");
            }
        }
        
        #endregion
    }
}
