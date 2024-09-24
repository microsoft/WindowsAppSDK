# 1. Application Data

- [1. Application Data](#1-application-data)
- [2. Background](#2-background)
- [3. Description](#3-description)
  - [3.1. ApplicationData and ApplicationDataManager functionality](#31-applicationdata-and-applicationdatamanager-functionality)
  - [3.2. \*Path properties](#32-path-properties)
  - [3.3. Reliable access](#33-reliable-access)
  - [3.4. Per-Machine data store](#34-per-machine-data-store)
    - [3.4.1. Machine Path/Folder](#341-machine-pathfolder)
    - [3.4.2. Manifested Opt-In](#342-manifested-opt-in)
    - [3.4.3. Machine Path Creation/Deletion](#343-machine-path-creationdeletion)
    - [3.4.4. APIs](#344-apis)
  - [3.5. Unpackaged app data stores](#35-unpackaged-app-data-stores)
- [4. Examples](#4-examples)
  - [4.1. Packaged app using LocalPath](#41-packaged-app-using-localpath)
  - [4.2. Unpackaged app using package'd app's LocalPath](#42-unpackaged-app-using-packaged-apps-localpath)
  - [4.3. Packaged app using MachinePath](#43-packaged-app-using-machinepath)
  - [4.4. Unpackaged app using LocalPath](#44-unpackaged-app-using-localpath)
- [5. Remarks](#5-remarks)
  - [5.1. Platform Support](#51-platform-support)
- [6. API Details](#6-api-details)

This feature provides application data APIs comparable to those in namespaces
[Windows.Storage](https://learn.microsoft.com/uwp/api/windows.storage) and
[Windows.Management.Core](https://learn.microsoft.com/uwp/api/windows.management.core) but with
additional functionality, improved developer experience and performance optimizations.

This feature provides APIs to access and manipulate app data stores.

# 2. Background

Windows provides data stores for packaged applications to store data by user and package family via
WinRT APIs in the Windows.Storage and Windows.Management.Core namespaces. These API provide the
means to create, use and manage data in these data stores.

The Application Data APIs were originally introduced in Windows 8. However, as one of the earliest
WinRT APIs they include some patterns out of step with current API practices and recommendations.
Windows App SDK offers the opportunity to provide a new generation of APIs in line with the latest
patterns and recommendations for an improved developer experience as well as functional enhancements
and improved runtime efficiencies.

Microsoft-internal tasks [22308619](https://task.ms/22308619),
[30002314](https://task.ms/30002314), [39401257](https://task.ms/39401257),
[39414843](https://task.ms/39414843), [40050113](https://task.ms/40050113) and
[48332357](https://task.ms/48332357).

# 3. Description

This API supports app data stores focusing on the following scenarios:

* ApplicationData and ApplicationDataManager functionality
* *Path properties
* Reliable access
* Per-Machine data store
* Unpackaged app data stores

## 3.1. ApplicationData and ApplicationDataManager functionality

This API provides an equivalent superset of
[Windows.Storage.ApplicationData](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata),
with the following notable differences:

* **No roaming functionality** -- We don't provide equivalents to Windows.Storage.ApplicationData's
  [RoamingSettings](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.roamingsettings),
  [RoamingStorageQuota](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.roamingstoragequota),
  [Version](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.version),
  [SetVersionAsync()](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.setversionasync),
  [SignalDataChanged()](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.signaldatachanged)
  and
  [DataChanged](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.datachanged).
  See [5.1. Platform Support](#51-platform-support) for more details.
* **GetDefault() works for all packaged apps** -- Equivalent to [Windows.Storage.ApplicationData.Current](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.current)
  but works for all packaged apps (not just callers running in an AppContainer). See
  [3.3. Reliable access](#33-reliable-access).
* **`GetForPackageFamily()`** -- Equivalent to [Windows.Storage.ApplicationDataManager.CreateForPackageFamily()](https://learn.microsoft.com/uwp/api/windows.management.core.applicationdatamanager.createforpackagefamily).
* **`GetForUser()`** -- Synchronous equivalent to [Windows.Storage.ApplicationData.GetForUserAsync()](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.getforuserasync).
* **`GetForUnpackaged()`** -- Equivalent functionality for unpackaged apps. See
  [3.5. Unpackaged app data stores](#35-unpackaged-app-data-stores).

## 3.2. *Path properties

New *Path equivalents to Windows.Storage.ApplicationData's *Folder but returning a `String` rather than `StorageFolder`.

## 3.3. Reliable access

`Windows.Storage.ApplicationData.Current` only works for packaged apps **running in an
AppContainer**. Processes not running in an AppContainer (e.g. MediumIL) must use the equivalent
`Windows.Management.Core.ApplicationDataManager.CreateForPackageFamily(Windows.ApplicationModel.Package.Current.Id.FamilyName)`.

Microsoft.Windows.Storage.ApplicationData provides consistent behavior as developers expect e.g.
`ApplicationData.Current` works regardless if the caller's running in an AppContainer or not.

## 3.4. Per-Machine data store

Package families can optionally have a per-machine data store.

**NOTE:** This location is ACL'd by default to only grant Write access to System and TrustedInstaller.
Other users (even Administrators) have Read and eXecute rights but not Write. Processes running as
LocalSystem (e.g. [<desktop6:Extension Category="windows.service">](https://learn.microsoft.com/uwp/schemas/appxpackage/uapmanifestschema/element-desktop6-extension))
can use this location to manage per-machine data for a package family. This can be useful to share
data with other drivers or other privileged processes.

Processes with Write access can (if they choose) alter access rights on files or subdirectories in
a per-machine data store. For example, a Service running as LocalSystem can create a subdirectory
and call [SetSecurityInfo()](https://learn.microsoft.com/windows/win32/api/aclapi/nf-aclapi-setsecurityinfo)
to grant more access than provided by default.

**NOTE:** Consider carefully the security implications if alter permissions granting more permissive access than the default.

### 3.4.1. Machine Path/Folder

The path for a package family's "Machine Folder" is located at `%ProgramData%\Microsoft\Windows\AppRepository\Families\ApplicationData\...packagefamilyname...\Machine`.

This directory's ACL = `prefix + appxmanifest + suffix` where

* **prefix** = "D:AI(A;OICI;GA;;;S-1-5-80-956008885-3418522649-1831038044-1853292631-2271478464)(A;OICI;GA;;;SY)"
* **appxmanifest** = optional SDDL per `<appdata:MachineFolder Sddl="sdd"/>` in  appxmanifes.xml
* **suffix** = "(A;OICI;FRFX;;;BA)S:"

Thus the ACL has a Discretionary Access Control List (DACL) granting full control to Trusted
Installer (S-1-5-80-956008885-3418522649-1831038044-1853292631-2271478464) and LocalSystem  so
Windows can manage the directory, plus additional ACEs (if specified in the package's
appxmanifest.xml) and FILE_READ and FILE_EXECUTE rights to Built-in administrators (unless denied by
ACEs in appxmanifest).

For example, if no additional ACEs are specified in appxmanifest.xml the Machine Folder is ACL'd as

```
NT SERVICE\TrustedInstaller:(I)(F)
NT SERVICE\TrustedInstaller:(I)(CI)(IO)(F)
NT AUTHORITY\SYSTEM:(I)(F)
NT AUTHORITY\SYSTEM:(I)(OI)(CI)(IO)(F)
BUILTIN\Administrators:(I)(RX)
BUILTIN\Administrators:(I)(OI)(CI)(IO)(GR,GE)
```

### 3.4.2. Manifested Opt-In

The "Machine Folder" is only available for packages that explicitly opt-in to enabling it via appxmanifest.xml

```xml
<Package>
  ...
  <Properties>
    <appdata:ApplicationData>
      <MachineFolder/>
    </appdata:ApplicationData>
    ...
```

### 3.4.3. Machine Path Creation/Deletion

A new Undocked Deployment Extension Handler (DEH) creates the Machine path when a package in the package family is installed, if it doesn't already exist.

The Machine path is removed when the last package in the package family is removed from the machine.

### 3.4.4. APIs

New properties and methods to access per-machine data:

* ApplicationDataLocality.Machine
* ClearFolderAsync(Locality=Machine)
* IsMachinePathSupported
* MachineFolder
* MachinePath

## 3.5. Unpackaged app data stores

Unpackaged applications can use the ApplicationData API to access app data stores in the classic locations:

|Packaged                        |Unpackaged                                                         |
|--------------------------------|-------------------------------------------------------------------|
|ApplicationData.LocalCachePath  |`%LOCALAPPDATA%\<publisher>\<product>`                              |
|ApplicationData.LocalPath       |`%LOCALAPPDATA%\<publisher>\<product>`                               |
|ApplicationData.MachinePath     |`%ProgramData%\<publisher>\<product>`                                |
|ApplicationData.RoamingPath     |`%APPDATA%`                                                          |
|ApplicationData.TemporaryPath   |`[GetTempPath2W()](https://learn.microsoft.com/windows/win32/api/fileapi/nf-fileapi-gettemppath2w)\<publisher>\<product>`<sup>1,2</sup>|
|ApplicationData.LocalSettings   |`HKCU\SOFTWARE\Classes\Local Settings\Software\<publisher>\<product>`|
|ApplicationData.RoamingSettings |`HKCU\SOFTWARE\<publisher>\<product>`                                |

<sup>1</sup>

[GetTempPath2W()](https://learn.microsoft.com/windows/win32/api/fileapi/nf-fileapi-gettemppath2w)
returns the temporary path for the caller. See [GetTempPath2W()](https://learn.microsoft.com/windows/win32/api/fileapi/nf-fileapi-gettemppath2w)
for more details.

<sup>2</sup>

`GetTempPath2W()` is available on Windows version &gt;= 10.0.20348.0. `ApplicationData.TemporaryPath`
performs the equivalent logic on older systems (aka Polyfill).

# 4. Examples

## 4.1. Packaged app using LocalPath

Fabrikam packaged app creating a file in the LocalPath data store.

```c#
void SaveData(string data)
{
    var applicationData = ApplicationData.GetDefault();
    var filename = Path.Combine(applicationData.LocalPath, "stuff.dat");
    File.WriteAllText(filename, data, System.Text.UTF8Encoding);
}
```

## 4.2. Unpackaged app using package'd app's LocalPath

An unpackaged app app creating a file in the Fabrikam app's LocalPath data store.

```c#
void SaveData(string data)
{
    string packageFamilyName = "Fabrikam.Contoso_1234567890abc";
    var applicationData = ApplicationData.GetForPackageFamily(packageFamilyName);
    var filename = Path.Combine(applicationData.LocalPath, "stuff.dat");
    File.WriteAllText(filename, data, System.Text.UTF8Encoding);
}
```

## 4.3. Packaged app using MachinePath

Fabrikam packaged app running elevated and creating a file in the LocalPath data store.

```c#
void SaveData(string data)
{
    var applicationData = ApplicationData.GetDefault();
    var filename = Path.Combine(applicationData.MachinePath, "importantstuff.dat");
    File.WriteAllText(filename, data, System.Text.UTF8Encoding);
}
```

## 4.4. Unpackaged app using LocalPath

An unpackaged app app creating a file its LocalPath data store.

```c#
void SaveData(string data)
{
    string publisher = "Fabrikam";
    string product = "Contoso";
    var applicationData = ApplicationData.GetForUnpackaged(publisher, product);
    var filename = Path.Combine(applicationData.LocalPath, "stuff.dat");
    File.WriteAllText(filename, data, System.Text.UTF8Encoding);
}
```

# 5. Remarks

## 5.1. Platform Support

Per https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.roamingfolder#remarks:
  > Roaming data and settings is no longer supported as of Windows 11. The recommended replacement
      is Azure App Service. Azure App Service is widely supported, well documented, reliable, and
      supports cross-platform/cross-ecosystem scenarios such as iOS, Android and web. Settings
      stored here no longer roam (as of Windows 11), but the settings store is still available.

We provide `RoamingFolder` and `RoamingSettings` equivalents but they're only as functional as
Windows provides (i.e. no data roaming on Windows after 1909 aka 19H2 aka 10.0.18363.0).

We don't provide equivalents to Windows.Storage.ApplicationData's...

* [DataChanged](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.datachanged)
* [RoamingFolder](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.roamingfolder)
* [RoamingSettings](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.roamingsettings)
* [RoamingStorageQuota](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.roamingstoragequota)
* [SetVersionAsync()](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.setversionasync)
* [SignalDataChanged()](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.signaldatachanged)
* [Version](https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.version)

If you need this functionality use the OS APIs in `Windows.Storage.ApplicationData`.

# 6. API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.Storage
{
    [contractversion(2)]
    apicontract ApplicationDataContract{};

    /// Specifies the type of data store.
    /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdatalocality
    [contract(ApplicationDataContract, 1)]
    enum ApplicationDataLocality
    {
        // NOTE: Values 0-99 match Windows.Storage.ApplicationDataLocality.
        //       Values 1000+ are unique to us here.
        Local = 0,
        LocalCache = 3,
        SharedLocal = 4,
        Temporary = 2,
        Machine = 1000,
    };

    /// Specifies options for creating application data containers or returning existing containers.
    [contract(ApplicationDataContract, 1)]
    enum ApplicationDataCreateDisposition
    {
        /// Always returns the specified container. Creates the container if it does not exist.
        Always = 0,

        // Returns the specified container only if it already exists. Raises an exception of type System.Exception if the specified container does not exist.
        Existing,
    };

    /// Represents a container for settings. The methods and properties of this class support creating, deleting, enumerating, and traversing the container hierarchy.
    /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdatacontainer
    [contract(ApplicationDataContract, 1)]
    runtimeclass ApplicationDataContainer : Windows.Foundation.IClosable
    {
        /// Return the child settings containers of the settings container.
        /// https://learn.microsoft.com/uwp/api/windows.storage.applicationdatacontainer.containers
        IMap<String, ApplicationDataContainer> Containers { get; };

        /// Return the name of the current settings container.
        /// https://learn.microsoft.com/uwp/api/windows.storage.applicationdatacontainer.name
        String Name { get; };

        /// Return the type of the app data store that is associated with the settings container.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdatacontainer.locality
        ApplicationDataLocality Locality { get; };

        /// Return an object that represents the settings in the settings container.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdatacontainer.values
        Windows.Foundation.Collections.IPropertySet Values { get; };

        /// Create or open the specified settings container in the settings container.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdatacontainer.createcontainer
        ApplicationDataContainer CreateContainer(String name, ApplicationDataCreateDisposition disposition);

        /// Delete the specified settings container, its subcontainers, and all settings in the hierarchy.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdatacontainer.deletecontainer
        void DeleteContainer(String name);
    };

    /// Provides access to the application data store.
    /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata
    [contract(ApplicationDataContract, 1)]
    runtimeclass ApplicationData : Windows.Foundation.IClosable
    {
        /// Get an instance of ApplicationData for the current user.
        /// @note Requires the current process has package identity.
        /// @note This is equivalent to Windows.Storage.ApplicationData.Current if running in an AppContainer.
        /// @note This is equivalent to Windows.Storage.ApplicationDataManager.CreateForPackageFamily(GetCurrentPackageFamilyName()) if not running in an AppContainer.
        static ApplicationData GetDefault();

        /// Get an instance of ApplicationData for the specified user.
        /// @note This is equivalent to Windows.Storage.ApplicationData.GetForUserAsync()
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.getforuserasync
        static ApplicationData GetForUser(Windows.System.User user);

        /// Get an instance of ApplicationData for the specified package family for the current user.
        /// @note This is equivalent to Windows.Storage.ApplicationDataManager.CreateForPackageFamily()
        /// @see https://learn.microsoft.com/uwp/api/windows.management.core.applicationdatamanager.createforpackagefamily
        static ApplicationData GetForPackageFamily(String packageFamilyName);

        /// Get an instance of ApplicationData for the specified unpackaged app for the current user.
        [feature(Feature_ApplicationData)]
        [contract(ApplicationDataContract, 2)]
        static ApplicationData GetForUnpackaged(String publisher, String product);

        /// Return true if the package family supports the machine data store.
        Boolean IsMachinePathSupported { get; };

        /// Return the path for the local cache data store not included in backup and restore operations.
        /// @note This is equivalent to Windows.Storage.ApplicationData.LocalCacheFolder().Path()
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.localcachefolder
        String LocalCachePath { get; };

        /// Return the path for the local data store. This location is backed up to the cloud.
        /// @note This is equivalent to Windows.Storage.ApplicationData.LocalFolder().Path()
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.localfolder
        String LocalPath { get; };

        /// Return the path for the machine data store.
        /// @note This location is per-machine (not per-user like other *Path properties).
        /// @note Empty string is returned if not supported.
        /// @see IsMachinePathSupported
        String MachinePath { get; };

        /// Return the path for the shared data store.
        /// @note This is equivalent to Windows.Storage.ApplicationData.SharedLocalFolder().Path()
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.sharedlocalfolder
        String SharedLocalPath { get; };

        /// Return the path for the temporary data store.
        /// @note This is equivalent to Windows.Storage.ApplicationData.TemporaryFolder().Path()
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.temporaryfolder
        String TemporaryPath { get; };

        /// Return a StorageFolder for the local cache data store not included in backup and restore operations.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.localcachefolder
        Windows.Storage.StorageFolder LocalCacheFolder { get; };

        /// Return a StorageFolder for the local data store. This location is backed up to the cloud.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.localfolder
        Windows.Storage.StorageFolder LocalFolder { get; };

        /// Return a StorageFolder for the machine data store.
        /// @note This location is per-machine (not per-user like other *Folder properties).
        /// @note `null` is returned if not supported.
        /// @see IsMachinePathSupported
        Windows.Storage.StorageFolder MachineFolder { get; };

        /// Return a StorageFolder for the shared data store.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.sharedlocalfolder
        Windows.Storage.StorageFolder SharedLocalFolder { get; };

        /// Return a StorageFolder for the temporary data store.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.temporaryfolder
        Windows.Storage.StorageFolder TemporaryFolder { get; };

        /// Return the settings container in the local data store.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.localsettings
        ApplicationDataContainer LocalSettings { get; };

        /// Remove all data from the specified data store.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.clearasync
        Windows.Foundation.IAsyncAction ClearAsync(ApplicationDataLocality locality);

        /// Clear the files and subfolders from the specified subfolder of the shared storage folder for the publisher.
        /// @see GetPublisherCachePath()
        /// @see GetPublisherCacheFolder()
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.clearpublishercachefolderasync
        Windows.Foundation.IAsyncAction ClearPublisherCacheFolderAsync(String folderName);

        /// Return the specified path of the shared data store for the publisher of the app.
        /// @note This is equivalent to Windows.Storage.ApplicationData.GetPublisherCacheFolder(folderName).Path()
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.getpublishercachefolder
        String GetPublisherCachePath(String folderName);

        /// Return the specified subfolder of the shared data store for the publisher of the app.
        /// @see https://learn.microsoft.com/uwp/api/windows.storage.applicationdata.getpublishercachefolder
        Windows.Storage.StorageFolder GetPublisherCacheFolder(String folderName);
    }
}
```
