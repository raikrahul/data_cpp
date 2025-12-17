# Problem 26: Transform Parity Derivation

## Data Layout

```
v_addr = 0x600000 (Start)
w_addr = 0x600040 (Start)
sizeof(int) = 4 bytes
```

## Step 1: Input Analysis (Fill by hand)

```
01. v[0] @ 0x600000 = 10
02. 10 = 2 × 5 + 0
03. Remainder = 0
04. Even? ✓
05. w[0] @ 0x600040 ← 1

06. v[1] @ 0x600004 = 23
07. 23 = 2 × 11 + 1
08. Remainder = 1
09. Even? ✗
10. w[1] @ 0x600044 ← -1

11. v[2] @ 0x600008 = 44
12. 44 = 2 × ___ + ___
13. Remainder = ___
14. Even? ___
15. w[2] @ 0x600048 ← ___

16. v[3] @ 0x60000c = 15
17. 15 = 2 × ___ + ___
18. Remainder = ___
19. Even? ___
20. w[3] @ 0x60004c ← ___

21. v[4] @ 0x600010 = 6
22. 6 = 2 × ___ + ___
23. Remainder = ___
24. Even? ___
25. w[4] @ 0x600050 ← ___

26. v[5] @ 0x600014 = 91
27. 91 = 2 × ___ + ___
28. Remainder = ___
29. Even? ___
30. w[5] @ 0x600054 ← ___

31. v[6] @ 0x600018 = 108
32. 108 = 2 × ___ + ___
33. Remainder = ___
34. Even? ___
35. w[6] @ 0x600058 ← ___
```

## Step 2: Lambda Construction

```
36. Input Type: int (value from v)
37. Output Type: int (value to w)
38. Logic:
39.   Input % 2 == 0 → Output 1
40.   Input % 2 == 1 → Output -1
41. Syntax:
42.   [](int n) { return (n % 2 == 0) ? 1 : -1; }
```

## Step 3: Transform Call Construction

```
43. Source Start: v.begin()
44. Source End:   v.end()
45. Dest Start:   w.begin()
46. Operation:    lambda (from above)

47. Call:
48. std::transform(v.begin(), v.end(), w.begin(), lambda);
```

## Step 4: Execution Trace (Debugger Mode)

```
49. Iteration 0:
50.   READ v[0] (10)
51.   OP   10 % 2 = 0 → 1
52.   WRITE w[0] (1)
53.   ADVANCE ptrs

54. Iteration 1:
55.   READ v[1] (23)
56.   OP   23 % 2 = 1 → -1
57.   WRITE w[1] (-1)
58.   ADVANCE ptrs

59. Iteration 2:
60.   READ v[2] (44)
61.   OP   ___
62.   WRITE ___
63.   ADVANCE ptrs

64. Iteration 3:
65.   READ v[3] (15)
66.   OP   ___
67.   WRITE ___
68.   ADVANCE ptrs

... (Finish trace for all items) ...
```

## Failures to Predict

```
F1. Output Size:
    Expected: w.size() == v.size()
    Failure: w not allocated → segmentation fault or overwrite ✗

F2. Overlap:
    Expected: source and dest non-overlapping (or identical)
    Failure: overlapping but not aligned → undefined behavior ✗

F3. Type Mismatch:
    Expected: lambda returns int
    Failure: lambda returns bool (true/false) → w contains 0/1 instead of -1/1 ✗
```
