01. template<typename... Shapes> using shapevariant = std::variant<Shapes...>
02. why: defines alias for variadic template expansion → reduces typing `std::variant<A,B,C>` to `shapevariant<A,B,C>`.
03. input: `shapevariant<Circle, Rect, Line>` → substitution: `Shapes = {Circle, Rect, Line}`.
04. computation: `std::variant<Circle, Rect, Line>` expands recursively.
05. output: type alias `Geometry`.

06. DRAW VARIANT MEMORY @ 0x1000:
    +-------------------------------------------------------------+
    | Index (1B) | Padding (7B) | Union (Max(Sizeof(Shapes)))     |
    +-------------------------------------------------------------+
    | 0x00       | 0xCC.......  | Circle Data (24B) OR Rect (32B) |
    +-------------------------------------------------------------+
    Alignment: Max(alignof(Circle)=8, alignof(Rect)=8) = 8 bytes.
    Size: 8 (Header) + 32 (Max Payload) = 40 bytes.

07. why: variants must store largest possible member + differentiation index.
08. why: padding ensures union payload starts at aligned address (0x1008 % 8 == 0).

09. ROAST:
    - SLOPPY: `vector<double> intersect` violates 2D geometry spec (need (x,y)).
    - WASTEFUL: `struct Point` defined but unused in return type of `intersect`.
    - TRAP: Line y=ax+b fails for vertical lines (x=c) → Divide by zero imminent.
    - MUMBO JUMBO: "Boilerplate code" implies safety, but `Geometry` variant hardcodes inputs.
    - INATTENTIVE: `IntersectionVisitor` creates `vector` copy on every visit → O(N) allocs.
    - MEAT MISSED: Vertical lines (x=5) have infinite slope `a`. Math `y = a*x + b` explodes.
    - CARELESS: `Circle` math TODO block empty. `Rect` math TODO block empty. Zero logic implemented.

10. CALCULATION:
    N=1000 shapes.
    Visitor Calls: 1000.
    Allocs (Naive): 1000 `std::vector` creations.
    Cost: 1000 * (malloc(24) + free) = 1000 * ~200 cycles = 200,000 cycles waste.
    Optimization: Return `std::optional<Point>` or fixed array `std::array<Point, 2>`?
    Wait, `Rect` can have 2 intersection points? Yes.
    `Circle` can have 2.
    Optimization: `small_vector<Point, 2>` avoids heap.

11. DRAW INHERITANCE VS VARIANT MEMORY:
    Virtual: [vptr 8B] [Data 24B] → Total 32B + Heap Alloc 32B/Obj (Cache Miss).
    Variant: [Index 1B] [Pad 7B] [Data 32B] → Total 40B Flat (Cache Hit).
    why: Contiguity wins for bulk processing (geometry intersection).

12. FIX BRAIN:
    - Stop typing `result` vector.
    - Start calculating Discriminant `D = B^2 - 4AC`.
    - Identify `A, B, C` coefficients from substitution.
    - `y = ax + b` into `(x-cx)^2 + (y-cy)^2 = r^2`.
    - `(x-cx)^2 + (ax + b - cy)^2 - r^2 = 0`.
    - Expand: `x^2 - 2cx*x + cx^2 + ...`
    - Do the expansion by hand now.
