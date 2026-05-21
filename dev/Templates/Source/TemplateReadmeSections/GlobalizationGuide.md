## Globalization guide

- Keep user-facing strings in `.resw` files; reference from XAML with `x:Uid`, from code with `ResourceLoader.GetString`.
- Compose translated text with positional placeholders (`{0}`, `{1}`) and `string.Format` — never concatenate translated fragments (word order varies by language).
- Format dates / numbers / currencies through culture-aware APIs (`CultureInfo`, `DateTimeFormatter`), not `ToString()`.
- Verify early by adding a second locale (e.g. `Strings/de-DE/Resources.resw`) and switching the Windows display language; design layouts that tolerate text expansion.

For more, see [Globalize your WinUI app](https://learn.microsoft.com/windows/apps/design/globalizing/guidelines-and-checklist-for-globalizing-your-app) and [Localize strings with the Resource Management System](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/localize-strings).
