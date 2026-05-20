## Globalization guide

For globalization, keep user-facing strings in `.resw` resource files,
format dates, numbers, and currencies through culture-aware APIs, and
design layouts that tolerate text expansion.

It is recommended to verify localization early by adding a second locale
(e.g., `Strings/de-DE/Resources.resw` alongside `Strings/en-US/Resources.resw`)
and switching the Windows display language. Layout overflow and missing
strings show up immediately.

For per-task guidance:

- **Adding UI text**:
  [Localize strings in XAML with `x:Uid`](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/localize-strings#refer-to-a-string-resource-identifier-from-xaml)
  (covers `x:Uid` markup and matching `.resw` keys).
- **Loading strings from code**:
  [Localize strings with the Resource Management System](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/localize-strings)
  (covers `ResourceLoader.GetString` and per-locale `.resw` layout).
- **Composing translated text**: use positional placeholders (`{0}`,
  `{1}`) with `string.Format` rather than concatenating fragments,
  because the grammatical word-order varies between languages, and
  concatenation often produces awkward translations.
- **Culture-aware formatting and layout**:
  [Globalize your WinUI app](https://learn.microsoft.com/windows/apps/design/globalizing/guidelines-and-checklist-for-globalizing-your-app)
  (covers `CultureInfo`, `DateTimeFormatter`, and designing for text expansion).
