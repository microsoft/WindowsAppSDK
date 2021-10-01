
### Building the Installer

For inner-loop testing and running the InstallerFunctionalTests, this solution requires test
packages be built. Typically this only needs to be done once unless the set of packages changes.
To build the test packages, build CreateInstallerTestPackages.sln, located under
installer\test\CreateInstallerTestPackages.

For building an installer with real packages, create a 'windowsappruntime_definitions_override.h'
file in this folder with preprocessor redefinitions that override the package paths for inclusion.
See 'windowsappruntime_definitions.h' for details.
