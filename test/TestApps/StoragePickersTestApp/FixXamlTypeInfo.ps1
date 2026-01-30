# Fix XAML code generator bug: remove self-referential XamlMetaDataProvider from OtherProviders
# The generated XamlTypeInfo.g.cpp incorrectly adds the app's own XamlMetaDataProvider to _otherProviders,
# causing infinite recursion during type lookup.

param(
    [Parameter(Mandatory=$true)]
    [string]$FilePath
)

if (-not (Test-Path $FilePath)) {
    Write-Host "File not found: $FilePath"
    exit 0
}

$content = Get-Content $FilePath -Raw
$pattern = '_otherProviders\.push_back\(::winrt::StoragePickersTestApp::XamlMetaDataProvider\(\)\);'
$replacement = '// Removed self-reference to avoid infinite recursion'

if ($content -match $pattern) {
    $content = $content -replace $pattern, $replacement
    Set-Content $FilePath -Value $content -NoNewline
    Write-Host "Fixed: Removed self-referential XamlMetaDataProvider from OtherProviders"
} else {
    Write-Host "Pattern not found or already fixed"
}
