# BanglaScript CLI Guide

The **BanglaScript CLI** (`banglascript` or alias `bs`) is a standalone, high-performance command-line tool built in C++17.

---

## Command Reference

### 1. Execute a Program (`run`)
Compiles the specified `.bs` file and executes it directly inside the TAC Virtual Machine.

```bash
banglascript run program.bs
# or using short alias:
bs run program.bs
```

### 2. Syntax & Semantic Check (`check`)
Validates lexical tokens, grammar rules, symbol tables, and type consistency without executing the program.

```bash
banglascript check program.bs
```

### 3. Pipeline Verification (`compile`)
Executes all compiler stages and prints progress indicators:

```bash
banglascript compile program.bs
```

Output:
```text
Compiling: program.bs

[OK] Lexer
[OK] Parser
[OK] Semantic Analysis & Type Checking
[OK] TAC Generation (10 instructions)
[OK] Optimization (10 instructions)

Compilation successful.
```

### 4. Abstract Syntax Tree (`ast`)
Generates an ASCII visualization of the Abstract Syntax Tree.

```bash
banglascript ast program.bs
```

### 5. Three-Address Code (`tac`)
Displays intermediate representation quadruples:

```bash
# Raw TAC
banglascript tac program.bs

# Optimized TAC (constant folded & dead code eliminated)
banglascript tac program.bs --opt
```

### 6. Interactive REPL (`repl`)
Starts an interactive multiline session supporting expression evaluation:

```bash
banglascript repl
```

Commands available in REPL:
- `.help` — Show command overview
- `.keywords` — Cheat sheet of keywords
- `.clear` — Clear terminal screen
- `.exit` — Quit REPL

### 7. Project Scaffolding (`init`)
Creates a structured project with `src/main.bs`, unit tests, configuration, and documentation:

```bash
banglascript init my-app
```

### 8. Environment Doctor (`doctor`)
Verifies compiler toolchain health, OS platform details, and console UTF-8 readiness:

```bash
banglascript doctor
```
