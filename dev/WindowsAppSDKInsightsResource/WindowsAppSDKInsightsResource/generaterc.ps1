param($packagever, $experimentationLevel)
$content = Get-Content -Path ".\resource.templ"
$content = $content -replace "%WINDOWSAPPSDK_PACKAGE_VER%",$packagever
$content = $content -replace "%WINDOWSAPPSDK_EXPERIMENTATION_LEVEL%", $experimentationLevel
$content | Set-Content ".\resource.rc"
