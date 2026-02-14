---
description: 'Security requirements for secrets management, input validation, permissions, and secure coding'
applyTo: '**/*.cs, **/*.appxmanifest'
---

# Security

These rules apply to **every feature and change**. They are not optional add-ons.

---

## Rules

- **Never hard-code secrets** (API keys, passwords, connection strings) — use environment variables, Windows Credential Manager, or Azure Key Vault.
- Validate and sanitize **all external input** (user input, file content, network responses).
- Use `SecureString` or `PasswordVault` for sensitive data in memory when practical.
- Follow the **principle of least privilege** — request only the permissions the app actually needs in `Package.appxmanifest`.
- Keep NuGet packages up to date — run `dotnet list package --outdated` regularly.
- Enable **code signing** for published MSIX packages.
- When using `HttpClient`, always validate TLS certificates and use HTTPS.
- Never log sensitive data (PII, tokens, passwords).

## Anti-patterns

- Storing secrets in `appsettings.json` committed to source control.
- Disabling TLS validation for debugging and forgetting to re-enable it.
- Using `Process.Start` with unsanitized user input.
- Broad `try { } catch (Exception) { }` that swallows errors silently without any logging.

## Validation

- Build & register the MSIX package — see **Build, Run & Deploy** in `Agents.md`.
- Check for hard-coded secrets: search for `password`, `apikey`, `secret`, `connectionstring` in `.cs` files.

### Verification Checklist

- [ ] No secrets are hard-coded

## Must Read & Research

> **Agent Rule:** Before any security-related change (auth, input handling, permissions, HTTP), you **must** fetch and review these references using `fetch_webpage`. Apply what you learn.

| # | Reference | When to consult |
|---|---|---|
| 1 | [.NET Security Best Practices](https://learn.microsoft.com/en-us/dotnet/standard/security/) | Any code handling credentials, tokens, or sensitive data |
| 2 | [Secure coding guidelines for .NET](https://learn.microsoft.com/en-us/dotnet/standard/security/secure-coding-guidelines) | Input validation, exception handling, type safety |
| 3 | [MSIX Security](https://learn.microsoft.com/en-us/windows/msix/msix-container) | Packaging, signing, or distribution changes |
| 4 | [Package.appxmanifest capabilities](https://learn.microsoft.com/en-us/windows/uwp/packaging/app-capability-declarations) | Adding or modifying app capabilities/permissions |
