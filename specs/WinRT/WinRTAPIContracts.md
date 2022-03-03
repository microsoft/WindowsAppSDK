


# Windows App SDK API Contracts

## Summary
Customers trust that Microsoft products are sound.  As Windows App SDK evolves and more developers use Windows App SDK in their own projects Windows App SDK needs a way, at build time and run time, to allow apps to light up API features and to gracefully degrade.  This can be achieved by looking at the deltas between APIs.  

In order to allow apps to depend on API versions Windows App SDK will add contracts to all their WinRT APIs.


## Architecture Decisions
1. Contract boundaries
   1. One contract per feature/component/sub-system
   2. Contracts will not span across a transport package/repo.
2. Contract numbering.
Contracts will be versioned with one number, starting with 1 and is incremented for any interface change.  This version does not correlate with the Windows App SDK version.
3. Enforcement
The build systems will have enforcement gates to make sure that contracts are present, up to date, and there are no conflicts.
4. Contract Migration.
Contract Migration will not be a part of this spec.  Windows App SDK will add a spec on contract migration if, and when, there is a situation where it is needed.
5. Internal contracts
All WinRT internal APIs will have an contract and the version will always be 1 regardless of any interface changes.

## Adding a new contract
Developers are encouraged to use their best judgment when deciding where to place a new contract.  If in doubt you can reach out to the Windows App SDK team.

## Example

    namespace Microsoft.Windows.System
    {
        [contractversion(2)]
        apicontract MicrosoftWindowsSystem
        
        // version 2
        [Contract(MicrosoftWindowsSystem(2)]
        public enum Scope
        {
            user,
            machine
        }

        [Contract(MicrosoftWindowsSystem(2)]
        public class EnvironmentManager
        {
            public String GetEnvironmentVariable(String name, Scope scope);
        }

        // base version
        [contract(MicrosoftWindowsSystem, 1)]
        public class EnvironmentManager
        {
            public String GetEnvironmentVariable(String name);
        }
    }

## Forbidden interface changes
To help keep ABI and binary compatibility between different versions of Windows App SDK here is a list of changes that should not happen between interface versions.
1. Method order in the interface.
2. Method signatures.

## 1.1 ship blocker
Any APIs that changed between 1.0 and 1.1 need to add a contract or 1.1 will not ship.

## Telemetry
API specific telemetry will not be collected because it does not provide any additional information compared to the Windows App SDK version.

## Gate check-ins
Because the contracts are used for API versions there will need to be work done in the build system to make sure
1. All APIs have contracts
2. Each contract is correct.  This means version and name.
3. All Contracts and dependencies work with each other.

If there is an issue then the build should stop and no release should be made.

## Open issues
None.