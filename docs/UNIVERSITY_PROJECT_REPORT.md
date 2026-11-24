# Academic Project Report: Design & Implementation of BanglaScript Compiler and Virtual Machine

**Course:** Compiler Design & Engineering  
**Project Title:** NEXORA: The BanglaScript Programming Language Ecosystem  
**Target Platform:** Windows 10/11 x64 (Cross-Platform Ready for Linux/macOS)  
**Tools & Technologies:** Flex (win_flex), GNU Bison (win_bison), C++17, CMake  

---

## Abstract
This project presents the design and implementation of **BanglaScript**, a statically typed, structured programming language with custom syntax supporting transliterated ASCII keywords and native Bengali Unicode script. Built on a modular C++17 architecture, the compiler pipeline features lexical analysis via Flex, LALR(1) parsing using GNU Bison, AST generation, scoped symbol table management, static type checking, Three-Address Code (TAC) generation, compile-time optimization passes (constant folding, constant propagation, and dead code elimination), and execution on a custom stack-based TAC Virtual Machine. The ecosystem includes a standalone CLI (`banglascript` / `bs`), interactive REPL, and a Visual Studio Code language extension.

---

## 1. System Architecture & Compiler Pipeline

The compiler follows the classical multi-phase compiler pipeline:

```text
Source Code (.bs)
   │
   ▼
[ Phase 1: Lexical Analyzer (Flex) ] ──> Token Stream with line & column coordinates
   │
   ▼
[ Phase 2: Syntax Analyzer (GNU Bison) ] ──> Abstract Syntax Tree (AST)
   │
   ▼
[ Phase 3: Semantic Analyzer ] ──> Multi-Scope Symbol Table & Type Checking
   │
   ▼
[ Phase 4: Intermediate Code Generator ] ──> Three-Address Code (TAC Quadruples)
   │
   ▼
[ Phase 5: Code Optimizer ] ──> Constant Folding, Propagation, DCE
   │
   ▼
[ Phase 6: TAC Virtual Machine ] ──> Execution & Standard Output
```

---

## 2. Phase 1: Lexical Analysis (Tokenization)

The lexical analyzer is specified in `compiler/lexer/scanner.l` and processed by Flex.

### 2.1 Keyword Specification
| Keyword (ASCII) | Keyword (Bengali) | Token Type | Description |
| :--- | :--- | :--- | :--- |
| `sonkha` | `সংখ্যা` | `TOKEN_TYPE_SONKHA` | 64-bit integer type |
| `dosomik` | `দশমিক` | `TOKEN_TYPE_DOSOMIK` | 64-bit float type |
| `bakya` | `বাক্য` | `TOKEN_TYPE_BAKYA` | String type |
| `sotti` | `সত্যি` | `TOKEN_TYPE_SOTTI` | Boolean type |
| `shunno` | `শূন্য` | `TOKEN_TYPE_SHUNNO` | Void type |
| `jodi` | `যদি` | `TOKEN_JODI` | Conditional if |
| `nahole` | `নাহলে` | `TOKEN_NAHOLE` | Conditional else |
| `jotokhon` | `যতক্ষণ` | `TOKEN_JOTOKHON` | While loop |
| `bondho` | `বন্ধ` | `TOKEN_BONDHO` | Loop break |
| `chaliyejao` | `চালিয়েযাও` | `TOKEN_CHALIYEJAO` | Loop continue |
| `kaj` | `কাজ` | `TOKEN_KAJ` | Function declaration |
| `ferot` | `ফেরত` | `TOKEN_FEROT` | Return statement |
| `dekhao` | `দেখাও` | `TOKEN_DEKHAO` | Standard output |
| `nao` | `নাও` | `TOKEN_NAO` | Standard input |

### 2.2 Numerical & Unicode Support
The lexer natively decodes both ASCII digits (`0-9`) and Bengali numerals (`০-৯`) directly into 64-bit signed integers.

---

## 3. Phase 2: Syntax Analysis & Grammar (GNU Bison)

