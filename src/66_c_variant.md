
01. Definition: C-Style Discriminated Union (Variant).
02. Enum VariantTag { TAG_INT=0, TAG_FLOAT=1 }. Size: 4 bytes (ARM32/64 assumption, check `sizeof(enum)`).
03. Union Data { int32_t i; float f; }. Size: 4 bytes.
04. Struct Variant { Tag tag; Union data; }.
05. Layout: [ tag(4) ] [ data(4) ] → Total 8 bytes.
06. Alignment: 4 bytes.
07. Padding: 0 bytes (Packed perfectly 4+4).
08. Memory 0x20000000: Tag @ 0x00, Data @ 0x04.

09. Operation: Initialization.
10. `Variant v;` → Stack garbage.
11. `v.tag` = 0xDEADBEEF. `v.data` = 0xCAFEF00D.
12. Check: `get_int(&v)` → tag != TAG_INT → matches garbage?
13. If deadbeef == 0? Probability 1/2^32. Unlikely.
14. If deadbeef != 0 and != 1 → `get_int` fails, `get_float` fails.
15. Result: "ERROR: Invalid state". Safe? Yes, if checked.
16. Unsafe? If user assumes `else { return data.f; }` (The "Only 2 types" fallacy).
17. F1: User assumes (tag==0) -> int, else -> float.
18. Reality: tag=garbage -> float access -> reinterprets garbage bits -> NaN or outliers.

19. Operation: Write Sequence (Race Condition).
20. `v.tag = TAG_INT; v.data.i = 42;` (Wrong Order).
21. ASM:
    - 0x100: `mov [v], 0` (Set Tag)
    - 0x104: INTERRUPT!
    - ISR: Check Tag? 0 (INT). Read Data? Garbage.
    - 0x108: `mov [v+4], 42` (Set Data).
22. Result: ISR processed Garbage as 42. Logic Error.
23. Fix: Data First, Tag Last.
    - 0x100: `mov [v+4], 42`
    - 0x104: `dmb` (Memory Barrier)
    - 0x108: `mov [v], 0`
    - 0x10C: INTERRUPT!
    - ISR: Check Tag? Old value (FLOAT?). Read Float? Old Float.
    - OR ISR: Check Tag? New value (INT). Read Int? 42.
    - ∴ Atomic State Transition.

24. Operation: Byte Serialization (UART).
25. `send(&v, sizeof(v))`.
26. Endianness Trap:
    - Host (Little Endian): Tag=0x00000000 → 00 00 00 00.
    - Receiver (Big Endian): Reads 00 00 00 00.
    - Data=42 (0x0000002A) → 2A 00 00 00.
    - Receiver (Big): 0x2A000000 = 704643072.
27. F2: Raw struct serialization fails across architectures.
28. Fix: Serialize fields manually `htonl(v.tag)`, `htonl(v.data.i)`.

29. Memory Map: `variant_get_int`
30. Input: `v` @ 0x2000. `v.tag`=0. `v.data.i`=100.
31. Call: `variant_get_int(&v, &out)`.
32. Check: `v->tag == 0`? Yes.
33. Access: `v->data.i`.
34. Copy: `*out = 100`.
35. Return: true.
36. Cost: Load(tag) + Cmp + Branch + Load(data) + Store(out).
37. Registers: r0=&v, r1=&out.
38. `ldr r2, [r0]` (Tag).
39. `cmp r2, #0`.
40. `bne fail`.
41. `ldr r3, [r0, #4]` (Data).
42. `str r3, [r1]`.
43. `mov r0, #1` (True).
44. `bx lr`.

45. Hands-On Task:
46. Implement `src/66_c_variant.c`.
47. Structs, Enums, Getters, Setters.
48. Test Race Window (Simulation).
49. Test Uninitialized Garbage.
50. Test Serialization.

51. Axiom: Type Safety in C = Discipline + Runtime Checks.
52. Axiom: Unions are unchecked memory overlays.
53. Axiom: Tags are the runtime type information (RTTI).
