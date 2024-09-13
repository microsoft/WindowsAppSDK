@echo off

nuget.exe install Microsoft.WinAppSDK.DevCheck -Source https://microsoft.pkgs.visualstudio.com/ProjectReunion/_packaging/Project.Reunion.nuget.internal/nuget/v3/index.json

set search_pattern=DevCheck.ps1
set search_dir=%~dp0\packages
set devcheck_file=
for /f "delims=" %%f in ('where /r %search_dir% %search_pattern%') do (
    rem Perform actions on each file
    set devcheck_file=%%f
)

if "%devcheck_file%"=="" (
    echo No DevCheck.ps1 file found.
    exit /b 1
)

echo Using %devcheck_file%

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %devcheck_file% %*

exit /b %ERRORLEVEL%