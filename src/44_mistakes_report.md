```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ ASSEMBLY ERROR PATTERN: instruction → expected → actual → fix                                                   │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ E1: movq rbp → identifier "rbp" → expected %rbp → missing % prefix → ✗                                         │
│ E2: SPACE indent → label candidate → expected TAB → delimiter mismatch → ✗                                     │
│ E3: call puts → rax clobbered → expected rax=42 → SysV ABI: caller-saved → ✗                                   │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. line 86: `    movq $42, %rax` → SPACE indent → scanner sees label → expected TAB → fix: `\tmovq $42, %rax`
02. line 93: call puts@PLT → rax,rcx,rdx,rsi,rdi,r8-r11 CLOBBERED → movq $42,%rax BEFORE call → garbage after call → fix: movq AFTER call
03. line 225: leaq -24(rbp), %rax → rbp without % → undefined identifier → fix: leaq -24(%rbp), %rax
04. line 252-256: # leaq ... → commented out → never executes → fix: remove # to activate
05. ■ AT&T syntax: %register, $immediate, src→dest ■
06. clobber rule: call → rax,rcx,rdx,rsi,rdi,r8-r11 = garbage
07. preserve rule: rbx,rbp,r12-r15 = callee-saved
08. ■ assume all caller-saved registers destroyed after call ■
---PREVENTION---
P1. editor "Show Whitespace" → distinguish TAB from SPACE
P2. trace register state step-by-step through each instruction
P3. verify uncommented code with objdump
P4. SysV ABI: know caller-saved vs callee-saved
