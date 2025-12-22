# 72_assembly_axioms.md

STEP 01: x86-64 has 16 general purpose registers, each 64 bits = 8 bytes, register names are RAX RBX RCX RDX RSI RDI RBP RSP R8 R9 R10 R11 R12 R13 R14 R15, lower 32 bits accessed via EAX EBX ECX EDX ESI EDI EBP ESP, store value 0x123456789ABCDEF0 in RAX then EAX = 0x9ABCDEF0 (lower 32 bits).

STEP 02: RAX = 0x00000000DEADBEEF → EAX = 0xDEADBEEF, AX = 0xBEEF (lower 16 bits), AL = 0xEF (lower 8 bits), verify: 0xDEADBEEF & 0xFFFFFFFF = 0xDEADBEEF ✓, 0xDEADBEEF & 0xFFFF = 0xBEEF ✓, 0xDEADBEEF & 0xFF = 0xEF ✓.

STEP 03: RBP = base pointer = frame pointer = 0x7FFF0100 (example), RSP = stack pointer = 0x7FFF00C0 (example), stack grows downward ∴ RSP < RBP, difference = 0x7FFF0100 - 0x7FFF00C0 = 0x40 = 64 bytes of stack frame.

STEP 04: movq means move quad word = move 8 bytes, movl means move long = move 4 bytes, movw means move word = move 2 bytes, movb means move byte = move 1 byte, q=8 l=4 w=2 b=1 → memorize this mapping.

STEP 05: movq %rdi, -8(%rbp) means RBP = 0x7FFF0100 → destination = 0x7FFF0100 - 8 = 0x7FFF00F8 → write 8 bytes (value of RDI) to address 0x7FFF00F8, if RDI = 0xA000 then memory at 0x7FFF00F8 = 0x00000000 0000A000 (little endian: 00 A0 00 00 00 00 00 00).

STEP 06: movl %esi, -12(%rbp) means RBP = 0x7FFF0100 → destination = 0x7FFF0100 - 12 = 0x7FFF00F4 → write 4 bytes (value of ESI) to address 0x7FFF00F4, if ESI = 100 = 0x64 then memory at 0x7FFF00F4 = 0x00000064 (little endian: 64 00 00 00).

STEP 07: leaq means load effective address quad = compute address but do NOT dereference, leaq -48(%rbp), %rax means RAX = RBP - 48 = 0x7FFF0100 - 48 = 0x7FFF0100 - 0x30 = 0x7FFF00D0, NO memory read happens, just arithmetic.

STEP 08: movq -8(%rbp), %rax means READ 8 bytes from (RBP - 8) and store in RAX, RBP = 0x7FFF0100 → source = 0x7FFF00F8 → RAX = *(0x7FFF00F8) = value stored there, if we stored 0xA000 earlier via STEP 05 then RAX = 0xA000.

STEP 09: movq %rdx, (%rax) means WRITE 8 bytes (value of RDX) to address pointed by RAX, if RAX = 0xA000 and RDX = 0x4010 then memory at 0xA000 = 0x4010, parentheses = dereference ∴ (%rax) = *RAX.

STEP 10: movl %edx, 8(%rax) means WRITE 4 bytes (value of EDX) to address (RAX + 8), if RAX = 0xA000 and EDX = 100 then memory at 0xA008 = 100 = 0x64, 8(%rax) = *(RAX + 8) = offset 8 from base.

STEP 11: pushq %rbp means RSP = RSP - 8 then *(RSP) = RBP, if RSP = 0x7FFF00C8 and RBP = 0x7FFF0100 then new RSP = 0x7FFF00C0 and memory at 0x7FFF00C0 = 0x7FFF0100, stack grew by 8 bytes.

STEP 12: popq %rbp means RBP = *(RSP) then RSP = RSP + 8, if RSP = 0x7FFF00C0 and memory at 0x7FFF00C0 = 0x7FFF0100 then RBP = 0x7FFF0100 and new RSP = 0x7FFF00C8, reverse of push.

STEP 13: call LABEL means pushq %rip (save return address) then jmp LABEL, if RIP = 0x401050 before call and LABEL = 0x401200 then RSP -= 8, *(RSP) = 0x401050 + size_of_call_instruction, RIP = 0x401200.

STEP 14: ret means popq %rip, if RSP = 0x7FFF00C0 and *(0x7FFF00C0) = 0x401055 then RIP = 0x401055 and RSP = 0x7FFF00C8, execution continues at 0x401055 which is instruction after call.

STEP 15: subq $32, %rsp means RSP = RSP - 32 = RSP - 0x20, if RSP = 0x7FFF00C8 then new RSP = 0x7FFF00A8, allocates 32 bytes on stack for local variables.

STEP 16: addq $8, %rax means RAX = RAX + 8, if RAX = 0xA000 then new RAX = 0xA008, used for pointer arithmetic like &obj.weight = &obj + 8.

