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

OutHeader=$(OutDir)$(TargetName)\IPurojekutoTenpuret.h

all: build

$(OutHeader): $(ProjectDir)IPurojekutoTenpuret.idl
    @if not exist $(IntDir) md $(IntDir)
    midl.exe /env $(ENV) /out $(IntDir) /h "IPurojekutoTenpuret.h" /W1 /char signed /target "NT60" /notlb /nologo /dlldata "dlldata.c" "$(ProjectDir)IPurojekutoTenpuret.idl"
    @copy $(IntDir)IPurojekutoTenpuret.h $(OutDir)$(TargetName)\IPurojekutoTenpuret.h
    @copy $(ProjectDir)IPurojekutoTenpuret.idl $(OutDir)$(TargetName)\IPurojekutoTenpuret.idl

build: $(OutHeader)

clean:
    @if exist $(IntDir)dlldata.c del $(IntDir)dlldata.c /q
    @if exist $(IntDir)IPurojekutoTenpuret_p.c del $(IntDir)IPurojekutoTenpuret_p.c /q
    @if exist $(IntDir)IPurojekutoTenpuret.h del $(IntDir)IPurojekutoTenpuret.h /q
    @if exist $(OutDir)$(TargetName)\IPurojekutoTenpuret.h del $(OutDir)$(TargetName)\IPurojekutoTenpuret.h /q

rebuild: clean build
