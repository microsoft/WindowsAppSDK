# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.

#!include <WindowsAppRuntime.Tools.MakeMsix.mak>

MAKEAPPX_OPTS=
!IFDEF VERBOSE
MAKEAPPX_OPTS=/v
!ENDIF

SIGNTOOL_OPTS=
!IFDEF VERBOSE
SIGNTOOL_OPTS=/v
!ENDIF

!IFDEF VERBOSE
!MESSAGE SolutionDir                     =$(SolutionDir)
!MESSAGE ProjectDir                      =$(ProjectDir)
!MESSAGE OutDir                          =$(OutDir)
!MESSAGE TargetName                      =$(TargetName)
!MESSAGE WindowsAppRuntimeBuildPipeline  =$(WindowsAppRuntimeBuildPipeline)
!ENDIF

TARGET_BASENAME=PushNotificationsLongRunningTask

TARGET_EXE=$(TARGET_BASENAME)
TARGET_EXE_DIR=$(OutDir)$(TARGET_EXE)
TARGET_EXE_FILE=$(TARGET_EXE_DIR)\$(TARGET_EXE).exe

TARGET_STARTUPEXE=$(TARGET_BASENAME).StartupTask
TARGET_STARTUPEXE_DIR=$(OutDir)$(TARGET_STARTUPEXE)
TARGET_STARTUPEXE_FILE=$(TARGET_STARTUPEXE_DIR)\$(TARGET_STARTUPEXE).exe

TARGET_PROXYSTUB=PushNotificationsLongRunningTask.ProxyStub
TARGET_PROXYSTUB_DIR=$(OutDir)$(TARGET_PROXYSTUB)
TARGET_PROXYSTUB_FILE=$(TARGET_PROXYSTUB_DIR)\$(TARGET_PROXYSTUB).dll
!IFDEF VERBOSE
!MESSAGE $(TARGET_PROXYSTUB_FILE)
!ENDIF

TargetDir=$(OutDir)$(TargetName)
WorkDir=$(TargetDir)\msix
OutMsix=$(TargetDir)\$(TargetName)

!IFDEF VERBOSE
!MESSAGE Workdir           =$(WorkDir)
!MESSAGE OutMsix           =$(OutMsix)
!ENDIF

all: build

$(OutMsix): $(ProjectDir)appxmanifest.xml
    @if not exist $(WorkDir) md $(WorkDir)
    @copy /Y $(ProjectDir)appxmanifest.xml $(WorkDir)\appxmanifest.xml
    @copy /Y $(OutDir)WindowsAppRuntime_DLL\Microsoft.Internal.FrameworkUdk.dll $(WorkDir)\Microsoft.Internal.FrameworkUdk.dll
    @if not exist $(WorkDir)\Assets md $(WorkDir)\Assets >NUL
    @copy /Y $(ProjectDir)Assets\* $(WorkDir)\Assets\* >NUL
    @copy /Y $(TARGET_EXE_FILE) $(WorkDir) >NUL
    @copy /Y $(TARGET_STARTUPEXE_FILE) $(WorkDir) >NUL
    @copy /Y $(TARGET_PROXYSTUB_FILE) $(WorkDir) >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS) /o /h SHA256 /d $(WorkDir) /p $(OutMsix)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(SolutionDir)temp\MSTest.pfx $(OutMsix)

build: $(OutMsix)

clean:
    @if exist $(WorkDir) rd $(WorkDir) /s /q
    @if exist $(OutMsix) del $(OutMsix)
    @if exist $(TARGET_BASENAME).*.msix del $(TARGET_BASENAME).*.msix

rebuild: clean build
