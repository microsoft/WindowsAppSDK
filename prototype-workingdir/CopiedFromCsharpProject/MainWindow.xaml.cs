using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using Microsoft.UI.Xaml;

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
                case 0: return Windows.Storage.Pickers.PickerLocationId.DocumentsLibrary;
                case 1: return Windows.Storage.Pickers.PickerLocationId.ComputerFolder;
                case 2: return Windows.Storage.Pickers.PickerLocationId.Desktop;
                case 3: return Windows.Storage.Pickers.PickerLocationId.Downloads;
                case 4: return Windows.Storage.Pickers.PickerLocationId.HomeGroup;
                case 5: return Windows.Storage.Pickers.PickerLocationId.MusicLibrary;
                case 6: return Windows.Storage.Pickers.PickerLocationId.PicturesLibrary;
                case 7: return Windows.Storage.Pickers.PickerLocationId.VideosLibrary;
                case 8: return Windows.Storage.Pickers.PickerLocationId.Objects3D;
                case 9: return Windows.Storage.Pickers.PickerLocationId.Unspecified;
                default: throw new InvalidOperationException("Invalid location selected");
            }
        }

        private Microsoft.Windows.Storage.Pickers.PickerLocationId GetSelectedNewLocationId()
        {
            switch (StartLocationComboBox.SelectedIndex)
            {
                case 0: return Microsoft.Windows.Storage.Pickers.PickerLocationId.DocumentsLibrary;
                case 1: return Microsoft.Windows.Storage.Pickers.PickerLocationId.ComputerFolder;
                case 2: return Microsoft.Windows.Storage.Pickers.PickerLocationId.Desktop;
                case 3: return Microsoft.Windows.Storage.Pickers.PickerLocationId.Downloads;
                case 4: return Microsoft.Windows.Storage.Pickers.PickerLocationId.HomeGroup;
                case 5: return Microsoft.Windows.Storage.Pickers.PickerLocationId.MusicLibrary;
                case 6: return Microsoft.Windows.Storage.Pickers.PickerLocationId.PicturesLibrary;
                case 7: return Microsoft.Windows.Storage.Pickers.PickerLocationId.VideosLibrary;
                case 8: return Microsoft.Windows.Storage.Pickers.PickerLocationId.Objects3D;
                case 9: return Microsoft.Windows.Storage.Pickers.PickerLocationId.Unspecified;
                default: throw new InvalidOperationException("Invalid location selected");
            }
        }

        private Windows.Storage.Pickers.PickerViewMode GetSelectedViewMode()
        {
            switch (ViewModeComboBox.SelectedIndex)
            {
                case 0: return Windows.Storage.Pickers.PickerViewMode.List;
                case 1: return Windows.Storage.Pickers.PickerViewMode.Thumbnail;
                default: throw new InvalidOperationException("Invalid view mode selected");
            }
        }

        private Microsoft.Windows.Storage.Pickers.PickerViewMode GetSelectedNewViewMode()
        {
            switch (ViewModeComboBox.SelectedIndex)
            {
                case 0: return Microsoft.Windows.Storage.Pickers.PickerViewMode.List;
                case 1: return Microsoft.Windows.Storage.Pickers.PickerViewMode.Thumbnail;
                default: throw new InvalidOperationException("Invalid view mode selected");
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

                picker.FileTypeFilter.Clear();
                if (FileTypeFilterCheckBox.IsChecked == true)
                {
                    foreach (var filter in GetFileFilters())
                    {
                        picker.FileTypeFilter.Add(filter);
                    }
                }

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (ViewModeCheckBox.IsChecked == true)
                {
                    picker.ViewMode = GetSelectedViewMode();
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedLocation();
                }

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

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (ViewModeCheckBox.IsChecked == true)
                {
                    picker.ViewMode = GetSelectedNewViewMode();
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedNewLocationId();
                }

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

                picker.FileTypeFilter.Clear();
                if (FileTypeFilterCheckBox.IsChecked == true)
                {
                    foreach (var filter in GetFileFilters())
                    {
                        picker.FileTypeFilter.Add(filter);
                    }
                }

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (ViewModeCheckBox.IsChecked == true)
                {
                    picker.ViewMode = GetSelectedViewMode();
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedLocation();
                }
                
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

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (ViewModeCheckBox.IsChecked == true)
                {
                    picker.ViewMode = GetSelectedNewViewMode();
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedNewLocationId();
                }

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

                picker.FileTypeFilter.Clear();
                if (FileTypeFilterCheckBox.IsChecked == true)
                {
                    foreach (var filter in GetFileFilters())
                    {
                        picker.FileTypeFilter.Add(filter);
                    }
                }

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (ViewModeCheckBox.IsChecked == true)
                {
                    picker.ViewMode = GetSelectedViewMode();
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedLocation();
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

                picker.FileTypeFilter.Clear();
                if (FileTypeFilterCheckBox.IsChecked == true)
                {
                    foreach (var filter in GetFileFilters())
                    {
                        picker.FileTypeFilter.Add(filter);
                    }
                }

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (ViewModeCheckBox.IsChecked == true)
                {
                    picker.ViewMode = GetSelectedNewViewMode();
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedNewLocationId();
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
        
        #endregion
        
        #region FileSavePicker Tests
        
        private async void UwpFileTypeChoices_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var picker = new Windows.Storage.Pickers.FileSavePicker();
                var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
                WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);

                if (SuggestedFileNameCheckBox.IsChecked == true)
                {
                    picker.SuggestedFileName = SuggestedFileNameInput.Text;
                }

                if (DefaultFileExtensionCheckBox.IsChecked == true)
                {
                    picker.DefaultFileExtension = DefaultFileExtensionInput.Text;
                }

                picker.FileTypeChoices.Clear();
                if (FileTypeChoicesCheckBox.IsChecked == true)
                {
                    var choicesJson = FileTypeChoicesInput.Text;
                    if (!string.IsNullOrEmpty(choicesJson))
                    {
                        var choices = System.Text.Json.JsonSerializer.Deserialize<Dictionary<string, List<string>>>(choicesJson);
                        foreach (var choice in choices)
                        {
                            picker.FileTypeChoices.Add(choice.Key, choice.Value);
                        }
                    }
                }

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedLocation();
                }
                
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

                if (SuggestedFileNameCheckBox.IsChecked == true)
                {
                    picker.SuggestedFileName = SuggestedFileNameInput.Text;
                }

                if (DefaultFileExtensionCheckBox.IsChecked == true)
                {
                    picker.DefaultFileExtension = DefaultFileExtensionInput.Text;
                }

                picker.FileTypeChoices.Clear();
                if (FileTypeChoicesCheckBox.IsChecked == true)
                {
                    var choicesJson = FileTypeChoicesInput.Text;
                    if (!string.IsNullOrEmpty(choicesJson))
                    {
                        var choices = System.Text.Json.JsonSerializer.Deserialize<Dictionary<string, List<string>>>(choicesJson);
                        foreach (var choice in choices)
                        {
                            picker.FileTypeChoices.Add(choice.Key, choice.Value);
                        }
                    }
                }

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedNewLocationId();
                }
                                
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

                picker.FileTypeFilter.Clear();
                if (FileTypeFilterCheckBox.IsChecked == true)
                {
                    foreach (var filter in GetFileFilters())
                    {
                        picker.FileTypeFilter.Add(filter);
                    }
                }

                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedLocation();
                }
                
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
                
                if (CommitButtonCheckBox.IsChecked == true)
                {
                    picker.CommitButtonText = CommitButtonTextInput.Text;
                }

                if (SettingsIdCheckBox.IsChecked == true)
                {
                    picker.SettingsIdentifier = SettingsIdInput.Text;
                }

                if (SuggestedStartLocationCheckBox.IsChecked == true)
                {
                    picker.SuggestedStartLocation = GetSelectedNewLocationId();
                }
                
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
        
        #endregion

        #region test any code
        // Write anything here.
        private async void TestAnyCode_Click(object sender, RoutedEventArgs e)
        {
            var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);
            //// Initialize UWP picker
            //var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
            //WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);
            picker.FileTypeFilter.Add("");

            //var picker = new Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindow.Id);

            //picker.SettingsIdentifier = "Test04011829";
            //picker.SuggestedStartLocation = Microsoft.Windows.Storage.Pickers.PickerLocationId.MusicLibrary;
            //picker.CommitButtonText = CommitButtonTextInput.Text;

            //var file = await picker.PickSingleFileAsync();
            //if (file != null)
            //{
            //    LogResult($"UWP FileOpenPicker - PickSingleFileAsync:\nFile: Path: {file.Path}");
            //}
            //else
            //{
            //    LogResult("UWP FileOpenPicker - PickSingleFileAsync: Operation cancelled");
            //}


        }

        #endregion
    }
}
