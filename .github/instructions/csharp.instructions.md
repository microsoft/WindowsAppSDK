---
description: 'Guidelines for C# Windows App SDK development'
applyTo: '**/*.cs'
---

# C# Windows App SDK Development

Guidelines for writing C# code in the Windows App SDK.

## C# Instructions

- Use C# language features appropriate for the target .NET version in the SDK
- Write clear and concise comments explaining API implementation patterns
- Follow SDK coding standards for production-quality code

## General Instructions

- Follow **production-quality standards** – write clean, maintainable code
- Implement **proper error handling** with meaningful exception messages
- Handle edge cases with clear exception handling
- Comment on why certain patterns or design decisions are used

## Naming Conventions

- Follow PascalCase for component names, method names, and public members
- Use camelCase for private fields and local variables
- Prefix interface names with "I" (e.g., IWindowService)

## Formatting

- Apply code-formatting style defined in `.editorconfig` at repo root
- Prefer file-scoped namespace declarations
- Insert a newline before the opening curly brace (Allman style)
- Use pattern matching and switch expressions where they improve clarity
- Use `nameof` instead of string literals when referring to member names

## Code Analysis

- All code must pass **StyleCop.Analyzers** rules without warnings
- All code must pass **Microsoft.CodeAnalysis.NetAnalyzers** (CA rules) without warnings
- Suppress warnings only with justification comments when absolutely necessary
- Common rules to follow:
  - [StyleCop.Analyzers rules](https://github.com/DotNetAnalyzers/StyleCopAnalyzers/blob/master/DOCUMENTATION.md)
  - [Code quality rules (CA)](https://learn.microsoft.com/dotnet/fundamentals/code-analysis/quality-rules/)
  - [Code style rules (IDE)](https://learn.microsoft.com/dotnet/fundamentals/code-analysis/style-rules/)

## Nullable Reference Types

- Declare variables non-nullable, and check for `null` at entry points
- Always use `is null` or `is not null` instead of `== null` or `!= null`
- Trust the C# null annotations and don't add null checks when the type system says a value cannot be null

## Windows App SDK Patterns

### App Lifecycle and Activation

- Demonstrate proper activation handling (file, protocol, launch)
- Show single-instance patterns using `AppInstance`
- Handle restart and state persistence scenarios

### WinUI 3 and XAML

- Use x:Bind for data binding where possible
- Demonstrate proper resource management and theming
- Show Window and navigation patterns

### Packaging and Deployment

- Support both packaged (MSIX) and unpackaged scenarios where applicable
- Use `WindowsPackageType` appropriately in project files
- Demonstrate self-contained deployment patterns when relevant

## Copyright Headers

All C# files must include:
```csharp
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
```
