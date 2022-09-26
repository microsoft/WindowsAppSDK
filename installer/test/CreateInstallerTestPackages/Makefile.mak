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

TARGET_BASENAME=Microsoft.WindowsAppRuntime.Test.InstallFramework

TargetDir=$(OutDir)$(TargetName)
MSTestPfx=$(SolutionDir)..\..\..\temp\MSTest.pfx
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
Main_x86=$(InstallerPackagesDir)\main_x86.msix
Main_x64=$(InstallerPackagesDir)\main_x64.msix
Main_arm64=$(InstallerPackagesDir)\main_arm64.msix
Main_license=$(InstallerPackagesDir)\main_license.xml
Singleton_x86=$(InstallerPackagesDir)\singleton_x86.msix
Singleton_x64=$(InstallerPackagesDir)\singleton_x64.msix
Singleton_arm64=$(InstallerPackagesDir)\singleton_arm64.msix
Singleton_license=$(InstallerPackagesDir)\singleton_license.xml
DDLM_x86=$(InstallerPackagesDir)\ddlm_x86.msix
DDLM_x64=$(InstallerPackagesDir)\ddlm_x64.msix
DDLM_arm64=$(InstallerPackagesDir)\ddlm_arm64.msix

verifypfx:
    @if not exist $(MSTestPfx) echo Missing $(MSTestPfx), please run DevCheck.cmd to set up your developer environment. && exit /b 1

all: build

$(OutMsix_x86): $(ProjectDir)appxmanifest_fw_x86.xml
    @if not exist $(WorkDir_x86) md $(WorkDir_x86) >NUL
    @if not exist $(WorkDir_x86)\Assets md $(WorkDir_x86)\Assets >NUL
    @copy /Y $(ProjectDir)Assets\* $(WorkDir_x86)\Assets\* >NUL
    @copy /Y $(ProjectDir)appxmanifest_fw_x86.xml $(WorkDir_x86)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x86) /p $(OutMsix_x86)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x86)
    @if not exist $(InstallerPackagesDir) md $(InstallerPackagesDir)
    @copy /Y $(OutMsix_x86) $(Framework_x86) >NUL
    @copy /Y $(ProjectDir)appxmanifest_main_x86.xml $(WorkDir_x86)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x86) /p $(OutMsix_x86)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x86)
    @copy /Y $(OutMsix_x86) $(Main_x86) >NUL
    @copy /Y $(ProjectDir)main_license.xml $(Main_license) >NUL
    @copy /Y $(ProjectDir)appxmanifest_singleton_x86.xml $(WorkDir_x86)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x86) /p $(OutMsix_x86)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x86)
    @copy /Y $(OutMsix_x86) $(Singleton_x86) >NUL
    @copy /Y $(ProjectDir)singleton_license.xml $(Singleton_license) >NUL
    @copy /Y $(ProjectDir)appxmanifest_ddlm_x86.xml $(WorkDir_x86)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x86) /p $(OutMsix_x86)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x86)
    @copy /Y $(OutMsix_x86) $(DDLM_x86) >NUL

$(OutMsix_x64): $(ProjectDir)appxmanifest_fw_x64.xml
    @if not exist $(WorkDir_x64) md $(WorkDir_x64) >NUL
    @if not exist $(WorkDir_x64)\Assets md $(WorkDir_x64)\Assets >NUL
    @copy /Y $(ProjectDir)Assets\* $(WorkDir_x64)\Assets\* >NUL
    @copy /Y $(ProjectDir)appxmanifest_fw_x64.xml $(WorkDir_x64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x64) /p $(OutMsix_x64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x64)
    @if not exist $(InstallerPackagesDir) md $(InstallerPackagesDir)
    @copy /Y $(OutMsix_x64) $(Framework_x64) >NUL
    @copy /Y $(ProjectDir)appxmanifest_main_x64.xml $(WorkDir_x64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x64) /p $(OutMsix_x64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x64)
    @copy /Y $(OutMsix_x64) $(Main_x64) >NUL
    @copy /Y $(ProjectDir)main_license.xml $(Main_license) >NUL
    @copy /Y $(ProjectDir)appxmanifest_singleton_x64.xml $(WorkDir_x64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x64) /p $(OutMsix_x64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x64)
    @copy /Y $(OutMsix_x64) $(Singleton_x64) >NUL
    @copy /Y $(ProjectDir)singleton_license.xml $(Singleton_license) >NUL
    @copy /Y $(ProjectDir)appxmanifest_ddlm_x64.xml $(WorkDir_x64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_x64) /p $(OutMsix_x64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_x64)
    @copy /Y $(OutMsix_x64) $(DDLM_x64) >NUL

$(OutMsix_arm64): $(ProjectDir)appxmanifest_fw_arm64.xml
    @if not exist $(WorkDir_arm64) md $(WorkDir_arm64) >NUL
    @if not exist $(WorkDir_arm64)\Assets md $(WorkDir_arm64)\Assets >NUL
    @copy /Y $(ProjectDir)Assets\* $(WorkDir_arm64)\Assets\* >NUL
    @copy /Y $(ProjectDir)appxmanifest_fw_arm64.xml $(WorkDir_arm64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_arm64) /p $(OutMsix_arm64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_arm64)
    @if not exist $(InstallerPackagesDir) md $(InstallerPackagesDir)
    @copy /Y $(OutMsix_arm64) $(Framework_arm64) >NUL
    @copy /Y $(ProjectDir)appxmanifest_main_arm64.xml $(WorkDir_arm64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_arm64) /p $(OutMsix_arm64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_arm64)
    @copy /Y $(OutMsix_arm64) $(Main_arm64) >NUL
    @copy /Y $(ProjectDir)main_license.xml $(Main_license) >NUL
    @copy /Y $(ProjectDir)appxmanifest_singleton_arm64.xml $(WorkDir_arm64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_arm64) /p $(OutMsix_arm64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_arm64)
    @copy /Y $(OutMsix_arm64) $(Singleton_arm64) >NUL
    @copy /Y $(ProjectDir)singleton_license.xml $(Singleton_license) >NUL
    @copy /Y $(ProjectDir)appxmanifest_ddlm_arm64.xml $(WorkDir_arm64)\appxmanifest.xml >NUL
    @makeappx.exe pack $(MAKEAPPX_OPTS)/o /h SHA256 /d $(WorkDir_arm64) /p $(OutMsix_arm64)
    @signtool.exe sign /a $(SIGNTOOL_OPTS) /fd SHA256 /f $(MSTestPfx) $(OutMsix_arm64)
    @copy /Y $(OutMsix_arm64) $(DDLM_arm64) >NUL

clean:
    @if exist $(TargetDir) rd $(TargetDir) /s /q
    @if exist $(InstallerPackagesDir) rd $(InstallerPackagesDir) /s /q

build: verifypfx $(OutMsix_x86) $(OutMsix_x64) $(OutMsix_arm64)

rebuild: clean build
