# Error Report: User Mistakes

## Mistake 1: capacity < size

```
YOUR ANSWER: | push_back(10) | 4 | 3 | ✓ |
PROBLEM:     size=4, capacity=3 → 4 > 3 → IMPOSSIBLE

WHAT YOU DID:
├── Incremented size: 3 → 4 ✓
├── Forgot to increment capacity
└── Did not check: size ≤ capacity (invariant)

ORTHOGONAL CHECK:
├── Can array hold more elements than allocated?
└── NO → capacity must grow BEFORE size can grow
```

---

## Mistake 2: All rows marked as reallocation

```
YOUR ANSWER: ✓ for push(20), push(30)
REALITY:     capacity=6 had room for size=5,6

WHAT YOU DID:
├── Assumed push_back ALWAYS reallocates
├── Did not calculate: slots_available = capacity - size
└── Did not check: slots_available > 0 → no realloc

ORTHOGONAL CHECK:
├── Why allocate if space exists?
└── Reallocation is EXPENSIVE, done only when REQUIRED
```

---

## Mistake 3: "6 bytes" instead of "24 bytes"

```
YOUR ANSWER: 6 bytes
REALITY:     6 elements × 4 bytes/element = 24 bytes

WHAT YOU DID:
├── Wrote element count as byte count
├── Forgot: sizeof(int) = 4
└── Confused WHAT with HOW MUCH

ORTHOGONAL CHECK:
├── Elements: count of items
├── Bytes: memory size = count × sizeof(type)
└── 6 ≠ 24
```

---

## Mistake 4: "1 element copied" on no-realloc push

```
YOUR ANSWER: 1 element copied
REALITY:     0 elements copied

WHAT YOU DID:
├── Confused INSERT (write new) with COPY (move existing)
├── INSERT: writes 1 new value to empty slot
├── COPY: moves existing elements during reallocation
└── No reallocation → copy count = 0

ORTHOGONAL CHECK:
├── What is being copied? NEW element or OLD elements?
└── COPY refers to OLD elements moved. NEW element is INSERTED.
```

---

## Mistake 5: \*it = 10 after reallocation

```
YOUR ANSWER: *it = 10
REALITY:     UNDEFINED BEHAVIOR

WHAT YOU DID:
├── Assumed data still exists at old address
├── Forgot: old block is FREED
├── FREED memory = unpredictable content
└── Dereference freed pointer = undefined

ORTHOGONAL CHECK:
├── Who owns memory at 0x5555555592a0 after free()?
└── NOBODY or SOMEONE ELSE → value is UNKNOWN
```

---

## Mistake 6: Mental model - push_back at end = beginning safe

```
YOUR ASSUMPTION: "push_back at end → beginning iterators fine"
REALITY:         Entire block moves → ALL iterators invalid

WHAT YOU DID:
├── Applied linked-list logic to vector
├── Linked list: nodes independent, add node = others untouched
├── Vector: ONE contiguous block, add element = may move ALL
└── Confused logical position with physical address

ORTHOGONAL CHECK:
├── Is vector made of separate nodes? NO
├── Is vector ONE block? YES
└── Can you extend a block in-place? NOT GUARANTEED
```

---

## Pattern: Your Thinking Errors

| Error Type          | Your Pattern                  | Correct Pattern               |
| ------------------- | ----------------------------- | ----------------------------- |
| Invariant violation | Changed size, forgot capacity | Check: size ≤ capacity always |
| Unit confusion      | Wrote elements as bytes       | Multiply: elements × sizeof   |
| Action confusion    | INSERT vs COPY                | INSERT = new, COPY = existing |
| Memory model        | Pointer survives free         | freed → undefined             |
| Container model     | Vector = linked               | Vector = contiguous array     |

---

## Questions For Your Brain

```
1. Before writing size, did you write capacity?
   └── NO → capacity-first rule violated

2. Before marking reallocation, did you calculate slots?
   └── NO → blind guess

3. Bytes or elements? Which unit was asked?
   └── Did not read question

4. What does COPY mean in "bytes copied"?
   └── Did not define term before using

5. Where does data live after reallocation?
   └── Did not trace memory addresses

6. Is vector a chain or a block?
   └── Wrong mental model
```

---

## Fix Protocol

```
BEFORE filling any table:
1. Define all terms (size, capacity, reallocation, copy)
2. State invariants (size ≤ capacity)
3. Calculate slots_available FIRST
4. Check units (elements vs bytes)
5. Trace memory addresses step-by-step
```

---

## Mistake 7: weak_count=2 when no weak_ptr exists

