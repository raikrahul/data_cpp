# 41_inheritance_virtual_worksheet

## START FROM MIDDLE: You have ptr=0x6000_0000, you want to call get_distance(). What happens?

001. ptr=0x6000_0000 → this is address of some object → you do not know what type yet → read first 8 bytes at 0x6000_0000 → result = ? (you fill this)
002. *(void**)0x6000_0000 = 0x400200 → this 8-byte value is called what? → where does 0x400200 point to? → section of executable = ?
003. 0x400200 is start of a table → table entry [0] at 0x400200+0 = ? → table entry [1] at 0x400200+8 = ? → which entry is get_distance? → which entry is destructor?
004. Read *(void**)(0x400200 + 0) = 0x403000 → this is address of what? → in which section? → .text or .rodata?
005. CPU executes: CALL 0x403000 with RDI=0x6000_0000 → why RDI? → what calling convention?
006. Inside function at 0x403000, code reads this->cx → what is offset of cx from this? → this+0 = vptr → this+8 = ? → read *(double*)(0x6000_0000 + 8) = ?

## YOU FILL: What is at each offset of object at 0x6000_0000?

```
0x6000_0000: [________] ← 8 bytes, you write what goes here
0x6000_0008: [________] ← 8 bytes, field name = ?, value = ?
0x6000_0010: [________] ← 8 bytes, field name = ?, value = ?
0x6000_0018: [________] ← 8 bytes, field name = ?, value = ?
```

007. Total bytes = ? → sizeof(this_object) = ?
008. If Circle has 3 doubles (cx, cy, r), why is sizeof not 24? → what is the extra 8 bytes?

## BEFORE YOU WRITE ANY CODE: Draw vector state

009. std::vector<T> has 3 pointers internally: _M_start, _M_finish, _M_end_of_storage → sizeof(vector) on stack = ?
010. Empty vector: _M_start=0x0, _M_finish=0x0, _M_end=0x0 → size() = _M_finish - _M_start = ? → capacity() = _M_end - _M_start = ?

```
Stack 0x7fff_e000: vector struct
+0x00: _M_start  = [________]
+0x08: _M_finish = [________]
+0x10: _M_end    = [________]
```

011. You call push_back(make_unique<Circle>(1,3,4)) → what happens first? → make_unique calls what? → new Circle(...) returns what address?
012. new Circle(1,3,4) → malloc(32) returns 0x6000_0000 → Circle constructor runs → writes vptr at offset 0 → vptr value = ? (you derive this)
013. vptr comes from where? → compiler generated → stored in which section? → address depends on linker

## YOU CALCULATE: Circle constructor writes these bytes

```
Circle c(1.0, 3.0, 4.0);
Object at 0x6000_0000:

Offset 0x00: vptr = 0x400200 (given)
Offset 0x08: cx = 1.0 → IEEE 754 double = 0x3ff0_0000_0000_0000 → little-endian bytes = [00 00 00 00 00 00 f0 3f]
Offset 0x10: cy = 3.0 → IEEE 754 double = ? → you calculate → 3.0 = 1.5 * 2^1 = (1 + 0.5) * 2^1 → exponent = 1023 + 1 = 1024 = 0x400 → mantissa = 0.5 = 0x8000000000000 → combined = ?
Offset 0x18: r = 4.0 → IEEE 754 double = ? → 4.0 = 1.0 * 2^2 → exponent = 1023 + 2 = 1025 = 0x401 → mantissa = 0 → combined = ?
```

014. After new returns 0x6000_0000 → make_unique wraps this in unique_ptr → unique_ptr stores what internally? → just the raw pointer → sizeof(unique_ptr<Circle>) = ?
015. push_back(unique_ptr&&) → vector needs to store this pointer → current capacity = 0 → must allocate → malloc(8) returns 0x6001_0000 → writes [0x6000_0000] at 0x6001_0000

```
After first push_back:
Stack 0x7fff_e000:
+0x00: _M_start  = 0x6001_0000
+0x08: _M_finish = 0x6001_0008  ← why 0008? → 0000 + sizeof(unique_ptr) = 0000 + 8 = 0008
+0x10: _M_end    = 0x6001_0008  ← capacity = 1

Heap 0x6001_0000 (vector's internal array):
[0]: 0x6000_0000  ← this is the Circle object address
```

016. You call push_back(make_unique<Rectangle>(0,0,5,4)) → new Rectangle returns 0x6000_0040 → unique_ptr wraps it → push_back needs to store second element
017. Current capacity = 1, size = 1 → need capacity 2 → realloc? no → malloc(16) returns 0x6002_0000 → copy old array → free old array

