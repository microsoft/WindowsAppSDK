# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.

#!include <ProjectReunion.Tools.MakeMsix.mak>

!MESSAGE SolutionDir       =$(SolutionDir)
!MESSAGE ProjectDir        =$(ProjectDir)
!MESSAGE OutDir            =$(OutDir)
!MESSAGE TargetName        =$(TargetName)

TARGET_BASENAME=Main.Sidecar

TARGET_EXE=$(TARGET_BASENAME).LifetimeManager
TARGET_EXE_DIR=$(OutDir)$(TARGET_EXE)
TARGET_EXE_FILE=$(TARGET_EXE_DIR)\$(TARGET_EXE).exe

TARGET_PROXYSTUB=$(TARGET_BASENAME).LifetimeManager.ProxyStub
TARGET_PROXYSTUB_DIR=$(OutDir)$(TARGET_PROXYSTUB)
TARGET_PROXYSTUB_FILE=$(TARGET_PROXYSTUB_DIR)\$(TARGET_PROXYSTUB).dll
!MESSAGE $(TARGET_PROXYSTUB_FILE)

TargetDir=$(OutDir)$(TargetName)
WorkDir=$(TargetDir)\msix
OutMsix=$(TargetDir)\$(TargetName)

!MESSAGE Workdir           =$(WorkDir)
!MESSAGE OutMsix           =$(OutMsix)

all: build

build:
    if not exist $(WorkDir) md $(WorkDir)
    copy /Y $(ProjectDir)appxmanifest.xml $(WorkDir)\appxmanifest.xml
    if not exist $(WorkDir)\Assets md $(WorkDir)\Assets
    copy /Y $(ProjectDir)Assets\* $(WorkDir)\Assets\*
    copy /Y $(TARGET_EXE_FILE) $(WorkDir)
    copy /Y $(TARGET_PROXYSTUB_FILE) $(WorkDir)
    makeappx.exe pack /v /o /h SHA256 /d $(WorkDir) /p $(OutMsix)
    signtool.exe sign /a /v /fd SHA256 /f $(SolutionDir)build\MSTest.pfx $(OutMsix)

clean:
    if exist $(WorkDir) rd $(WorkDir) /s /q
    if exist $(OutMsix) del $(OutMsix)

$(OutMsix): $(ProjectDir)appxmanifest.xml

rebuild: clean build
