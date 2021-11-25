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
!MESSAGE SolutionDir                =$(SolutionDir)
!MESSAGE ProjectDir                 =$(ProjectDir)
!MESSAGE OutDir                     =$(OutDir)
!MESSAGE TargetName                 =$(TargetName)
!MESSAGE WindowsAppSdkBuildPipeline =$(WindowsAppSdkBuildPipeline)
!ENDIF

TARGET_BASENAME=Microsoft.WindowsAppRuntime.Test.Main

TargetDir=$(OutDir)$(TargetName)
WorkDir=$(TargetDir)\msix
OutMsix=$(TargetDir)\$(TargetName).msix

!IFDEF VERBOSE
!MESSAGE Workdir           =$(WorkDir)
!MESSAGE OutMsix           =$(OutMsix)
!ENDIF

all: build

$(OutMsix): $(ProjectDir)appxmanifest.xml
    @if not exist $(WorkDir) md $(WorkDir)
    @copy /Y $(ProjectDir)appxmanifest.xml $(WorkDir)\appxmanifest.xml
    @if not exist $(WorkDir)\Assets md $(WorkDir)\Assets >NUL
    @copy /Y $(ProjectDir)Assets\* $(WorkDir)\Assets\* >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS) /o /h SHA256 /d $(WorkDir) /p $(OutMsix)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(SolutionDir).user\winappsdk.certificate.test.pfx $(OutMsix)

build: $(OutMsix)

clean:
    @if exist $(WorkDir) rd $(WorkDir) /s /q
    @if exist $(OutMsix) del $(OutMsix)
    @if exist $(TARGET_BASENAME).*.msix del $(TARGET_BASENAME).*.msix

rebuild: clean build
