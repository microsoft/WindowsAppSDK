<#
.SYNOPSIS
    Resolve all unresolved review threads for a PR.

.PARAMETER PRNumber
    PR number to resolve.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [int]$PRNumber
)

$repoRoot = Resolve-Path (Join-Path $PSScriptRoot '..\..\..\..')
Set-Location $repoRoot

$slug = gh repo view --json nameWithOwner --jq .nameWithOwner 2>$null
$Owner, $Repo = $slug -split '/'

$query = "query { repository(owner:`"$Owner`", name:`"$Repo`") { pullRequest(number:" + $PRNumber + ') { reviewThreads(first:100) { nodes { id isResolved } } } } }'
$threads = gh api graphql -f query=$query --jq '.data.repository.pullRequest.reviewThreads.nodes[] | select(.isResolved==false) | .id'

foreach ($threadId in $threads) {
    $mutation = 'mutation { resolveReviewThread(input:{threadId:"' + $threadId + '"}) { thread { isResolved } } }'
    gh api graphql -f query=$mutation | Out-Null
}

$threadsAfter = gh api graphql -f query=$query --jq '.data.repository.pullRequest.reviewThreads.nodes[] | select(.isResolved==false) | .id'

if ($threadsAfter) {
    Write-Warning "Unresolved threads remain for PR #$PRNumber"
} else {
    Write-Host "All threads resolved for PR #$PRNumber"
}