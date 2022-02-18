
# Windows App SDK API Contracts

## Summary
Customers trust that Microsoft products are sound.  As Windows App SDK evolves and more developers use Windows App SDK in their own projects Windows App SDK needs a way, at build time and run time, to allow apps to light up API features and to gracefully degrade.  This can be achieved by looking at the deltas between APIs.  

In order to allow apps to depend on API versions Windows App SDK will add contracts to all their WinRT APIs.


## Architecture Decisions
1. Contract boundaries
Contracts will be split among the winmd boundaries.  This is a good medium between having 1 contract for everything, and 1 contract per class.
2. Contract numbering.
Contracts will be numbered with MAJOR.MINOR.  Any update to the API is a MAJOR change.  Any servicing update is a MINOR change.  The MAJOR and MINOR versions do not correlate with MAJOR and MINOR versions from Windows App SDK.
3. Enforcement
The build systems will have enforcement gates to make sure that contracts are present, up to date, and there are no conflicts.

## Example
    namespace Microsoft.Windows.System
    {
        [contractversion(2.0)]
        apicontract MicrosoftWindowsSystem
        
        // version 2.0
        [Contract(MicrosoftWindowsSystem(2.0)]
        public enum Scope
        {
            user,
            machine
        }

        [Contract(MicrosoftWindowsSystem(2.0)]
        public class EnvironmentManager
        {
            public String GetEnvironmentVariable(String name, Scope scope);
        }

        // servicing
        [Contract(MicrosoftWindowsSystem(1.5)]	    
        public class EnvironmentManager
        {
            public String GetEnvironmentVariable(String name, String scope);
        }

        // base version
        [contract(MicrosoftWindowsSystem, 1.0),]
        public class EnvironmentManager
        {
            public String GetEnvironmentVariable(String name);
        }
    }

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
1. Telemetry needed for the data science team. The Data Science team should be involved with our contracts so we can make sure they have the correct data to answer business questions. (No telemetry for API versions)
2. Contract boundary.  1 contract for WASDK is too big.  Yet, 1 contract per API is too many.  1 contract per winmd is a good middle.  This is an open issue because there might be a better option.
3. Should ProjectReunionClosed use contracts? (Yes)