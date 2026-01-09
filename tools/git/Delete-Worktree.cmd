@echo off
REM Delete-Worktree.cmd - Wrapper for Delete-Worktree.ps1
REM Usage: Delete-Worktree.cmd -Pattern <pattern> [-Force] [-KeepBranch] [-KeepRemote]
powershell -ExecutionPolicy Bypass -File "%~dp0Delete-Worktree.ps1" %*
