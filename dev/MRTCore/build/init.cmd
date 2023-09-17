@echo off
set RepoRoot=%~dp0
rem Remove the trailing backslash
set RepoRoot=%RepoRoot:~0,-1%
set EnvOnly=
set Verbose=

rem In case we run init.cmd multiple times, we don't want to keep our additions to PATH around.
rem We'll save the original value of PATH and restore it on future calls to init.cmd.
rem Given that PATH can get super long, we'll split this into multiple statements since having both "set"
rem statements on the same line can cause cmd to complain the command is too large.
if "%_OriginalPathBeforeInit%" neq "" goto :OriginalPathSet
set _OriginalPathBeforeInit=%PATH%
goto :DoneSettingPath
:OriginalPathSet
set PATH=%_OriginalPathBeforeInit%
:DoneSettingPath

set x86=
set amd64=
set fre=
set chk=
set _BuildArch=
set _BuildType=

rem Defaults
set _archIsSet=

:parseArgs
if /i "%1"=="" (
    goto:doneParsingArgs
) else if /i "%1"=="/envonly" (
    set EnvOnly=true
) else if /i "%1"=="/verbose" (
    set Verbose=-Verbosity normal
) else if /i "%1"=="x86chk" (
    set x86=1
    set chk=1
    set _archIsSet=1
) else if /i "%1"=="x86fre" (
    set x86=1
    set fre=1
    set _archIsSet=1
rem The caller has a code path that leaves a '\' in the input string in case of fre, cope with that. Similar below.
rem We now echo the input string if it's found to be invalid.
) else if /i "%1"=="x86\fre" (
    set x86=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="x64fre" (
    set amd64=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="x64\fre" (
    set amd64=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="x64chk" (
    set amd64=1
    set chk=1
    set _archIsSet=1
) else if /i "%1"=="amd64fre" (
    set amd64=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="amd64\fre" (
    set amd64=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="amd64chk" (
    set amd64=1
    set chk=1
    set _archIsSet=1
)  else if /i "%1"=="armfre" (
    set arm=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="arm\fre" (
    set arm=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="armchk" (
    set arm=1
    set chk=1
    set _archIsSet=1
) else if /i "%1"=="arm64fre" (
    set arm64=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="arm64\fre" (
    set arm64=1
    set fre=1
    set _archIsSet=1
) else if /i "%1"=="arm64chk" (
    set arm64=1
    set chk=1
    set _archIsSet=1
) else (
    echo Syntax:    %0 ^<arch^>^<flavor^> [^<toolset^>]
    echo.
    echo            ^<arch^> :          x86 ^| ^(x64^|amd64^) ^| arm ^| arm64
    echo            ^<flavor^> :        chk ^| fre
    echo.
    echo Invalid: %1.
    exit /b 1
)
shift
goto:parseArgs

:doneParsingArgs
if "%_archIsSet%"=="" (
    set x86=1
    set chk=1
)
set _archIsSet=

if "%x86%"=="1" (set _BuildArch=x86&&set Platform=Win32)
if "%amd64%"=="1" (set _BuildArch=amd64&&set Platform=x64)
if "%arm%"=="1" (set _BuildArch=arm&&set Platform=arm)
if "%arm64%"=="1" (set _BuildArch=arm64&&set Platform=arm64)

set BUILDPLATFORM=%Platform%
if "%x86%"=="1" (set BUILDPLATFORM=x86)

rem Unsure if this is needed
rem if "%arm%"=="1" set ARM_WORKAROUND=1
rem if "%arm64%"=="1" set ARM64_WORKAROUND=1

if "%fre%"=="1" (set _BuildType=fre&&set Configuration=Release)
if "%chk%"=="1" (set _BuildType=chk&&set Configuration=Debug)

if "%DevEnvDir%" == "" (
    echo DevEnvDir environment variable not set. Running DevCmd.cmd to get a developer command prompt...
    call %RepoRoot%\DevCmd.cmd /PreserveContext /prerelease -arch=%_BuildArch% -host_arch=amd64
    if errorlevel 1 (echo Could not set up a developer command prompt && exit /b %ERRORLEVEL%)
)
echo DevCmd.cmd succeeded.

set _subfolder=\

call:AddPathIfExists "%VSINSTALLDIR%\MSBuild\Current\Bin%_subfolder%"
echo AddPathIfExists returned %ERRORLEVEL%

set PATH=%RepoRoot%\.buildtools\MSBuild\Current\Bin;%RepoRoot%\.tools;%RepoRoot%\.tools\VSS.NuGet.AuthHelper;%RepoRoot%\tools;%RepoRoot%\dxaml\scripts;%PATH%

set BuildArtifactsDir=%RepoRoot%\BuildOutput

set BinRoot=%BuildArtifactsDir%\Bin
set BuildOutputRoot=%BuildArtifactsDir%\Obj
set TEMP=%BuildArtifactsDir%\Temp\%_BuildArch%%_BuildType%
set TMP=%TEMP%

if not exist %TEMP% mkdir %TEMP%

rem call %RepoRoot%\scripts\init\SetDotnetVars.cmd %RepoRoot%

if "%EnvOnly%"=="" (
    echo EnvOnly variable NOT set, running init.ps1.
    powershell -ExecutionPolicy Bypass -NoProfile -Command %RepoRoot%\init.ps1
) else (
    echo EnvOnly variable IS set, skipped init.ps1.
)

set EnvironmentInitialized=1

title DCPP %_BuildArch%%_BuildType% 2019
rem doskey /macrofile=%RepoRoot%\scripts\aliases
echo ERROR: title DCPP returned %ERRORLEVEL%
goto:eof


:AddPathIfExists
rem Remove quotes we used above
set _ToAdd=%1
set _subfolder=
if not exist %_ToAdd%  (
    goto:PathNotFound %1
)
set PATH=%_ToAdd:~1,-1%;%PATH%
set _ToAdd=
exit /b 0

:PathNotFound
set _A=%1
echo Could not find path: %_A:~1,-1%
set _A=
exit /b 4
