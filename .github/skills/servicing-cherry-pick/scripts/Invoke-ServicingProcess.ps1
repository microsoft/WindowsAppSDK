# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Main orchestrator for servicing cherry-pick automation.

.DESCRIPTION
    Automates the end-to-end process of cherry-picking a merged PR to release branches:
    1. Fetches PR details and discovers target branches
    2. For each branch: determines patch version, creates ADO bug, cherry-picks,
       applies containment wrapping, updates IDL, and creates a GitHub PR
    3. Persists state for resumability

.PARAMETER PullRequestNumber
    The merged PR number to cherry-pick.

.PARAMETER Repository
    The GitHub repository in owner/repo format. Defaults to config value.

.PARAMETER TargetBranches
    Override auto-detected release branches. Array of branch names.

.PARAMETER ConfigPath
    Path to servicing-config.json. Defaults to skill's config directory.

.PARAMETER SkipAdoBugs
    Skip ADO bug creation (useful for testing).

.PARAMETER DryRun
    Preview all actions without executing them.

.PARAMETER RequireApproval
    Pause for human review at each AI-generated output.

.EXAMPLE
    # Full run for a specific PR
    ./Invoke-ServicingProcess.ps1 -PullRequestNumber 5865

.EXAMPLE
    # Dry run against a single branch
    ./Invoke-ServicingProcess.ps1 -PullRequestNumber 5865 -DryRun

