# Step 01: Functionality Review

**Goal**: Verify the PR's code changes correctly implement the intended functionality without introducing regressions.

## Output file
`Generated Files/prReview/{{pr_number}}/01-functionality.md`

## Checks to execute

### Core functionality
- [ ] Does the code do what the PR description/linked issue claims?
- [ ] Are all acceptance criteria from the linked issue addressed?
- [ ] Do new features work correctly in both enabled and disabled states?
- [ ] Are feature flags/settings properly respected?

### Logic correctness
- [ ] Are conditional branches handling all expected cases?
- [ ] Are loops terminating correctly (no infinite loops, off-by-one errors)?
- [ ] Are null/empty checks in place where needed?
- [ ] Are error conditions handled gracefully?
- [ ] Are edge cases considered (empty input, max values, boundary conditions)?

### State management
- [ ] Is state properly initialized before use?
- [ ] Is state cleaned up appropriately (disposal, event unsubscribe)?
- [ ] Are race conditions possible with shared state?
- [ ] Is state persisted/loaded correctly for settings?

### Integration points
- [ ] Do changes integrate correctly with existing code paths?
- [ ] Are dependencies properly injected/resolved?
- [ ] Do IPC/inter-process communications work correctly?
- [ ] Are module enable/disable transitions handled?

### Repo-specific checks
- [ ] Are WinRT activation factory registrations correct and complete?
- [ ] Are C++/WinRT projection types used correctly (no mismatched ABI/projection boundaries)?
- [ ] Are API contract versions specified and additive-only?
- [ ] Is thread safety ensured for WinRT objects (STA/MTA awareness, agile references)?

## File template
```md
# Functionality Review
**PR:** {{pr_number}} — Base:{{baseRefName}} Head:{{headRefName}}
**Review iteration:** {{iteration}}

## Iteration history
### Iteration {{iteration}}
- <Key finding 1>
- <Key finding 2>

## Checks executed
- <List specific checks performed>

## Findings
(If none, write **None**. Otherwise use mcp-review-comment blocks:)

```mcp-review-comment
{"file":"path/to/file.cs","start_line":123,"end_line":125,"severity":"high|medium|low|info","tags":["functionality","pr-{{pr_number}}"],"body":"Problem → Why it matters → Concrete fix."}
```
```

## Severity guidelines
- **High**: Code doesn't work as intended, crashes, data loss possible
- **Medium**: Partial functionality, edge cases broken, degraded experience
- **Low**: Minor issues, cosmetic problems, suboptimal but working
- **Info**: Suggestions for improvement, not blocking

## External references (MUST research)
Before completing this step, fetch and check the PR against these authoritative sources:

| Reference | URL | Check for |
| --- | --- | --- |
| C# Design Guidelines | https://docs.microsoft.com/en-us/dotnet/csharp/fundamentals/coding-style/coding-conventions | Coding conventions violations |
| .NET API Design | https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/ | API design issues |
| Component Interface | `docs/contributor-guide.md` | Module contract violations |

**Enforcement**: In the output file, include a `## References consulted` section listing which guidelines were checked and any violations found.
