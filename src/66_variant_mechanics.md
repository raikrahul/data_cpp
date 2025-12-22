
01. 0x0000 → sizeof(int) → 4 bytes.
02. 0x0000 → sizeof(double) → 8 bytes.
03. Union{int, double} → Max(4, 8) → 8 bytes.
04. Variant{int, double} → Union + Discriminator(index).
05. Index type → size_t (usually) or smaller → let's assume 8 bytes for alignment on 64-bit.
06. Alignment(double) → 8 bytes.
07. Alignment(Variant) → LCM(8, 8) → 8 bytes.
08. Structure: [ Union (8 bytes) ] [ Discriminator (? bytes) ] [ Padding (? bytes) ].
09. Hypothesis A (Min): [ Data(8) ] [ Index(1, byte) ] [ Pad(7) ] → Total 16 bytes.
10. Hypothesis B (Packed): [ Data(8) ] [ Index(4) ] [ Pad(4) ] → Total 16 bytes.
11. Actual: sizeof(std::variant<int, double>) → check compiler output.

12. Operation: `std::variant<int, double> v = 10;`
13. Memory 0x1000: [ 10 (4 bytes) | garbage(4 bytes) ] [ Index = 0 (int) ] ...
14. v.index() → 0.
15. Access: `std::get<0>(v)` → returns *(int*)0x1000 → 10 ✓.
16. Access: `std::get<int>(v)` → returns *(int*)0x1000 → 10 ✓.
17. Access: `std::get<1>(v)` → index(0) != requested(1) → THROW `bad_variant_access` ✗.
18. Access: `std::get<double>(v)` → index(0) != index(double) → THROW `bad_variant_access` ✗.
19. Access: `std::get_if<0>(&v)` → returns (int*)0x1000 ✓.
20. Access: `std::get_if<1>(&v)` → returns nullptr ∅.

21. Operation: `v = 3.14;`
22. Memory 0x1000: [ 3.14 (double, 8 bytes) ] [ Index = 1 (double) ] ...
23. v.index() → 1.
24. Access: `std::get<int>(v)` → index(1) != index(int) → THROW ✗.
25. Access: `std::get<double>(v)` → index(1) == index(double) → returns *(double*)0x1000 → 3.14 ✓.

26. ------------------------------------------------------------------------------------------------
27. CALCULATION: `sizeof` variants.
28. Case 1: `variant<char, char>`
29. Union size: 1 byte. Align: 1 byte. Index: 1 byte (likely). Padding: 0. Total: 2 or so? 
30. Stop! Library implementation dependent. Index usually follows alignment of max type? No, usually separate member.
31. Common implementation: `struct { recursive_union data; unsigned char index; }`.
32. `variant<char>` → [char(1)] [index(1)] → total 2 bytes? Alignment 1.
33. Wait, index optimization exists? `variant<T>` with `valueless_by_exception` capability needs index.
34. Let's calculate for `variant<int, double>`.
35. Max_Align = alignof(double) = 8.
36. Union_Size = 8.
37. Index typically `unsigned int` or `size_t` or `unsigned char`?
38. GCC/Clang: index usually occupies following bytes.
39. Offset of index = 8.
40. Size so far = 8 + sizeof(index).
41. Padding to multiple of 8.
42. If index is 1 byte, Size = 9, Pad → 16.
43. If index is 4 bytes, Size = 12, Pad → 16.
44. ∴ Expected sizeof `variant<int, double>` = 16.

45. ------------------------------------------------------------------------------------------------
46. VISITATION MECHANICS.
47. `std::visit(lambda, v)`
48. Input: `v` (index=1, value=3.14), `lambda` (generic).
49. Internal Switch:
50. switch(v.index()) {
51.   case 0: return lambda( v.get<0>() ); // int
52.   case 1: return lambda( v.get<1>() ); // double
53. }
54. Code Gen → generates N branches.
55. Binary size → O(Types).
56. Runtime overhead → switch/jump table.

