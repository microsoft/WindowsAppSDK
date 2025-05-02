@ECHO OFF
SETLOCAL

IF %PYTHON_EXE%x == x GOTO NoPythonExe

SET C=C:\Python313\python.exe -c


%C% "left=1     ; right=2     ; expected=1     ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=123   ; right=4567  ; expected=123   ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=1     ; right=-2    ; expected=1     ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-1    ; right=-2    ; expected=-1    ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-1    ; right=2     ; expected=-1    ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=1.2   ; right=3.45  ; expected=1.2   ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-1.2  ; right=3.45  ; expected=-1.2  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=1.2   ; right=-3.45 ; expected=1.2   ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-1.2  ; right=-3.45 ; expected=-1.2  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=.2    ; right=.45   ; expected=0.2   ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-.2   ; right=.45   ; expected=-0.2  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=.2    ; right=-.45  ; expected=0.2   ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-.2   ; right=-.45  ; expected=-0.2  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=2     ; right=1     ; expected=0     ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=4567  ; right=123   ; expected=16    ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=3.45  ; right=1.2   ; expected=1.05  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=2     ; right=-1    ; expected=0     ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-2    ; right=1     ; expected=0     ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-2    ; right=-1    ; expected=0     ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=3.45  ; right=-1.2  ; expected=1.05  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-3.45 ; right=1.2   ; expected=-1.05 ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-3.45 ; right=-1.2  ; expected=-1.05 ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=.45   ; right=.2    ; expected=0.05  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=.45   ; right=-.2   ; expected=0.05  ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-.45  ; right=.2    ; expected=-0.05 ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')
%C% "left=-.45  ; right=-.2   ; expected=-0.05 ; result=left %% right ; print(f'{left} %% {right} = {result}\t\t     ==> {result} == {expected}\n')

GOTO TheEnd

:NoPythonExe
ECHO ERROR PYTHON_EXE environment variable not set

:TheEnd
ENDLOCAL
