# Raw Mechanical Calculation Chain - Swap Two Integers Evolution

---

## Memory Base Assumptions
- 64-bit Linux x86_64, little-endian
- `int` = 4 bytes, aligned to 4-byte boundary
- `int*` = 8 bytes, aligned to 8-byte boundary
- Stack grows downward from 0x7FFEE000
- Each push subtracts 8 bytes for alignment

---

## Version 0: C Raw Pointers (Mechanical State Dump)

`1. int a = 5;`
- Stack pointer (rsp) = 0x7FFEE000
- Address allocation: 0x7FFEE000 - 4 = 0x7FFDFFF8 (adjusted for alignment)
- Memory write: `*(int*)0x7FFDFFF8 = 5`
- **What**: 5 → 0x7FFDFFF8
- **Why**: Declaration requires storage
- **Where**: 0x7FFDFFF8 (stack offset -8)
- **Who**: Compiler generated mov instruction
- **When**: At function entry, before any other operations
- **Without**: 5 → undefined bits at 0x7FFDFFF8
- **Which**: 4 bytes at [0x7FFDFFF8..0x7FFDFFFB]

`2. int b = 7;`
- rsp = 0x7FFEE000 (prior state)
- Address allocation: 0x7FFDFFF8 - 4 = 0x7FFDFFF4
- Memory write: `*(int*)0x7FFDFFF4 = 7`
- **What**: 7 → 0x7FFDFFF4
- **Why**: Sequential stack allocation
- **Where**: 0x7FFDFFF4 (stack offset -12)
- **Who**: Compiler generated mov instruction
- **When**: Immediately after a's allocation
- **Without**: 7 → garbage at 0x7FFDFFF4
- **Which**: 4 bytes at [0x7FFDFFF4..0x7FFDFFF7]

`3. int *pa = &a;`
- Address of a: `&*(int*)0x7FFDFFF8 = 0x7FFDFFF8`
- rsp = 0x7FFEE000
- Address allocation: 0x7FFDFFF4 - 8 = 0x7FFDFFEC
- Memory write: `*(int**)0x7FFDFFEC = 0x7FFDFFF8`
- **What**: 0x7FFDFFF8 → 0x7FFDFFEC
- **Why**: Store pointer value for indirection
- **Where**: 0x7FFDFFEC (stack offset -20)
- **Who**: leaq instruction calculates address
- **When**: After a and b are allocated
- **Without**: 0x7FFDFFF8 → random 8 bytes
- **Which**: 8 bytes at [0x7FFDFFEC..0x7FFDFFF3]

`4. int *pb = &b;`
- Address of b: `&*(int*)0x7FFDFFF4 = 0x7FFDFFF4`
- rsp = 0x7FFEE000
- Address allocation: 0x7FFDFFEC - 8 = 0x7FFDFFE4
- Memory write: `*(int**)0x7FFDFFE4 = 0x7FFDFFF4`
- **What**: 0x7FFDFFF4 → 0x7FFDFFE4
- **Why**: Second pointer for swap target
- **Where**: 0x7FFDFFE4 (stack offset -28)
- **Who**: leaq instruction
- **When**: After pa is stored
- **Without**: 0x7FFDFFF4 → uninitialized pointer
- **Which**: 8 bytes at [0x7FFDFFE4..0x7FFDFFEB]

`5. int tmp = *pa;`
- Dereference: `*(*(int**)0x7FFDFFEC) = *(int*)0x7FFDFFF8 = 5`
- rsp = 0x7FFEE000
- Address allocation: 0x7FFDFFE4 - 4 = 0x7FFDFFE0
- Memory write: `*(int*)0x7FFDFFE0 = 5`
- **What**: 5 → 0x7FFDFFE0
- **Why**: Preserve a's value before overwrite
- **Where**: 0x7FFDFFE0 (stack offset -32)
- **Who**: mov instruction with dereference
- **When**: Before any modification to a
- **Without**: 5 → a's value lost forever
- **Which**: 4 bytes at [0x7FFDFFE0..0x7FFDFFE3]