STEP 17: salq $3, %rax means shift arithmetic left by 3 = multiply by 2^3 = multiply by 8, if RAX = 5 then new RAX = 40 = 5 × 8, used for array indexing: arr[i] address = base + i × sizeof(element).

STEP 18: cltq means sign-extend EAX to RAX, if EAX = 0x0000003 then RAX = 0x0000000000000003, if EAX = 0xFFFFFFFF (= -1) then RAX = 0xFFFFFFFFFFFFFFFF (= -1 in 64-bit), converts 32-bit signed to 64-bit signed.

STEP 19: (%rip) means RIP-relative addressing, leaq SYMBOL(%rip), %rax means RAX = RIP + offset_to_SYMBOL, if RIP = 0x401050 and SYMBOL is at 0x404000 then offset = 0x404000 - 0x401050 = 0x2FB0 and at runtime RAX = current_RIP + 0x2FB0.

STEP 20: leaq 16+_ZTV17AnimalBaseVirtual(%rip), %rdx means compute address of vtable + 16, if vtable_base = 0x404000 then RDX = 0x404000 + 16 = 0x404010, +16 skips offset-to-top (8 bytes) and RTTI pointer (8 bytes), RDX now points to slot[0] of vtable.

STEP 21: System V AMD64 calling convention → RDI = arg1 (or this), RSI = arg2, RDX = arg3, RCX = arg4, R8 = arg5, R9 = arg6, RAX = return value, call foo(a,b,c) → RDI=a RSI=b RDX=c then call _Z3fooiii.

STEP 22: obj.speak(42) translates to RDI = &obj = 0xA000, RSI = 42, call _ZN...5speakEi, inside speak() function RDI holds this pointer ∴ *(RDI+8) = this->weight, *(RDI+12) = this->age.

STEP 23: Direct call = call _ZN...speakEi means function address 0x401200 is encoded in instruction, indirect call = call *(%rax) means load function address from memory at RAX then jump there, call *8(%rax) means load from RAX+8 then jump.

STEP 24: vtable slot access → if vptr = *(this+0) = 0x404010 and slot[0] at offset 0, slot[1] at offset 8, then call speak (slot 0) = call *(0x404010+0) = call *(0x404010), call dtor (slot 1) = call *(0x404010+8) = call *(0x404018).

STEP 25: Full virtual call sequence → movq (%rdi), %rax loads vptr from object, if RDI = 0xA000 and *(0xA000) = 0x404010 then RAX = 0x404010 = vptr, then call *(%rax) means load *(0x404010) = 0x401300 = &speak, then jump to 0x401300.

STEP 26: Constructor ctor vptr init → line 22: leaq 16+_ZTV(%rip), %rdx → RDX = 0x404010, line 23: movq -8(%rbp), %rax → RAX = this = 0xA000, line 24: movq %rdx, (%rax) → *(0xA000) = 0x404010 ∴ vptr stored at offset 0 of object.

STEP 27: Member access with vptr present → weight at offset 8 not 0, line 27: movl %edx, 8(%rax) means *(this+8) = weight, line 30: movl %edx, 12(%rax) means *(this+12) = age, contrast Task 1 where weight at offset 0.

STEP 28: Destructor vptr reset → line 165: leaq 16+_ZTV(%rip), %rdx → RDX = &Base_vtable[0], line 167: movq %rdx, (%rax) → *(this+0) = &Base_vtable, ∴ during Base dtor any virtual call dispatches to Base version not Derived.

STEP 29: Memory layout derivation → sizeof = 16, &obj = 0xA000, &obj.weight = 0xA008 ∴ offset = 0xA008 - 0xA000 = 8 ∴ vptr occupies bytes 0-7, &obj.age = 0xA00C ∴ offset = 12 ∴ weight occupies bytes 8-11, age occupies bytes 12-15.

STEP 30: Vtable layout → .quad 0 at offset -16 = offset-to-top = 0 for single inheritance, .quad _ZTI... at offset -8 = RTTI typeinfo pointer, .quad _ZN...speakEi at offset 0 = slot[0] = &speak, .quad _ZN...D1Ev at offset 8 = slot[1] = &dtor.

---

AXIOM CHECK:

01. STEP 01-04: Defined registers and mov suffixes from x86-64 ISA manual, no new inference.
02. STEP 05-10: Each instruction derived from STEP 01-04 definitions by substituting values, no jump ahead.
03. STEP 11-16: Stack operations derived from RSP decrement/increment axiom, no new variable introduced without computation.
04. STEP 17-19: Shift and sign-extend are ISA primitives, RIP-relative addressing derived from position-independent code requirement.
05. STEP 20-25: Virtual call derived from vtable axiom (vptr at offset 0 → dereference → slot offset → dereference → call).
06. STEP 26-30: Constructor/destructor vptr handling derived from C++ object model axiom (ctor sets vptr, dtor resets vptr).

NO NEW INFERENCE INTRODUCED WITHOUT PRIOR DERIVATION ✓
