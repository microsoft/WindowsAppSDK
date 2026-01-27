# Feature Area Contacts

This document maps Windows App SDK feature areas to their engineering contacts. Update this file when team assignments change.

> **Last Updated**: January 2026

## Area Contact Mapping

| Feature Area | Primary Contact | Secondary Contact | Notes |
|--------------|-----------------|-------------------|-------|
| area-Activation | Tim Kurtzman | | App activation patterns |
| area-AOT | Scott Jones | Manodasan Wignarajah | Ahead-of-time compilation |
| area-AppContainer | Alex Lam | | App container support |
| area-AppExtension | Carl Russell | | App extensions |
| area-ApplicationData | Carl Russell | | Application data APIs |
| area-BackgroundTask | Godly Alias | | Background task management |
| area-Decimal | Carl Russell | | Decimal type support |
| area-DeveloperTools | James Pike | | Dev tooling and templates |
| area-dotnet | Scott Jones | Manodasan Wignarajah | .NET projections |
| area-DWriteCore | Leonardo Blanco | | DirectWrite text rendering |
| area-DynamicDependencies | Carl Russell | | Dynamic dependency resolution |
| area-Elevation | Sarah Paracha | | Triage driver - elevation scenarios |
| area-External | Sarah Paracha | | Triage driver - redirect to external teams |
| area-File access | Gordon Lam | Dinah Gao, Xiang Hong | File system access APIs |
| area-Graphics | Zachary Northrup | Saharsh Jaiswal | DisplayInformation, Camera Capture |
| area-Infrastructure | Alex Lam | Felipe da Conceicao Guimaraes | Build/CI infrastructure |
| area-Installer | Sarah Paracha | | Installer experience |
| area-Lifecycle | Tim Kurtzman | | App lifecycle management |
| area-Metapackage | Scott Jones | Manodasan Wignarajah | NuGet metapackage |
| area-MRTCore | Kent Shipley | | Resource management |
| area-Notification | Vivek Khare | | App/Push/Toast notifications |
| area-PackageManagement | Carl Russell | | Package management APIs |
| area-Packaging | James Pike | | App packaging |
| area-Power | Anis Mohammed Khaja Mohideen | | Power state notifications |
| area-Projections | Scott Jones | Manodasan Wignarajah | Language projections |
| area-Security | Steve Syfuhs | | Security features (OAuth, etc.) |
| area-SelfContained | Scott Jones | Manodasan Wignarajah | Self-contained deployment |
| area-Shell UX | Sarah Paracha | | Triage driver - shell/UX features |
| area-UndockedRegFreeWinRT | Carl Russell | | Registration-free WinRT |
| area-VersionInfo | Chris Wall | | Version information APIs |
| area-WCR | Connor Al-Joundi | Aditi Narvekar | Windows Copilot Runtime |
| area-WebView | Sandeep Chadda | Hemant Kumar | WebView2 integration |
| area-Widgets | Pranav Gupta | | Widget board integration |
| area-WinAppSDK:Templates | Lauren Ciha | | Project templates |
| area-WinAppSDKDeployment | James Pike | | Deployment scenarios |
| area-Windowing | Chris Raubecher | | Windowing APIs |
| area-WinML | Andrew Leader | Aditya Rastogi, Jason Holmes, Nick Eubanks | Machine learning |
| area-WinUI | Ajit Surana | Snigdha | WinUI framework issues |

## Special Areas

### Triage-Only Areas

These areas are managed for triage/redirection purposes:

| Area | Triage Driver | Purpose |
|------|---------------|---------|
| area-External | Sarah Paracha | Issues to redirect to other Microsoft teams |
| area-Elevation | Sarah Paracha | Elevation/admin scenarios (needs owner) |
| area-Shell UX | Sarah Paracha | Shell UX features (interim triage) |

### Cross-Functional Areas

| Area | Primary Team | Cross-functional With |
|------|--------------|----------------------|
| area-WinUI | WinUI team | microsoft/microsoft-ui-xaml |
| area-WebView | WebView team | MicrosoftEdge/WebView2Feedback |
| area-Widgets | Widgets team | Windows Widgets team |

## Updating Contacts

### When to Update

- Team member leaves or changes roles
- New feature area added
- Responsibility transfer between teams

### How to Update

1. Edit this file with the new contact information
2. Include the date of update in the "Last Updated" field
3. If a contact is temporary (interim), add note in the Notes column
4. For triage-only areas, specify "Triage driver" in Notes

### Contact Format

- Use full names (e.g., "Tim Kurtzman" not "tkurtzman")
- For multiple contacts, separate with comma
- Add role clarification in Notes if needed (e.g., "[DisplayInfo]: Zach")

## Configuration File

For automated scripts, this data is also available in JSON format:

```json
{
  "areaContacts": {
    "area-Activation": {
      "primary": "Tim Kurtzman",
      "secondary": null,
      "notes": "App activation patterns"
    },
    "area-AOT": {
      "primary": "Scott Jones",
      "secondary": "Manodasan Wignarajah",
      "notes": "Ahead-of-time compilation"
    }
  },
  "specialAreas": {
    "triageOnly": ["area-External", "area-Elevation", "area-Shell UX"],
    "crossFunctional": {
      "area-WinUI": "microsoft/microsoft-ui-xaml",
      "area-WebView": "MicrosoftEdge/WebView2Feedback"
    }
  },
  "lastUpdated": "2026-01"
}
```

The `Get-AreaContacts.ps1` script reads from `area-contacts.json` in the same directory.