`6. *pa = *pb;`
- *pb calculation: `*(*(int**)0x7FFDFFE4) = *(int*)0x7FFDFFF4 = 7`
- Memory write: `*(int*)0x7FFDFFF8 = 7`
- **What**: 7 → 0x7FFDFFF8
- **Why**: Transfer b's value to a's location
- **Where**: 0x7FFDFFF8 (a's address)
- **Who**: mov instruction with double dereference
- **When**: After tmp stores a's original
- **Without**: 7 → a becomes 7, old value 5 lost without tmp
- **Which**: 4 bytes overwritten at [0x7FFDFFF8..0x7FFDFFFB]

`7. *pb = tmp;`
- tmp read: `*(int*)0x7FFDFFE0 = 5`
- Memory write: `*(int*)0x7FFDFFF4 = 5`
- **What**: 5 → 0x7FFDFFF4
- **Why**: Transfer original a's value to b
- **Where**: 0x7FFDFFF4 (b's address)
- **Who**: mov instruction
- **When**: After pa is overwritten
- **Without**: 5 → b becomes 5, completes swap
- **Which**: 4 bytes overwritten at [0x7FFDFFF4..0x7FFDFFF7]

**Final State Verification:**
- 0x7FFDFFF8 = 7 (was 5)
- 0x7FFDFFF4 = 5 (was 7)
- 0x7FFDFFEC = 0x7FFDFFF8 (pa unchanged)
- 0x7FFDFFE4 = 0x7FFDFFF4 (pb unchanged)
- 0x7FFDFFE0 = 5 (tmp unchanged, now stale)

**Edge Case Calculations:**
- If a = 0, b = 0: tmp = 0, *pa = 0, *pb = 0 → result 0,0 (no change)
- If a = -2147483648, b = 1: tmp = -2147483648, *pa = 1, *pb = -2147483648 → result 1, -2147483648 (overflow risk none, values swapped)
- If pa == pb (alias): tmp = *pa, *pa = *pb (same), *pb = tmp → no net change (self-swap)

---

## Version 1: C++ References (Mechanical State Dump)

`int a = 5;` → 0x7FFDDFA8 = 5
`int b = 7;` → 0x7FFDDFA4 = 7
`int &ra = a;`
- No new storage, symbol table mapping: ra → 0x7FFDDFA8
- **What**: Alias creation, no bytes written
- **Why**: Reference is alternative name
- **Where**: Compiler symbol binding
- **Who**: Front-end name resolution
- **When**: At compile time, resolved at runtime
- **Without**: Alias → separate variable
- **Which**: 0 bytes, pure symbol

`int &rb = b;` → rb → 0x7FFDDFA4

`int tmp = ra;`
- Read through alias: `*(int*)0x7FFDDFA8 = 5`
- Write: 0x7FFDDFA0 = 5
- **What**: 5 → 0x7FFDDFA0 (same as *pa above)
- **Why**: Reference dereference at compile level
- **Where**: 0x7FFDDFA0
- **Who**: mov rax, [0x7FFDDFA8]; mov [0x7FFDDFA0], rax
- **When**: Alias resolved to address then loaded
- **Without**: Direct memory read
- **Which**: 4 bytes

`ra = rb;`
- Read rb: `*(int*)0x7FFDDFA4 = 7`
- Write to ra's target: `*(int*)0x7FFDDFA8 = 7`
- **What**: 7 → 0x7FFDDFA8
- **Why**: Assignment through reference writes to referee
- **Where**: 0x7FFDDFA8
- **Who**: mov rax, [0x7FFDDFA4]; mov [0x7FFDDFA8], rax
- **When**: After tmp saved
- **Without**: Overwrites a directly
- **Which**: 4 bytes

`rb = tmp;`
- Read tmp: `*(int*)0x7FFDDFA0 = 5`
- Write to rb's target: `*(int*)0x7FFDDFA4 = 5`
- **What**: 5 → 0x7FFDDFA4
- **Why**: Complete swap via alias
- **Where**: 0x7FFDDFA4
- **Who**: mov rax, [0x7FFDDFA0]; mov [0x7FFDDFA4], rax
- **When**: After ra modified
- **Without**: Direct memory manipulation
- **Which**: 4 bytes

**Memory Comparison:**
- Version 0: 4 variables (a,b,pa,pb,tmp) = 4 + 4 + 8 + 8 + 4 = 28 bytes stack
- Version 1: 3 variables (a,b,tmp) = 4 + 4 + 4 = 12 bytes stack + 2 symbols
- **Shortcut**: References eliminate pointer storage, reduce cache pressure: 28 → 12 bytes = 57.14% reduction

---

## Version 2: std::swap (Mechanical State Dump)

`int a = 5;` → 0x7FFDDEE8 = 5
`int b = 7;` → 0x7FFDDEE4 = 7
`std::swap(a, b);`
- Implementation: `int tmp = a;` → 0x7FFDDE80 = *(int*)0x7FFDDEE8 = 5
- `a = b;` → *(int*)0x7FFDDEE8 = *(int*)0x7FFDDEE4 = 7
- `b = tmp;` → *(int*)0x7FFDDEE4 = *(int*)0x7FFDDE80 = 5
- **What**: 5,7 → 7,5 in two memory cells
- **Why**: Template function abstracts three-step
- **Where**: 0x7FFDDEE8, 0x7FFDDEE4
- **Who**: Inlined mov operations from <utility>
- **When**: Function call resolves to three moves
- **Without**: Manual tmp creation
- **Which**: 8 bytes total swapped, 4 bytes tmp on stack

**Instruction Count Analysis:**
- Version 0: 6 mov instructions (3 direct, 3 indirect)
- Version 1: 6 mov instructions (all direct)
- Version 2: 3 mov instructions (compiler optimizes to register mov)
- **Speedup**: 6 → 3 = 50% instruction reduction

---

## Version 3: auto Deduction (Mechanical State Dump)

`auto a = 5;`
- Type deduction: `5` is `int` literal → type = int
- Storage: 0x7FFDDE48 = 5
- **What**: Compiler deduces int from int literal
- **Why**: auto replaces explicit type name
- **Where**: 0x7FFDDE48
- **Who**: Frontend type inference
- **When**: At variable declaration, compile-time deduction
- **Without**: `int` keyword written
- **Which**: 4 bytes, type int

`auto b = 7;` → 0x7FFDDE44 = 7

`std::swap(a, b);` → Same mechanical operations as Version 2, addresses differ

**Type Verification:**
- `sizeof(a) = 4` → confirms int
- `typeid(a).hash_code() == typeid(int).hash_code()` → true
- **Shortcut**: auto prevents type mismatch: `auto c = 5.0;` → double, size 8, address 0x7FFDDE40

---

## Version 4: Structured Bindings (Mechanical State Dump)

`auto [x, y] = std::pair{5, 7};`
- `std::pair{5, 7}` creates temporary: type = `pair<int,int>`
- Temporary storage: 0x7FFDDE00 (first) = 5, 0x7FFDDE04 (second) = 7
- Binding: x → ref to *(int*)0x7FFDDE00, y → ref to *(int*)0x7FFDDE04
- **What**: Two names bound to pair elements
- **Why**: Decompose aggregate into variables
- **Where**: 0x7FFDDE00, 0x7FFDDE04
- **Who**: Compiler-generated references
- **When**: After pair construction
- **Without**: Manual `.first`, `.second`
- **Which**: 8 bytes for pair, 2 symbolic references

`[x, y] = std::pair{y, x};`
- RHS evaluation: y = *(int*)0x7FFDDE04 = 7, x = *(int*)0x7FFDDE00 = 5
- Temporary pair created: 0x7FFDDDF8 = 7, 0x7FFDDDFC = 5
- Assignment: *(int*)0x7FFDDE00 = 7, *(int*)0x7FFDDE04 = 5
- **What**: 5,7 → 7,5 via temporary swap
- **Why**: Structured binding allows left-side decomposition
- **Where**: 0x7FFDDE00, 0x7FFDDE04
- **Who**: Pair assignment operator
- **When**: After RHS evaluation
- **Without**: Explicit tmp variable
- **Which**: 8 bytes overwritten

**Memory Overlap Check:**
- If x,y were same location (impossible here), assignment order matters
- Standard mandates right-to-left evaluation: y evaluated first (7), then x (5)
- No alias → safe

---

## Version 5: Full Example (Mechanical State Dump)

`auto priceA = 19.99;`
- Literal `19.99` is `double` → type = double
- Storage: 0x7FFDDDC0 = 0x403C7AE147AE147B (IEEE 754 representation)
- **What**: 19.99 → binary floating point
- **Why**: auto deduces double from decimal literal
- **Where**: 0x7FFDDDC0
- **Who**: Compiler type inference
- **When**: Declaration
- **Without**: `double` keyword
- **Which**: 8 bytes

`auto priceB = 34.50;` → 0x7FFDDDB8 = 0x4041400000000000 (34.50 in IEEE 754)

`std::swap(priceA, priceB);`
- tmp: xmm0 register = *(double*)0x7FFDDDC0 = 19.99
- *(double*)0x7FFDDDC0 = *(double*)0x7FFDDDB8 = 34.50
- *(double*)0x7FFDDDB8 = xmm0 = 19.99
- **What**: 19.99,34.50 → 34.50,19.99
- **Why**: Template specialization for double uses XMM registers
- **Where**: 0x7FFDDDC0, 0x7FFDDDB8
- **Who**: `movsd` instructions
- **When**: Function call
- **Without**: Manual register manipulation
- **Which**: 16 bytes swapped, 0 bytes stack tmp (register-based)

**Cache Line Analysis:**
- Addresses 0x7FFDDDC0 and 0x7FFDDDB8 differ by 8 bytes
- Cache line size = 64 bytes
- Both fall in same line: floor(0x7FFDDDC0/64) = floor(0x7FFDDDB8/64) = 0x7FFDDD80
- Single cache miss loads both values
- **Surprise**: 2 variables, 1 cache miss → 50% prefetch efficiency

---

## Annoying Concept Drilldown (Per Line)

**Line `int *pa = &a;`**
- *Why annoying?* Pointer syntax mixes declaration and address-of in one token
- *Where error?* `int* pa, pb;` declares `int* pa` and `int pb` (not pointer) → type split
- *Related to?* C declaration grammar: `*` binds to identifier, not type
- *How work?* `&a` yields rvalue address, converts to pointer type
- *How not work?* `pa = &b;` without `*` in declaration → type mismatch error
- *Annoyance fix:* Write `int* pa;` on separate line, initialize immediately: `int* pa{&a};`

**Line `std::swap(a, b);`**
- *Why annoying?* Template argument deduction fails for arrays: `int a[3], b[3]; std::swap(a,b);` swaps pointers, not elements
- *Where error?* `std::swap(5, 7);` → 5 is rvalue, cannot bind to `T&` → compile error
- *Related to?* Value category system: lvalue vs rvalue references
- *How work?* ADL finds `std::swap`, template parameter `T=int` deduced
- *How not work?* Non-assignable types: `const int a=5, b=7;` → const violation
- *Annoyance fix:* Use `std::exchange` for const-capable patterns

**Line `auto [x, y] = std::pair{5, 7};`**
- *Why annoying?* Cannot declare `auto [x, y]` without initializer → syntax error
- *Where error?* `auto [x, y]{5, 7};` → initializer list not allowed for structured bindings
- *Related to?* Aggregate initialization rules
- *How work?* Requires exact `std::pair` type on RHS
- *How not work?* `auto [x, y] = {5, 7};` → `{5,7}` is `std::initializer_list<int>`, not pair
- *Annoyance fix:* Use `std::make_pair` or explicit type: `std::pair<int,int>{5,7}`

---

## Pattern Recognition Exercises

1. **Address Pattern**: 0x7FFDDFA8, 0x7FFDDFA4 differ by 4 → consecutive ints
2. **Size Pattern**: 4,8,4,8 alternating → compiler padding for alignment
3. **Value Pattern**: 5,7 → prime numbers → test swap correctness with primes
4. **Cache Pattern**: 0x7FFDDDC0, 0x7FFDDDB8 → same cache line → false sharing risk
5. **Instruction Pattern**: mov, mov, mov → 3-move sequence → optimal swap

**Verification Chain:**
- Step 0: a=5,b=7 → after → a=7,b=5 ✓
- Step 1: a=5,b=7 → after → a=7,b=5 ✓
- Step 2: a=5,b=7 → after → a=7,b=5 ✓
- Step 3: a=5,b=7 → after → a=7,b=5 ✓
- Step 4: x=5,y=7 → after → x=7,y=5 ✓
- Step 5: priceA=19.99,priceB=34.50 → after → priceA=34.50,priceB=19.99 ✓

**Failure Predictions:**
1. **NULL pointer swap**: `int *pa = nullptr; *pa = 5;` → Segfault at 0x0 → ✗
2. **Self-swap**: `std::swap(a, a);` → tmp=a, a=a, a=tmp → no change, but safe → ✓
3. **Different types**: `int a; double b; std::swap(a,b);` → template mismatch → compile ✗
4. **Volatile swap**: `volatile int a=5, b=7; std::swap(a,b);` → volatile can't bind to non-volatile ref → compile ✗
5. **Register pressure**: 10 simultaneous swaps → register spilling → 5 cache misses → ✗ performance

---

## Memory Diagram (C Version - Explicit Addresses)

```
Stack Top: 0x7FFEE000
↓
0x7FFDFFE0: [05 00 00 00] (tmp)
0x7FFDFFE4: [F4 FF FD 7F 00 00 00 00] (pb → 0x7FFDFFF4)
0x7FFDFFEC: [F8 FF FD 7F 00 00 00 00] (pa → 0x7FFDFFF8)
0x7FFDFFF0: [00 00 00 00] (padding)
0x7FFDFFF4: [07 00 00 00] (b)
0x7FFDFFF8: [05 00 00 00] (a)
0x7FFDFFFC: [00 00 00 00] (padding)
```

**Pointer Chain Visualization:**
- pa (0x7FFDFFEC) → 0x7FFDFFF8 → value 05 00 00 00
- pb (0x7FFDFFE4) → 0x7FFDFFF4 → value 07 00 00 00
- After swap: 0x7FFDFFF8 = 07, 0x7FFDFFF4 = 05

---

## Shortcut/Trick Application

- **XOR swap trick**: `a ^= b; b ^= a; a ^= b;` → no tmp, but 3 ops, slower due dependencies
- **Register swap**: `xchg rax, rbx` → 1 micro-op on x86, but not portable
- **std::exchange**: `a = std::exchange(b, a);` → 1 line, 1 tmp, equivalent to swap
- **C++20 std::swap`constexpr`**?: Swap at compile time: `constexpr int a=5, b=7;` → not modifiable, fails

**Numerical Surprise Example:**
- Input: a = 0x12345678, b = 0x9ABCDEF0
- XOR swap sequence:
  - a = a ^ b = 0x12345678 ^ 0x9ABCDEF0 = 0x88888888
  - b = b ^ a = 0x9ABCDEF0 ^ 0x88888888 = 0x12345678 (original a)
  - a = a ^ b = 0x88888888 ^ 0x12345678 = 0x9ABCDEF0 (original b)
- **Surprise**: XOR swap works without tmp, but needs 3 serial deps → 3 cycles vs 1 cycle for std::swap (register move)

---

## Your Turn Calculations (Fill These)

1. **Address Calculation**: Stack at 0x7FFF0000, allocate `int x=3; int y=4;` → x addr? y addr? tmp addr?
2. **Size Calculation**: `struct { int a; char b; };` → size? padding? offset of b?
3. **Cache Calculation**: Array `int arr[1024];` at 0x1000, access `arr[512]` → cache line index? offset in line?
4. **Instruction Count**: `std::swap(arr[0], arr[1]);` → how many mov instructions? (consider array indexing)

---

## Answers (Verify by Hand First)

:01. x addr = 0x7FFF0000 - 4 = 0x7FFEFFFC. y addr = 0x7FFEFFFC - 4 = 0x7FFEFFF8. tmp addr = 0x7FFEFFF8 - 4 = 0x7FFEFFF4.
:02. size = 8 (int=4, char=1, padding=3). padding = 3 bytes. offset of b = 4.
:03. arr[512] addr = 0x1000 + 512*4 = 0x1000 + 0x800 = 0x1800. cache line = 0x1800 / 64 = 96. offset in line = 0x1800 % 64 = 0.
:04. arr[0] addr compute = 1 lea. arr[1] addr compute = 1 lea. tmp = arr[0] = 1 mov. arr[0] = arr[1] = 1 mov. arr[1] = tmp = 1 mov. Total = 2 lea + 3 mov = 5 instructions. With optimization: 3 mov (addresses folded into operands).

---

## IEEE 754 Calculation Examples

**19.99 → 0x403C7AE147AE147B**
- 19.99 = 19 + 0.99
- 19 = 10011₂
- 0.99 = 0.1111110101110000...₂ (approximate)
- 19.99 ≈ 10011.1111110101...₂
- Normalized: 1.00111111110101...₂ × 2⁴
- Exponent: 4 + 1023 = 1027 = 0x403
- Mantissa: 00111111110101110000101000111...₂
- Result: 0x403C7AE147AE147B ✓

**34.50 → 0x4041400000000000**
- 34.50 = 34 + 0.5
- 34 = 100010₂
- 0.5 = 0.1₂
- 34.50 = 100010.1₂
- Normalized: 1.000101₂ × 2⁵
- Exponent: 5 + 1023 = 1028 = 0x404
- Mantissa: 0001010000...₂
- Result: 0x4041400000000000 ✓
