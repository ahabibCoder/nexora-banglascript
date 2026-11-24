# BanglaScript Language Support for Visual Studio Code

Official Visual Studio Code extension for the **BanglaScript** programming language and the **NEXORA** ecosystem.

## Features

- **Syntax Highlighting:** Full TextMate grammar for all BanglaScript types (`sonkha`, `dosomik`, `bakya`, `sotti`, `shunno`), keywords (`jodi`, `nahole`, `jotokhon`, `kaj`, `ferot`), built-in I/O (`dekhao`, `nao`), and their native Bengali script counterparts (`সংখ্যা`, `দশমিক`, `যদি`, `দেখাও`, etc.).
- **Live Diagnostics:** Automatically reports syntax and semantic errors on save with line and column highlighting.
- **One-Click Run:** Dedicated "Run" button in editor title bar to execute `.bs` programs in the integrated terminal using `banglascript run`.
- **AST & TAC Visualizer:** Commands to view the Abstract Syntax Tree and Three-Address Code in side-by-side webview panels.
- **Snippets:** Complete code snippets for quick scaffolding.

## Commands

- `BanglaScript: Run Current File`
- `BanglaScript: Check Syntax & Types`
- `BanglaScript: Compile Current File`
- `BanglaScript: Show Abstract Syntax Tree (AST)`
- `BanglaScript: Show Three-Address Code (TAC)`

## Installation

### Option 1: Command Line (Fastest)
```bash
code --install-extension banglascript-language-support-1.0.0.vsix
```

### Option 2: Within VS Code UI
1. Open Visual Studio Code.
2. Press `Ctrl+Shift+X` (or `Cmd+Shift+X` on macOS) to open the Extensions tab.
3. Click the `...` menu (top right of Extensions view) and select **Install from VSIX...**
4. Select `banglascript-language-support-1.0.0.vsix` from this repository.
5. Reload VS Code or open any `.bs` file!

## Requirements

Install the BanglaScript CLI on your machine and ensure `banglascript` (or `bs`) is in your `PATH`.
