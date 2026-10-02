@ECHO OFF
SETLOCAL

IF %1x == x GOTO Help
IF %1x == --helpx GOTO Help
IF %1x == -?x GOTO Help
IF %1x == /?x GOTO Help
IF %2x == x GOTO Help
IF %3x == x GOTO Help
SET _KEEP=0
IF %4x == KEEPx SET _KEEP=1
IF %4x == keepx SET _KEEP=1

SET _VCPKGDIR=%1
SET _FROM=%_VCPKGDIR%\installed

SET _WORKDIR=%2
SET _TO=%_WORKDIR%\temp

SET _VERSION=%3

:GetNuget
ECHO Getting nuget.exe...
curl --get --location --progress-bar --output %_WORKDIR%\nuget.exe https://dist.nuget.org/win-x86-commandline/v6.4.0/nuget.exe
SET _NUGET=%_WORKDIR%\nuget.exe

:CopyFiles
IF EXIST %_TO% rd /s/q %_TO%
md %_TO%

ECHO Building nuget's \build...
md %_TO%\build\native >NUL
copy %~dp0\*.props %_TO%\build\native\* >NUL
copy %~dp0\*.targets %_TO%\build\native\* >NUL

ECHO Building nuget's \include...
REM Include files are the same regardless of architecture
md %_TO%\include >NUL
XCOPY %_FROM%\x64-windows-static\include\* %_TO%\include\* /S >NUL

ECHO Building nuget's \lib...
md %_TO%\lib >NUL
md %_TO%\lib\win10-arm64 >NUL
XCOPY %_FROM%\arm64-windows-static\lib\libprotobuf.lib %_TO%\lib\win10-arm64\* >NUL
md %_TO%\lib\win10-x64 >NUL
XCOPY %_FROM%\x64-windows-static\lib\libprotobuf.lib %_TO%\lib\win10-x64\* >NUL
md %_TO%\lib\win10-x86 >NUL
XCOPY %_FROM%\x86-windows-static\lib\libprotobuf.lib %_TO%\lib\win10-x86\* >NUL

ECHO Building nuget's share\...
REM Share files are the same regardless of architecture
md %_TO%\share >NUL
XCOPY %_FROM%\x64-windows-static\share\protobuf\copyright %_TO%\share\* >NUL
XCOPY %_FROM%\x64-windows-static\share\protobuf\vcpkg.spdx.json %_TO%\share\* >NUL
XCOPY %_FROM%\x64-windows-static\share\protobuf\vcpkg_abi_info.txt %_TO%\share\* >NUL

ECHO Building nuget's tools\...
md %_TO%\tools >NUL
md %_TO%\tools\arm64 >NUL
XCOPY %_FROM%\arm64-windows-static\tools\protobuf\* %_TO%\tools\arm64\* >NUL
md %_TO%\tools\x64 >NUL
XCOPY %_FROM%\x64-windows-static\tools\protobuf\* %_TO%\tools\x64\* >NUL
md %_TO%\tools\x86 >NUL
XCOPY %_FROM%\x86-windows-static\tools\protobuf\* %_TO%\tools\x86\* >NUL

copy %_FROM%\x64-windows-static\share\protobuf\copyright %_TO%\LICENSE >NUL
SET _NUGETARGS=%~dp0\Microsoft.WindowsAppSDK.Protobuf.nuspec -Version %_VERSION% -BasePath %_TO%
ECHO %_NUGET% pack %_NUGETARGS%
%_NUGET% pack %_NUGETARGS%

GOTO Cleanup

:Cleanup
IF %_KEEP% == 1 GOTO PostCleanup
ECHO Cleaning up...
del /q %_NUGET%
rd /s/q %_TO%
:PostCleanup
GOTO TheEnd

:Help
ECHO Protobuf-Nuget vcpkgpath version outdir [KEEP]
ECHO where
ECHO   vcpkgpath = Path to VCPKG repository
ECHO      outdir = Output directory
ECHO     version = Version of the nuget package
ECHO        KEEP = Keep intermediary artifacts (optional)
GOTO TheEnd

:TheEnd
ENDLOCAL