```
YOUR ANSWER: p2 = p1 → weak_count = 2
REALITY:     weak_count = 1 (no weak_ptr created yet)

WHAT YOU DID:
├── Assumed shared_ptr copy increments both counters
├── shared_ptr copy increments STRONG only
├── weak_ptr creation increments WEAK only
└── Two separate counters, two separate increment rules

ORTHOGONAL CHECK:
├── What type is being copied? shared_ptr
├── Which counter does shared_ptr affect? strong_count
└── 2 counters exist → must know which operation affects which
```

---

## Mistake 8: "weak is only for cycles"

```
YOUR ASSUMPTION: weak_ptr exists only to break cycles
REALITY:         weak_ptr = non-owning observer

WHAT WEAK_PTR DOES:
├── Observes object without keeping it alive
├── Can check if object still exists (expired())
├── Can attempt to get shared_ptr (lock())
└── Breaking cycles is ONE USE CASE, not the only one

OTHER USE CASES:
├── Cache: store weak_ptr, object deleted when not needed
├── Observer pattern: observers hold weak_ptr to subject
├── Parent-child: child holds weak_ptr to parent
└── Temporary access: get shared_ptr only when needed
```

---

## Mistake 9: "why weak_count=1 when no weak_ptr"

```
YOUR QUESTION: odd that weak_count=1 with 0 weak_ptrs

ANSWER:
weak_count = (number of weak_ptrs) + 1
             ↑
             +1 for CONTROL BLOCK LIFETIME

WHY +1:
├── Control block stores both counters + object
├── Control block must survive until ALL references gone
├── strong_count=0 → destroy object
├── weak_count=0 → destroy control block
└── If weak_ptr exists after object dead, needs control block to check

DIAGRAM:
strong=0, weak=1 (no weak_ptr, but base count):
┌────────────────────┐
│ strong_count = 0   │
│ weak_count   = 1   │ ← control block keeps itself alive
│ data: DESTROYED    │
└────────────────────┘
Control block freed when weak_count reaches 0.
```

---

## Mistake 10: "lock on p1 or p2"

```
YOUR QUESTION: what if lock() on p1 or p2?

ANSWER: lock() is weak_ptr method ONLY

shared_ptr p1;
p1.lock();     // COMPILE ERROR: no such method

weak_ptr w;
w.lock();      // OK: returns shared_ptr or nullptr

WHY:
├── shared_ptr OWNS object → always valid (if not null)
├── weak_ptr OBSERVES object → may be dead → need to CHECK
├── lock() = "try to get ownership"
├── shared_ptr already HAS ownership → no need to "try"
└── Method exists only where uncertainty exists
```

---

## Pattern: Smart Pointer Errors

| Error               | Your Model             | Correct Model               |
| ------------------- | ---------------------- | --------------------------- |
| Counter increment   | Both counters together | Each counter separate       |
| weak_ptr purpose    | Only for cycles        | Non-owning observer         |
| weak_count base     | Starts at 0            | Starts at 1 (control block) |
| lock() availability | Any smart pointer      | weak_ptr only               |

---

## Questions For Your Brain

```
7. When copying shared_ptr, which counter changes?
   └── Did not distinguish the two counters

8. What does weak_ptr do besides breaking cycles?
   └── Learned one use case, assumed it was the only one

9. Why is weak_count never 0 while shared_ptrs exist?
   └── Did not understand control block lifetime

10. Can shared_ptr call lock()?
    └── Did not check method availability per type
```

---

## Mistake 13: "new(3.0) allocates 3 bytes?"

```
YOUR ASSUMPTION: new Circle(3.0) might allocate size based on 3.0
REALITY:         new = operator new(sizeof(Circle)) + Constructor(3.0)

WHAT HAPPENS:
1. Allocator needs BYTES (sizeof(Circle) = 16 bytes).
2. Constructor needs VALUES (3.0).
3. "new" operator combines both steps.

ORTHOGONAL CHECK:
├── Who calculates size? Compiler (sizeof).
├── Who initializes values? Constructor.
├── Does 3.0 affect size? NO (double is always 8 bytes).
```

---

## Mistake 14: "operator new is not a function"

```
YOUR ASSUMPTION: "operator new" is a keyword/magic, not a function name.
REALITY:         It IS a function name, just with a space.

PROOF:
void* operator new(size_t n) { return malloc(n); }
It is a normal function you can call, hook, or replace.
```

---

## Mistake 15: "vptr is in the function"

