# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.

#!include <WindowsAppSDK.Tools.MakeMsix.mak>

MAKEAPPX_OPTS=
!IFDEF VERBOSE
MAKEAPPX_OPTS=/v
!ENDIF

SIGNTOOL_OPTS=
!IFDEF VERBOSE
SIGNTOOL_OPTS=/v
!ENDIF

!IFDEF VERBOSE
!MESSAGE SolutionDir       =$(SolutionDir)
!MESSAGE ProjectDir        =$(ProjectDir)
!MESSAGE OutDir            =$(OutDir)
!MESSAGE TargetName        =$(TargetName)
!ENDIF

TARGET_BASENAME=Microsoft.WindowsAppRuntime.Framework

TargetDir=$(OutDir)$(TargetName)
WorkDir=$(TargetDir)\msix
OutMsix=$(TargetDir)\$(TargetName).msix

!IFDEF VERBOSE
!MESSAGE Workdir           =$(WorkDir)
!MESSAGE OutMsix           =$(OutMsix)
!ENDIF

all: build

$(OutMsix): $(ProjectDir)appxmanifest.xml
    @if not exist $(WorkDir) md $(WorkDir) >NUL
    @copy /Y $(ProjectDir)appxmanifest.xml $(WorkDir)\appxmanifest.xml >NUL
    @copy /Y $(ProjectDir)logo.png $(WorkDir)\logo.png >NUL
    @copy /Y $(OutDir)WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.dll $(WorkDir)\Microsoft.WindowsAppRuntime.dll
    @copy /Y $(OutDir)WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.pdb $(WorkDir)\Microsoft.WindowsAppRuntime.pdb
    @copy /Y $(OutDir)WindowsAppRuntime_DLL\Microsoft.Internal.FrameworkUdk.dll $(WorkDir)\Microsoft.Internal.FrameworkUdk.dll
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir) /p $(OutMsix)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(SolutionDir)temp\MSTest.pfx $(OutMsix)

build: $(OutMsix)

clean:
    @if exist $(WorkDir) rd $(WorkDir) /s /q
    @if exist $(OutMsix) del $(OutMsix)

rebuild: clean build
