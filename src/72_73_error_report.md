# 72_73_error_report.md

## Session Errors

### E1: Confused about "this" pointer location
```
Your thought: "this" is stored inside object
Correct: "this" = address of object, passed in RDI register
Line: Task 1 Q1.7
```
Why: Mixup between object contents and object address.
Prevention: Draw memory diagram before answering. Object contains DATA, not pointer to self.

### E2: Wrong register for parameter
```
Your thought: "push 42 into rax"
Correct: movl $42, %esi (ESI = 2nd param, RAX = return)
Line: Task 1 Q1.3
```
Why: Guessed without checking calling convention.
Prevention: Memorize: RDI=arg1, RSI=arg2, RDX=arg3, RAX=return.

### E3: Confused about sizeof(empty class)
```
Your thought: "I do not know"
Correct: sizeof(empty class) = 1 byte (C++ requires unique address)
Line: Task 1 C1.4
```
Why: Did not look up.
Prevention: Test: `struct Empty {}; cout << sizeof(Empty);`

### E4: Lambda = operator() confusion
```
Your thought: "lambda takes x as arg" (stopping there)
Correct: Lambda IS a struct with operator() that takes x
Line: Step 462-465
```
Why: Saw syntax, missed underlying mechanism.
Prevention: Always expand: `[](int x){}` → `struct { void operator()(int x){} };`

### E5: Expected explicit "Visitor" class
```
Your thought: "there is no visitor"
Correct: Lambda IS the visitor (anonymous struct with operator())
Line: Step 459
```
Why: Looking for named struct, missing that lambda = anonymous struct.
Prevention: Lambda = visitor. `std::visit(lambda, variant)` = `std::visit(visitor, variant)`.

## Orthogonal Questions

Q1: You said "this inside object". What IS inside object?
```
Answer: member variables only
Horse: [speed=4bytes][weight=4bytes] = 8 bytes
NO pointer to self stored
```

Q2: You confused RAX with param register. What IS RAX for?
```
Answer: Return value
foo() returns int → EAX = return value
Not for passing arguments
```

Q3: You said "no visitor". What is visitor pattern?
```
Answer: Object with operator() for each variant type
Lambda [](auto a){} = object with template operator()
∴ Lambda IS visitor
```

## Pattern

1. Stopped at surface syntax, missed underlying mechanism (lambda → struct)
2. Guessed registers without checking convention
3. Confused pointer passing (register) with storage (memory)

## Prevention

1. Before answering register question: Write out RDI RSI RDX RCX R8 R9 RAX
2. Before answering "where is X stored": Draw memory diagram
3. Before answering lambda question: Expand to struct equivalent
