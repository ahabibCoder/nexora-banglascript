# TAC Virtual Machine (VM) Specification

The **BanglaScript Virtual Machine** executes Three-Address Code (TAC) intermediate representation directly, providing isolation, cross-platform deterministic output, and bounds checking.

---

## 1. Instruction Set Architecture (ISA)

| Opcode | Quadruple Format | Description |
| :--- | :--- | :--- |
| `ASSIGN` | `result = arg1` | Copy value or literal into variable / temporary |
| `ADD` | `result = arg1 + arg2` | Numeric addition or string concatenation |
| `SUB` | `result = arg1 - arg2` | Numeric subtraction |
| `MUL` | `result = arg1 * arg2` | Numeric multiplication |
| `DIV` | `result = arg1 / arg2` | Numeric division with zero-division trap |
| `MOD` | `result = arg1 % arg2` | Integer remainder with zero-division trap |
| `NEG` | `result = -arg1` | Unary negation |
| `NOT` | `result = !arg1` | Unary logical inversion |
| `EQ` | `result = arg1 == arg2`| Equality comparison |
| `NEQ` | `result = arg1 != arg2`| Inequality comparison |
| `LT` | `result = arg1 < arg2` | Less than comparison |
| `LE` | `result = arg1 <= arg2`| Less than or equal comparison |
| `GT` | `result = arg1 > arg2` | Greater than comparison |
| `GE` | `result = arg1 >= arg2`| Greater than or equal comparison |
| `AND` | `result = arg1 && arg2`| Logical conjunction |
| `OR` | `result = arg1 \|\| arg2`| Logical disjunction |
| `LABEL` | `result:` | Control-flow target marker |
| `JUMP` | `goto result` | Unconditional jump |
| `JUMP_IF_TRUE` | `if arg1 goto result` | Jump if condition is non-zero / true |
| `JUMP_IF_FALSE` | `if_false arg1 goto result` | Jump if condition is zero / false |
| `PARAM` | `param arg1` | Push argument onto call parameter queue |
| `CALL` | `result = call arg1, arg2` | Invoke function `arg1` with `arg2` arguments |
| `RETURN` | `return arg1` | Return value to caller frame and restore program counter |
| `FUNC_BEGIN`| `function result:` | Mark function entry point |
| `FUNC_END` | `end function result` | Mark function termination |
| `PRINT` | `print arg1` | Emit value to standard output followed by newline |
| `INPUT` | `input result` | Read token from standard input into target |
| `HALT` | `halt` | Stop virtual machine execution |

---

## 2. Memory Model & Activation Records

1. **Global Frame:** Stores top-level variables and script state.
2. **Call Stack:** Maintains a stack of `CallFrame` structures:
   - `functionName`: Identifies active subroutine.
   - `returnPC`: Instruction index to resume upon return.
   - `returnTarget`: Register/variable in caller receiving return value.
   - `locals`: Isolated symbol map for local variables and parameters.
3. **Execution Limits & Safety:**
   - **Instruction Counter Limit:** Capped at $10,000,000$ instructions to prevent infinite loops from hanging the host machine.
   - **Recursion Depth Limit:** Capped at $10,000$ frames to prevent host stack exhaustion during unbounded recursion.
