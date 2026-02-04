========================================================================
    StoragePickersTestApp - Storage Pickers API Test Application
========================================================================

This WinUI 3 application provides an interactive test environment for the
Microsoft.Windows.Storage.Pickers API built from the WindowsAppSDK repo.

PURPOSE:
--------
- Test FileOpenPicker, FileSavePicker, and FolderPicker APIs
- Verify API behavior with actual window handles and user interaction
- Provide a reference implementation for Storage Pickers usage

ARCHITECTURE:
-------------
This project intentionally uses a hybrid approach:
- WinUI 3 components come from the shipped Microsoft.WindowsAppSDK NuGet
- Storage Pickers API comes from the local repo's build output (WinMD)
- Isolated from repo build system via local Directory.Build.props/targets

BUILD PREREQUISITES:
--------------------
1. Build WindowsAppRuntime_DLL first (provides Storage Pickers WinMD):
   msbuild dev\WindowsAppRuntime_DLL\WindowsAppRuntime_DLL.vcxproj /p:Configuration=Release /p:Platform=x64

2. Then build this test app:
   msbuild test\TestApps\StoragePickersTestApp\StoragePickersTestApp.vcxproj /p:Configuration=Release /p:Platform=x64

OUTPUT:
-------
BuildOutput\Release\x64\StoragePickersTestApp\StoragePickersTestApp.exe

USAGE:
------
1. Run StoragePickersTestApp.exe
2. Click "Pick a File" button to test FileOpenPicker
3. Selected file path appears in the text box

========================================================================
Learn more about Windows App SDK:
https://docs.microsoft.com/windows/apps/windows-app-sdk/
Learn more about WinUI3:
https://docs.microsoft.com/windows/apps/winui/winui3/
========================================================================
