@echo off
REM worktree-helper.cmd - Unified Git worktree management helper
REM Usage: worktree-helper.cmd <action> [options]
REM Actions: list, new-branch, new-issue, delete, help
REM
REM Examples:
REM   worktree-helper.cmd list
REM   worktree-helper.cmd new-branch -Branch feature/login
REM   worktree-helper.cmd new-issue -Number 1234 -Title "Fix crash"
REM   worktree-helper.cmd delete -Pattern feature/login -Force

powershell -ExecutionPolicy Bypass -File "%~dp0worktree-helper.ps1" %*
