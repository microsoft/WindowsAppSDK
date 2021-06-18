Write-Host "TestPass-PreRun.ps1"

# This script is run on the test machine for each work item that executes there.
# It runs just before executing the test.

# This script is called by TestPass-PreRunCore.ps1 which is a part of the WinUI.Helix package.

.\TestPass-EnsureProjectReunionFrameworkPackage