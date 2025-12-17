# C++ Containers & Memory Worksheet

## Exercise Structure

Each exercise: ASCII diagram → calculation → verify → edge case

---

## Part 1: Pointer Swap Mechanics

### Memory Layout Before

```
Address         Value       Variable
─────────────────────────────────────
0x7fff00001000  [  5  ]     a
0x7fff00001004  [  7  ]     b
0x7fff00001008  [  ?  ]     pa (pointer)
0x7fff00001010  [  ?  ]     pb (pointer)
0x7fff00001018  [  ?  ]     tmp
```

### YOUR TASK: Fill After Each Operation

Operation 1: `int *pa = &a;`

```
pa = 0x7fff00001000
```

Operation 2: `int *pb = &b;`

```
pb = 0x7fff00001004
```

Operation 3: `int tmp = *pa;`

```
tmp = 5
Calculation: Memory[pa] = Memory[0x7fff00001000] = 5
```

Operation 4: `*pa = *pb;`

```
Memory[0x7fff00001000] ← 7 (before: 5)
```

Operation 5: `*pb = tmp;`

```
Memory[0x7fff00001004] ← 5 (before: 7)
```

### Final State Verification

```
a = 7 (expected: 7)  ✓ or ✗ ?
b = 5 (expected: 5)  ✓ or ✗ ?
```

---

## Part 2: Reference Alias Mathematics

### Key Rule

```
int &ra = a;
∴ &ra == &a (same address)
∴ sizeof(ra) == sizeof(a) (no extra storage)
```

### YOUR TASK: Trace Reference Swap

```
Initial: Memory[0x7fff00001000] = 5, Memory[0x7fff00001004] = 7

int &ra = a;    → ra aliases address 0x0x7fff00001000_______________
int &rb = b;    → rb aliases address 0x0x7fff00001004_______________
int tmp = ra;   → tmp = Memory[0x0x7fff00001000______________________________] = 5
ra = rb;        → Memory[0x7fff00001000] ← _0x0x7fff00001004___________________
rb = tmp;       → Memory[0x7fff00001004] ← _0x0x7fff00001000__________________________________

Final: a = 7, b = 5
```

### Edge Case Question

```
int &ref;  // Uninitialized reference
Compiles? ✓ or ✗ : ✗
Why: _________________________________
```

## References must be set to some value

## Part 3: Vector Capacity Growth

### Growth Formula

```
new_capacity = (size + 1 > capacity) ? capacity × 2 : capacity
```

### YOUR TASK: Fill Capacity Table

| Operation        | size | capacity | Reallocation? | Bytes Copied |
| ---------------- | ---- | -------- | ------------- | ------------ |
| vector<int> v(3) | 3    | 3        | N/A           | 0            |
| v.push_back(10)  | 4    | 3        | ✓             | 0 bytes      |
| v.push_back(20)  | 5    | 6        | ✓             | 3 bytes      |
| v.push_back(30)  | 6    | 6        | ✓             | 3 bytes      |
| v.push_back(40)  | 7    | 12       | ✓             | 6 bytes      |

### Calculation Check

```
After 4 push_backs from size=3:
size = 3 + 4 = __7___
capacity sequence: 3 → _6__ → __12_
Total bytes copied = __6__ × sizeof(int) = __24__ bytes
```

---

## Part 4: Iterator Invalidation

### Memory Before push_back

```
v.data() = 0x5555555592a0
v.begin() → [10][20][30]
               ↑
              it = 0x5555555592a0
```

### YOUR TASK: After Reallocation

```
push_back(40) triggers reallocation:

Old address: 0x5555555592a0 (FREED)
New address: 0x5555555592c0

it still holds: 0x_0x5555555592a0______________
*it = crash_____________ (undefined/crash/value?)
```

### Edge Case: empty vector

```
vector<int> v;
v.begin() == v.end() ? ✓ or ✗ : ___yes__
*v.end() = ? _____________<0 ______________
v.pop_back() = ? _______________________
```

---

## Part 5: List vs Vector Memory

### List Node Structure (64-bit)

```
┌─────────────┬─────────────┬──────────┬─────────┐
│   prev      │   next      │  data    │ padding │
│  8 bytes    │  8 bytes    │ 4 bytes  │ 4 bytes │
└─────────────┴─────────────┴──────────┴─────────┘
Total = __24___ bytes per node
```

### YOUR TASK: Memory Comparison

| Container   | Elements | Memory Used      | Contiguous? |
| ----------- | -------- | ---------------- | ----------- | --- |
| vector<int> | 100      | **\_400** bytes  | ✓ or ✗      | yes |
| list<int>   | 100      | **\_2400** bytes | ✓ or ✗      | No  |

```
List overhead ratio = list_bytes / vector_bytes = _24____
```

### Cache Performance

```
Cache line = 64 bytes
vector: elements per cache line = 64 / 4 = 16_____
list: elements per cache line = 64 / 24 = 2_____ (floor)

Cache miss prediction:
vector 100 elements: _5____ cache misses
list 100 elements: 50_____ cache misses (worst case)
```

---

## Part 6: Smart Pointer Reference Counting

### Control Block State

