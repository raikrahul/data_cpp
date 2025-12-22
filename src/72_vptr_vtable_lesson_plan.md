# 72_vptr_vtable_lesson_plan.md

## TASK GRILLING - NOT SOLUTIONS

---

## TASK 1: AnimalStandalone (No Virtual)

### Sub-questions about Task 1:
- Q1.1: What is sizeof(AnimalStandalone)? Just int members? Or hidden data?
   - sizeof = sum of members (no hidden vptr)
- Q1.2: Does ctor do anything special? Or just member initialization?
      nothing special
- Q1.3: What assembly for `obj.foo(42)`? Direct call or indirect?
          call function address and push 42 into rax
- Q1.4: Is function address known at compile time?
            yes
- Q1.5: Where is function code located? .text section?
            yes 
- Q1.6: What registers used? RDI = this? ESI = int param?
         rdi is always this, param can be anything
- Q1.7: Is there any pointer inside the object?
            this 
- Q1.8: What if object is on stack vs heap?
            the this pointer will be called 
            // this will come from some other part not from the stack in the elf file
- Q1.9: Does `new AnimalStandalone()` generate different ctor assembly?
            // yes -- it calls @new in the embedded library 


### Counter-questions:
- C1.1: If no virtual, why would there be vptr? no
- C1.2: How does compiler resolve function address without vtable? direct lookup into text section 
            // or relocatable section i thinks 
- C1.3: What is the difference between `call _ZN6Animal3fooEi` vs `call *(%rax)`?
            // the other one first reads the address in rax
            // then it calls the function at that address 
            // first one is just a call to an address 
- C1.4: Can you prove NO vptr by checking sizeof?
        - i do not know size of an empty class 

### Expected observations:
- sizeof = sum of members (no hidden vptr)
- ctor = just initialize members
- call = direct `call LABEL` instruction
- no indirection through memory

---

## TASK 2: AnimalBaseVirtual (Virtual + Non-Virtual, No Derived)

### Sub-questions about Task 2:
- Q2.1: What is sizeof(AnimalBaseVirtual)? 
- Q2.2: Where does the extra 8 bytes come from?
- Q2.3: What is vptr? Pointer to what?
- Q2.4: When is vptr set? Ctor? Before ctor body? After?
- Q2.5: What assembly in ctor sets vptr?
- Q2.6: What is vtable? Array of what?
- Q2.7: Where is vtable stored? .rodata? .data?
- Q2.8: How many entries in vtable for 1 virtual function?
- Q2.9: What about destructor? Is it in vtable?
- Q2.10: Virtual destructor vs non-virtual destructor?

### Sub-questions about calls:
- Q2.11: Call to non-virtual function: direct or indirect?
- Q2.12: Call to virtual function: what assembly?
- Q2.13: What is `movq (%rax), %rax`? Loading vptr?
- Q2.14: What is `call *(%rax)` or `call *8(%rax)`?
- Q2.15: How does compiler know offset 0 vs offset 8 in vtable?

### Counter-questions:
- C2.1: If no derived class, why use virtual at all?
- C2.2: Does virtual add overhead even when not overridden?
- C2.3: What is cost of virtual call vs direct call? Cycles?
- C2.4: Can compiler devirtualize if type is known?

### Expected observations:
- sizeof = members + 8 (vptr)
- ctor writes vptr before body
- non-virtual call = direct call
- virtual call = load vptr, load from vtable, indirect call

---

## TASK 3: AnimalBaseVirtual + Derived (Call from Derived Object)

### Sub-questions about Task 3:
- Q3.1: What is sizeof(Derived)?
- Q3.2: Does Derived have its own vptr or shares with Base?
- Q3.3: Where is Base's data in Derived layout?
- Q3.4: What is offset of vptr in Derived?
- Q3.5: Does Derived have separate vtable or modifies Base's?
- Q3.6: What entries in Derived's vtable?
- Q3.7: If Derived overrides foo(), which address in vtable?
- Q3.8: If Derived does NOT override foo(), which address?

### Sub-questions about Derived ctor:
- Q3.9: Does Derived ctor call Base ctor?
- Q3.10: In what order? Base first or Derived first?
- Q3.11: When is vptr set to Base's vtable?
- Q3.12: When is vptr OVERWRITTEN to Derived's vtable?
- Q3.13: What happens if Base ctor calls virtual function?
- Q3.14: Which version is called: Base's or Derived's?

### Sub-questions about call from Derived object:
- Q3.15: `Derived d; d.foo();` — direct or indirect call?
- Q3.16: Does compiler know static type is Derived?
- Q3.17: Can compiler devirtualize?
- Q3.18: What if optimization is -O0 vs -O2?

### Counter-questions:
- C3.1: Why call through vptr when type is known?
- C3.2: What prevents compiler from direct call?
- C3.3: At -O0, does compiler still use vtable?
- C3.4: How to prove vptr is overwritten in Derived ctor?

---

## TASK 4: Polymorphic Call (Base* ptr = &Derived)

