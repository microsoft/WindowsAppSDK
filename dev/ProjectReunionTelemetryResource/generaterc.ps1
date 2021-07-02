param($packagever, $experimentationLevel)
$content = Get-Content -Path ".\resource.templ"
$content = $content -replace "%REUNION_PACKAGE_VER%",$packagever
$content = $content -replace "%REUNION_EXPERIMENTATION_LEVEL%", $experimentationLevel
$content | Set-Content ".\resource.rc"
