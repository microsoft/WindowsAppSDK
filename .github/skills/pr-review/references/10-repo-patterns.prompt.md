# Step 10: Repository Patterns Review

**Goal**: Ensure changes follow established Windows App SDK repository conventions and patterns.

## Output file
`Generated Files/prReview/{{pr_number}}/10-repo-patterns.md`

## Checks to execute

### Code style compliance
- [ ] Does C++ code follow `docs/Coding-Guidelines.md` and `.editorconfig`?
- [ ] Does C# code follow `.editorconfig` (4-space indent, Allman braces, UTF-8 BOM)?
- [ ] Are naming conventions followed (PascalCase for public API, camelCase for locals)?
- [ ] Do all source files include the Microsoft copyright header?

### Project structure
- [ ] Are new files in the correct component folder under `dev\<ComponentName>\`?
- [ ] Is the component structure consistent with existing SDK components?
- [ ] Are shared utilities in `dev\Common\`, not duplicated across components?
- [ ] Are test projects placed under `test\` with appropriate naming?
- [ ] Are `.vcxitems` shared-items projects used correctly (compile into `WindowsAppRuntime_DLL`)?

### WinRT API patterns
- [ ] Do new public APIs follow Windows Runtime conventions (WinRT types, HSTRING, IInspectable)?
- [ ] Are C++/WinRT projections correct and idiomatic?
- [ ] Are IDL files properly authored for new WinRT types?
- [ ] Are activation factories registered correctly?
- [ ] Is minimum OS version (Windows 10 1809 / build 17763) respected?

### Logging patterns
- [ ] Is WIL (Windows Implementation Library) used for error handling and logging?
- [ ] Is TraceLogging used for ETW events?
- [ ] Are `THROW_IF_FAILED`, `RETURN_IF_FAILED`, `LOG_IF_FAILED` WIL macros used appropriately?
- [ ] Are log levels appropriate (no verbose logging in release builds)?
- [ ] Are sensitive values excluded from traces?

### Build patterns
- [ ] Are project references used (not DLL references)?
- [ ] Are package versions managed via `Directory.Packages.props`?
- [ ] Is the project included in `WindowsAppRuntime.sln` correctly?
- [ ] Are build configurations consistent across x64, x86, ARM64?
- [ ] Does the change work with both Debug and Release configurations?

### Error handling patterns
- [ ] Are HRESULT error codes used and checked consistently?
- [ ] Are WIL error-handling macros preferred over raw try/catch?
- [ ] Is graceful degradation preferred over crashing?
- [ ] Are COM errors propagated correctly across WinRT boundaries?

### Resource & packaging patterns
- [ ] Are resources in the correct `.resw`/`.rc` files?
- [ ] Is resource naming following conventions?
- [ ] Are MRT (MRT Core) resource patterns followed?
- [ ] Are NuGet package contents structured correctly?

## Repo-specific patterns
```cpp
// WIL error handling pattern
THROW_IF_FAILED(SomeComCall());
RETURN_IF_FAILED(AnotherCall());
LOG_IF_FAILED(OptionalCall());  // log but don't fail

// C++/WinRT component pattern
namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    struct MyFeature : MyFeatureT<MyFeature>
    {
        MyFeature() = default;
        void DoWork();
    };
}

// TraceLogging pattern
DEFINE_TRACELOGGING_EVENT_PARAM1(MyEvent, PCWSTR, message, TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE));
```

```csharp
// C# projection usage
using Microsoft.Windows.AppLifecycle;
var instance = AppInstance.GetCurrent();
```

## Files to reference
- Coding Guidelines: `docs/Coding-Guidelines.md`
- Contributor Guide: `docs/contributor-guide.md`
- AI Contributor Guide: `AGENTS.md`
- Build system: `BuildAll.ps1`, `build/` directory

## File template
```md
# Repository Patterns Review
**PR:** {{pr_number}} — Base:{{baseRefName}} Head:{{headRefName}}
**Review iteration:** {{iteration}}

## Iteration history
### Iteration {{iteration}}
- <Key finding 1>
- <Key finding 2>

## Checks executed
- <List specific pattern checks performed>

## Findings
```mcp-review-comment
{"file":"path/to/file.cpp","start_line":123,"end_line":125,"severity":"high|medium|low|info","tags":["repo-patterns","pr-{{pr_number}}"],"body":"Pattern deviation → Repo convention reference → How to fix."}
```
```

## Severity guidelines
- **High**: Major deviation from required patterns, will cause build/integration issues
- **Medium**: Pattern inconsistency, makes codebase harder to maintain
- **Low**: Minor style issues, naming improvements
- **Info**: Suggestions for better alignment with repo conventions

## External references (MUST research)
Before completing this step, **fetch and analyze** these local documentation files:

| Reference | Path | Check for |
| --- | --- | --- |
| Coding Guidelines | `docs/Coding-Guidelines.md` | Style guide adherence |
| Contributor Guide | `docs/contributor-guide.md` | Contribution requirements |
| AI Contributor Guide | `AGENTS.md` | AI-specific conventions |
| Build System | `BuildAll.ps1` | Build integration |

**Enforcement**: Include `## References consulted` section with repo docs checked and deviations found.
