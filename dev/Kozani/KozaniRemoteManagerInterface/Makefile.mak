# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.

!IFDEF VERBOSE
!MESSAGE SolutionDir       =$(SolutionDir)
!MESSAGE ProjectDir        =$(ProjectDir)
!MESSAGE IntDir            =$(IntDir)
!MESSAGE OutDir            =$(OutDir)
!MESSAGE TargetName        =$(TargetName)
!MESSAGE Configuration     =$(Configuration)
!MESSAGE Platform          =$(Platform)
!ENDIF

!IF "$(Platform)" == "Win32" || "$(Platform)" == "x86" || "$(Platform)" == "X86"
ENV=win32
!ELSEIF "$(Platform)" == "x64" || "$(Platform)" == "X64"
ENV=x64
!ELSEIF "$(Platform)" == "arm" || "$(Platform)" == "arm32" || "$(Platform)" == "ARM" || "$(Platform)" == "ARM32"
ENV=arm32
!ELSEIF "$(Platform)" == "arm64" ||  "$(Platform)" == "ARM64"
ENV=arm64
!ELSE
!ERROR "Unknown platform $(Platform)"
!endif

OutHeader=$(OutDir)$(TargetName)\KozaniRemoteManagerInterface.h

all: build

$(OutHeader): $(ProjectDir)KozaniRemoteManagerInterface.idl
    @if not exist $(IntDir) md $(IntDir)
    midl.exe /env $(ENV) /out $(IntDir) /h "KozaniRemoteManagerInterface.h" /W1 /char signed /target "NT60" /notlb /nologo /dlldata "dlldata.c" "$(ProjectDir)KozaniRemoteManagerInterface.idl"
    @copy $(IntDir)KozaniRemoteManagerInterface.h $(OutDir)$(TargetName)\KozaniRemoteManagerInterface.h
    @copy $(ProjectDir)KozaniRemoteManagerInterface.idl $(OutDir)$(TargetName)\KozaniRemoteManagerInterface.idl

build: $(OutHeader)

clean:
    @if exist $(IntDir)dlldata.c del $(IntDir)dlldata.c /q
    @if exist $(IntDir)KozaniRemoteManagerInterface_p.c del $(IntDir)KozaniRemoteManagerInterface_p.c /q
    @if exist $(IntDir)KozaniRemoteManagerInterface.h del $(IntDir)KozaniRemoteManagerInterface.h /q
    @if exist $(OutDir)$(TargetName)\KozaniRemoteManagerInterface.h del $(OutDir)$(TargetName)\KozaniRemoteManagerInterface.h /q

rebuild: clean build
