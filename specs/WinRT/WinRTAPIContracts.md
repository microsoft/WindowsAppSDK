- [1. Windows App SDK API Contracts](#1-windows-app-sdk-api-contracts)
- [2. Architectural Decisions](#2-architectural-decisions)
- [3. Adding a new contract](#3-adding-a-new-contract)
  - [3.1. Example](#31-example)
- [4. Missing contracts is a ship blocker](#4-missing-contracts-is-a-ship-blocker)
  - [4.1. Gate check-ins](#41-gate-check-ins)
- [5. Telemetry](#5-telemetry)
- [6. All Contracts in Windows App SDK](#6-all-contracts-in-windows-app-sdk)

# 1. Windows App SDK API Contracts

Customers trust that Microsoft products are sound. As Windows App SDK evolves and more developers
use Windows App SDK in their own projects Windows App SDK needs a way, at build time and run time,
to allow apps to light up API features and to gracefully degrade. This can be achieved by looking
at the deltas between APIs.

In order to allow apps to depend on API versions Windows App SDK will add contracts to all their
WinRT APIs.

# 2. Architectural Decisions
1. **Contract Boundaries**<BR>
   1. One contract per feature/component/sub-system
   2. Contracts will not span across a transport package/repo
2. **Contract Version**<BR>
Contracts versions are a single number with no minor version, no "x.y". The contract version is
frozen on a stable release. Any changes after a stable release requires the version to be incremented.
3. **Enforcement**<BR>
The build system has gates that enforce contract versioning to verify that contract is present,
 up to date, and there are no conflicts between APIs.
4. **Contract Migration**<BR>
This spec does not deal with contract migration. A separate spec will be available for contract
migration if, and when, it is needed.
5. **Contract naming**<BR>
Contract names must end with `Contract`.
6. **Internal contracts**<BR>
Internal contracts follow additional rules:
    1. All internal WinRT APIs have an internal contract.
    2. Internal contracts are tagged with `[internal]`.
    3. Internal contracts are always version 1. The version is never updated.
    4. Internal contract names must end with `InternalContract`

# 3. Adding a new contract
Contract placement is part of an API review. When adding a new API, the API team will
talk about what contract the API will go under.

## 3.1. Example

```c# (really midl3)
namespace Microsoft.Windows.System
{
    [contractversion(1)]
    apicontract EnvironmentManagerContract {}

    [contract(EnvironmentManagerContract, 1)]
    runtimeclass EnvironmentManager
    {
        static EnvironmentManager GetForProcess();
        static EnvironmentManager GetForUser();
        static EnvironmentManager GetForMachine();

        static Boolean IsSupported{ get; };

        IMapView<String, String> GetEnvironmentVariables();
        String GetEnvironmentVariable(String name);
        void SetEnvironmentVariable(String name, String value);

        // Path manipulation
        void AppendToPath(String path);
        void RemoveFromPath(String path);

        // PathExt Manipulation
        void AddExecutableFileExtension(String pathExt);
        void RemoveExecutableFileExtension(String pathExt);
    }
}
```

# 4. Missing contracts is a ship blocker
WinRT APIs without a contract are a shipblocking bug.

## 4.1. Gate check-ins
Because the contracts are used for API versions there will need to be work done in the build system
to make sure
1. All APIs have contracts
2. Each contract is correct. This means version and name.
3. All Contracts and dependencies work with each other.
4. Contracts/Types in releases honor the source/binary/behavior compatibility rules e.g.
contracts/types in a stable release doesn't change in future releases of the same major version
(e.g. contracts/types in 1.1 don't change in 1.2, 1.3, ...)

The builds that check for contracts compatibility are:
1. Nightly
2. Release
3. PR

# 5. Telemetry
API contract version specific telemetry will not be collected because it does not provide any
additional information compared to the Windows App SDK version.

# 6. All Contracts in Windows App SDK
The list of all contracts defined across Windows App SDK

| Feature            | Repository    | Contract                        | Namespace                                            | Comment |
|--------------------|---------------|---------------------------------|----------------------------------------------------------------------------|---------|
| AccessControl      | windowsappsdk | AccessControlContract           | Microsoft.Windows.Security.AccessControl             |         |
| AppLifecycle       | windowsappsdk | AppLifecycleContract            | Microsoft.Windows.AppLifecycle                       |         |
| AppNotifications   | windowsappsdk | AppNotificationsContract        | Microsoft.Windows.AppNotifications                   |         |
| BackgroundTask     | windowsappsdk | BackgroundTaskContract          | Microsoft.Windows.ApplicationModel.Background        |         |
| CameraCaptureUI    | windowsappsdk | CameraCaptureUIContract         | Microsoft.Windows.Media.Capture                      |         |
| Deployment         | windowsappsdk | DeploymentManagerContract       | Microsoft.Windows.ApplicationModel.WindowsAppRuntime |         |
| DynamicDependency  | windowsappsdk | DynamicDependencyContract       | Microsoft.Windows.ApplicationModel.DynamicDependency |         |
| EnvironmentManager | windowsappsdk | EnvironmentManagerContract      | Microsoft.Windows.System                             |         |
| MRTCore            | windowsappsdk | MrtCoreContract                 | Microsoft.Windows.ApplicationModel.Resources         |         |
| PowerNotifications | windowsappsdk | PowerNotificationsContract      | Microsoft.Windows.System.Power                       |         |
| PushNotifications  | windowsappsdk | PushNotificationsContract       | Microsoft.Windows.PushNotifications                  |         |
| OAuth              | windowsappsdk | OAuthContract                   | Microsoft.Windows.Security.Authentication.OAuth      |         |
| WinUI              | winui         | HostingContract                 | Microsoft.UI.Xaml.Hosting                            |         |
| WinUI              | winui         | WinUIContract                   | Microsoft.UI.Xaml                                    |         |
| WinUI              | winui         | WinUIControlsContract           | Microsoft.UI.Xaml.Controls                           |         |
| WinUI              | winui         | XamlDirectContract              | Microsoft.UI.Xaml.Core.Direct                        |         |
| ---                | ---           | WindowsAppSDKContract           | Microsoft.Foundation                                 |1,2,3    |

<sup>1</sup> Only for use by InteractiveExperiences.<BR>
<sup>2</sup> This contract is misnamed. It should have been `InteractiveExperiencesContract` in the `Windows.UI.Composition` namespace.<BR>
<sup>3</sup> This contract is misversioned. It should have been `[contract(...,1)]` instead of `[contract(...,1.1)]`. The next contract version will be `[contract(...,2)]`.<BR>
