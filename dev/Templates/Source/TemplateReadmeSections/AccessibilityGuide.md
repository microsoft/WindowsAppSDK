## Accessibility guide

For accessibility, make your app usable with a keyboard alone, expose
accessible names to screen readers, and respect High Contrast and system
text scaling. Reaching for semantic controls (`Button`, `HyperlinkButton`,
`ListView`) instead of click-handled `Border`/`Grid` covers most of this
without extra work, since those controls already provide focus, keyboard
activation, and automation peers. Avoiding color-only signals — pair
color with an icon, label, or pattern — keeps the UI usable for
color-blind users too.

It is recommended to run [Accessibility Insights for Windows](https://accessibilityinsights.io/docs/windows/overview/)
against your build. It runs 60+ automated checks, inspects the live UI
Automation tree, and verifies tab order, keyboard traps, and color
contrast.

For per-task guidance:

- **Labeling controls**:
  [Expose basic accessibility information](https://learn.microsoft.com/windows/apps/design/accessibility/basic-accessibility-information)
  (covers `AutomationProperties.Name`, `LabeledBy`, automation IDs).
- **Tab order, access keys, shortcuts**:
  [Keyboard accessibility](https://learn.microsoft.com/windows/apps/design/accessibility/keyboard-accessibility).
- **Custom styles or colors**:
  [High Contrast themes](https://learn.microsoft.com/windows/apps/design/accessibility/high-contrast-themes)
  — keep text contrast above the WCAG ratios (4.5:1 for normal text, 3:1
  for large text), and verify the result under the Windows high-contrast
  theme.
- **Images and icons**: set `AutomationProperties.Name` on informative
  images so screen readers can describe them, and
  `AutomationProperties.AccessibilityView="Raw"` on purely decorative
  ones so assistive technology skips past them.
- **Custom controls and broader concepts**:
  [Accessibility overview](https://learn.microsoft.com/windows/apps/design/accessibility/accessibility-overview)
  (UI Automation, custom automation peers, captioning).
