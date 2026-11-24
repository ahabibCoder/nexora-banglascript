# BanglaScript Language Specification (v1.0.0)

**BanglaScript** is a modern, statically typed, structured programming language designed for clarity, educational excellence, and native computational power.

---

## 1. Lexical Structure

### 1.1 Source Encoding
Source files must be encoded in **UTF-8**. File extension is `.bs`.

### 1.2 Comments
- **Single-line Comments:** Begins with `//` and extends to the end of the line.
- **Multi-line Comments:** Enclosed within `/*` and `*/`.

```javascript
// This is a single-line comment
/*
   This is a multi-line comment in BanglaScript
*/
```

### 1.3 Whitespace
Whitespace (spaces, tabs, newlines) serves as token delimiters and is otherwise ignored except within string literals.

---

## 2. Type System

BanglaScript enforces strict static typing at compile time.

| Type Keyword (Transliterated) | Type Keyword (Bengali Script) | Description | Internal Representation |
| :--- | :--- | :--- | :--- |
| `sonkha` | `সংখ্যা` | 64-bit signed integer | `int64_t` |
| `dosomik` | `দশমিক` | 64-bit IEEE 754 floating point | `double` |
| `bakya` | `বাক্য` | UTF-8 encoded string | `std::string` |
| `sotti` | `সত্যি` | Boolean (`true` / `false`) | `bool` |
| `shunno` | `শূন্য` | Void / Absence of return value | `void` |

---

## 3. Keywords & Identifiers

### 3.1 Reserved Keywords
Both English transliteration (standard CLI/keyboard) and native Bengali script keywords are recognized interchangeably by the lexer:

| English Transliteration | Bengali Script | Semantic Role |
| :--- | :--- | :--- |
| `sonkha` | `সংখ্যা` | Integer type specifier |
| `dosomik` | `দশমিক` | Floating point type specifier |
| `bakya` | `বাক্য` | String type specifier |
| `sotti` | `সত্যি` | Boolean type specifier |
| `shunno` | `শূন্য` | Void return specifier |
| `jodi` | `যদি` | Conditional `if` branch |
| `nahole` | `নাহলে` | Conditional `else` branch |
| `jotokhon` | `যতক্ষণ` | `while` loop iteration |
| `bondho` | `বন্ধ` | `break` loop termination |
| `chaliyejao` | `চালিয়েযাও` | `continue` next iteration |
| `kaj` | `কাজ` | Function declaration |
| `ferot` | `ফেরত` | Function `return` statement |
| `dekhao` | `দেখাও` | Standard output statement |
| `nao` | `নাও` | Standard input statement |
| `true` / `sotti` | `সত্য` / `সত্যি` | Boolean true literal |
| `false` / `mittha` | `মিথ্যা` | Boolean false literal |

### 3.2 Identifiers
Identifiers must start with an ASCII letter (`a-z`, `A-Z`), underscore (`_`), or a Bengali Unicode letter (`\u0985`–`\u09B9`), followed by letters, digits (`0-9` or `০-৯`), or underscores.

---

## 4. Operators and Precedence

Listed from highest to lowest precedence:

1. **Primary Expressions:** Literals, Variables, Parenthesized Expressions `( )`, Function Calls `f(...)`
2. **Unary Operators:** Negative `-`, Logical NOT `!` / `na`
3. **Multiplicative:** Multiplication `*`, Division `/`, Modulo `%`
4. **Additive:** Addition `+`, Subtraction `-`, String Concatenation `+`
5. **Relational:** Less Than `<`, Less or Equal `<=`, Greater Than `>`, Greater or Equal `>=`
6. **Equality:** Equal `==`, Not Equal `!=`
7. **Logical AND:** `&&` / `ebong`
8. **Logical OR:** `||` / `othoba`
9. **Assignment:** `=`

---

## 5. Grammar & Syntax Examples

### 5.1 Variable Declarations & Scope
```javascript
sonkha age = 22;
dosomik gpa = 3.85;
bakya name = "Hujaifa";
sotti isEnrolled = true;

{
    // Nested scope: variable shadowing is legal but isolated
    sonkha age = 30;
    dekhao(age); // prints 30
}
dekhao(age); // prints 22
```

### 5.2 Control Flow
```javascript
sonkha score = 85;

jodi (score >= 90) {
    dekhao("Grade: A+");
} nahole jodi (score >= 80) {
    dekhao("Grade: A");
} nahole {
    dekhao("Grade: Other");
}
```

### 5.3 Loops with Break and Continue
```javascript
sonkha count = 0;

jotokhon (count < 10) {
    count = count + 1;
    jodi (count == 3) {
        chaliyejao; // continue
    }
    jodi (count == 8) {
        bondho; // break
    }
    dekhao(count);
}
```

### 5.4 Functions & Recursion
```javascript
kaj jog(sonkha a, sonkha b) {
    ferot a + b;
}

kaj factorial(sonkha n) {
    jodi (n <= 1) {
        ferot 1;
    }
    ferot n * factorial(n - 1);
}

sonkha res = factorial(5);
dekhao(res); // prints 120
```

---

## 6. Standard Library & Built-in I/O

- `dekhao(expr);` — Prints value followed by a newline to standard output.
- `nao(variable);` — Reads a value corresponding to the variable's type from standard input.
