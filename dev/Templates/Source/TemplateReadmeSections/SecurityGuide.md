## Security guide

- Trim `Package.appxmanifest` capabilities to exactly what the app needs ([App capability declarations](https://learn.microsoft.com/windows/uwp/packaging/app-capability-declarations)).
- Keep dependencies fresh: `dotnet list package --outdated`.
- Secrets: use environment variables, [PasswordVault](https://learn.microsoft.com/windows/uwp/security/credential-locker), or [Azure Key Vault](https://learn.microsoft.com/azure/key-vault/general/overview) — never commit them.
- Validate / sanitize anything that crosses a trust boundary before use in queries, paths, or `Process.Start`.
- Use `HttpClient` over HTTPS with default TLS validation; guard any relaxation with `#if DEBUG`.
- Keep tokens / PII out of logs; never swallow exceptions silently.
- Production releases need a trusted certificate; see [Create a certificate for package signing](https://learn.microsoft.com/windows/msix/package/create-certificate-package-signing).

For more, see [.NET secure coding guidelines](https://learn.microsoft.com/dotnet/standard/security/secure-coding-guidelines).
