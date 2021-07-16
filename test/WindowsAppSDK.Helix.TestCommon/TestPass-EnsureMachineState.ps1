Write-Host "TestPass-EnsureMachineState.ps1"

# This script is run on the test machine before executing the tests. 
# In the cases of failing tests getting re-run, this script is also run before the retries.

# This script is called by TestPass-EnsureMachineStateCore.ps1 which is a part of the WinUI.Helix package.

# It is a good place to add any code that ensures the machine is in a good state to run the tests.
# For example, if you know of a Windows process that might interfere with your tests, here is a good place
# to end that process.