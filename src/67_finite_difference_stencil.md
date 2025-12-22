01. RAM | 0x1000=1.0 | 0x1008=2.0 | 0x1010=5.0 | 0x1018=4.0 | 0x1020=1.0 |
02. Ptr | src=0x1000 | type=double* | sizeof(double)=8 |
03. i=1 | target output index.
04. Addr(center) → src + i*8 → 0x1000 + 1*8 = 0x1008.
05. Addr(left)   → src + (i-1)*8 → 0x1000 + 0 = 0x1000.
06. Addr(right)  → src + (i+1)*8 → 0x1000 + 16 = 0x1010.
07. Val(center)  → *0x1008 = 2.0.
08. Val(left)    → *0x1000 = 1.0.
09. Val(right)   → *0x1010 = 5.0.
10. Stencil      → c_left*1.0 + c_center*2.0 + c_right*5.0.
11. Constants    → c_left=1.0, c_center=-2.0, c_right=1.0.
12. Calc         → (1.0*1.0) + (-2.0*2.0) + (1.0*5.0).
13. Calc Step 1  → 1.0 - 4.0 + 5.0.
14. Result       → 2.0.
15. Dest Addr    → dst + i*8 → 0x2000 + 8 = 0x2008.
16. Op           → *0x2008 = 2.0.
17. i=2          → target output index.
18. Addr(center) → 0x1000 + 2*8 = 0x1010 (5.0).
19. Addr(left)   → 0x1010 - 8 = 0x1008 (2.0).
20. Addr(right)  → 0x1010 + 8 = 0x1018 (4.0).
21. Calc         → (1.0*2.0) + (-2.0*5.0) + (1.0*4.0).
22. Calc Step 1  → 2.0 - 10.0 + 4.0.
23. Result       → -4.0.
24. Store        → dst[2] = -4.0.
25. i=3          → target output index.
26. Addr(center) → 0x1018 (4.0).
27. Addr(left)   → 0x1010 (5.0).
28. Addr(right)  → 0x1020 (1.0).
29. Calc         → (1.0*5.0) + (-2.0*4.0) + (1.0*1.0).
30. Calc Step 1  → 5.0 - 8.0 + 1.0.
31. Result       → -2.0.
32. Store        → dst[3] = -2.0.
33. i=0          → BOUNDARY. Left=0x0FF8 (Outside) → ✗ SKIP.
34. i=4          → BOUNDARY. Right=0x1028 (Outside) → ✗ SKIP.
35. Loop Range   → i=1 to N-2 (inclusive) OR i=1 to i < N-1.
36. Check        → N=5. i < 4. Loops: 1, 2, 3. ✓.
37. Pointer Math → src_ptr[i] ≡ *(src_ptr + i).
38. Pointer Math → src_ptr[i-1] ≡ *(src_ptr + i - 1).
39. Pointer Math → src_ptr[i+1] ≡ *(src_ptr + i + 1).
40. User Task    → Fill C++ code with these exact offsets.
