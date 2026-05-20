## Security guide

For security, it helps to treat secrets, external input, and capabilities
with the same care as the rest of the codebase — mistakes here have a
much larger blast radius than elsewhere.

It is recommended to keep `Package.appxmanifest` capabilities trimmed to
exactly what the app needs — see
[App capability declarations](https://learn.microsoft.com/windows/uwp/packaging/app-capability-declarations)
— and to keep dependencies fresh with `dotnet list package --outdated`.
Removing an unused capability or upgrading a stale package is one of the
cheapest security wins available.

For per-task guidance:

- **Secrets**: keep API keys, tokens, and connection strings out of
  source control. Prefer environment variables, the
  [Windows Credential Manager / `PasswordVault`](https://learn.microsoft.com/windows/uwp/security/credential-locker),
  or [Azure Key Vault](https://learn.microsoft.com/azure/key-vault/general/overview)
  over committing them to `appsettings.json`.
- **External input**: validate and sanitize anything that crosses a
  trust boundary (user input, file contents, network responses) before
  using it in queries, file paths, or `Process.Start` arguments.
- **Networking**: stick with `HttpClient` over HTTPS and the default
  TLS validation. If you have to relax certificate validation while
  debugging, guard it with `#if DEBUG` so it can't slip into a release
  build.
- **Logging and error handling**: keep tokens, passwords, and personal
  data out of logs, and avoid silent
  `try { … } catch (Exception) { }` blocks — at minimum, log what
  failed so future-you can diagnose it.
- **Signing**: production releases need a certificate from a trusted
  authority. The development certificate flow for local testing is
  documented at
  [Create a certificate for package signing](https://learn.microsoft.com/windows/msix/package/create-certificate-package-signing).

For a broader treatment, see
[.NET secure coding guidelines](https://learn.microsoft.com/dotnet/standard/security/secure-coding-guidelines).
