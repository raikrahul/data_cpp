| Line | Instruction | Error | Correct | Logic Gap | Prevention |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 86 | `    movq $42, %rax` | SPACE instead of TAB | `\tmovq $42, %rax` | Ignoring low-level delimiter requirements | Use editor "Show White Space" |
| 93 | `call puts@PLT` | Clobbering `%rax` | Move `movq` after `call` | Ignored SysV ABI caller-saved registers | Assume all registers clobbered after `call` |
| 225 | `leaq -24(rbp), %rax` | Missing register prefix `%` | `leaq -24(%rbp), %rax` | Mapping C variables to registers without syntax check | Strict adherence to AT&T syntax |
| 225 | [Multiple] | Code in comment block | Move to execution block | Derivation block != execution block | Distinguish doc from code |
| 252-256 | `# leaq ...` | Commented execution code | `leaq ...` (no #) | Left instructions as comments | Verify uncommenting on every TODO |
| 206 | `leaq ...rax\` | Trailing backslash | `leaq ...rax` | Accidental character insertion | Review line endings |
| 229 | `movq (%rax), %rax` | Redundant deref | Part of chain | Forgot state of %rax after step 1 | Trace register state step-by-step |

? Why confuse derivation space with execution space?
? Why ignore register prefix rules?
? Why rely on space-based indentation in a tab-based language?
? Why comment out the actual logic?
? Why call a function that overwrites your target register before you read it?

Orthogonal Process:
1. Syntax != Intention. Assembler executes syntax. Intention is invisible.
2. Register `%` is the trigger for register mapping. `rbp` is just a string.
3. `#` is a block for the parser. Parser is blind to code behind `#`.
4. TAB is the start-of-instruction signal. SPACE is ignored noise.
5. `call` is a destructive operation. All caller-saved registers are now garbage.
