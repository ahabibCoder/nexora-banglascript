# BanglaScript Windows Installer Script (PowerShell)
# Automatically registers banglascript & bs in User PATH

$ErrorActionPreference = "Stop"

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectRoot = Split-Path -Parent (Split-Path -Parent $scriptDir)
$binDir = Join-Path $projectRoot "build\bin"

if (-not (Test-Path (Join-Path $binDir "banglascript.exe"))) {
    Write-Host "[ERROR] banglascript.exe not found in $binDir. Please build the project first." -ForegroundColor Red
    exit 1
}

$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($userPath -split ";" -notcontains $binDir) {
    Write-Host "[INFO] Adding $binDir to User PATH..." -ForegroundColor Cyan
    $newPath = "$userPath;$binDir"
    [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
    $env:Path = "$env:Path;$binDir"
    Write-Host "[SUCCESS] Added to PATH successfully!" -ForegroundColor Green
} else {
    Write-Host "[INFO] $binDir is already present in User PATH." -ForegroundColor Yellow
}

Write-Host "`n========================================================" -ForegroundColor Green
Write-Host "   BanglaScript Installation Verified Successfully!     " -ForegroundColor Green
Write-Host "========================================================`n" -ForegroundColor Green

& (Join-Path $binDir "banglascript.exe") --version

# Automatically install VS Code extension if VS Code CLI is available
$vsixPath = Join-Path $projectRoot "editors\vscode-banglascript\banglascript-language-support-1.0.0.vsix"
if ((Get-Command "code" -ErrorAction SilentlyContinue) -and (Test-Path $vsixPath)) {
    Write-Host "`n[INFO] Detected VS Code. Installing BanglaScript extension..." -ForegroundColor Cyan
    try {
        & code --install-extension $vsixPath --force
        Write-Host "[SUCCESS] VS Code extension installed successfully!" -ForegroundColor Green
    } catch {
        Write-Host "[NOTE] To install VS Code extension manually, run: code --install-extension $vsixPath" -ForegroundColor Yellow
    }
}

Write-Host "`nYou can now open any terminal and run:" -ForegroundColor Cyan
Write-Host "  banglascript --help" -ForegroundColor White
Write-Host "  bs repl" -ForegroundColor White
Write-Host "  banglascript run hello.bs`n" -ForegroundColor White
