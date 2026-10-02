@echo OFF

pushd %~dp0

PATH %PATH%;%~dp0\tools
set PrereleaseArg=

setlocal enableextensions enabledelayedexpansion
set _ARGS=
rem Try to fall back to the original value, 2019, if the value 2022 run into issues.
set VsVersion=2022
if exist %temp%\WinUI.PreserveContext.marker del %temp%\WinUI.PreserveContext.marker
:ParseArgs
if "%1" EQU "" (
    goto :DoneParsing
) else if /i "%1" EQU "/PreserveContext" (
    echo. > %temp%\WinUI.PreserveContext.marker
) else if /i "%1" EQU "/Prerelease" (
    set PrereleaseArg=-prerelease
) else (
    set _ARGS=%_ARGS% %1=%2
    shift
)
shift
goto ParseArgs

:DoneParsing
set vswhere="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist %vswhere% (echo VSWhere.exe not found. Install MSBuild first from OneTimeSetup.cmd && exit /b 1)
echo %_ARGS% > %temp%\WinUI.args

rem Try MSBuild first
%vswhere% -products Microsoft.VisualStudio.Product.BuildTools -property InstallationPath %PrereleaseArg% -latest | findstr %VsVersion% > %TEMP%\vsinstalldir.txt
set /p MSBuildInstallPath=<%temp%\vsinstalldir.txt
if "%MSBuildInstallPath%" NEQ "" (goto:found)
rem We didn't find MSBuild, try a full VSexit
%vswhere% -requires Microsoft.Component.MSBuild -property InstallationPath %PrereleaseArg% -latest | findstr %VsVersion% > %TEMP%\vsinstalldir.txt
set /p _success=<%TEMP%\vsinstalldir.txt
if "%_success%" EQU "" (
    echo Could not find an MSBuild install, exiting
    if defined AGENT_NAME (
        call:PrintVsWhere
    )
    exit /b 2
)

:found
echo %VsVersion%> %Temp%\VsVersion.args
endlocal
set /p VsVersion=<%Temp%\VsVersion.args
del %Temp%\VsVersion.args
set /p _VSINSTALLDIR=<%TEMP%\vsinstalldir.txt

if "%_VSINSTALLDIR%"=="" (
    echo Could not find VS or MSBuild, exiting.
    exit /b 2
)

if %ERRORLEVEL% GEQ 1 (exit /b %ERRORLEVEL%)

set /p _ARGS=<%temp%\WinUI.args

call "%_VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" /no_logo %_ARGS%

if not exist %temp%\WinUI.PreserveContext.marker (
    echo Starting cmd /k
    cmd /k "cd /d %RepoRoot%"
)

if exist %temp%\WinUI.PreserveContext.marker (del %temp%\WinUI.PreserveContext.marker)
if exist %temp%\WinUI.args (del %temp%\WinUI.args)

goto:eof

:PrintVsWhere
echo on
%vswhere% -products Microsoft.VisualStudio.Product.BuildTools -property InstallationPath
%vswhere% -requires Microsoft.Component.MSBuild -property InstallationPath
@echo off
exit /b
