# GitHub Artifacts MCP Server

A Model Context Protocol (MCP) server that enables Copilot prompts to download and analyze images and ZIP attachments from GitHub issues and pull requests.

## Features

- **`github_issue_images`** — Downloads images from issue/PR body and comments, returns as base64 for LLM analysis
- **`github_issue_attachments`** — Downloads and extracts ZIP attachments (diagnostic bundles, logs) to a local folder, returns text file contents

## Prerequisites

- Node.js 18 or later
- `GITHUB_TOKEN` environment variable set with a valid GitHub personal access token

## Setup

### VS Code / Copilot Chat Integration

1. Open VS Code settings (JSON) or your MCP configuration file
2. Add the following MCP server configuration:

```json
{
  "mcp": {
    "servers": {
      "github-artifacts": {
        "command": "node",
        "args": ["tools/mcp/github-artifacts/launch.js"],
        "env": {
          "GITHUB_TOKEN": "${env:GITHUB_TOKEN}"
        }
      }
    }
  }
}
```

3. Reload VS Code to activate the MCP server

### Manual Testing

```bash
cd tools/mcp/github-artifacts
npm install
npm test
```

## Usage

Once configured, the MCP tools become available in Copilot prompts:

### Download Images from an Issue

```
Use github_issue_images to get screenshots from microsoft/PowerToys#25595
```

### Extract ZIP Attachments

```
Use github_issue_attachments to extract logs from issue #39476 to "Generated Files/logs"
```

## Environment Variables

| Variable | Required | Description |
|----------|----------|-------------|
| `GITHUB_TOKEN` | Yes | GitHub personal access token for API authentication |

## Limitations

- ZIP extraction uses native PowerShell (`Expand-Archive`) on Windows
- Text file contents are limited to common extensions (`.txt`, `.log`, `.json`, `.xml`, etc.) and capped at 100KB per file
- Maximum of 20 images per issue by default (configurable via `maxImages` parameter)

## License

MIT License - See repository root for details.