## YOU TRACE: What happens during vector resize?

```
Before resize:
Heap 0x6001_0000: [0x6000_0000]  ← old array, cap=1

During resize:
1. malloc(16) → 0x6002_0000
2. Move element: read 0x6001_0000 → value = 0x6000_0000 → write to 0x6002_0000
3. Write new element: write 0x6000_0040 to 0x6002_0008
4. free(0x6001_0000)

After resize:
Heap 0x6002_0000: [0x6000_0000, 0x6000_0040]  ← new array, cap=2

Stack 0x7fff_e000:
+0x00: _M_start  = 0x6002_0000  ← CHANGED
+0x08: _M_finish = 0x6002_0010  ← 0000 + 2*8 = 0010
+0x10: _M_end    = 0x6002_0010
```

018. TRAP: If you held pointer p = &vec[0] before push_back → p was 0x6001_0000 → after push_back → p is now dangling → free'd memory → UB

## YOU CALCULATE: Distance formula step by step

019. Line equation: Ax + By + C = 0 → given A=1, B=-1, C=2 → this is line x - y + 2 = 0
020. Point (px, py) distance to line = |A*px + B*py + C| / sqrt(A² + B²)
021. Circle center = (1, 3), radius = 4
022. Numerator = |A*cx + B*cy + C| = |1*1 + (-1)*3 + 2| = |1 - 3 + 2| = |0| = 0
023. Denominator = sqrt(1² + (-1)²) = sqrt(1 + 1) = sqrt(2) = ?

## YOU CALCULATE: sqrt(2) by hand (Newton-Raphson)

```
sqrt(2): find x where x² = 2
Initial guess: x₀ = 1.5
Iteration 1: x₁ = (x₀ + 2/x₀) / 2 = (1.5 + 2/1.5) / 2 = (1.5 + 1.333) / 2 = 2.833 / 2 = 1.4166
Iteration 2: x₂ = (1.4166 + 2/1.4166) / 2 = (1.4166 + 1.4118) / 2 = 2.8284 / 2 = 1.4142
Iteration 3: x₃ = (1.4142 + 2/1.4142) / 2 = (1.4142 + 1.4142) / 2 = 1.4142
Converged: sqrt(2) ≈ 1.41421356
```

024. Distance from center to line = 0 / 1.41421356 = 0.0
025. Distance from circle surface to line = 0.0 - radius = 0.0 - 4.0 = -4.0

## TRAP: What does -4.0 mean?

026. Negative distance means what? → line passes through interior → "penetration depth" = 4.0 → or should you clamp to 0? → depends on specification

## YOU CALCULATE: Rectangle corners

027. Rectangle = (x1=0, y1=0, x2=5, y2=4) → 4 corners: (0,0), (5,0), (5,4), (0,4)
028. Corner (0,0): |1*0 + (-1)*0 + 2| / 1.4142 = |0 + 0 + 2| / 1.4142 = 2 / 1.4142 = ?

## YOU CALCULATE: 2 / 1.4142 by hand

```
2.0000 / 1.4142 = ?
1.4142 * 1 = 1.4142  → 2.0000 - 1.4142 = 0.5858 → quotient so far: 1
0.5858 * 10 = 5.858  → 1.4142 * 4 = 5.6568 → 5.858 - 5.6568 = 0.2012 → quotient: 1.4
0.2012 * 10 = 2.012  → 1.4142 * 1 = 1.4142 → 2.012 - 1.4142 = 0.5978 → quotient: 1.41
0.5978 * 10 = 5.978  → 1.4142 * 4 = 5.6568 → 5.978 - 5.6568 = 0.3212 → quotient: 1.414
∴ 2 / 1.4142 ≈ 1.4142
```

029. Corner (5,0): |1*5 + (-1)*0 + 2| / 1.4142 = |7| / 1.4142 = 7 / 1.4142 = ?
030. Corner (5,4): |1*5 + (-1)*4 + 2| / 1.4142 = |5 - 4 + 2| / 1.4142 = |3| / 1.4142 = ?
031. Corner (0,4): |1*0 + (-1)*4 + 2| / 1.4142 = |0 - 4 + 2| / 1.4142 = |-2| / 1.4142 = 2 / 1.4142 = 1.4142

## YOU CALCULATE: 7 / 1.4142 and 3 / 1.4142 by long division

032. 7 / 1.4142 = ?
033. 3 / 1.4142 = ?
034. Minimum of {1.4142, ?, ?, 1.4142} = ?