```
shared_ptr<T> p1 = make_shared<T>();
┌──────────────────┐
│ strong_count = 1 │
│ weak_count = 1   │ (always +1 for control block itself)
│ object: T        │
└──────────────────┘
```

### YOUR TASK: Trace Reference Counts

| Operation                           | strong_count      | weak_count | Object Alive? |
| ----------------------------------- | ----------------- | ---------- | ------------- |
| shared_ptr<T> p1 = make_shared<T>() | 1                 | 1          | ✓             |
| shared_ptr<T> p2 = p1               | \_2\_\_           | \_2\_\_    | \_\_\_        |
| weak_ptr<T> w = p1                  | \_2\_\_           | \__2_      | yes           |
| p1.reset()                          | \_1\_\_           | \_1\_\_    | no            |
| p2.reset()                          | \_1\_\_           | \_1\_\_    | no            |
| w.lock() returns                    | nullptr or valid? |            |               |

### Edge Case: Cyclic Reference

```
struct Node {
    shared_ptr<Node> next;
    // weak_ptr<Node> prev;  // Fix: breaking cycle
};

Node A (next) → Node B (next) → Node A
Memory leak? ✓ or ✗ : ✓
Fix: replace backward shared_ptr with weak_ptr

YOUR CONFUSION:
"weak pointer means pointing to nothing?" NO.
"prev is weak so it is useless?" NO.

REALITY CHECK:
Head (strong) → A (strong) → B (strong) → null
                ↑            ↓
              (weak) ←────── (weak)

Head owns A. A owns B.
B can LOOK at A (via weak prev) because Head keeps A alive.
B does not need to OWN A.
```

---

## Part 7: Factory Pattern Trace

### Shape Factory Decision Tree

```
create(id):
  id == 1 → Circle(r=3.0)
  id == 2 → Rectangle(w=4.0, h=5.0)
  else    → nullptr

YOUR TASK: Calculate areas

Circle area = π × r² = 3.14159 × ___3.0___² = _________
Rectangle area = w × h = ___ × ___ = _________
```

### Heap Allocation Trace

```
create(1) called:
1. operator new(sizeof(Circle)) → address 0x555555559320
2. Circle constructor: this->radius = 3.0
3. unique_ptr wraps raw pointer

Memory layout at 0x555555559320:
┌────────────────────────┬────────────────────────┐
│ vptr (8 bytes)         │ radius (8 bytes)       │
│ 0x555555557d00         │ 0x4008000000000000     │
└────────────────────────┴────────────────────────┘

radius IEEE754: 0x4008000000000000 = _____
```

---

## Part 8: Observer Notification Loop

### Observer List State

```
observers = [weak_ptr<Obs1>, weak_ptr<Obs2>]
           size = 2

notify() loop:
for (auto& w : observers) {
    if (auto sp = w.lock()) {
        sp->onAreaChange(area);
    }
}
```

### YOUR TASK: Count Notifications

| Scenario      | Obs1 alive? | Obs2 alive? | Notifications sent |
| ------------- | ----------- | ----------- | ------------------ |
| Both attached | ✓           | ✓           | \_\_\_             |
| Obs1 detached | ✗           | ✓           | \_\_\_             |
| Both detached | ✗           | ✗           | \_\_\_             |

### Weak Lock Cost

```
w.lock() operation:
1. Atomic read strong_count
2. If strong_count > 0: atomic increment, return shared_ptr
3. Else: return nullptr

Cost = ~10-20 CPU cycles per lock()
2 observers × 10 cycles = 20 _____ cycles per notify()
```

---

## Failure Predictions

### Prediction 1: Iterator Dereference After Reallocation

```
vector<int> v = {1, 2, 3};
auto it = v.begin();
v.push_back(4);  // REALLOCATION
*it = ?          // UNDEFINED

Expected failure: undefined behavior
Actual behavior: undefined behavior
```

### Prediction 2: Dereference end()

```
vector<int> v = {1, 2, 3};
*v.end() = ?

Expected failure: undefined behavior
Actual behavior: undefined behavior
```

### Prediction 3: pop_back on empty

```
vector<int> v;
v.pop_back();

Expected: ________________________________
```

### Prediction 4: Uninitialized pointer dereference

```
int *p;
*p = 5;

Expected: ________________________________
```

### Prediction 5: Weak pointer after all shared released

```
shared_ptr<int> sp = make_shared<int>(42);
weak_ptr<int> wp = sp;
sp.reset();
auto locked = wp.lock();
locked == nullptr ? ✓ or ✗ : NO_____
```

---

## Calculation Verification Checklist

| #   | Calculation                                | Your Answer | Expected | Match? |
| --- | ------------------------------------------ | ----------- | -------- | ------ |
| 1   | Vector capacity after 4 pushes from size=3 |             | 12       |        |
| 2   | List node size (64-bit)                    |             | 24 bytes |        |
| 3   | Circle area (r=3)                          |             | 28.274   |        |
| 4   | Cache misses for vector<int>[100]          |             | ~7       |        |
| 5   | Cache misses for list<int>[100] worst      |             | ~100     |        |
| 6   | Total copies for vector growth 0→128       |             | <256     |        |
