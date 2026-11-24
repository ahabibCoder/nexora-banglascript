# NEXORA — BanglaScript Programming Language Ecosystem

**Tagline:** Beyond the Ordinary  
**Language:** BanglaScript  
**File Extension:** `.bs`  
**CLI Executable:** `banglascript` (Short alias: `bs`)  
**VS Code Extension:** BanglaScript Language Support (`.vsix`)  

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Language](https://img.shields.io/badge/language-BanglaScript-blue.svg)]()
[![Compiler](https://img.shields.io/badge/core-C%2B%2B17-orange.svg)]()
[![Lexer](https://img.shields.io/badge/lexer-Flex-yellow.svg)]()
[![Parser](https://img.shields.io/badge/parser-GNU%20Bison-purple.svg)]()
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

---

## 🌟 Overview

**BanglaScript** is a modern, statically typed, structured programming language with custom grammar supporting both transliterated Latin keywords and native Bengali Unicode script.

Unlike JavaScript-based transpilers, BanglaScript features its own independent native compiler architecture written in C++17, compiling code through a classical multi-stage pipeline into Three-Address Code (TAC), optimizing it, and executing it on a custom stack-based Virtual Machine.

```text
Source Code (.bs)
       │
       ▼
[ Lexical Analyzer (Flex) ] ──────> Token Stream (Line & Column tracking)
       │
       ▼
[ Syntax Analyzer (Bison) ] ──────> Abstract Syntax Tree (AST)
       │
       ▼
[ Semantic Analyzer ]       ──────> Multi-Scope Symbol Table & Type Checking
       │
       ▼
[ TAC Generator ]           ──────> Three-Address Code Quadruples
       │
       ▼
[ Optimizer Engine ]        ──────> Constant Folding, Propagation & DCE
       │
       ▼
[ TAC Virtual Machine ]     ──────> Program Execution & Output
```

---

## 🚀 Quick Start (Windows)

### 1. Build the Project
Open PowerShell in the project directory:

```powershell
cmake -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
cmake --build build
```

This compiles:
- `build/bin/banglascript.exe` — The full compiler and runtime CLI
- `build/bin/bs.exe` — Convenient short command alias
- `build/bin/banglascript_tests.exe` — Automated test suite

### 2. 1-Click Install to System PATH
Run the installer script:
```powershell
.\installers\windows\install.bat
```
Now `banglascript` and `bs` are available globally from any PowerShell or CMD terminal!

---

## 💻 Running BanglaScript Programs

### Example: `hello.bs`
```javascript
sonkha a = 10;
sonkha b = 20;

sonkha result = a + b;

dekhao("Hello from BanglaScript!");
dekhao(result);
```

### Execute:
```bash
banglascript run examples/01_hello.bs
```

Output:
```text
Hello from BanglaScript!
30
```

---

## 🛠️ CLI Features

| Command | Action |
| :--- | :--- |
| `banglascript run <file.bs>` | Compile and run program in the Virtual Machine |
| `banglascript check <file.bs>`| Validate syntax and types without running |
| `banglascript compile <file.bs>`| Verify all compiler stages (`[OK] Lexer`, `[OK] Parser`, etc.) |
| `banglascript ast <file.bs>` | Print formatted ASCII Abstract Syntax Tree |
| `banglascript tac <file.bs>` | Print Three-Address Code (`--opt` for optimized) |
| `banglascript repl` | Start interactive multiline REPL session |
| `banglascript init <name>` | Scaffold a new project structure |
| `banglascript doctor` | Check environment and UTF-8 console health |

---

## 💻 Interactive REPL

```bash
banglascript repl
```

```text
bs> sonkha x = 15;
bs> sonkha y = 25;
bs> dekhao(x + y);
40
bs> .help
bs> .keywords
bs> .exit
```

---

## 🧩 Visual Studio Code & Multi-IDE Support

BanglaScript is designed to work in any code editor or IDE of your choice:

### 1. Visual Studio Code / Cursor / Windsurf
A full-featured extension is pre-packaged in `editors/vscode-banglascript/`.

**CLI Install:**
```bash
code --install-extension editors/vscode-banglascript/banglascript-language-support-1.0.0.vsix
```

**Manual Install in VS Code:**
1. Open Extensions (`Ctrl+Shift+X`).
2. Click the `...` menu at top right and choose **Install from VSIX...**
3. Select `editors/vscode-banglascript/banglascript-language-support-1.0.0.vsix`.

**Features:**
- **Syntax Highlighting:** TextMate grammar for types, keywords, and Bengali script.
- **Live Diagnostics:** Errors and warnings shown with squiggles on save.
- **Run Button:** Direct execution inside integrated terminal.
- **AST & TAC Visualizer:** Inspect generated AST and TAC in split webview panes.
- **Snippets:** Built-in code templates for quick scaffolding.

### 2. Built-in NEXORA Graphical IDE
For quick editing without installing external editors:
```bash
# Windows double-click:
Launch_NEXORA_IDE.bat

# Or run directly via Python:
python ide/nexora_ide.py
```

### 3. JetBrains IDEs (CLion, IntelliJ IDEA, PyCharm, WebStorm)
1. Go to `Settings -> Editor -> TextMate Bundles`.
2. Click `+` and add the `editors/vscode-banglascript` folder.
3. Open any `.bs` file with full syntax highlighting.

### 4. Sublime Text
Copy `editors/sublime-text/BanglaScript.sublime-syntax` into your Sublime Text `Packages/BanglaScript/` directory.

### 5. Vim / Neovim
Copy syntax and filetype detection files:
```bash
cp editors/vim/syntax/banglascript.vim ~/.vim/syntax/
cp editors/vim/ftdetect/banglascript.vim ~/.vim/ftdetect/
```

### 6. Notepad++
Import `editors/notepadplusplus/banglascript.xml` via **Language -> User Defined Language -> Define your language... -> Import**.

---

## 🧪 Automated Testing

Execute the test suite verifying all compiler phases:

```bash
.\build\bin\banglascript_tests.exe
```

Output:
```text
============================================
   BanglaScript Automated Test Suite        
============================================

[TEST] Running Basic Arithmetic & VM Execution... PASSED
[TEST] Running Control Flow & While Loop... PASSED
[TEST] Running Recursive Factorial Function... PASSED
[TEST] Running Native Bengali Script Keywords... PASSED
[TEST] Running Semantic Error Diagnostics... PASSED
[TEST] Running TAC Optimizer (Constant Folding)... PASSED

>>> ALL 6 TEST SUITES PASSED CLEANLY! <<<
```

---

## 📚 Documentation

- [Language Specification](docs/LANGUAGE_SPEC.md)
- [CLI Reference Guide](docs/CLI_GUIDE.md)
- [Virtual Machine Architecture](docs/VM_DESIGN.md)
- [University Project Report](docs/UNIVERSITY_PROJECT_REPORT.md)
