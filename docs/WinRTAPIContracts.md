# Windows App SDK API Contracts

## Summary
Customers trust Microsoft that the products we make are sound, and will work.  Windows App SDK (WASDK) has recently released version 1.0.  As WASDK evolvs and more developers use WASDK in their own projects WASDK needs a way to guarantee that the API’s that ship are stable and that API versions are well documented.
To keep customers’ trust in WASDK, and to make sure the WASDK API’s are
1.  Binary compatible
2.  Stable
3.  Customizable so developers can include only the parts they want

Contracts, and contract versions should be added to WASDK.

## Architecture Decisions
1. Contract boundaries
Contracts will be split among the winmd boundaries.  This is a good medium between having 1 contract for everything, and 1 contract per class.
2. Contract numbering.
Contracts will be numbered with MAJOR.MINOR.  Any update to the API is a MAJOR change.  Any servicing update is a MINOR change.
3. Enforcement
The build systems will have enforcement gates to make sure that contracts are present, up to date, and there are no conflicts

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
Any API's that changed between 1.0 and 1.1 need to add a contract or 1.1 will not ship.

## Telemetry
Because all API's have a contract version data can be used to see
 1. How many people are using each API
 2. How many people are using each specific version

This data will allow us to better direct our development efforts to help the most developers.

## Gate check-ins
Because the contracts are used for API versions there will need to be work done in the build system to make sure
1. All API's have contracts
2. Each contract is correct.  This means version and name.
3. All Contracts and dependencies work with each other.

If there is an issue then the build should stop and no release should be made.

## Open issues
1. Telemetry needed for the data science team. The Data Science team should be involved with our contracts so we can make sure they have the correct data to answer business questions.
2. Contract boundary.  1 contract for WASDK is too big.  Yet, 1 contract per API is too many.  1 contract per winmd is a good middle.  This is an open issue because there might be a better option.
3. Should ProjectReunionClosed use contracts?