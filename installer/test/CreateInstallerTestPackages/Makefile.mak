# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.

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

TARGET_BASENAME=Microsoft.ProjectReunion.Test.InstallerFramework

TargetDir=$(OutDir)$(TargetName)
MSTestCert=$(SolutionDir)..\..\build\MSTest.pfx
InstallerPackagesDir=$(SolutionDir)\..\testpackages
WorkDir_x86=$(TargetDir)\msix_x86
WorkDir_x64=$(TargetDir)\msix_x64
WorkDir_arm64=$(TargetDir)\msix_arm64
OutMsix_x86=$(TargetDir)\$(TargetName)_x86.msix
OutMsix_x64=$(TargetDir)\$(TargetName)_x64.msix
OutMsix_arm64=$(TargetDir)\$(TargetName)_arm64.msix
Framework_x86=$(InstallerPackagesDir)\framework_x86.msix
Framework_x64=$(InstallerPackagesDir)\framework_x64.msix
Framework_arm64=$(InstallerPackagesDir)\framework_arm64.msix

all: build

$(OutMsix_x86): $(ProjectDir)appxmanifest_x86.xml
    @if not exist $(WorkDir_x86) md $(WorkDir_x86) >NUL
    @copy /Y $(ProjectDir)appxmanifest_x86.xml $(WorkDir_x86)\appxmanifest.xml >NUL
    @copy /Y $(ProjectDir)logo.png $(WorkDir_x86)\logo.png >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x86) /p $(OutMsix_x86)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestCert) $(OutMsix_x86)
    @if not exist $(InstallerPackagesDir) md $(InstallerPackagesDir)
    @copy /Y $(OutMsix_x86) $(Framework_x86) >NUL

$(OutMsix_x64): $(ProjectDir)appxmanifest_x64.xml
    @if not exist $(WorkDir_x64) md $(WorkDir_x64) >NUL
    @copy /Y $(ProjectDir)appxmanifest_x64.xml $(WorkDir_x64)\appxmanifest.xml >NUL
    @copy /Y $(ProjectDir)logo.png $(WorkDir_x64)\logo.png >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x64) /p $(OutMsix_x64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestCert) $(OutMsix_x64)
    @if not exist $(InstallerPackagesDir) md $(InstallerPackagesDir)
    @copy /Y $(OutMsix_x64) $(Framework_x64) >NUL

$(OutMsix_arm64): $(ProjectDir)appxmanifest_arm64.xml
    @if not exist $(WorkDir_arm64) md $(WorkDir_arm64) >NUL
    @copy /Y $(ProjectDir)appxmanifest_arm64.xml $(WorkDir_arm64)\appxmanifest.xml >NUL
    @copy /Y $(ProjectDir)logo.png $(WorkDir_arm64)\logo.png >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_arm64) /p $(OutMsix_arm64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestCert) $(OutMsix_arm64)
    @if not exist $(InstallerPackagesDir) md $(InstallerPackagesDir)
    @copy /Y $(OutMsix_arm64) $(Framework_arm64) >NUL


build: $(OutMsix_x86) $(OutMsix_x64) $(OutMsix_arm64)

clean:
    @if exist $(TargetDir) rd $(TargetDir) /s /q
    @if exist $(InstallerPackagesDir) rd $(InstallerPackagesDir) /s /q

rebuild: clean build