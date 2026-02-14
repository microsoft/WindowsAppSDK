---
description: 'Accessibility requirements for interactive controls, keyboard navigation, screen readers, and contrast'
applyTo: '**/*.cs, **/*.xaml'
---

# Accessibility

These rules apply to **every UI change**. They are not optional add-ons.

---

## Rules

- **Every interactive control** must have an `AutomationProperties.Name` or `AutomationProperties.LabeledBy`.
- Add a stable, unique `AutomationProperties.AutomationId` for controls targeted by UI automation tests (and for key interactive elements).
- Use semantic XAML controls — prefer `Button`, `HyperlinkButton`, `ListView` over styled `Border`/`Grid` with click handlers.
- Ensure **keyboard navigation** works for all features:
  - Logical tab order via `TabIndex`.
  - `AccessKey` bindings for frequently used actions.
  - `KeyboardAccelerator` for shortcut keys.
- Maintain **minimum contrast ratios** (4.5:1 for normal text, 3:1 for large text) — test in High Contrast mode.
- Support **screen readers** (Narrator / NVDA): test that all content is announced correctly.
- Images must have `AutomationProperties.Name` describing the image purpose (or `AutomationProperties.AccessibilityView="Raw"` for decorative images).
- Do not rely on colour alone to convey meaning — add icons, text, or patterns.

## Anti-patterns

- Clickable `TextBlock` or `Image` without `AutomationProperties`.
- Custom controls that are not keyboard-focusable.
- Using `Visibility.Collapsed` to "hide" content from screen readers (use `AccessibilityView` instead).

## Validation

- Build & register the MSIX package — see **Build, Run & Deploy** in `Agents.md`.
- Test keyboard navigation: tab through every new/changed UI area.
- Test High Contrast: switch to Windows High Contrast theme and verify readability.
- Run Accessibility Insights for Windows on the app.

### Verification Checklist

- [ ] All interactive controls have `AutomationProperties.Name`
- [ ] Keyboard navigation works for the changed area
- [ ] Tested with High Contrast theme enabled
- [ ] Tab through the entire UI with keyboard only.
- [ ] Verify key interactive controls have stable, unique `AutomationProperties.AutomationId` values (especially controls used by UI automation tests).
- [ ] Switch to Windows High Contrast theme and verify readability.
- [ ] Run Narrator and verify all controls are announced correctly.
- [ ] Run **Accessibility Insights for Windows** on the app.

## Must Read & Research

> **Agent Rule:** Before any accessibility-related change, you **must** fetch and review these references using `fetch_webpage`. Apply what you learn.

| # | Reference | When to consult |
|---|---|---|
| 1 | [Accessibility in WinUI](https://learn.microsoft.com/en-us/windows/apps/design/accessibility/accessibility) | Any UI change — verify accessibility approach |
| 2 | [AutomationProperties](https://learn.microsoft.com/en-us/windows/apps/design/accessibility/basic-accessibility-information) | Adding or modifying interactive controls |
| 3 | [Accessibility Insights](https://accessibilityinsights.io/docs/windows/overview/) | Testing tool — run before finalizing UI changes |
| 4 | [Keyboard Accessibility](https://learn.microsoft.com/en-us/windows/apps/design/accessibility/keyboard-accessibility) | Adding navigation, focus management, or shortcut keys |
| 5 | [High Contrast Themes](https://learn.microsoft.com/en-us/windows/apps/design/accessibility/high-contrast-themes) | Adding custom styles, colours, or theme resources |
