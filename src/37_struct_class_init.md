01. sizeof(int)=4, sizeof(float)=4, sizeof(std::string)=32 (libstdc++ assumption), alignof(int)=4, alignof(float)=4, alignof(std::string)=8 → struct Person {int age; float height; std::string name;} layout derived: age @ 0x00 (size 4) → height @ 0x04 (size 4, aligned 4) → name @ 0x08 (size 32, aligned 8) → total size = 0x08 + 0x20 = 0x28 (40 bytes) → alignof(Person)=8 → Padding check: 0x04+4=0x08 (aligned 8? Yes) → 0 padding bytes.
02. Stack frame simulation for `main`: Base `0x7ffc_c000` → `myNeighbor` allocated `0x7ffc_c000` to `0x7ffc_c027` (40 bytes).
03. Initialization `age=21`: 21 = `0x15` → Memory writes [0x7ffc_c000..0x7ffc_c003]: `15 00 00 00` (Little Endian).
04. Initialization `height=1.76`: Sign (+)=0, Integer=1, Fraction=0.76. Binary fraction: 0.76→1.52(1), 0.52→1.04(1), 0.04→0.08(0), 0.08→0.16(0), 0.16→0.32(0), 0.32→0.64(0), 0.64→1.28(1), 0.28→0.56(0), 0.56→1.12(1) → `0.110000101...` → Norm: `1.110000101... * 2^0` → Exp: 127+0=127 (`01111111`) → Mantissa: `11000010100011110101110` → Hex: `3F E1 47 AE` → Memory writes [0x7ffc_c004..0x7ffc_c007]: `AE 47 E1 3F`.
05. Initialization `name="Peter"`: Length 5 (including \0 = 6). SSO Threshold 15. 5 < 15 → SSO Active. No malloc. String object at `0x7ffc_c008`. Internal fields: pointer (8B), size (8B), capacity/buffer (16B). GCC layout: Ptr @ 0x00 points to internal buffer @ 0x10 (relative). Size @ 0x08 = 5. Buffer start @ 0x10 (relative) = `0x7ffc_c018` (absolute).
06. Write "Peter" to SSO buffer: 'P'(0x50), 'e'(0x65), 't'(0x74), 'e'(0x65), 'r'(0x72), '\0'(0x00) → Memory writes [0x7ffc_c018..0x7ffc_c01D]: `50 65 74 65 72 00`. Guaranteed no heap allocation at 0x5555_xxxx.
07. Access `myNeighbor.age`: Base `0x7ffc_c000` + Offset 0 → Load DWORD `15 00 00 00` → Register EAX `0x15` (21).
08. Access `myNeighbor.height`: Base `0x7ffc_c000` + Offset 4 → Load DWORD `AE 47 E1 3F` → Register XMM0 `0x3FE147AE` → fpu stack ensures 1.76.
09. Access `myNeighbor.name`: Base `0x7ffc_c000` + Offset 8 → `0x7ffc_c008`. `std::string::c_str()` inspects pointer. In SSO, pointer points to `0x7ffc_c018`. Returns address `0x7ffc_c018`.
10. Failure Prediction F1 (Alignment Padding): Struct `Bad {char c; double d;}` → c @ 0, d @ 8 (align 8) → 7 bytes padding [1..7]. Size 16. Wasted 43%. Fix: Reorder larger types first or packed.
11. Failure Prediction F2 (SSO Overflow): `name="1234567890123456"` (16 chars) → >15 → Malloc triggered. Ptr @ `0x7ffc_c008` points to Heap `0x5555_d000`. Stack contains pointer. Data on Heap.
12. Failure Prediction F3 (Narrowing): `Person{21, 1.76, "Peter"}` OK. `Person{21.9, ...}` → 21.9 is double. Brace init checks type. Double→Int narrowing forbidden. Compiler Error.
13. Failure Prediction F4 (Shadowing/Scope): `Person p` in inner scope shadows outer `p`. Stack offsets differ. Be aware of `rbp` offsets.
14. Failure Prediction F5 (Memcpy danger): `memcpy(&dest, &src, 40)` on Heap-allocated string → Copied pointer. Both point to `0x5555_d000`. Double free on destruction. CRITICAL FAIL.
15. Failure Prediction F6 (Return by Value): `Person p = make_person()` → RVO (Return Value Optimization) → Constructed in place. No copy. Address of `p` in `main` passed as hidden argument to `make_person`.
16. Code verification task: Check `sizeof(Person)`. If 32, using Clang/libc++. If 40/48, using GCC/libstdc++. Adjust offsets accordingly.
17. Trick: `std::string` internal pointer points to *internal buffer* (SSO) or *allocated memory* (Heap). User must differentiate by inspecting address value vs structure address.
18. Trick: `*(int*)&p` modification → Changes `age`.:01. DRAW MEMORY LAYOUT [0x1000]. `struct Pad { char c; int i; };`. [0x1000]=c (1 byte). [0x1001..0x1003]=UNUSED (Padding). [0x1004..0x1007]=i (4 bytes). **Why**: `int` requires 4-byte alignment. It cannot start at 0x1001. Efficiency: Used=5, Allocated=8. Ratio=62%. **Verification**: `sizeof(Pad)` is 8, not 5. **Reorder**: `struct Pack { int i; char c; };`. [0x1000]=i. [0x1004]=c. [0x1005..0x1007]=Padding. Still 8 bytes? Yes, because total size must align to largest member (4). **Array Impact**: `Pad arr[2]`. [0x1000]..[0x1007] (Pad 1), [0x1008]..[0x100F] (Pad 2). Hole propagates. **Action**: Calculate wasted bytes in `struct { bool a; double b; bool c; }`. 1+7(pad)+8+1+7(pad)=24 bytes. Reordered: 8+1+1+6(pad)=16 bytes. Savings=33%.
# Struct/Class Init & Memory Analysis
Direct memory manipulation bypasses protection (if any).
19. Trick: `myNeighbor.name.c_str()` return value lifetime → tied to `myNeighbor`. If `myNeighbor` destroyed, pointer dangles.
20. Edge Case: `age=INT_MAX+1` → 0x7FFFFFFF + 1 = 0x80000000 → -2147483648 (Overflow/Wrap).
21. Edge Case: `height=NaN` → 0x7FC00000. Comparison `h == h` returns False.
22. Calculation: User to verify `1.76` float bits `3F E1 47 AE` by manual binary multiplication.
23. Calculation: User to draw ASCII memory map of `0x7ffc_c000` to `0x7ffc_c027` with byte values.
24. Calculation: User to determine offset of `height` if `age` was `short` (2 bytes) + `char` (1 byte). Alignment of `float` (4) forces padding byte @ offset 3.
25. Final Step: Compile with `-O0` to observe raw `mov` instructions matching manual stack writes. `-O2` might vectorize or optimize away.