.EXAMPLE
    # Target specific branch with approval gates
    ./Invoke-ServicingProcess.ps1 -PullRequestNumber 5865 `
        -TargetBranches "release/1.8-stable" -RequireApproval

.NOTES
    State is saved to 'Generated Files/servicing/<PR>/state.json' after each branch.
    Re-running the command resumes from the last checkpoint.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [int]$PullRequestNumber,

    [Parameter()]
    [string]$Repository,

    [Parameter()]
    [string[]]$TargetBranches,

    [Parameter()]
    [string]$ConfigPath,

    [switch]$SkipAdoBugs,

    [switch]$DryRun,

    [switch]$RequireApproval
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

$config = Get-ServicingConfig -ConfigPath $ConfigPath

if (-not $Repository) {
    $Repository = $config.repository
}

$repoRoot = Get-RepoRoot

# ╔══════════════════════════════════════════════════════════════════════════╗
# ║ Step 1: Validate Prerequisites                                         ║
# ╚══════════════════════════════════════════════════════════════════════════╝

Write-StepHeader '1' 'Validating prerequisites'

if (-not (Test-AllPrerequisites -SkipAdoBugs:$SkipAdoBugs)) {
    Err "Prerequisites check failed. Please install/authenticate the required tools."
    exit 1
}
Ok "All prerequisites met."

# ╔══════════════════════════════════════════════════════════════════════════╗
# ║ Step 2: Fetch PR Details                                               ║
# ╚══════════════════════════════════════════════════════════════════════════╝

Write-StepHeader '2' "Fetching PR #$PullRequestNumber details"

$prDetails = & "$PSScriptRoot/Get-PullRequestDetails.ps1" `
    -PullRequestNumber $PullRequestNumber `
    -Repository $Repository

Info "PR: #$($prDetails.Number) - $($prDetails.Title)"
Info "  Author: $($prDetails.Author)"
Info "  Merge commit: $($prDetails.MergeCommitSha)"
Info "  Changed files: $($prDetails.Files.Count)"

# ╔══════════════════════════════════════════════════════════════════════════╗
# ║ Step 3: Discover Target Branches                                       ║
# ╚══════════════════════════════════════════════════════════════════════════╝

Write-StepHeader '3' 'Discovering target release branches'

if ($TargetBranches) {
    # Manual override - build branch objects
    $branches = @()
    foreach ($tb in $TargetBranches) {
        if ($tb -match 'release/(\d+)\.(\d+)-stable') {
            $branches += [PSCustomObject]@{
                Branch = $tb
                Major  = [int]$Matches[1]
                Minor  = [int]$Matches[2]
            }
        }
        else {
            Warn "Skipping unrecognized branch format: $tb"
        }
    }
}
else {
    $branches = & "$PSScriptRoot/Get-ServicingBranches.ps1" -ConfigPath $ConfigPath
}

if ($branches.Count -eq 0) {
    Err "No target branches found."
    exit 1
}

Info "Target branches ($($branches.Count)):"
foreach ($b in $branches) {
    Info "  - $($b.Branch)"
}

# ╔══════════════════════════════════════════════════════════════════════════╗
# ║ Load/Initialize State                                                   ║
# ╚══════════════════════════════════════════════════════════════════════════╝

$state = Get-ServicingState -PullRequestNumber $PullRequestNumber -RepoRoot $repoRoot

# Store PR details in state
$state.pullRequestNumber = $PullRequestNumber
if (-not $state.PSObject.Properties['prTitle']) {
    $state | Add-Member -NotePropertyName 'prTitle' -NotePropertyValue $prDetails.Title -Force
}
else {
    $state.prTitle = $prDetails.Title
}

# ╔══════════════════════════════════════════════════════════════════════════╗
# ║ Step 4: Process Each Branch                                            ║
# ╚══════════════════════════════════════════════════════════════════════════╝

$results = @()

foreach ($branchInfo in $branches) {
    $branch = $branchInfo.Branch
    $branchKey = $branch -replace '/', '_'

    Write-Host ""
    Write-Host ("*" * 70) -ForegroundColor Magenta
    Write-Host "  Processing: $branch" -ForegroundColor Magenta
    Write-Host ("*" * 70) -ForegroundColor Magenta

    # Check if this branch was already completed
    $branchState = $null
    if ($state.branches -is [hashtable] -and $state.branches.ContainsKey($branchKey)) {
        $branchState = $state.branches[$branchKey]
    }
    elseif ($state.branches.PSObject -and $state.branches.PSObject.Properties[$branchKey]) {
        $branchState = $state.branches.$branchKey
    }

    if ($null -ne $branchState -and $branchState.status -eq 'completed') {
        Ok "  Branch $branch already completed (PR: $($branchState.prUrl)). Skipping."
        $results += [PSCustomObject]@{
            Branch   = $branch
            Status   = 'skipped (already completed)'
            PrUrl    = $branchState.prUrl
            BugId    = $branchState.bugId
        }
        continue
    }

    # Initialize branch state
    $currentBranchState = @{
        status    = 'in_progress'
        startedAt = (Get-Date -Format 'o')
    }

    try {
        # ── 4a: Get Next Patch Version ──────────────────────────────────
        Write-StepHeader '4a' "Determining next patch version for $branch"

        $patchVersion = & "$PSScriptRoot/Get-NextPatchVersion.ps1" `
            -Branch $branch -Major $branchInfo.Major -Minor $branchInfo.Minor `
            -ConfigPath $ConfigPath

        Info "  Next version: $($patchVersion.VersionString) (symbol: $($patchVersion.Symbol))"
        $currentBranchState.patchVersion = $patchVersion.VersionString
        $currentBranchState.patchSymbol = $patchVersion.Symbol

        # ── 4b: AI - Generate Enum Name ─────────────────────────────────
        Write-StepHeader '4b' 'Generating enum name (AI)'

        $enumPromptTemplate = Get-Content -LiteralPath (Join-Path $PSScriptRoot '..\templates\enum-naming-prompt.md') -Raw
        $enumPrompt = $enumPromptTemplate
        $enumPrompt = $enumPrompt -replace '\{\{PR_TITLE\}\}', $prDetails.Title
        $enumPrompt = $enumPrompt -replace '\{\{PR_BODY\}\}', ($prDetails.Body | Select-Object -First 1)
        $changedFilesList = ($prDetails.Files | ForEach-Object { $_.Path }) -join ', '
        $enumPrompt = $enumPrompt -replace '\{\{CHANGED_FILES\}\}', $changedFilesList

        $enumNameArgs = @{
            Prompt           = $enumPrompt
            SystemPrompt     = 'Return ONLY a PascalCase_With_Underscores enum name. Nothing else.'
            FallbackToManual = $true
        }
        if ($RequireApproval) { $enumNameArgs['RequireApproval'] = $true }

        $enumName = Invoke-WithDryRun -Description "Generate enum name via AI" -DryRun:$DryRun -ScriptBlock {
            $result = & "$PSScriptRoot/Get-AiCompletion.ps1" @enumNameArgs
            return ($result -replace '[\r\n]', '' -replace '\s+', '').Trim()
        }

        if ($DryRun) { $enumName = 'DryRun_PlaceholderEnumName' }
        Info "  Enum name: $enumName"
        $currentBranchState.enumName = $enumName

        # ── 4c: AI - Generate ADO Bug Description ───────────────────────
        Write-StepHeader '4c' 'Generating ADO bug description (AI)'

        $adoPromptTemplate = Get-Content -LiteralPath (Join-Path $PSScriptRoot '..\templates\ado-bug-prompt.md') -Raw
        $adoPrompt = $adoPromptTemplate
        $adoPrompt = $adoPrompt -replace '\{\{PR_NUMBER\}\}', $prDetails.Number
        $adoPrompt = $adoPrompt -replace '\{\{PR_TITLE\}\}', $prDetails.Title
        $adoPrompt = $adoPrompt -replace '\{\{PR_BODY\}\}', $prDetails.Body
        $adoPrompt = $adoPrompt -replace '\{\{TARGET_BRANCH\}\}', $branch
        $adoPrompt = $adoPrompt -replace '\{\{VERSION_STRING\}\}', $patchVersion.VersionString
        $adoPrompt = $adoPrompt -replace '\{\{ENUM_NAME\}\}', $enumName

        $adoDescArgs = @{
            Prompt           = $adoPrompt
            SystemPrompt     = 'Return ONLY a valid JSON object with the specified fields. No markdown, no explanation.'
            FallbackToManual = $true
        }
        if ($RequireApproval) { $adoDescArgs['RequireApproval'] = $true }

        $adoFields = Invoke-WithDryRun -Description "Generate ADO bug fields via AI" -DryRun:$DryRun -ScriptBlock {
            $raw = & "$PSScriptRoot/Get-AiCompletion.ps1" @adoDescArgs
            # Extract JSON from the response (strip markdown fences if present)
            $jsonText = $raw -replace '(?s)^```json\s*', '' -replace '(?s)\s*```$', ''
            return ($jsonText | ConvertFrom-Json)
        }

        if ($DryRun) {
            $adoFields = [PSCustomObject]@{
                title           = "[$($patchVersion.VersionString) servicing] $($prDetails.Title)"
                description     = 'Dry run - no description generated'
                reproSteps      = ''
                customerImpact  = ''
                riskAssessment  = ''
            }
        }

        # ── 4d: Create ADO Bug ──────────────────────────────────────────
        Write-StepHeader '4d' 'Creating ADO servicing bug'

        $bugResult = $null
        if (-not $SkipAdoBugs) {
            $bugResult = & "$PSScriptRoot/New-AdoServicingBug.ps1" `
                -Title $adoFields.title `
                -Description $adoFields.description `
                -ReproSteps $adoFields.reproSteps `
                -CustomerImpact $adoFields.customerImpact `
                -RiskAssessment $adoFields.riskAssessment `
                -OriginalPrUrl $prDetails.Url `
                -TargetBranch $branch `
                -VersionString $patchVersion.VersionString `
                -EnumName $enumName `
                -ConfigPath $ConfigPath `
                -DryRun:$DryRun

            $currentBranchState.bugId = $bugResult.BugId
            $currentBranchState.bugUrl = $bugResult.Url
            Info "  Bug ID: $($bugResult.BugId)"
        }
        else {
            Info "  Skipping ADO bug creation (-SkipAdoBugs)"
            $currentBranchState.bugId = 0
        }

        $bugId = if ($bugResult) { $bugResult.BugId } else { 0 }

        # ── 4e: Create Worktree ─────────────────────────────────────────
        Write-StepHeader '4e' "Creating worktree for $branch"

        $slug = ConvertTo-BranchSlug -Title $prDetails.Title
        $branchName = Format-BranchName -Pattern $config.naming.branchPattern -Values @{
            author  = $prDetails.Author
            slug    = $slug
            version = "$($branchInfo.Major).$($branchInfo.Minor)"
        }

        $worktree = Invoke-WithDryRun -Description "Create worktree on $branch" -DryRun:$DryRun -ScriptBlock {
            & "$PSScriptRoot/New-ServicingWorktree.ps1" `
                -Branch $branch `
                -BranchName $branchName `
                -PullRequestNumber $PullRequestNumber `
                -RepoRoot $repoRoot
        }

        if ($DryRun) {
            $worktree = [PSCustomObject]@{
                WorktreePath = Join-Path $repoRoot "Generated Files/servicing/$PullRequestNumber/worktree-$($branchInfo.Major).$($branchInfo.Minor)"
                BranchName   = $branchName
            }
        }

        $currentBranchState.worktreePath = $worktree.WorktreePath
        $currentBranchState.branchName = $branchName

        # ── 4f: Cherry-Pick ─────────────────────────────────────────────
        Write-StepHeader '4f' "Cherry-picking $($prDetails.MergeCommitSha)"

        $cpResult = Invoke-WithDryRun -Description "Cherry-pick merge commit" -DryRun:$DryRun -ScriptBlock {
            & "$PSScriptRoot/Invoke-CherryPick.ps1" `
                -WorktreePath $worktree.WorktreePath `
                -MergeCommitSha $prDetails.MergeCommitSha
        }

        if (-not $DryRun -and $cpResult -and $cpResult.HasConflicts) {
            Warn "Cherry-pick has conflicts. AI will attempt to resolve them during containment wrapping."
            # Abort the cherry-pick so AI can work with the files
            git -C $worktree.WorktreePath cherry-pick --abort 2>$null | Out-Null
        }

        # ── 4g: AI - Containment Wrapping ───────────────────────────────
        Write-StepHeader '4g' 'Applying containment wrapping (AI)'

        $containmentResult = Invoke-WithDryRun -Description "Apply containment wrapping via AI" -DryRun:$DryRun -ScriptBlock {
            & "$PSScriptRoot/Add-ContainmentWrapping.ps1" `
                -WorktreePath $worktree.WorktreePath `
                -OriginalDiff $prDetails.Diff `
                -BugId $bugId `
                -PatchVersionSymbol $patchVersion.Symbol `
                -VersionString $patchVersion.VersionString `
                -PrTitle $prDetails.Title `
                -RequireApproval:$RequireApproval
        }

        # ── 4h: Update IDL ──────────────────────────────────────────────
        Write-StepHeader '4h' 'Updating RuntimeCompatibilityOptions.idl'

        $idlResult = Invoke-WithDryRun -Description "Insert enum entry into IDL" -DryRun:$DryRun -ScriptBlock {
            & "$PSScriptRoot/Update-RuntimeCompatibilityIdl.ps1" `
                -WorktreePath $worktree.WorktreePath `
                -EnumName $enumName `
                -BugId $bugId `
                -VersionString $patchVersion.VersionString `
                -ConfigPath $ConfigPath
        }

        # ── 4i: AI - Generate PR Body ───────────────────────────────────
        Write-StepHeader '4i' 'Generating PR body summary'

        # The template-based PR body is sufficient; AI enhancement is optional
        $prBody = $null  # Will use template default in New-ServicingPullRequest

        # ── 4j: Create GitHub PR ────────────────────────────────────────
        Write-StepHeader '4j' 'Creating GitHub pull request'

        $prResult = & "$PSScriptRoot/New-ServicingPullRequest.ps1" `
            -WorktreePath $worktree.WorktreePath `
            -BranchName $branchName `
            -TargetBranch $branch `
            -OriginalPrNumber $prDetails.Number `
            -OriginalPrTitle $prDetails.Title `
            -BugId $bugId `
            -VersionString $patchVersion.VersionString `
            -EnumName $enumName `
            -Repository $Repository `
            -ConfigPath $ConfigPath `
            -DryRun:$DryRun

        $currentBranchState.prNumber = $prResult.PrNumber
        $currentBranchState.prUrl = $prResult.PrUrl

        # ── 4k: Update ADO Bug with PR Link ─────────────────────────────
        if ($bugId -and $bugId -ne 0 -and -not $DryRun -and -not $SkipAdoBugs) {
            Write-StepHeader '4k' 'Linking PR to ADO bug'

            $linkArgs = @(
                'boards', 'work-item', 'relation', 'add',
                '--org', $config.ado.organization,
                '--id', $bugId,
                '--relation-type', 'Hyperlink',
                '--target-url', $prResult.PrUrl,
                '--output', 'none'
            )
            $null = az @linkArgs 2>&1
            if ($LASTEXITCODE -ne 0) {
                Warn "  Could not link PR to ADO bug $bugId (non-critical)."
            }
            else {
                Ok "  ADO bug $bugId linked to $($prResult.PrUrl)"
            }
        }

        # ── 4l: Save Checkpoint ─────────────────────────────────────────
        $currentBranchState.status = 'completed'
        $currentBranchState.completedAt = (Get-Date -Format 'o')

        # Update state
        if ($state.branches -is [hashtable]) {
            $state.branches[$branchKey] = $currentBranchState
        }
        else {
            $state.branches | Add-Member -NotePropertyName $branchKey -NotePropertyValue $currentBranchState -Force
        }
        Save-ServicingState -State $state -RepoRoot $repoRoot

        $results += [PSCustomObject]@{
            Branch   = $branch
            Status   = 'completed'
            PrUrl    = $prResult.PrUrl
            BugId    = $bugId
        }

        Ok "Branch $branch completed successfully!"

    }
    catch {
        Err "Error processing $branch`: $($_.Exception.Message)"

        $currentBranchState.status = 'failed'
        $currentBranchState.error = $_.Exception.Message

        if ($state.branches -is [hashtable]) {
            $state.branches[$branchKey] = $currentBranchState
        }
        else {
            $state.branches | Add-Member -NotePropertyName $branchKey -NotePropertyValue $currentBranchState -Force
        }
        Save-ServicingState -State $state -RepoRoot $repoRoot

        $results += [PSCustomObject]@{
            Branch   = $branch
            Status   = "failed: $($_.Exception.Message)"
            PrUrl    = ''
            BugId    = 0
        }

        Warn "Saved state. Re-run the command to retry this branch."
        continue
    }
}

