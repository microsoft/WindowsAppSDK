## Name
PowerNotifications.APITests & FunctionalTests

## Feature Area
PowerStateNotifications

## Area Path
dev/PowerNotifications

## ETA: < 5 mins

## Special needs
A battery level aware VM will fail on the battery level and power source tests as the tests are currently configured for AC power devices.

## Test steps
1. Install Visual Studio 2019 or later
2. Install TDP/Tshell
2. Load up the AppSDK project
3. Recommened to make sure that the project builds successfully
4. Build test/PowerNotifications
5. The newly build dll should show up in TDP/Tshell
If not, manually load up BuildOutput\[Release/Debug]\[Arch]\PowerNotifications\PowerNotifications.dll
6. The tests will be under the loaded dll, both API and functional

## Pass criteria
All tests should run successfully
## Applicability: [Default]

## Automation Plan: None at the moment as the tests also have an Integration test equivalent and this has been deemed enough for this feature.