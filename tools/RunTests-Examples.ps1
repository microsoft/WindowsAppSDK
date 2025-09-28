# RunTests.ps1 Usage Examples

# This file contains examples of how to use the RunTests.ps1 script for development

# Simplest possible usage - Run tests with all defaults (BuildOutput, x64 Release, no WPR profile)
.\RunTests.ps1 -TestDefName "Deployment" -Test

# List tests with all defaults
.\RunTests.ps1 -TestDefName "VersionInfoTests" -List

# Override platform to x86
.\RunTests.ps1 -TestDefName "PushNotifications" -Platform "x86" -Test

# Override configuration to Debug
.\RunTests.ps1 -TestDefName "CameraCaptureUI" -Configuration "Debug" -Test

# Override both platform and configuration
.\RunTests.ps1 -TestDefName "StoragePickerTests" -Platform "x86" -Configuration "Debug" -Test

# Override output folder (if using different build location)
.\RunTests.ps1 -TestDefName "Deployment" -OutputFolder "MyCustomBuildOutput" -Test

# Run tests without showing system info
.\RunTests.ps1 -TestDefName "CameraCaptureUI" -ShowSystemInfo:$false -Test

# Run tests with WPR profile for ETW logging (optional)
.\RunTests.ps1 -TestDefName "Deployment" -wprProfilePath "profile.wprp" -Test

# Common testdef names you might use:
# - Deployment
# - VersionInfoTests  
# - CameraCaptureUI
# - StoragePickerTests
# - PushNotifications
# - AppNotifications
# - DynamicDependency
# - PackageManager
# - And many more...

# Note: The script will automatically search for the .testdef file in the BuildOutput directory structure
# You only need to provide the TestDefName (without the .testdef extension)
# Default values: OutputFolder=BuildOutput, Platform=x64, Configuration=Release
# The wprProfilePath parameter is optional - if not provided, tests will run without ETW logging