The grammar is specified in `compiler/parser/parser.y` as an unambiguous LALR(1) Context-Free Grammar (CFG).

### 3.1 Operator Precedence & Associativity
```yacc
%nonassoc LOWER_THAN_ELSE
%nonassoc TOKEN_NAHOLE
%right TOKEN_ASSIGN
%left TOKEN_OR
%left TOKEN_AND
%left TOKEN_EQ TOKEN_NEQ
%left TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_STAR TOKEN_SLASH TOKEN_PERCENT
%right TOKEN_NOT UMINUS
```

### 3.2 CFG Production Rules (Excerpt)
```bnf
<program>        ::= <items>
<item>           ::= <function_decl> | <statement>
<var_decl>       ::= <type> IDENTIFIER ';' | <type> IDENTIFIER '=' <expression> ';'
<if_stmt>        ::= 'jodi' '(' <expression> ')' <statement>
                   | 'jodi' '(' <expression> ')' <statement> 'nahole' <statement>
<while_stmt>     ::= 'jotokhon' '(' <expression> ')' <statement>
<func_decl>      ::= 'kaj' <type> IDENTIFIER '(' <param_list> ')' <block>
                   | 'kaj' IDENTIFIER '(' <param_list> ')' <block>
<expression>     ::= IDENTIFIER '=' <expression>
                   | <expression> '+' <expression>
                   | <expression> '-' <expression>
                   | <expression> '*' <expression>
                   | <expression> '/' <expression>
                   | IDENTIFIER '(' <arg_list> ')'
                   | IDENTIFIER | LITERAL
```

---

## 4. Phase 3: Semantic Analysis & Symbol Table

The `TypeChecker` traverses the AST to enforce static semantics:
1. **Scope Hierarchy:** Employs a scoped symbol table supporting lexical nesting.
2. **Duplicate Declaration Trap:** Prevents re-declaring variables within the same scope.
3. **Undeclared Variable Trap:** Ensures all identifiers are defined before utilization.
4. **Type Compatibility:** Verifies assignments and arithmetic operations.
5. **Control-Flow Context:** Enforces that `bondho` and `chaliyejao` only occur inside active loops.

---

## 5. Phase 4: Intermediate Code Generation (Three-Address Code)

Intermediate representations translate high-level control structures and expressions into linear quadruples:

### Sample Translation
**BanglaScript Source:**
```javascript
sonkha a = 15;
sonkha b = 25;
sonkha c = a + b * 2;
dekhao(c);
```

**Generated Three-Address Code:**
```text
  t0 = 15
  a = t0
  t1 = 25
  b = t1
  t2 = 2
  t3 = b * t2
  t4 = a + t3
  c = t4
  print c
  halt
```

---

## 6. Phase 5: Code Optimization

The compiler applies three optimization passes:
1. **Constant Folding:** Evaluates static expressions at compile time ($b * 2$ where $b=25$ folds to $50$).
2. **Constant Propagation:** Propagates known constants forward into subsequent statements.
3. **Dead Code Elimination (DCE):** Removes instructions made redundant after unconditional branches or assignments.

---

## 7. Phase 6: TAC Virtual Machine

The custom virtual machine in `runtime/src/VirtualMachine.cpp` executes TAC instructions:
- **Stack Frames:** Allocates activation records for function parameters and local variables.
- **Recursion Safety:** Safeguards against stack overflow (depth capped at 10,000).
- **Infinite Loop Protection:** Enforces instruction limits ($10^7$ steps) with diagnostics.
- **Division-by-Zero Trap:** Catches runtime math errors and displays formatted diagnostic reports.

---

## 8. Experimental Results & Verification

All test suites and sample programs compile and execute cleanly on Windows 10/11:

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

## 9. Conclusion
The **NEXORA BanglaScript** compiler satisfies all university requirements for the Compiler Design course, demonstrating real-world software engineering practices, formal language theory, robust error diagnostics, and a working runtime ecosystem.
