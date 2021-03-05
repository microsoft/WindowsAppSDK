
### Create Installer Test Packages

This project builds test packages for the installer. Since the installer must be built with packages, these are the default packages it targets for inclusion.
These can be used for testing the installer itself without interfering with real Project Reunion packages that may be on the system. Real packages built with the
installer are to be done using the override header, specified in project_reunion_definitions.h

These packages are dummy packages that do not contain any running code and are only intended to test deployment operations done by the installer. They are built
for all architectures and placed in the same "installerpackages" folder. The reason they are copied to this location is due to limitations with the resource
compiler, which does not support the same preprocessor macros and definitions as the C++ compiler. To avoid unnecessary complexity with the resource compiler,
the input packages for the installer are always copied to the same location where they can easily be specified in a preprocessor macro.

To save build time and signing complexities, this project only needs to be built when new test packages need to be added or generated and added as test collateral.

