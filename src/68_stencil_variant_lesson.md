01. N=10, sizeof(double)=8 → total bytes for U = 10×8 = ____ → fill this.
02. U starts at 0x1000 → U[0]=0x1000, U[1]=0x1000+8=0x1008, U[2]=0x1000+16=0x____ → fill this.
03. U[9] address = 0x1000 + 9×8 = 0x1000 + 72 = 0x1000 + 0x48 = 0x____ → fill this.
04. U_end_address = U[9] + 7 = 0x1048 + 7 = 0x____ → fill this (last byte of last element).
05. nodes starts at 0x2000, sizeof(variant<Dirichlet,O2,O4>) = ? → Dirichlet has 1 double (8 bytes), O2 has 1 double (8 bytes), O4 has 1 double (8 bytes) → max = 8, discriminator = 1 byte → 9 bytes → align to 8 → ____ bytes.
06. 10 nodes × 16 bytes = ____ bytes total.
07. nodes[0]=0x2000, nodes[1]=0x2000+16=0x2010, nodes[2]=0x____ → fill this.
08. nodes[9] address = 0x2000 + 9×16 = 0x2000 + 144 = 0x2000 + 0x90 = 0x____ → fill this.
09. nodes_end_address = 0x2090 + 15 = 0x____ → fill this.
10. new_U must start AFTER 0x209F → choose 0x____ (next 64-byte aligned address after 0x209F).
11. 0x209F / 64 = 0x209F / 0x40 → 0x209F = 8351 decimal → 8351 / 64 = 130.48... → ceil = 131 → 131 × 64 = 8384 = 0x____ → fill this.
12. new_U starts at 0x20C0 → new_U[0]=0x20C0, new_U[9]=0x20C0+72=0x____ → fill this.
13. TRAP CHECK: Does new_U overlap nodes? nodes ends at 0x209F, new_U starts at 0x20C0 → 0x20C0 > 0x209F → ____ (✓ or ✗).
14. U_raw = {0.0, 0.588, 0.951, 0.951, 0.588, 0.0, -0.588, -0.951, -0.951, -0.588} → copy to U[0..9].
15. nodes config: i=0 Dirichlet(val=0.0), i=1 O2(a=1.0), i=2 O2(a=1.0), i=3 O4(a=1.0), i=4 O4(a=1.0), i=5 O4(a=1.0), i=6 O2(a=1.0), i=7 O2(a=1.0), i=8 O2(a=1.0), i=9 Dirichlet(val=0.0).
16. i=0 (Dirichlet) → new_U[0] = val = 0.0 → no calculation needed → new_U[0] = ____.
17. i=1 (O2) → needs U[i-1], U[i], U[i+1] → needs U[0], U[1], U[2] → indices {0,1,2} ⊆ {0..9} ✓.
18. i=1: val_left = U[0] = 0.0, val_center = U[1] = 0.588, val_right = U[2] = 0.951.
19. i=1: O2 weights = {-0.5, 0.0, +0.5} → s = (-0.5)×0.0 + (0.0)×0.588 + (+0.5)×0.951.
20. i=1: term₁ = -0.5 × 0.0 = ____.
21. i=1: term₂ = 0.0 × 0.588 = ____.
22. i=1: term₃ = +0.5 × 0.951 = 0.951 / 2 = ____.
23. i=1: s = 0.0 + 0.0 + 0.4755 = ____.
24. i=1: dt = 0.1, a = 1.0 → Δ = a × dt × s = 1.0 × 0.1 × 0.4755 = ____.
25. i=1: new_U[1] = U[1] + Δ = 0.588 + 0.04755 = ____.
26. i=2 (O2) → needs U[1], U[2], U[3] → U[1]=0.588, U[2]=0.951, U[3]=0.951.
27. i=2: term₁ = -0.5 × 0.588 = ____.
28. i=2: term₂ = 0.0 × 0.951 = ____.
29. i=2: term₃ = +0.5 × 0.951 = ____.
30. i=2: s = -0.294 + 0.0 + 0.4755 = ____.
31. i=2: Δ = 0.1 × 0.1815 = ____.
32. i=2: new_U[2] = 0.951 + 0.01815 = ____.
33. i=3 (O4) → needs U[i-2], U[i-1], U[i], U[i+1], U[i+2] → needs U[1], U[2], U[3], U[4], U[5].
34. i=3: indices {1,2,3,4,5} ⊆ {0..9} ✓.
35. i=3: U[1]=0.588, U[2]=0.951, U[3]=0.951, U[4]=0.588, U[5]=0.0.
36. i=3: O4 weights = {+1/12, -2/3, 0, +2/3, -1/12}.
37. i=3: 1/12 = 0.08333..., 2/3 = 0.66666....
38. i=3: term₁ = (+1/12) × U[1] = (+1/12) × 0.588.
39. i=3: 0.588 / 12 = ? → 588 / 12 = 49 → 0.588 / 12 = ____.
40. i=3: term₂ = (-2/3) × U[2] = (-2/3) × 0.951.
41. i=3: 0.951 × 2 = 1.902 → 1.902 / 3 = 0.634 → term₂ = -____.
42. i=3: term₃ = 0 × U[3] = 0 × 0.951 = ____.
43. i=3: term₄ = (+2/3) × U[4] = (+2/3) × 0.588.
44. i=3: 0.588 × 2 = 1.176 → 1.176 / 3 = ____.
45. i=3: term₅ = (-1/12) × U[5] = (-1/12) × 0.0 = ____.
46. i=3: s = 0.049 + (-0.634) + 0.0 + 0.392 + 0.0 = ____.
47. i=3: Δ = 0.1 × (-0.193) = ____.
48. i=3: new_U[3] = 0.951 + (-0.0193) = ____.
49. i=4 (O4) → needs U[2], U[3], U[4], U[5], U[6].
50. i=4: U[2]=0.951, U[3]=0.951, U[4]=0.588, U[5]=0.0, U[6]=-0.588.
51. i=4: term₁ = (+1/12) × 0.951 = 0.951 / 12 = ? → 951 / 12 = 79.25 → 0.951 / 12 = ____.
52. i=4: term₂ = (-2/3) × 0.951 = ____ (same as i=3 term₂).
53. i=4: term₃ = 0.
54. i=4: term₄ = (+2/3) × 0.0 = ____.
55. i=4: term₅ = (-1/12) × (-0.588) = +0.588/12 = ____.
56. i=4: s = 0.07925 + (-0.634) + 0.0 + 0.0 + 0.049 = ____.
57. i=4: Δ = 0.1 × (-0.50575) = ____.
58. i=4: new_U[4] = 0.588 + (-0.050575) = ____.
59. i=5 (O4) → needs U[3], U[4], U[5], U[6], U[7].
60. i=5: U[3]=0.951, U[4]=0.588, U[5]=0.0, U[6]=-0.588, U[7]=-0.951.
61. i=5: term₁ = (+1/12) × 0.951 = ____.
62. i=5: term₂ = (-2/3) × 0.588 = ____.
63. i=5: term₃ = 0.
64. i=5: term₄ = (+2/3) × (-0.588) = ____.
65. i=5: term₅ = (-1/12) × (-0.951) = ____.
66. i=5: s = 0.07925 + (-0.392) + 0.0 + (-0.392) + 0.07925 = ____.
67. i=5: Δ = 0.1 × s = ____.
68. i=5: new_U[5] = 0.0 + Δ = ____.
69. i=6 (O2) → needs U[5], U[6], U[7] → U[5]=0.0, U[6]=-0.588, U[7]=-0.951.
70. i=6: s = (-0.5)×0.0 + (0.0)×(-0.588) + (+0.5)×(-0.951) = ____.
71. i=6: Δ = 0.1 × (-0.4755) = ____.
72. i=6: new_U[6] = -0.588 + (-0.04755) = ____.
73. i=7 (O2) → needs U[6], U[7], U[8] → U[6]=-0.588, U[7]=-0.951, U[8]=-0.951.
74. i=7: s = (-0.5)×(-0.588) + (0.0)×(-0.951) + (+0.5)×(-0.951) = ____.
75. i=7: 0.294 + 0.0 + (-0.4755) = ____.
76. i=7: Δ = 0.1 × (-0.1815) = ____.
77. i=7: new_U[7] = -0.951 + (-0.01815) = ____.
78. i=8 (O2) → needs U[7], U[8], U[9] → U[7]=-0.951, U[8]=-0.951, U[9]=-0.588.
79. i=8: s = (-0.5)×(-0.951) + (0.0)×(-0.951) + (+0.5)×(-0.588) = ____.
80. i=8: 0.4755 + 0.0 + (-0.294) = ____.
81. i=8: Δ = 0.1 × 0.1815 = ____.
82. i=8: new_U[8] = -0.951 + 0.01815 = ____.
83. i=9 (Dirichlet) → new_U[9] = val = ____.
84. VERIFY SYMMETRY: new_U[1] + new_U[8] = 0.63555 + (-0.93285) = ? → should be negative of (new_U[8] pattern) → check anti-symmetry.
85. VERIFY: new_U[1] = 0.63555, new_U[8] = -0.93285 → 0.63555 + 0.93285 = 1.5684 ≠ 0 → anti-symmetry broken? → recheck calculations.
86. BOUNDARY CHECK i=1 (O2): min_index = 1-1 = 0 ✓, max_index = 1+1 = 2 ✓ → valid.
87. BOUNDARY CHECK i=3 (O4): min_index = 3-2 = 1 ✓, max_index = 3+2 = 5 ✓ → valid.
88. FAILURE MODE F1: O4 at i=1 → min_index = 1-2 = -1 → U[-1] access → SEGFAULT ✗.
89. FAILURE MODE F2: O4 at i=8 → max_index = 8+2 = 10 → U[10] access (N=10, max valid = 9) → SEGFAULT ✗.
90. FAILURE MODE F3: In-place update U[i] = ... while loop reads U[i-1] → corrupts data for next iteration ✗.
91. FAILURE MODE F4: Integer division 1/12 = 0 in C++ → use 1.0/12.0 = 0.08333... ✓.
92. FAILURE MODE F5: Dirichlet uses += instead of = → boundary drifts ✗.
93. FAILURE MODE F6: variant_size assumed 8 but actual 16 → nodes buffer too small → overlap ✗.
94. FAILURE MODE F7: Forgot dt factor → Δ = s instead of Δ = a × dt × s → magnitude 10× too large ✗.
95. CODE TODO 1: In loop body, read U[i-1] using pointer *(src_ptr + i - 1).
96. CODE TODO 2: In loop body, read U[i] using pointer *(src_ptr + i).
97. CODE TODO 3: In loop body, read U[i+1] using pointer *(src_ptr + i + 1).
98. CODE TODO 4: Compute s = w_left × val_left + w_center × val_center + w_right × val_right.
99. CODE TODO 5: Compute Δ = a × dt × s.
100. CODE TODO 6: Store result *(dst_ptr + i) = U[i] + Δ.