57. ------------------------------------------------------------------------------------------------
58. MATRIX VISITATION (Double Dispatch).
59. `std::visit(lambda, v1, v2)`
60. Types: v1 {A, B}, v2 {X, Y}.
61. Combinations: (A,X), (A,Y), (B,X), (B,Y).
62. Switch Structure:
63. switch(v1.index()) {
64.   case 0 (A):
65.     switch(v2.index()) {
66.       case 0 (X): lambda(A, X);
67.       case 1 (Y): lambda(A, Y);
68.     }
69.   case 1 (B):
70.     switch(v2.index()) {
71.       case 0 (X): lambda(B, X);
72.       case 1 (Y): lambda(B, Y);
73.     }
74. }
75. branches = N1 × N2.

76. ------------------------------------------------------------------------------------------------
77. FAILURE PREDICTIONS (As requested).
78. F1. Accessing wrong type → `std::get<int>(double_variant)` → throws Exception → CRASH if uncaught.
79. F2. Using `get_if` incorrectly → returns nullptr → dereferencing nullptr → SEGFAULT.
80. F3. Assuming `sizeof(variant<A,B>)` == `sizeof(A) + sizeof(B)` → WRONG. It's `max(A,B) + overhead`.
81. F4. `valueless_by_exception` → exception during assignment → variant loses value → index becomes `npos` (-1).
82. F5. Passing variant by value to visit → strict copy → expensive if types are large. Use `const &`.
83. F6. Visitor not handling all types → compile error (if lambda is not generic/auto). 
84. F7. Thinking variant allocates heap memory → NO. It is stack/inline only.
85. F8. Pointer invalidation → reassigning variant to different type invalidates pointers to old content.

86. ------------------------------------------------------------------------------------------------
87. YOUR TURN.
88. Calculate: sizeof(std::variant<char, float, long double>)
89. Data: char(1, align 1), float(4, align 4), long double(16, align 16).
90. Union Size = max(1, 4, 16) = 16.
91. Alignment = max(1, 4, 16) = 16.
92. Index offset = 16.
93. Index size = ? (likely 1 or 4).
94. Total size = 16 + index + pad to 16.
95. If index=1, size=17 -> pad to 32? (User check on machine).

96. Calculate: Number of generated paths for `visit(f, v1, v2, v3)` where size(v)=3.
97. 3 × 3 × 3 = 27 paths.
98. Binary bloat warning.

99. ------------------------------------------------------------------------------------------------
100. ASSEMBLY & CYCLE ANALYSIS (Block 2 & 5 Derivation).
101. Initialization: `variant<int,double> v = 4;`
102. Action: Store tag=0 (int) at `v.index_offset`. Store value=4 at `v.data_offset`.
103. ASM: `mov [base+offset_tag], 0` → 1 cycle.
104. ASM: `mov [base+offset_data], 4` → 1 cycle.
105. Total Init Cost: ~2 cycles.
106. Compare Union: `u.i = 4` → `mov [base], 4` → 1 cycle. 
107. ∴ Variant Overhead = 1 cycle (tag write).

108. Access: `std::get<int>(v)`
109. ASM: `cmp [base+offset_tag], 0` → Check tag.
110. ASM: `jne throw_label` → Branch if wrong.
111. ASM: `mov reg, [base+offset_data]` → Load value.
112. Cost: 1 cycle (cmp) + 1 cycle (jmp predict) + 1 cycle (load) = 3 cycles.
113. Compare Union: `u.i` → `mov` → 1 cycle.
114. ∴ Safety Cost = 2 cycles.
115. Scale: 1,000,000 accesses → 2,000,000 extra cycles ≈ 0.67ms @ 3GHz.

