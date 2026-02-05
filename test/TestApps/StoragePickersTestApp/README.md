# StoragePickersTestApp

A WinUI 3 test application for the **Microsoft.Windows.Storage.Pickers** API built from the 
WindowsAppSDK repo.

## Purpose

- **Compare** new Storage Pickers API (`Microsoft.Windows.Storage.Pickers`) side-by-side with legacy 
UWP Pickers API (`Windows.Storage.Pickers`)
- **Test** FileOpenPicker, FileSavePicker, and FolderPicker APIs
- **Verify** local code changes in `Microsoft.Windows.Storage.Pickers`

> **Important:** Storage Pickers has been released since WindowsAppSDK 1.8. However, this test app 
exists specifically to test the **latest local code**, not the released version. We explicitly load 
our locally-built DLL to bypass the system's normal WinRT activation.

## Architecture

This project uses a hybrid approach:

| Component | Source |
|-----------|--------|
| WinUI 3 | Shipped Microsoft.WindowsAppSDK 1.6 |
| `Microsoft.Windows.Storage.Pickers` API | Local repo build output |
| Build isolation | Local `Directory.Build.props/targets` |

## How It Works

The app manually loads our locally-built `Microsoft.WindowsAppRuntime.dll` via `LoadLibraryExW` with 
full path, then calls `DllGetActivationFactory` to create picker instances.

This logic is encapsulated in `StoragePickersActivation.h/.cpp`.

## Build

### Prerequisites

1. Build `WindowsAppRuntime_DLL` first (provides Storage Pickers WinMD):
   ```powershell
   msbuild dev\WindowsAppRuntime_DLL\WindowsAppRuntime_DLL.vcxproj /p:Configuration=Release /p:Platform=x64
   ```

2. Then build this test app:
   ```powershell
   msbuild test\TestApps\StoragePickersTestApp\StoragePickersTestApp.vcxproj /p:Configuration=Release /p:Platform=x64
   ```

### Output

```
BuildOutput\Release\x64\StoragePickersTestApp\StoragePickersTestApp.exe
```

## Usage

1. Run `StoragePickersTestApp.exe`
2. Click **"Pick a File"** → Tests the NEW Storage Pickers API (local build)
3. Click **"Pick a File (UWP)"** → Tests the LEGACY UWP Pickers API
4. Selected file path appears in the text box
5. Compare behavior, performance, and ease of use between the two APIs

---

## Appendix: Why Manual DLL Loading?

Since Storage Pickers is released (WindowsAppSDK 1.8+), normal WinRT activation would load the 
**released** version. To test our **latest local code**, we must bypass normal activation.

### Approaches Tried (and why they failed)

| Approach | Code/Method | Result |
|----------|-------------|--------|
| Normal WinRT Activation | `FileOpenPicker picker{ windowId };` | Activates the **released** version, not local build |
| Manifest-Based Activation | `<activatableClass>` in app.manifest | XAML crash (`STATUS_STOWED_EXCEPTION`) - conflicts with NuGet's activation context |
| Simple LoadLibrary | `LoadLibraryW(L"Microsoft.WindowsAppRuntime.dll")` | Loads **system** DLL from `C:\Program Files\WindowsApps\...` |
| LoadLibraryExW (no .pri) | Full path but missing .pri file | "Element not found" - missing localization resources |

### Working Solution

1. Get application's directory path
2. `LoadLibraryExW` with **full path** + `LOAD_WITH_ALTERED_SEARCH_PATH`
3. `GetProcAddress` for `DllGetActivationFactory`
4. Call `DllGetActivationFactory` with class name → `IActivationFactory`
5. Query for specific factory interface (e.g., `IFileOpenPickerFactory`)
6. `CreateInstance` to create the picker
7. Copy both `.dll` **and** `.pri` files to output directory

This ensures we always test the locally-built version, not the released one.

---

## Learn More

- [Windows App SDK Documentation](https://docs.microsoft.com/windows/apps/windows-app-sdk/)
- [WinUI 3 Documentation](https://docs.microsoft.com/windows/apps/winui/winui3/)
