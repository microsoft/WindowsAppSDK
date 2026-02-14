---
description: 'Design principles (DRY, KISS, SOLID, YAGNI) enforced in every code change'
applyTo: '**/*.cs, **/*.xaml'
---

# Design Principles

Apply these principles in **every change** you make to this codebase. When in doubt, favour simplicity and clarity over cleverness.

---

## 1. DRY — Don't Repeat Yourself

> *"Every piece of knowledge must have a single, unambiguous, authoritative representation within a system."*

### Rules
- Before writing new code, **search** the codebase for existing implementations that solve the same problem.
- Extract shared logic into helper methods, base classes, or services.
- If you find duplicated code during a task, **refactor it** as part of the same change.
- Prefer generic/reusable components over copy-paste variations.

### Anti-patterns to avoid
- Copy-pasting code between classes/files instead of extracting a shared method.
- Creating multiple converters/helpers that do the same thing.
- Duplicating validation logic across ViewModel and Model layers.

---

## 2. KISS — Keep It Simple, Stupid

> *"Simplicity is the ultimate sophistication."*

### Rules
- Choose the **simplest approach** that meets the requirement.
- Avoid unnecessary abstractions, inheritance hierarchies, or patterns that add complexity without clear benefit.
- Write code that **reads like plain English** — favour descriptive names over comments.
- If a method is longer than ~30 lines, consider splitting it.
- If a class does more than one thing, split it (see SRP below).

### Anti-patterns to avoid
- Over-engineering with factories/builders/strategies for simple object creation.
- Creating deep inheritance trees when composition would suffice.
- Using complex LINQ chains when a simple `foreach` is clearer.

---

## 3. SOLID Principles

### 3.1 SRP — Single Responsibility Principle
> *"A class should have only one reason to change."*

- Each class/file should have **one clear responsibility**.
- ViewModels handle UI state & commands. Services handle business logic. Models hold data.
- If a class name contains "And" or "Manager", it likely violates SRP.

### 3.2 OCP — Open/Closed Principle
> *"Software entities should be open for extension, but closed for modification."*

- Use interfaces and abstract classes so behaviour can be extended without modifying existing code.
- Prefer adding new implementations over modifying existing ones.
- Use dependency injection to swap implementations.

### 3.3 LSP — Liskov Substitution Principle
> *"Objects of a superclass should be replaceable with objects of its subclasses without altering correctness."*

- Derived classes must honour the contracts of their base classes.
- Never throw `NotImplementedException` in overridden methods — if a subclass can't fulfil the contract, the inheritance is wrong.

### 3.4 ISP — Interface Segregation Principle
> *"No client should be forced to depend on methods it does not use."*

- Keep interfaces small and focused.
- Prefer multiple small interfaces over one large one.
- Example: `INavigationService`, `IDialogService`, `ISettingsService` — not `IAppService`.

### 3.5 DIP — Dependency Inversion Principle
> *"Depend upon abstractions, not concretions."*

- High-level modules must not depend on low-level modules. Both should depend on abstractions.
- Use constructor injection for dependencies.
- Register services in a DI container (e.g., `Microsoft.Extensions.DependencyInjection`).

---

## 4. YAGNI — You Aren't Gonna Need It

> *"Don't add functionality until it is necessary."*

### Rules
- Only implement what is **explicitly requested** or **clearly needed right now**.
- Do not add "just in case" parameters, methods, or abstractions.
- If you're unsure whether something is needed, **leave it out** — it can always be added later.

### Anti-patterns to avoid
- Adding unused interface methods "for future use".
- Building a generic framework when a single concrete class suffices.
- Creating configuration options nobody has asked for.

---

## Quick Reference Checklist

Before submitting any code change, verify:

- [ ] No duplicated code exists (DRY)
- [ ] The solution is as simple as possible (KISS)
- [ ] Each class has one responsibility (SRP)
- [ ] New behaviour is added via extension, not modification (OCP)
- [ ] Derived types can substitute their base types (LSP)
- [ ] Interfaces are small and focused (ISP)
- [ ] Dependencies point toward abstractions (DIP)
- [ ] No speculative features were added (YAGNI)

## Validation

- Review every new/changed class for SRP violations — ask "does this class have more than one reason to change?"
- Search the codebase for duplicate logic before adding new helpers: `grep_search` for similar method names or patterns.
- Verify no speculative code was added — every line must trace back to the original request.
- Build & register the MSIX package — see **Build, Run & Deploy** in `Agents.md`.

---

## Must Read & Research

> **Agent Rule:** Before making any code change related to design principles, you **must** fetch and review the relevant references below using `fetch_webpage`. Apply what you learn — do not skip this step.

| # | Reference | When to consult |
|---|---|---|
| 1 | [SOLID Principles in C# — Microsoft Learn](https://learn.microsoft.com/en-us/archive/msdn-magazine/2014/may/csharp-best-practices-dangers-of-violating-solid-principles-in-csharp) | Adding/refactoring classes, interfaces, or inheritance |
| 2 | [.NET Design Guidelines](https://learn.microsoft.com/en-us/dotnet/standard/design-guidelines/) | Designing public APIs, naming, type design |
| 3 | [Framework Design Guidelines (Book)](https://learn.microsoft.com/en-us/dotnet/standard/design-guidelines/) | Deep-dive on member design, exception patterns, collections |
| 4 | [Clean Code Summary](https://gist.github.com/wojteklu/73c6914cc446146b8b533c0988cf8d29) | Code readability, function size, naming clarity |
