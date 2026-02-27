---
description: 'Static analysis, StyleCop, EditorConfig, naming conventions, and code cleanup rules'
applyTo: '**/*.cs, **/*.editorconfig, **/stylecop.json'
---

# Code Quality — Static Analysis, StyleCop & Code Cleanup

Maintain strict code quality through automated analysis and consistent style enforcement.

---

## 1. Static Analysis (Roslyn Analyzers)

### Required Analyzer Packages

Add these to the `.csproj` if not already present:

```xml
<ItemGroup>
  <!-- Use the latest stable versions; do not hard-code version numbers in instructions -->
  <PackageReference Include="Microsoft.CodeAnalysis.NetAnalyzers" Version="*" />
  <PackageReference Include="StyleCop.Analyzers" Version="*">
    <PrivateAssets>all</PrivateAssets>
    <IncludeAssets>runtime; build; native; contentfiles; analyzers</IncludeAssets>
  </PackageReference>
</ItemGroup>
```

### Analysis Configuration in `.csproj`

```xml
<PropertyGroup>
  <EnableNETAnalyzers>true</EnableNETAnalyzers>
  <AnalysisLevel>latest-recommended</AnalysisLevel>
  <EnforceCodeStyleInBuild>true</EnforceCodeStyleInBuild>
  <TreatWarningsAsErrors>false</TreatWarningsAsErrors>
  <Nullable>enable</Nullable>
</PropertyGroup>
```

### Rule Enforcement

Follow **all** CA* (quality) and IDE* (code style) analyzer rules at their configured severity. Do not cherry-pick — obey every warning the analyzers report. When encountering a specific rule violation, fetch the corresponding documentation from the **Must Read & Research** references below to understand and apply the correct fix.

### `.editorconfig`

The project's `.editorconfig` in the solution root is the source of truth for code style. Obey all rules defined there. When creating or modifying `.editorconfig`, fetch the [EditorConfig Reference](https://learn.microsoft.com/en-us/dotnet/fundamentals/code-analysis/code-style-rule-options) for the full list of available settings.

Key project conventions enforced via `.editorconfig`:
- Private fields use `_camelCase` prefix (SA1101 suppressed, SA1309 suppressed).
- File-scoped namespaces are required.
- `this.` qualification is not used.

---

## 2. StyleCop Rules

### StyleCop Configuration (`stylecop.json`)

Place this file in the project root alongside the `.csproj`:

```json
{
  "$schema": "https://raw.githubusercontent.com/DotNetAnalyzers/StyleCopAnalyzers/master/StyleCop.Analyzers/StyleCop.Analyzers/Settings/stylecop.schema.json",
  "settings": {
    "documentationRules": {
      "companyName": "YourProjectName",
      "copyrightText": "Copyright (c) {companyName}. All rights reserved.",
      "xmlHeader": false,
      "documentInterfaces": true,
      "documentExposedElements": true,
      "documentInternalElements": false,
      "documentPrivateElements": false,
      "documentPrivateFields": false
    },
    "orderingRules": {
      "usingDirectivesPlacement": "outsideNamespace",
      "systemUsingDirectivesFirst": true
    },
    "layoutRules": {
      "newlineAtEndOfFile": "require"
    },
    "namingRules": {
      "allowCommonHungarianPrefixes": false
    }
  }
}
```

### Rule Enforcement

Follow **all** SA* (StyleCop) rules at their configured severity. When encountering a specific SA* violation, fetch the [StyleCop Rules Reference](https://github.com/DotNetAnalyzers/StyleCopAnalyzers/blob/master/DOCUMENTATION.md) to understand the rule and apply the correct fix. Do not suppress rules without justification in a code comment.

---

## 3. Code Cleanup Rules (Always Enforced)

### After Every Edit

1. **Remove unused `using` statements** — No unused imports should remain.
2. **Remove commented-out code** — Version control tracks history; dead code is noise.
3. **Remove unused variables and fields** — If it's declared but never read, delete it.
4. **Remove empty methods** — If an event handler or override does nothing, remove it.
5. **Simplify code** — Apply IDE suggestions (IDE0001–IDE0090) for:
   - Removing unnecessary casts
   - Simplifying `default` expressions
   - Using pattern matching
   - Using null-coalescing operators

### Naming Conventions

| Element | Convention | Example |
|---|---|---|
| Class / Struct | PascalCase | `MainViewModel` |
| Interface | I + PascalCase | `INavigationService` |
| Public method | PascalCase | `LoadDataAsync()` |
| Private method | PascalCase | `ValidateInput()` |
| Public property | PascalCase | `CurrentPage` |
| Private field | _camelCase | `_settingsService` |
| Parameter | camelCase | `userName` |
| Local variable | camelCase | `itemCount` |
| Constant | PascalCase | `MaxRetryCount` |
| Async method | Suffix `Async` | `FetchDataAsync()` |
| Boolean | Prefix `Is/Has/Can` | `IsLoading`, `HasAccess` |

### File Organization

Each `.cs` file should follow this order:

1. `using` directives (System first, then others, alphabetically)
2. Namespace declaration (file-scoped)
3. Class/struct/interface declaration
4. Inside the type:
   1. Constants
   2. Static fields
   3. Instance fields
   4. Constructors
   5. Properties
   6. Public methods
   7. Private/internal methods
   8. Event handlers
   9. Nested types

---

## Validation

- Build & register the MSIX package — see **Build, Run & Deploy** in `.github/agents/Agents.md`.
- Fix **all** warnings — do not suppress without justification in a code comment.
- Verify no unused `using` statements remain after every edit.
- Verify no commented-out code remains.
- Confirm naming conventions match the table above for every new symbol.

---

## Must Read & Research

> **Agent Rule:** Before configuring analyzers, fixing warnings, or adjusting code style, you **must** fetch and review the relevant references below using `fetch_webpage`. Apply what you learn — do not skip this step.

| # | Reference | When to consult |
|---|---|---|
| 1 | [.NET Code Analysis Overview](https://learn.microsoft.com/en-us/dotnet/fundamentals/code-analysis/overview) | Setting up or modifying analyzer configuration |
| 2 | [Code Style Rules (IDE0001–IDE0090)](https://learn.microsoft.com/en-us/dotnet/fundamentals/code-analysis/style-rules/) | Resolving IDE* warnings or adjusting `.editorconfig` |
| 3 | [Quality Rules (CA*)](https://learn.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/) | Resolving CA* warnings or suppressing with justification |
| 4 | [StyleCop.Analyzers GitHub](https://github.com/DotNetAnalyzers/StyleCopAnalyzers) | Adding/updating StyleCop package or configuration |
| 5 | [StyleCop Rules Reference](https://github.com/DotNetAnalyzers/StyleCopAnalyzers/blob/master/DOCUMENTATION.md) | Understanding specific SA* rule violations |
| 6 | [EditorConfig Reference](https://learn.microsoft.com/en-us/dotnet/fundamentals/code-analysis/code-style-rule-options) | Modifying `.editorconfig` style or severity settings |
| 7 | [.NET Naming Conventions](https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/coding-style/identifier-names) | Verifying naming patterns for types, members, parameters |