116. Visitiation vs Virtual Dispatch (Block 5).
117. Scenario: 10,000 objects, 60 FPS.
118. Virtual Call: Load vptr → Load func ptr → Call indirect.
119. Cost: ~7 cycles (L1/L2 hits) + branch mispredict risk.
120. Variant Visit: Load tag → Jump Table [tag] → Jump indirect.
121. Cost: ~3-4 cycles + no branch sequence divergence (if sorted).
122. Calculation:
123. Virtual: 10,000 × 7 = 70,000 cycles.
124. Variant: 10,000 × 3 = 30,000 cycles.
125. Savings per frame: 40,000 cycles.
126. Total per second: 40,000 × 60 = 2,400,000 cycles.
127. Time saved @ 3GHz: 2.4M / 3G ≈ 0.8ms.

128. ------------------------------------------------------------------------------------------------
129. MEMORY WASTE CALCULATION (Block 4).
130. Type: `variant<int, double, std::string>`.
131. Max Size: `sizeof(std::string)` ≈ 32 bytes (libstdc++).
132. Max Align: 8 bytes.
133. Tag: 1-4 bytes.
134. Total Size: 32 (data) + 8 (tag+pad) = 40 bytes.
135. Case: Holding `int` (4 bytes).
136. Used: 4 bytes. Wasted: 36 bytes.
137. Overhead Ratio: 36/4 = 9x or 900%.
138. Scenario: 1,000,000 integers stored this way.
139. Raw `vector<int>`: 4MB.
140. `vector<variant>`: 40MB.
141. Cache Impact: 40MB >> 8MB L3 Cache. Wastes bandwidth.
142. Conclusion → ✗ Bad for homogeneous primitive data.

143. ------------------------------------------------------------------------------------------------
144. GPU WARP DIVERGENCE (Block 6 Derivation).
145. Architecture: Warp = 32 threads. Lock-step execution.
146. Virtual Method:
147. Thread 0..15: Type A (func A). Thread 16..31: Type B (func B).
148. Execution: Run A (16 active, 16 stall) → switch → Run B (16 stall, 16 active).
149. Throughput: 50%.
150. Variant Method:
151. Structure: Array of `variant` (aligned uniform size).
152. Coalescing: Load `v[tid]` → 1 transaction (perfect).
153. Dispatch: `switch(tag)`.
154. If tag distribution random → same divergence as virtual.
155. If sorted by tag → Wait! Sort variants by index first.
156. Sorted: Threads 0..31 all tag=0.
157. Execution: Run Case 0 (32 active). No divergence.
158. ∴ Variant + Sort >> Virtual.

159. ------------------------------------------------------------------------------------------------
160. HANDS-ON EXERCISES (From User Request).
161. Exercise 1: Memory Map Drawing.
162. Input: `variant<int, double>` at 0x3000. Value: `double 3.14159`.
163. Tag Map: 0=int, 1=double.
164. Hex(3.14159) ≈ 0x4048F5C3 (float) / 0x400921FB54442D18 (double).
165. Action: Draw bytes at 0x3000..0x300F.
166. Address | Value (Hex)        | Meaning
167. 0x3000  | 18 2D 44 54        | Double LSB (Data)
168. 0x3004  | FB 21 09 40        | Double MSB (Data)
169. 0x3008  | 01 00 00 00        | Tag = 1 (double)
170. 0x300C  | 00 00 00 00        | Padding (to 16)
171. Check size: 16 bytes ✓.

172. Exercise 2: Particle System Design.
173. Types: Fire (4B), Smoke (4B), Water (4B).
174. Variant: `variant<Fire, Smoke, Water>`. Size = 4 (union) + 4 (tag due to align) = 8 bytes.
175. Array: `std::vector<Particle>` (N=1M). Size = 8MB.
176. Compare Virtual: `Base*` pointers.
177. Storage: `vector<Base*>` (8MB pointers) + Heap Objects (16B header + 4B data = 20B/obj?).
178. Total Memory Virtual: 8MB + 20MB = 28MB.
179. Indirection: Random Heap Access → Cache Miss Hell.
180. Variant: Contiguous 8MB → Linear Prefetching.
181. ∴ Variant expected 3-4x speedup on iteration.
182. User Task: Implement this in separate file if interested.
