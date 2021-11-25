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

!IF "$(Platform)" == "Win32" || "$(Platform)" == "x86" || "$(Platform)" == "X86"
Architecture=x86
!ELSEIF "$(Platform)" == "x64" || "$(Platform)" == "X64"
Architecture=x64
!ELSEIF "$(Platform)" == "arm" || "$(Platform)" == "arm32" || "$(Platform)" == "ARM" || "$(Platform)" == "ARM32"
Architecture=arm
!ELSEIF "$(Platform)" == "arm64" ||  "$(Platform)" == "ARM64"
Architecture=arm64
!ELSE
!ERROR "Unknown platform $(Platform)"
!endif

TARGET_BASENAME=DynamicDependencyLifetimeManager

TARGET_EXE=$(TARGET_BASENAME)
TARGET_EXE_DIR=$(OutDir)$(TARGET_EXE)
TARGET_EXE_FILE=$(TARGET_EXE_DIR)\$(TARGET_EXE).exe

TARGET_PROXYSTUB=$(TARGET_BASENAME).ProxyStub
TARGET_PROXYSTUB_DIR=$(OutDir)$(TARGET_PROXYSTUB)
TARGET_PROXYSTUB_FILE=$(TARGET_PROXYSTUB_DIR)\$(TARGET_PROXYSTUB).dll
!IFDEF VERBOSE
!MESSAGE $(TARGET_PROXYSTUB_FILE)
!ENDIF

DDLM_SHADOW=DynamicDependencyLifetimeManagerShadow
DDLM_SHADOW_EXE=$(DDLM_SHADOW)
DDLM_SHADOW_EXE_DIR=$(OutDir)$(DDLM_SHADOW_EXE)
DDLM_SHADOW_EXE_FILE=$(DDLM_SHADOW_EXE_DIR)\$(DDLM_SHADOW_EXE).exe
DDLM_SHADOW_EXE_PDB=$(DDLM_SHADOW_EXE_DIR)\$(DDLM_SHADOW_EXE).pdb

VERSIONINFO_DIR=$(ProjectDir)
VERSIONINFO_FILE=$(VERSIONINFO_DIR)Microsoft.WindowsAppRuntime.Release!4.1.0

TargetDir=$(OutDir)$(TargetName)
WorkDir=$(TargetDir)\msix
OutMsix=$(TargetDir)\$(TargetName)

!IFDEF VERBOSE
!MESSAGE Workdir              =$(WorkDir)
!MESSAGE OutMsix              =$(OutMsix)
!MESSAGE DDLM_SHADOW_EXE_FILE =$(DDLM_SHADOW_EXE_FILE)
!MESSAGE DDLM_SHADOW_EXE_PDB  =$(DDLM_SHADOW_EXE_PDB)
!ENDIF

MAKE_APPXMANIFEST_FROM_TEMPLATE=$(SolutionDir)tools\MakeAppxManifestFromTemplate.cmd

all: build

$(OutMsix): $(ProjectDir)appxmanifest.xml
    @if not exist $(WorkDir) md $(WorkDir)
    REM @copy /Y $(ProjectDir)appxmanifest.xml $(WorkDir)\appxmanifest.xml
    @call $(MAKE_APPXMANIFEST_FROM_TEMPLATE) $(ProjectDir)appxmanifest.xml $(WorkDir)\appxmanifest.xml $(Architecture)
    @if not exist $(WorkDir)\Assets md $(WorkDir)\Assets >NUL
    @copy /Y $(ProjectDir)Assets\* $(WorkDir)\Assets\* >NUL
    @copy /Y $(TARGET_EXE_FILE) $(WorkDir) >NUL
    @copy /Y $(TARGET_PROXYSTUB_FILE) $(WorkDir) >NUL
    @copy /Y $(DDLM_SHADOW_EXE_FILE) $(WorkDir) >NUL
    @copy /Y $(DDLM_SHADOW_EXE_PDB) $(WorkDir) >NUL
    @copy /Y $(VERSIONINFO_FILE) $(WorkDir) >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS) /o /h SHA256 /d $(WorkDir) /p $(OutMsix)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(SolutionDir).user\winappsdk.certificate.test.pfx $(OutMsix)

build: $(OutMsix)

clean:
    @if exist $(WorkDir) rd $(WorkDir) /s /q
    @if exist $(OutMsix) del $(OutMsix)
    @if exist $(TARGET_BASENAME).*.msix del $(TARGET_BASENAME).*.msix

rebuild: clean build