```
YOUR ASSUMPTION: vptr lives in the code/function.
REALITY:         vptr lives in the DATA (the object).

WHY:
Object needs to carry its ID card.
If vptr was in the function, you'd need to know the function to find the function (Circular).
Objects carry the map (vptr) to find the destination (code).
```

---

## Mistake 16: "What is dynamic about it?"

```
YOUR ASSUMPTION: If vptr points to a static table, it's static.
REALITY:         The POINTER is dynamic (can change targets).

SCENARIO:
Shape* s;
if (input == 1) s = new Circle();     // s->vptr = CircleTable
if (input == 2) s = new Rectangle();  // s->vptr = RectTable

s->area(); // CODE IS SAME. DESTINATION CHANGE IS DYNAMIC.

Static Dispatch:  Call address 0x4000 (Hardcoded)
Dynamic Dispatch: Call address [s->vptr->index] (Computed at runtime)
```

---

## Mistake 17: Operator Precedence `auto x = y != nullptr`

```
YOUR CODE: if (auto cb = weak.lock() != nullptr)
REALITY:   cb becomes BOOL (result of !=), not POINTER.

WHY:
!= has higher precedence than =.
Expression evaluates (lock() != nullptr) -> true/false.
Then assigns bool to cb.
Then tries cb->notify() -> ERROR (cannot dereference bool).

FIX:
if (auto cb = weak.lock()) { ... }
Implicitly converts pointer to bool for 'if', but 'cb' remains pointer.
```

---

## Mistake 18: Ignoring Return Value `[[nodiscard]]`

```
YOUR CODE: size_t observer_count() const { ... }
WARNING:   Computes value but caller might ignore it.

WHY:
Pure getter functions have no side effects.
Calling them without using result is 100% waste of CPU.
[[nodiscard]] tells compiler to warn if result is ignored.
```

---

## Mistake 19: Unnecessary Copy of Smart Pointer

```
YOUR CODE: void attach(weak_ptr<T> obs)
REALITY:   3 atomic operations (Copy Arg, Copy to Vector, Destroy Arg).

WHY:
Pass-by-value triggers atomic increment/decrement on Control Block.
Atomic ops lock memory bus -> SLOW.

FIX:
void attach(const weak_ptr<T>& obs)
Pass-by-reference = 0 atomic ops for argument passing.
Only 1 atomic op to copy into vector. Saves 66% overhead.
```

---

## Mistake 20: LValue Ref to Temporary

```
YOUR CODE: void attach(weak_ptr<T>& obs)
CALLER:    attach(shared_ptr)
ERROR:     Cannot bind non-const lvalue ref to temporary.

WHY:
1. shared_ptr converts to TEMPORARY weak_ptr.
2. Non-const ref implies you want to MODIFY the caller's variable.
3. Modifying a temporary is useless (it dies immediately).
4. C++ forbids this to prevent logic bugs.

FIX:
void attach(const weak_ptr<T>& obs)
Const ref extends temporary lifetime and promises no modification.
```

---

## Mistake 11: "Weak pointer means pointing to nothing"

```
YOUR ASSUMPTION: weak_ptr is a parasite, so it cannot point to a valid node in a list.
REALITY:         weak_ptr points to an object OWNED BY SOMEONE ELSE.

OWNERSHIP CHAIN (The "Next" Pointers):
HEAD (owner) → Node A (owned) → Node B (owned) → Node C (owned)
Every node is ALIVE because the PREVIOUS node owns it (strong ref).

OBSERVATION CHAIN (The "Prev" Pointers):
Node B (observer) → Node A (observed)
Node B.prev is weak. It looks at Node A.
Node A is ALIVE because HEAD owns it.
Therefore, B.prev points to a VALID, ALIVE object.

ORTHOGONAL CHECK:
├── Who owns Node A? HEAD (or previous node).
├── Does A exist? YES.
├── Can B look at A without owning it? YES (via weak_ptr).
├── Does B need to own A? NO, HEAD already owns A.
```

---

## Mistake 12: "prev is banned/useless if weak"

```
YOUR THOUGHT: "next is something serious (strong), prev is banned (weak)?"
REALITY:      strong = "I keep you alive". weak = "I know who you are".

WHY PREV IS WEAK:
If B owned A (strong prev) AND A owned B (strong next):
A ⇄ B (Cycle)
Both keep each other alive -> Memory Leak.

WHY PREV WORKS:
B says "I know A is my predecessor".
B does NOT say "I demand A stays alive".
A stays alive because the LIST OWNER says so.
If the list owner drops A, B should not force A to live.
```
