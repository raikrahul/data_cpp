:01. DRAW REGISTER STATE. `movq -8(%rbp), %rax` → Input: rbp=0x7FFF0000. Calculation: 0x7FFF0000-8=0x7FFEFFF8. Memory[0x7FFEFFF8]=0x401234. Output: rax=0x401234. :02. DRAW INSTRUCTION. `movq A, B` → AT&T: Source→Dest. A=source, B=dest. rax←mem[0x7FFEFFF8]. :03. TRAP. Wrote `movq rbp` Missing `%`. Compiler sees identifier `rbp`. Error. Fix: `%rbp`. :04. TRAP. Wrote SPACE indent. `.s` requires TAB. Scanner sees `    movq` as label candidate. Error. Fix: `\tmovq`. :05. DRAW CLOBBER. `call puts@PLT` → SysV: rax,rcx,rdx,rsi,rdi,r8-r11 = GARBAGE. Input: rax=42. After call: rax=???. :06. F1. `movq $42, %rax` before `call`. After call: rax clobbered. Fix: `movq $42, %rax` AFTER call. :07. DRAW COMMENT. `# leaq ...` → Parser ignores. CPU never sees. Remove `#` to execute. Verification: objdump shows 0 bytes for commented line.
# Assembly Mistakes Report

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
