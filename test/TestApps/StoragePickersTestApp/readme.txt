========================================================================
    StoragePickersTestApp - Storage Pickers API Test Application
========================================================================

This WinUI 3 application provides an interactive test environment for the
Microsoft.Windows.Storage.Pickers API built from the WindowsAppSDK repo.

PURPOSE:
--------
- Test FileOpenPicker, FileSavePicker, and FolderPicker APIs from LOCAL builds
- Verify the LATEST code changes before they are released
- Ensure we are NOT using the shipped/released version of Storage Pickers

IMPORTANT: Storage Pickers has been released since WindowsAppSDK 1.8. However,
this test app exists specifically to test the LATEST local code, not the
released version. We must explicitly load our locally-built DLL to bypass
the system's normal WinRT activation which would use the released version.

ARCHITECTURE:
-------------
This project intentionally uses a hybrid approach:
- WinUI 3 components come from the shipped Microsoft.WindowsAppSDK NuGet
- Storage Pickers API comes from the LOCAL repo's build output (not released)
- Isolated from repo build system via local Directory.Build.props/targets

HOW IT WORKS:
-------------
The app manually loads our locally-built Microsoft.WindowsAppRuntime.dll via
LoadLibraryExW with full path, then calls DllGetActivationFactory to create
picker instances. This logic is encapsulated in StoragePickersActivation.h/.cpp.

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
                    APPENDIX: WHY MANUAL DLL LOADING?
========================================================================

Since Storage Pickers is released (WindowsAppSDK 1.8+), normal WinRT activation
would load the RELEASED version. To test our LATEST local code, we must bypass
normal activation and explicitly load our locally-built DLL.

The following approaches were tried, and their failures illustrate why:

1. Normal WinRT Activation (standard constructor)
   Code: FileOpenPicker picker{ windowId };
   Result: Activates the RELEASED version from system, not our local build.

2. Manifest-Based Activation (activatableClass in app.manifest)
   Result: XAML crash (STATUS_STOWED_EXCEPTION 0xc000027b) - manifest entries
           conflict with the shipped NuGet's activation context.

3. Simple LoadLibrary
   Code: LoadLibraryW(L"Microsoft.WindowsAppRuntime.dll")
   Result: Loads SYSTEM DLL from C:\Program Files\WindowsApps\..., not local.

4. LoadLibraryExW with Full Path (without .pri file)
   Result: "Element not found" - missing .pri resource file for localization.

WORKING SOLUTION:
-----------------
1. Get application's directory path
2. LoadLibraryExW with FULL PATH + LOAD_WITH_ALTERED_SEARCH_PATH
3. GetProcAddress for DllGetActivationFactory
4. Call DllGetActivationFactory with class name → IActivationFactory
5. Query for specific factory interface (e.g., IFileOpenPickerFactory)
6. CreateInstance to create the picker
7. Copy both .dll AND .pri files to output directory

This ensures we always test the locally-built version, not the released one.

========================================================================
Learn more about Windows App SDK:
https://docs.microsoft.com/windows/apps/windows-app-sdk/
Learn more about WinUI3:
https://docs.microsoft.com/windows/apps/winui/winui3/
========================================================================
