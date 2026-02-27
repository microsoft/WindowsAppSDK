---
description: 'Globalization & Localization requirements for user-facing strings, resource files, and culture-aware formatting'
applyTo: '**/*.cs, **/*.xaml, **/*.resw'
---

# Globalization & Localization

These rules apply to **every feature and change** involving user-facing text. They are not optional add-ons.

---

## Rules

- **All user-facing strings** (UI text, error messages, tooltips) must come from `.resw` resource files — never hard-code them in XAML or C#.
- Resource file location: `Strings/en-us/Resources.resw` (default locale).
- Use `x:Uid` in XAML to bind controls to resource keys:
  ```xml
  <TextBlock x:Uid="WelcomeMessage" />
  ```
  With a matching `.resw` entry: `WelcomeMessage.Text` = "Welcome!"
- In code-behind / ViewModels, use the `ResourceLoader`:
  ```csharp
  var loader = new Microsoft.Windows.ApplicationModel.Resources.ResourceLoader();
  string message = loader.GetString("ErrorFileNotFound");
  ```
- **Format dates, numbers, and currencies** using `CultureInfo.CurrentCulture` or `DateTimeFormatter` — never assume a specific regional format.
- Avoid concatenating translated strings — use format placeholders (`{0}`, `{1}`).
- Design UI layouts to accommodate text expansion (~30-40% longer for German vs. English).

## Anti-patterns

- Hard-coded strings in `.xaml` or `.cs` files (e.g., `Content="Save"`).
- Using `string.Format` with hard-coded ordinal assumptions.
- Fixed-width UI elements that clip translated text.

## Validation

- Build & register the MSIX package — see **Build, Run & Deploy** in `.github/agents/Agents.md`.
- Check for hard-coded strings: search `Content="` and `Text="` in `.xaml` files — replace with `x:Uid`.

### Verification Checklist

- [ ] All user-facing strings are in `.resw` resource files

## Must Read & Research

> **Agent Rule:** Before any localization-related change, you **must** fetch and review these references using `fetch_webpage`. Apply what you learn.

| # | Reference | When to consult |
|---|---|---|
| 1 | [Globalize your WinUI app](https://learn.microsoft.com/en-us/windows/apps/design/globalizing/guidelines-and-checklist-for-globalizing-your-app) | Adding any new user-facing strings or culture-aware formatting |
| 2 | [Resource Management System](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/mrtcore/localize-strings) | Setting up or modifying `.resw` files and `ResourceLoader` usage |
| 3 | [WinUI Localization with x:Uid](https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/localizing-strings) | Binding XAML controls to localized resources via `x:Uid` |


