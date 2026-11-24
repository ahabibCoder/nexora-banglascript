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

## Requirements

Install the BanglaScript CLI on your machine and ensure `banglascript` is in your `PATH`.