## VTABLE DISPATCH: You trace by hand

035. Loop iteration 0: vec[0] = 0x6000_0000 → read *(void**)0x6000_0000 = 0x400200 → read *(void**)0x400200 = 0x403000 → CALL 0x403000
036. Loop iteration 1: vec[1] = 0x6000_0040 → read *(void**)0x6000_0040 = ? → you need to know Rectangle's vptr → different from Circle's vptr → why?

## TRAP: sizeof calculation

037. You think sizeof(Circle) = 3 * sizeof(double) = 3 * 8 = 24 → WRONG → actual = 32 → extra 8 bytes = ?
038. You think sizeof(Rectangle) = 4 * sizeof(double) = 4 * 8 = 32 → WRONG → actual = 40 → extra 8 bytes = ?
039. You think sizeof(unique_ptr<T>) = 16 or 24 (like shared_ptr) → WRONG → actual = 8 → why?

## YOU WRITE CODE: One block at a time after filling above

Block 1: Write struct Shape with virtual destructor and pure virtual get_distance
Block 2: Write struct Circle with cx, cy, r and constructor
Block 3: Write Circle::get_distance using formula you derived above
Block 4: Write struct Rectangle with x1, y1, x2, y2 and constructor
Block 5: Write Rectangle::get_distance returning min of 4 corner distances
Block 6: Write main() creating vector, pushing shapes, calling get_distance in loop

## BEFORE BLOCK 1: Answer these

Q1: Why virtual destructor? What happens without it when you do delete ptr where ptr is Shape*?
Q2: Why = 0 at end of get_distance declaration?
Q3: Why const at end of get_distance?

## BEFORE BLOCK 2: Answer these

Q4: What is offset of cx inside Circle object? (not 0)
Q5: What is offset of cy inside Circle object?
Q6: What is offset of r inside Circle object?

## BEFORE BLOCK 3: Answer these

Q7: What is std::hypot(A, B)? How is it different from sqrt(A*A + B*B)?
Q8: Why std::abs and not abs?

## BEFORE BLOCK 5: Answer these

Q9: std::min({a,b,c,d}) takes initializer_list → what header?
Q10: Lambda [&](double x, double y) captures what? By reference or value?

## IEEE 754 EXERCISE: You verify

040. 1.0 = (-1)^0 * 1.0 * 2^0 → sign=0, exponent=1023=0x3ff, mantissa=0 → 64-bit = 0x3ff0_0000_0000_0000 ✓
041. 3.0 = (-1)^0 * 1.5 * 2^1 → sign=0, exponent=1024=0x400, mantissa=0.5=0x8000000000000 → 64-bit = 0x4008_0000_0000_0000 ✓
042. 4.0 = (-1)^0 * 1.0 * 2^2 → sign=0, exponent=1025=0x401, mantissa=0 → 64-bit = 0x4010_0000_0000_0000 ✓
043. 5.0 = (-1)^0 * 1.25 * 2^2 → sign=0, exponent=1025=0x401, mantissa=0.25=? → 64-bit = ?

## MEMORY DUMP EXERCISE: You fill little-endian bytes

044. 0x3ff0_0000_0000_0000 as bytes at 0x6000_0008: [00 00 00 00 00 00 f0 3f] ← why reversed?
045. 0x4008_0000_0000_0000 as bytes at 0x6000_0010: [__ __ __ __ __ __ __ __] ← you fill
046. 0x4010_0000_0000_0000 as bytes at 0x6000_0018: [__ __ __ __ __ __ __ __] ← you fill

## DESTRUCTOR CHAIN: You trace

047. } end of main → vector destructor runs → for i=0 to size-1: unique_ptr[i].~unique_ptr() → delete ptr → this calls what function?
048. delete ptr where ptr=Shape* pointing to Circle → if ~Shape is virtual → vtable lookup → calls ~Circle() first → then ~Shape() → then free(ptr)
049. If ~Shape is NOT virtual → no vtable lookup → calls ~Shape() directly → ~Circle() never called → if Circle had resources → leaked

## YOU VERIFY: Run this and check output matches your hand calculations

```cpp
// After you fill all above, write this code:
std::vector<std::unique_ptr<Shape>> v;
v.push_back(std::make_unique<Circle>(1,3,4));
v.push_back(std::make_unique<Rectangle>(0,0,5,4));
double A=1, B=-1, C=2;
std::cout << v[0]->get_distance(A,B,C) << "\n";  // your prediction: ?
std::cout << v[1]->get_distance(A,B,C) << "\n";  // your prediction: ?
```
