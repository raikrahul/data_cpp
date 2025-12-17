# Task Analysis: Shared Pointer Reassignment & Rust Comparison

## Goal

Validate behavior when a `shared_ptr` is reassigned to a NEW object while `weak_ptr`s still point to the OLD object. Compare this C++ runtime behavior with Rust's compile-time borrow checker.

## Sub-Task 1: C++ Experiment (`src/reassign_proof.cpp`)

**Scenario:**

1. Create `sp` pointing to Object A (id=1).
2. Create `wp` pointing to `sp` (Object A).
3. Reassign `sp` to Object B (id=2). `sp = make_shared<int>(2);`
4. Check `wp.lock()`.

**Questions to Grill:**

- When `sp` is reassigned, what happens to Object A's ref count?
  - Does it decrement to 0 immediately?
  - Does Object A get destroyed immediately?
- What does `wp` point to after reassignment?
  - Does it track `sp` (variable) or Object A (memory)?
  - Is `wp` now dangling? Or pointing to a dead control block?
- Can `wp` lock onto Object B? (Answer: No, it bound to A's control block).

**Expected Outcome (Hypothesis):**

- Object A destroyed (strong=0).
- `wp` points to A's control block (tombstone).
- `wp.lock()` returns nullptr.
- Object B is alive, managed by `sp`.

## Sub-Task 2: Rust Comparison (`src/reassign_proof.rs`)

**Scenario:**

- `Rc<RefCell<T>>` / `Weak<T>` equivalent.
- Or `Arc<Mutex<T>>`.
- Borrow checker implications?
  - Actually, `Rc`/`Weak` are runtime checked in Rust too, similar to C++.
  - The "Borrow Checker" usually refers to references (`&T`, `&mut T`).
  - `Rc` is for _shared ownership_ where lifetimes are dynamic.

**Questions to Grill:**

- Does Rust `Rc` behave exactly like C++ `shared_ptr`?
- If we use `&` references, does the compiler preventing reassignment while `wp` exists?
  - Wait, `wp` is not a borrow. `wp` is a struct.
  - Reassigning the owner (`sp`) drops the old value.
  - Rust should match C++ behavior here for `Rc`.
- **CRITICAL DISTINCTION:** `shared_ptr` is NOT a reference. It's an Owner handle.
- Comparing to "Borrow Checker" might be a category error if we use `Rc`.
- Should we compare to `&mut` vs `&`?
  - If we hold `&T` (borrow), we CANNOT move/reassign the owner.
  - This is the key difference. C++ `weak_ptr` allows the owner to leave. Rust `&T` forbids the owner from leaving.

**Plan for Rust:**

- Show 1: `Rc` path (Runtime, matches C++).
- Show 2: `&T` path (Compile time, FORBIDS the reassignment).
  - This proves the "Borrow Checker" difference.

## Execution Plan

1. Write `src/reassign_proof.cpp` with detailed memory tracing comments.
2. Write `src/reassign_proof.rs` showing both `Rc` (allowed) and `&` (refused).
3. Compile and Run C++.
4. Compile and Run Rust (expecting compile error on part 2).
