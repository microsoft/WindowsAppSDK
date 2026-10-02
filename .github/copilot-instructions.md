---
description: 'Windows App SDK AI contributor guidance'
---

# Windows App SDK – Copilot Instructions

Concise guidance for AI contributions to the Windows App SDK. For complete details, see [AGENTS.md](../AGENTS.md).

## Quick Reference

- **Build**: `BuildAll.ps1` / `BuildAll.cmd` (builds the full SDK solution)
- **Run**: Test on x64, x86, ARM64 in Debug and Release
- **Verify**: Run `TestAll.ps1` / `TestAll.cmd`
- **Exit code 0 = success** – do not proceed if build fails

## Key Rules

- Code should be **production-quality** – follow SDK coding standards
- Follow **modular design** – clear component boundaries
- Support all platforms: x64, x86, ARM64 (Debug and Release)
- Minimum OS: Windows 10 version 1809 (build 17763)
- Include copyright headers; build clean with no warnings

## Style Enforcement

- **C#**: Follow `.editorconfig` at repo root
- **C++**: Use C++/WinRT; follow `docs/Coding-Guidelines.md`

## When to Ask for Clarification

- Ambiguous sample requirements after reviewing docs
- Cross-feature impact unclear
- API usage patterns not well documented

## Detailed Documentation

- [AGENTS.md](../AGENTS.md) – Full AI contributor guide
- [Coding Guidelines](../docs/Coding-Guidelines.md) – Complete coding standards
- [Contributor Guide](../docs/contributor-guide.md) – Contribution requirements
- [PR Template](../docs/pull_request_template.md) – Pull request checklist
- [Windows App SDK Docs](https://docs.microsoft.com/windows/apps/windows-app-sdk/) – Official documentation
