Write-Host "TestPass-PostRun.ps1"

# This script is run on the test machine for each work item that executes there.
# It runs after executing the tests.

# This script is called by TestPass-PostRunCore.ps1 which is a part of the WinUI.Helix package.

# Kill any running tttracer processes
$traceProcessNames = @(
    "tttracer")

foreach($processName in $traceProcessNames)
{
    $procs = Get-Process -Name $processName -ErrorAction SilentlyContinue
    foreach($proc in $procs) 
    { 
        Write-Host "Found running proc: $($proc.Name) - $($proc.Id)" 
        Write-Host "Killing Process" 
        Stop-Process $proc -Force
    }
}