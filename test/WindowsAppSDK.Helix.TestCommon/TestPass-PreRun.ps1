Write-Host "TestPass-PreRun.ps1"

# This script is run on the test machine for each work item that executes there.
# It runs just before executing the test.

# This script is called by TestPass-PreRunCore.ps1 which is a part of the WinUI.Helix package.

# Output all environment variables to the console log.
dir env:

# Setup TTD tracing only if the path to the Internal Partner Nuget exists in the Helix work item payload.
$ttd_path = Resolve-Path "Microsoft.Internal.TTD.Partner.*"

if ($ttd_path) {
    reg add HKCU\SOFTWARE\Microsoft\TTD /v "EULASigned" /t REG_DWORD /d 0x1 /f

    $out_path = $env:HELIX_WORKITEM_UPLOAD_ROOT
    
    # Notes: We need to use `Start-Process` instead of `&` as TTD doesn't return the cmd prompt once started.
    # All of the test machines are native amd64 (there is no native x86) so we directly invoke the amd64 version.
    # Note: There is no arm64 TTD. If/when we have arm64 test machines, this will need to be conditional on the machine's arch.
    Start-Process -FilePath "$ttd_path\amd64\TTD\tttracer.exe" -ArgumentList "-out $out_path -onLaunch te.processhost.exe" -RedirectStandardOutput "$out_path\ttt_console.out" -RedirectStandardError "$out_path\ttt_console.err"
}
