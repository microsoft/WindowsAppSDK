# New Document
# Windows App SDK API Contracts

## Summary
Customers trust that Microsoft products are sound. As Windows App SDK evolves and more developers
use Windows App SDK in their own projects Windows App SDK needs a way, at build time and run time,
to allow apps to light up API features and to gracefully degrade. This can be achieved by looking
at the deltas between APIs.

In order to allow apps to depend on API versions Windows App SDK will add contracts to all their
WinRT APIs.

## Architecture Decisions
1. Contract boundaries
   1. One contract per feature/component/sub-system.
   2. Contracts will not span across a transport package/repo.
2. Contract numbering  
Contracts versions are one number, starting with 1 and is incremented for any interface
change. This version does not correlate with the Windows App SDK version.
3. Enforcement  
The build system has gates that enforce contract versioning to verify that contract is present,
 up to date, and there are no conflicts between APIs.
4. Contract migration  
This spec does not deal with contract migration. A separate spec will be available for contract
migration if, and when, it is needed.
5. Internal contracts  
All WinRT internal APIs have a contract, and the version is 1. The version is never updated.
6. Contract naming  
Contract names need to end with the word `contract`.

## Adding a new contract
Contract placement is part of an API review. When adding a new API, the API team will
talk about what contract the API will go under.

## Example
```
namespace Microsoft.Windows.System
{
    [contractversion(1)]
    apicontract WindowsSystemContract {}
    
    [Contract(MicrosoftWindowsSystem, 1)]
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
## 1.1 ship blocker
Any APIs that changed between 1.0 and 1.1 need to add a contract or 1.1 will not ship.

## Telemetry
API specific telemetry will not be collected because it does not provide any additional information
compared to the Windows App SDK version.

## Gate check-ins
Because the contracts are used for API versions there will need to be work done in the build system
to make sure
1. All APIs have contracts
2. Each contract is correct. This means version and name.
3. All Contracts and dependencies work with each other.

The builds that check for contracts compatibility are:
1. Nightly
2. Release 
3. PR

## Open issues
None.