# ╔══════════════════════════════════════════════════════════════════════════╗
# ║ Step 5: Summary Report                                                 ║
# ╚══════════════════════════════════════════════════════════════════════════╝

Write-Host ""
Write-Host ("=" * 70) -ForegroundColor Green
Write-Host "  SERVICING SUMMARY - PR #$PullRequestNumber" -ForegroundColor Green
Write-Host ("=" * 70) -ForegroundColor Green
Write-Host ""
Write-Host "  PR: $($prDetails.Title)" -ForegroundColor White
Write-Host "  Author: $($prDetails.Author)" -ForegroundColor White
Write-Host ""

foreach ($r in $results) {
    $statusColor = if ($r.Status -eq 'completed') { 'Green' } elseif ($r.Status -like 'skipped*') { 'Yellow' } else { 'Red' }
    Write-Host "  $($r.Branch)" -ForegroundColor White -NoNewline
    Write-Host " - $($r.Status)" -ForegroundColor $statusColor
    if ($r.PrUrl) { Write-Host "    PR: $($r.PrUrl)" -ForegroundColor Cyan }
    if ($r.BugId -and $r.BugId -ne 0) { Write-Host "    Bug: $($r.BugId)" -ForegroundColor Cyan }
}

Write-Host ""
Write-Host ("=" * 70) -ForegroundColor Green

if ($DryRun) {
    Write-Host ""
    Warn "This was a DRY RUN. No changes were made."
}

$stateDir = Get-ServicingStateDir -PullRequestNumber $PullRequestNumber -RepoRoot $repoRoot
Info "State saved to: $stateDir/state.json"

exit 0