### Sub-questions about Task 4:
- Q4.1: What is the type of ptr? Base*
- Q4.2: What is the object? Derived
- Q4.3: What does ptr point to? Address of Derived object
- Q4.4: What is at offset 0 of object? vptr
- Q4.5: Which vtable does vptr point to? Derived's or Base's?
- Q4.6: Why Derived's vtable?
- Q4.7: When was vptr set to Derived's vtable?

### Sub-questions about call:
- Q4.8: `ptr->foo()` — what assembly?
- Q4.9: Step 1: Load ptr into register?
- Q4.10: Step 2: Load vptr from object?
- Q4.11: Step 3: Load function address from vtable?
- Q4.12: Step 4: Call through register?
- Q4.13: How many memory loads? 2? ptr→object, object→vptr, vtable→func?

### Sub-questions about address calculation:
- Q4.14: If foo() is first virtual function, offset in vtable = 0?
- Q4.15: If bar() is second virtual function, offset = 8?
- Q4.16: What if virtual destructor? Which slot?
- Q4.17: What is RTTI pointer? Slot -1?

### Counter-questions:
- C4.1: What if ptr is null? What happens at ptr->foo()?
- C4.2: What if Derived is deleted? Dangling vptr?
- C4.3: What if vtable is corrupted? Crash?
- C4.4: How to prove which vtable is used?

---

## EXPECTED MEMORY LAYOUTS

### Task 1: sizeof = members only
```
┌────────────────────────┐
│ member1 (4 bytes)      │
│ member2 (4 bytes)      │
└────────────────────────┘
sizeof = 8 (example)
```

### Task 2: sizeof = vptr + members
```
┌────────────────────────┐
│ vptr (8 bytes)         │ → points to vtable
│ member1 (4 bytes)      │
│ member2 (4 bytes)      │
└────────────────────────┘
sizeof = 16 (with padding)
```

### Task 3: Derived layout
```
┌────────────────────────┐
│ Base::vptr (8 bytes)   │ → points to Derived's vtable
│ Base::member (4 bytes) │
│ Derived::extra (4 bytes)│
└────────────────────────┘
```

### Task 4: Pointer indirection
```
ptr (8 bytes on stack)
    │
    ↓
┌────────────────────────┐
│ vptr → Derived_vtable  │
│ ...                    │
└────────────────────────┘
    │
    ↓
Derived_vtable:
┌────────────────────────┐
│ slot[0] = &Derived::foo│
│ slot[1] = &Derived::bar│
└────────────────────────┘
```

---

## EXPECTED ASSEMBLY PATTERNS

### Direct call (non-virtual):
```asm
call _ZN6Animal3fooEi    ; function address embedded in instruction
```

### Indirect call (virtual):
```asm
movq (%rdi), %rax        ; load vptr from object (rdi = this)
call *(%rax)             ; call through vtable slot 0
; or
call *8(%rax)            ; call through vtable slot 1
```

### Ctor vptr initialization:
```asm
leaq _ZTV6Animal+16(%rip), %rax   ; load vtable address
movq %rax, (%rdi)                 ; store to vptr (offset 0 of this)
```

---

## TRAPS TO WATCH FOR

### T1: Forgetting vptr adds 8 bytes to sizeof
### T2: Forgetting vptr is set in CTOR
### T3: Forgetting Derived ctor overwrites vptr
### T4: Confusing vtable address vs vtable content
### T5: Missing that vtable has +16 offset (RTTI and typeinfo)
### T6: Forgetting non-virtual calls are direct
### T7: Assuming -O2 devirtualizes everything

---

## NUMERICAL PREDICTIONS TO VERIFY

| Task | sizeof | vptr present | call type |
|------|--------|--------------|-----------|
| 1    | 4-8    | NO           | direct    |
| 2    | 12-16  | YES          | virtual=indirect, non-virtual=direct |
| 3    | 16-24  | YES (Derived's) | depends on optimization |
| 4    | N/A (ptr) | YES        | indirect through vtable |

---

## ASSEMBLY FILES TO GENERATE

1. `72_animal_standalone.s` — no virtual
2. `72_animal_base_virtual.s` — virtual, no derived
3. `72_animal_derived.s` — with derived, call from derived
4. `72_animal_polymorphic.s` — Base* = &Derived

---

## QUESTIONS YOU MUST ANSWER BY HAND BEFORE CODING

1. What is sizeof(AnimalStandalone)?
2. What is sizeof(AnimalBaseVirtual)?
3. What is sizeof(Derived)?
4. What is offset of vptr in each class?
5. What assembly instruction calls non-virtual function?
6. What assembly instruction calls virtual function?
7. What does ctor assembly look like for class with vptr?
8. What assembly proves vptr is set in ctor?
9. What assembly proves indirect call through vtable?
10. What is the vtable symbol name for class Animal?

---

## NO SOLUTIONS YET

This document contains ONLY questions.
The code will be written after numerical predictions are made.
Each prediction must be verified against actual assembly output.
