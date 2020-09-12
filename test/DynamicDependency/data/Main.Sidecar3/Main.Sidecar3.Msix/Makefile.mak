# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.

#TARGET=$(TargetName).msix
#ASSETS=

#!include <ProjectReunion.Tools.MakeMsix.mak>

WorkDir=$(OutDir)msix\
OutMsix=$(OutDir)$(TargetName).msix

all: build

build:
    @ECHO SolutionDir       =$(SolutionDir)
    @ECHO ProjectDir        =$(ProjectDir)
    @ECHO OutDir            =$(OutDir)
    @ECHO TargetDir         =$(TargetDir)
    @ECHO TargetFileName    =$(TargetFileName)
    @ECHO TargetName        =$(TargetName)
    @ECHO Workdir           =$(WorkDir)
    @ECHO OutMsix           =$(OutMsix)
    @ECHO $@                =$@
    @ECHO $$@               =$$@
    @ECHO $*                =$*
    @ECHO $**               =$**
    @ECHO $?                =$?
    @ECHO $<                =$<
    if not exist $(WorkDir) md $(WorkDir)
    REM copy $(ProjectDir)appxmanifest.template $(WorkDir)appxmanifest.xml
    REM if exist $(ProjectDir)logo.png copy $(ProjectDir)logo.png $(WorkDir)logo.png
    REM if exist $(ProjectDir)Assets md $(WorkDir)Assets
    REM if exist $(ProjectDir)Assets\* copy $(ProjectDir)Assets\* $(WorkDir)Assets\*
    REM copy $(TargetDir)$(TargetFileName) $(WorkDir)$(TargetFileName)
    REM makeappx.exe pack /v /o /h SHA256 /d $(WorkDir) /p $(OutMsix)
    REM signtool.exe sign /a /v /fd SHA256 /f $(SolutionDir)build\MSTest.pfx $(OutMsix)

clean:
    if exist $(WorkDir) rd $(WorkDir) /s /q

rebuild: clean build
