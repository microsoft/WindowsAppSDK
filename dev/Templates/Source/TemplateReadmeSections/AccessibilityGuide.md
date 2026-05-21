## Accessibility guide

- Use semantic controls (`Button`, `HyperlinkButton`, `ListView`) instead of click-handled `Border`/`Grid` — they ship with focus, keyboard activation, and automation peers.
- Set `AutomationProperties.Name` on informative images; set `AutomationProperties.AccessibilityView="Raw"` on decorative ones.
- Pair color signals with an icon, label, or pattern.
- Verify with [Accessibility Insights for Windows](https://accessibilityinsights.io/docs/windows/overview/) (automated checks, UIA tree, contrast).

For more, see [Accessibility in Windows apps](https://learn.microsoft.com/windows/apps/design/accessibility/accessibility-overview).
