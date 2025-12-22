# Rewiring Guide: Stencil-Based Polymorphic Simulation — Why Your Brain Freezes and How to Force It Through the Meat

> **Purpose**: This document is *not* a tutorial. It is a forensic dissection of *where* and *why* your working memory collapses when facing stencil-based polymorphic simulation code, especially when C++ `std::variant` or virtual dispatch is involved. It identifies the exact points where memorization replaces calculation, where the “middle” vanishes, and where hidden assumptions sabotage execution. Use this as a checklist *while* you fill out the C++ worksheet.

---

## 1. The Core Freeze Point: “Middle Steps” Are Not Missing — They Are *Skipped by Design*

You know:
- Input: a vector `U` of 10 doubles.
- Output: a new vector `new_U`.

What vanishes:
- The **exact memory address** of every node.
- The **byte count** of every write.
- The **index arithmetic** for stencil offsets *at each i*.
- The **fraction-to-decimal conversion** *per term*, not as a batch.

Why it vanishes:
- You were trained to see `weights = {−½, 0, +½}` and instantly think *“centered difference”*. That’s a label — not a computation. Your brain skips the multiplication because the *pattern* is memorized.
- The jump from `U[i-1], U[i+1]` to `Δ = a * Δt * (U[i+1] - U[i-1]) / 2` is a *shortcut*. It hides the two separate multiplications `(−½)×U[i-1]` and `(+½)×U[i+1]`. When those are hidden, you can’t debug sign errors, overflow, or rounding.

**→ Rewire by forcing two separate multiplies per stencil term. No factoring. No simplification.**

---

## 2. The Memory Layout Trap: “new_U overwrites nodes” Is Not an Edge Case — It’s a Default Failure

In the video, the speaker writes:
```cpp
std::vector<double> U(N);
std::vector<NodeVariant> nodes(N);
std::vector<double> new_U(N);
```
This *looks* safe — three vectors.

But:
- `std::vector` allocates *separately*.
- You *assume* they’re disjoint.
- In hand-simulation (or embedded systems), you often place them manually at fixed addresses: `U@0x100`, `nodes@0x200`, `new_U@0x300`.

Now compute:
- `sizeof(double) = 8` → `U` occupies `0x100 – 0x14F`.
- Assume max node size = 32 (alignment) → 10 nodes → `0x200 – 0x33F`.
- `new_U` at `0x300` → `0x300 – 0x34F`.

Overlap: `0x300 – 0x33F` = 64 bytes = *exactly 2 nodes* (node[8] and node[9]).

**→ Your brain skipped “how big is a variant?” because it memorized “variant is efficient”. Reality: variant = max(sizeof(Ts…)) + discriminator. You must compute it *before* placing buffers.**

---

## 3. The Stencil Boundary Trap: “O4 at i=3 is fine” — But Is i=2?

The video says: *“apply larger stencil only where function varies strongly”*.

Hidden constraint:
- O4 needs indices `i−2, i−1, i, i+1, i+2`.
- Valid i range: `2 ≤ i ≤ N−3`.

For N=10: valid i = {2,3,4,5,6,7}.

But the example places O4 at i=3,4,5 — fine.

**Trap**: if you copy-paste and change N=6, i=2 becomes the *first interior point*, but i=2 needs U[0] and U[4] — still ok. i=1 would need U[−1] → crash.

**→ Your brain used “looks symmetric” as proxy for “valid”. Instead: for each i, compute min_index = i−k, max_index = i+k, check `0 ≤ min_index ∧ max_index < N`. Do it per i.**

---

## 4. The Dirichlet Semantics Trap: `+=` vs `=`

The video shows:
```cpp
return constant_value;
```
and later:
```cpp
U[i] = visitor(node[i], U, i, dt);
```

But if you write:
```cpp
U[i] += visitor(...);   // WRONG
```
then for Dirichlet, `U[i] += 0.0` → no change. Boundary condition violated.

**→ Your brain memorized “visitor returns delta”, but Dirichlet is *not* a delta — it’s an *assignment*. You must check tag *before* deciding `+` or `=`.**

---

## 5. The Fraction Trap: `1/12` Is Not `0.083333`

In C++, `1/12` (integers) = 0.  
In hand calc, `1/12 = 0.083333…` → stored as `double` ≈ `0.08333333333333333`.

But:
- `0.588 × 1/12` = `0.588 / 12` = `0.049` exactly *only* because 588 is divisible by 12.
- `0.951 / 12` = `0.07925` *only* because 951 = 12×79 + 3 → remainder 3/12000 = 0.00025 added.

If you round early (e.g., use 0.08333), error accumulates.

**→ Rewire: compute `(numerator * value) / denominator` as integer division + remainder. Never pre-round weights.**

---

## 6. The Energy Trap: “CFL says stable” — But Sign Is Wrong

CFL for `u_t + a u_x = 0` with forward Euler + centered diff:
- Stable if `|a| Δt / Δx ≤ 1` **and** stencil implements **−∂/∂x**.

Our weights `[−½, 0, +½]` implement **+∂/∂x**.

So scheme solves `u_t − a u_x = 0` → wave travels *left*, but Dirichlet fixes *both* ends → wave reflects, interferes, energy grows.

**→ Your brain matched “CFL < 1 ⇒ stable” without checking PDE sign. Always verify: stencil × PDE coefficient = correct sign.**

---

## 7. Failure Mode Summary (Do *Not* Read Ahead — Use Only After You Hit a Crash)

| ID | Symptom | Root Cause | How to Detect *Before* Run |
|----|---------|------------|----------------------------|
| F1 | Segfault on i=1 with O4 | i−2 = −1 → out-of-bounds read | For each node, compute `{i−k,…,i+k}` ⊆ `{0,…,N−1}` |
| F2 | Boundary value drifts | Dirichlet used `+=` instead of `=` | Check tag first: if tag==0 → `U[i] = val` |
| F3 | new_U corrupted | new_U overlaps nodes in memory | Compute byte ranges: `start + count×size − 1` |
| F4 | Energy explosion | Stencil sign opposite PDE | Write stencil as `(U[i+1]−U[i−1])/2` → compare to PDE `+a u_x` or `−a u_x` |
| F5 | Wrong result for i=4 | Used `0.08333` instead of exact `1/12` | Compute `(951 × 1) / 12` = `79 r 3` → `0.079 + 0.00025` |
| F6 | Variant visitor compile error | Forgot `std::visit` or lambda captures | Write visitor *after* defining all node types |
| F7 | O2 at i=0 reads U[−1] | No boundary guard for O2 | O2 valid only for `1 ≤ i ≤ N−2` |

---

## 8. How to Use This Document

1. Open the C++ worksheet.
2. For **each TODO**, do *only* what is asked:
   - Compute a number.
   - Draw a memory box.
   - Fill a table cell.
3. *Do not* look at the next TODO until the current one is on paper.
4. When you hit a discrepancy (e.g., your `new_U[5]` ≠ expected), consult the *Failure Mode* table *only* for matching symptom.
5. Never copy a formula — derive it from the numbers you just wrote.

This is brain rewiring: *calculation is the path*, memorization is the shortcut that leads to the wall.

— End of Document —
