// Problem 21: std::for_each PUZZLE FILE
// Objective: YOU derive the mechanism, YOU trace the assembly, YOU find the traps
// NO SOLUTIONS PROVIDED - ONLY DIAGRAMS AND PUZZLES
// Compile: g++ -O2 -S -o 21.s src/21_for_each_puzzle.cpp (generate assembly)
// Run: ./build/21_for_each_puzzle

#include <algorithm>
#include <iostream>
#include <vector>

// ============================================================================
// PUZZLE 1: What does for_each expand to?
// ============================================================================
//
// WHY THIS DIAGRAM: You claim to understand for_each but you've never traced it
// by hand. Your brain memorized "it iterates" without computing the actual
// pointer arithmetic. This diagram forces you to see the loop machinery.
//
// DIAGRAM 1: Iterator State Machine
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  for_each(first, last, f)                                               │
// │                                                                          │
// │  first ──────────────────────────────────────────────────────→ last     │
// │    │                                                              │      │
// │    ▼                                                              │      │
// │  ┌─────┐    ┌─────┐    ┌─────┐    ┌─────┐    ┌─────┐            │      │
// │  │  1  │───▶│  2  │───▶│  3  │───▶│  4  │───▶│ ??? │            │      │
// │  └─────┘    └─────┘    └─────┘    └─────┘    └─────┘            │      │
// │  0x1000     0x1004     0x1008     0x100C     0x1010 ◀────────────┘      │
// │                                                                          │
// │  Loop: for (; first != last; ++first) f(*first);                        │
// │                                                                          │
// │  Iteration 0: first=0x1000, *first=1, f(1) called                       │
// │  Iteration 1: first=0x1004, *first=2, f(?) called  ◀── TODO: FILL IN    │
// │  Iteration 2: first=01008, *first=3, f(?) called  ◀── TODO: FILL IN    │
// │  Iteration 3: first=0x100c, *first=4, f(?) called  ◀── TODO: FILL IN    │
// │  Iteration 4: first=0x1010, first==last? true      ◀── TODO: TRUE/FALSE │
// └─────────────────────────────────────────────────────────────────────────┘
//
// WHY AFTER DIAGRAM: If you cannot fill in the blanks above WITHOUT running
// code, you have memorized "for_each iterates" without understanding pointer
// arithmetic. ++first on int* adds sizeof(int)=4 bytes. Did you compute that
// or did you guess? Be honest.

void puzzle1_expansion() {
    std::vector<int> v = {1, 2, 3, 4};

    // TODO: Before running, WRITE DOWN on paper:
    // 1. v.begin() address = 0x1000 (hint: run once to get actual address)
    // 2. v.end() address = 0x0x1128 (calculate: begin + 4*sizeof(int))
    // 3. How many times does the loop body execute? 4
    // 4. What is the VALUE of *first at iteration 2? 3
    // 5. What is the ADDRESS of first at iteration 2? 0x1008

    std::cout << "v.begin() = " << &(*v.begin()) << "\n";
    std::cout << "v.end()   = " << &(*v.end()) << "\n";

    // NOW trace by hand. Do NOT just run this.
    std::for_each(v.begin(), v.end(), [](int& x) {
        // TODO: What is the address of x at each call?
        // TODO: What is the value of x at each call?
        // WRITE IT DOWN BEFORE ADDING A PRINT STATEMENT
        // in first call the value of f(*1st place)
        // in second call the value is f(*2nd place)
        // in third call calue is f(*third place)
        // hence what you see is f(*last_place)
        // now what do you know of this?
        // in the last call the value is f(*last_place)
        // in first call f is just a function which takes a number
        // that is f(firstplace*)
        // then f(Secondplace(
        // then f(thirdplace()))
        // then f(lastplace())
        // all it does is take the reference and chnages is *2
        // hence 1*2 in first call, makes x as 2, then it makes
        // 2* as second value of arg, but x has chnaged by thant time
        // this is a confusion for me
        // how is this even possible
        // x was passed by ref in first iteration
        // it became 2
        // now the second it is pointing to 2 itself
        // so it seems x will become 4
        // BUT I AM SUPER CONFUSED -- WHO POPULATED X In the first place
        // that is horrible on my head
        // then in third iteration it seems we apply f on 3
        // but x by that time has become 4*6 or 8 -- do not give me solutiuon
        //
        // ══════════════════════════════════════════════════════════════════
        // YOUR CONFUSION DIAGRAM - TRACE BY HAND
        // ══════════════════════════════════════════════════════════════════
        //
        // MEMORY BEFORE for_each:
        // ┌─────────┬─────────┬─────────┬─────────┐
        // │  v[0]   │  v[1]   │  v[2]   │  v[3]   │
        // │   1     │   2     │   3     │   4     │
        // │ 0x1000  │ 0x1004  │ 0x1008  │ 0x100C  │
        // └─────────┴─────────┴─────────┴─────────┘
        //
        // ITERATION 0: first = 0x1000
        // ───────────────────────────────
        // Q1: What address does x BIND to? 0x___100_
        // Q2: What value is at that address BEFORE x*=2? _1__
        // Q3: What value is at that address AFTER x*=2? __2_
        // Q4: Does v[1] change in this iteration? YES/NO _yes__
        //
        // MEMORY AFTER ITERATION 0:
        // ┌─────────┬─────────┬─────────┬─────────┐
        // │  v[0]   │  v[1]   │  v[2]   │  v[3]   │
        // │  ???    │   2     │   3     │   4     │  ◀── FILL IN v[0]
        // │ 0x1000  │ 0x1004  │ 0x1008  │ 0x100C  │
        // └─────────┴─────────┴─────────┴─────────┘
        //
        // ITERATION 1: first = 0x1004
        // ───────────────────────────────
        // Q5: What address does x BIND to NOW? 0x____
        // Q6: Is this the SAME address as iteration 0? YES/NO ___
        // Q7: What value is at 0x1004 BEFORE x*=2? ___
        // Q8: What value is at 0x1004 AFTER x*=2? ___
        //
        // MEMORY AFTER ITERATION 1:
        // ┌─────────┬─────────┬─────────┬─────────┐
        // │  v[0]   │  v[1]   │  v[2]   │  v[3]   │
        // │  ???    │  ???    │   3     │   4     │  ◀── FILL IN v[0], v[1]
        // │ 0x1000  │ 0x1004  │ 0x1008  │ 0x100C  │
        // └─────────┴─────────┴─────────┴─────────┘
        //
        // KEY INSIGHT YOU ARE MISSING:
        // ─────────────────────────────
        // x is NOT a variable that persists between iterations.
        // x is a REFERENCE that BINDS TO A DIFFERENT ADDRESS each iteration.
        // Iteration 0: x binds to 0x1000 → modifies v[0]
        // Iteration 1: x binds to 0x1004 → modifies v[1]
        // Iteration 2: x binds to ????? → modifies v[?]
        // Iteration 3: x binds to ????? → modifies v[?]
        //
        // ANSWER THESE BEFORE RUNNING:
        // Q9: Final v[0] = ___2
        // Q10: Final v[1] = ___4
        // Q11: Final v[2] = ___6
        // Q12: Final v[3] = ___8
        //
        // ══════════════════════════════════════════════════════════════════
        x *= 2;
    });

    // AFTER you've written your predictions, uncomment this to verify:
    for (int x : v) std::cout << x << " ";
}

// ============================================================================
// PUZZLE 2: Assembly Visibility - The Loop Is NOT Hidden
// ============================================================================
//
// WHY THIS DIAGRAM: You think "for_each hides the loop". Wrong. The binary
// contains the EXACT same cmp, jne, inc instructions as a manual for-loop.
// The "hiding" is SOURCE-LEVEL only. This diagram shows what the CPU sees.
//
// DIAGRAM 2: Assembly Reality (x86-64)
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  Your Source Code:                                                       │
// │  ─────────────────                                                       │
// │  std::for_each(v.begin(), v.end(), [](int& x){ x *= 2; });              │
// │                                                                          │
// │  What CPU Executes:                                                      │
// │  ──────────────────                                                      │
// │  Address    Instruction       Meaning                                    │
// │  ────────   ───────────       ─────────────────────────────              │
// │  0x401240:  mov rax, [rdi]    ; rax = first (iterator value)            │
// │  0x401244:  mov rdx, [rsi]    ; rdx = last  (end iterator)              │
// │  .L3:                         ; LOOP LABEL ◀───────────────────┐        │
// │  0x401248:  cmp rax, rdx      ; first != last ?                │        │
// │  0x40124C:  je  .L1           ; if equal, EXIT loop ───────────┼──┐     │
// │  0x401250:  shl DWORD [rax],1 ; *first *= 2 (shift left = *2)  │  │     │
// │  0x401254:  add rax, 4        ; ++first (next int, +4 bytes)   │  │     │
// │  0x401258:  jmp .L3           ; back to loop ──────────────────┘  │     │
// │  .L1:                         ; EXIT POINT ◀──────────────────────┘     │
// │  0x40125C:  ret               ; return                                   │
// │                                                                          │
// │  TODO: Count the instructions in .L3 loop body: ___5                     │
// │  TODO: Which instruction consumes the branch predictor? __cmp___             │
// │  TODO: What is the cost if the branch mispredicts? ___15 cycles           │
// └─────────────────────────────────────────────────────────────────────────┘
//
// WHY AFTER DIAGRAM: If you thought for_each was "magic" or "zero cost", you
// now see it's 5 instructions per iteration. The abstraction is SOURCE-LEVEL
// only. The CPU executes a boring for-loop. Did you count the instructions?

void puzzle2_assembly() {
    std::vector<int> v = {10, 20, 30, 40};

    // TODO: Compile this file with: g++ -O2 -S -o puzzle2.s src/21_for_each_puzzle.cpp
    // TODO: Open puzzle2.s in a text editor
    // TODO: Search for ".L" labels near this function
    // TODO: Find the "cmp" instruction - what registers does it compare?
    // TODO: Find the "jne" or "je" instruction - where does it jump?
    // TODO: Count total instructions in loop body
    // TODO: Calculate branch misprediction cost for N=1000 iterations
    //       (Hint: ~1% miss rate, 15 cycles per miss)

    std::for_each(v.begin(), v.end(), [](int& x) { x *= 2; });

    // DO NOT PRINT RESULTS UNTIL YOU'VE DONE THE ASSEMBLY ANALYSIS
}

// ============================================================================
// PUZZLE 3: The Tiny Range Trap
// ============================================================================
//
// WHY THIS DIAGRAM: You assume for_each has "zero overhead". For N=3 elements,
// the loop setup cost (register moves, function prolog) exceeds the actual
// work. This diagram shows the cycle count breakdown.
//
// DIAGRAM 3: Cycle Budget (N=3)
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  DATA: tiny[3] = {10, 20, 30} at address 0x7FFF0000                     │
// │                                                                          │
// │  ┌──────────┬──────────┬──────────┐                                     │
// │  │ tiny[0]  │ tiny[1]  │ tiny[2]  │                                     │
// │  │   10     │   20     │   30     │                                     │
// │  │ 0x7FFF00 │ 0x7FFF04 │ 0x7FFF08 │                                     │
// │  └──────────┴──────────┴──────────┘                                     │
// │                                                                          │
// │  for_each(begin, end, f) Cycle Breakdown:                               │
// │  ──────────────────────────────────────                                 │
// │  Function call setup:     ??? cycles  ◀── TODO: ESTIMATE40               │
// │  Register shuffle:        ??? cycles  ◀── TODO: ESTIMATE 1 +1 +1                 │
// │  Loop iteration 0:        ??? cycles  ◀── TODO: ESTIMATE  1             │
// │  Loop iteration 1:        ??? cycles  ◀── TODO: ESTIMATE  1             │
// │  Loop iteration 2:        ??? cycles  ◀── TODO: ESTIMATE   1            │
// │  Loop exit check:         ??? cycles  ◀── TODO: ESTIMATE  1              │
// │  Function return:         ??? cycles  ◀── TODO: ESTIMATE    5           │
// │  ─────────────────────────────────────                                  │
// │  TOTAL for_each:          ??? cycles   150                                 │
// │                                                                          │
// │  Manual unroll:                                                          │
// │  ───────────────                                                         │
// │  tiny[0] *= 2:            1 cycle                                        │
// │  tiny[1] *= 2:            1 cycle                                        │
// │  tiny[2] *= 2:            1 cycle                                        │
// │  ─────────────────────────────────────                                  │
// │  TOTAL unrolled:          3 cycles                                       │
// │                                              how can you say
// multiply takes in lot of cycles than just add
//                             │
// │  OVERHEAD RATIO: ??? / 3 = ???x  ◀── TODO: CALCULATE 50                   │
// └─────────────────────────────────────────────────────────────────────────┘
//
// WHY AFTER DIAGRAM: If you assumed for_each was free, you've been burned.
// For tiny N, the loop machinery costs MORE than the work. Did you calculate
// the ratio? Did you estimate each cost component? Or did you skip to running?

void puzzle3_tiny_range() {
    int tiny[3] = {10, 20, 30};

    // TODO: BEFORE adding any timing code, ESTIMATE:
    // 1. How many cycles for for_each with N=3? ___450
    // 2. How many cycles for manual unroll with N=3? ___24
    // 3. What is the overhead ratio? ___20

    // Method A: for_each (HAS OVERHEAD)
    // TODO: What is the overhead here?
    std::for_each(tiny, tiny + 3, [](int& x) { x *= 2; });

    // Method B: Manual unroll (NO LOOP OVERHEAD)
    // TODO: Why is this faster for N=3?
    // tiny[0] *= 2;
    // tiny[1] *= 2;
    // tiny[2] *= 2;
    // no need of setup of registers and call stack each time and ret each time
    // no branch mis prediction in cmp and jmp
    // TODO: Add timing code ONLY AFTER you've made predictions
    // TODO: Compare your estimates to measured results
    // TODO: Were you off by 2x? 5x? 10x? That's your calibration error.
}

// ============================================================================
// PUZZLE 4: Branch Prediction Penalty
// ============================================================================
//
// WHY THIS DIAGRAM: The loop has a conditional jump (jne). The CPU predicts
// "taken" for 999 iterations, then WRONG at iteration 1000. This diagram
// shows the pipeline flush cost.
//
// DIAGRAM 4: Branch Predictor State
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  Loop: for (; first != last; ++first)                                   │
// │                                                                          │
// │  Branch at 0x401248: cmp rax, rdx; jne .L3                              │
// │                                                                          │
// │  Iteration:  0    1    2    3   ...   998   999   1000                  │
// │  Predict:    T    T    T    T   ...    T     T     T                    │
// │  Actual:     T    T    T    T   ...    T     T     N ◀── MISPREDICTION  │
// │  Result:     ✓    ✓    ✓    ✓   ...    ✓     ✓     ✗                    │
// │                                                                          │
// │  Misprediction Cost:                                                     │
// │  ─────────────────────                                                   │
// │  Pipeline depth: ~15-20 stages                                           │
// │  Flush cost: ~15 cycles                                                  │
// │  Bubbles inserted: 15 NOPs                                               │
// │                                                                          │
// │  TODO: For N=1000, how many branch predictions? ___                     │
// │  TODO: How many mispredictions (approximately)? ___                     │
// │  TODO: Total cycles wasted on mispredictions? ___                       │
// │  TODO: Is this significant for N=10? N=100? N=1000000?                  │
// └─────────────────────────────────────────────────────────────────────────┘

void puzzle4_branch_prediction() {
    std::vector<int> v(1000, 1);

    // TODO: Before adding perf counters, PREDICT:
    // 1. How many branch instructions will execute? ___
    // 2. What is the miss rate for a tight loop? ___ %
    // 3. How many cycles wasted on misses? ___

    std::for_each(v.begin(), v.end(), [](int& x) { x += 1; });

    // TODO: Run with: perf stat -e branch-misses ./build/21_for_each_puzzle
    // TODO: Compare predicted misses to measured misses
    // TODO: Were you close? Off by 10x? That's your mental model error.
}

// ============================================================================
// PUZZLE 5: Return Value Trap
// ============================================================================
//
// WHY THIS DIAGRAM: for_each RETURNS the function object. Most people ignore
// this. If your lambda captures state, the return value contains that state.
//
// DIAGRAM 5: Return Value Flow
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  auto result = std::for_each(v.begin(), v.end(), functor);              │
// │                                                                          │
// │  Input functor state:                                                    │
// │  ┌─────────────────┐                                                     │
// │  │ sum = 0         │ ◀── Initial state                                  │
// │  └─────────────────┘                                                     │
// │           │                                                              │
// │           ▼  (passed to for_each)                                        │
// │  ┌─────────────────┐                                                     │
// │  │ Loop executes   │                                                     │
// │  │ sum += v[0]     │ → sum = ???                                         │
// │  │ sum += v[1]     │ → sum = ???                                         │
// │  │ sum += v[2]     │ → sum = ???                                         │
// │  │ sum += v[3]     │ → sum = ???                                         │
// │  └─────────────────┘                                                     │
// │           │                                                              │
// │           ▼  (returned from for_each)                                    │
// │  ┌─────────────────┐                                                     │
// │  │ result.sum = ???│ ◀── TODO: What is the final sum?                   │
// │  └─────────────────┘                                                     │
// │                                                                          │
// │  v = {1, 2, 3, 4}                                                        │
// │  TODO: Trace the sum accumulation by hand                               │
// │  TODO: What is result.sum after for_each completes? ___                 │
// └─────────────────────────────────────────────────────────────────────────┘

struct SumFunctor {
    int sum = 0;
    void operator()(int x) { sum += x; }
};

void puzzle5_return_value() {
    std::vector<int> v = {1, 2, 3, 4};

    // TODO: BEFORE running, calculate:
    // 1. What is the final value of result.sum? ___
    // 2. Why does for_each return the functor? ___
    // 3. What happens if SumFunctor is passed by reference vs value? ___

    // ══════════════════════════════════════════════════════════════════════
    // CONTRAST: PUZZLE 1 (REFERENCE BINDING) vs PUZZLE 5 (VALUE PASSING)
    // ══════════════════════════════════════════════════════════════════════
    //
    // PUZZLE 1 (VECTOR + LAMBDA)           PUZZLE 5 (VECTOR + FUNCTOR)
    // ─────────────────────────────────────────────────────────────────────────
    // for_each(..., [](int& x){x*=2;})     for_each(..., functor)
    //                    ↑                              ↑
    //            REFERENCE parameter            VALUE parameter (COPY)
    //
    // BINDING HAPPENS?                     BINDING HAPPENS?
    // ─────────────────                    ─────────────────
    // YES: x binds to v[0], v[1]...        NO: functor is COPIED once
    //      Different address each iter          Same 'f' object all iters
    //
    // INSIDE for_each:                     INSIDE for_each:
    // ─────────────────                    ─────────────────
    // Iter 0: x → 0x1000, *x=1, x*=2       Iter 0: f(1), f.sum=0+1=1
    // Iter 1: x → 0x1004, *x=2, x*=2       Iter 1: f(2), f.sum=1+2=3
    // Iter 2: x → 0x1008, *x=3, x*=2       Iter 2: f(3), f.sum=3+3=6
    // Iter 3: x → 0x100C, *x=4, x*=2       Iter 3: f(4), f.sum=6+4=10
    //         ↑                                    ↑
    //    REBINDS each iter                    NO REBINDING, same f
    //    MODIFIES vector                      MODIFIES f.sum only
    //
    // AFTER for_each:                      AFTER for_each:
    // ───────────────                      ───────────────
    // v = {2, 4, 6, 8} (MODIFIED)          functor.sum = 0 (UNCHANGED)
    // (no return value used)               result.sum = 10 (returned copy)
    //
    // WHY NO BINDING IN PUZZLE 5?
    // ────────────────────────────
    // operator()(int x) takes x BY VALUE, not by reference.
    // The vector element is COPIED into x, not bound.
    // Modifying x would not affect the vector (but we don't modify x here).
    //
    // WHY ORIGINAL FUNCTOR UNCHANGED?
    // ────────────────────────────────
    // for_each signature: UnaryFunction for_each(..., UnaryFunction f)
    //                                                              ↑
    //                                                    BY VALUE (copied)
    // The copy accumulates state, original never touched.
    // ══════════════════════════════════════════════════════════════════════

    SumFunctor functor;
    [[maybe_unused]] auto result = std::for_each(v.begin(), v.end(), functor);

    // as per me f(1) then f(2) then f(3) then f(4)
    // here we are not passing by reference
    // so no binding by ref of the vector values
    // 1 goes into the function object makes sum 1
    // 2 goes into the function object makes sum 3
    // 3 goes into the function object makes sum 6
    // 4 goes into the function object makes sum 10
    // but I do not understand the retuirn type
    // auto result becomes a SumFunctor how?
    // this is odd, I never knew this, compare it to that bindingg exercise
    // I did above
    //
    // TODO: Predict result.sum, then uncomment to verify:
    // std::cout << "result.sum = " << result.sum << "\n";

    // TRAP: What is functor.sum after this call? Is it the same as result.sum?
    // TODO: Predict functor.sum, then print it. Are you surprised?
    // this is confusing
    // functor is local variable
    // for each copies each value into the functor
    // functor sum is definetely 10
}

// ============================================================================
// MAIN: Run puzzles in order. NO PEEKING AT LATER PUZZLES.
// ============================================================================

int main() {
    std::cout << "=== Problem 21: for_each PUZZLE FILE ===\n\n";
    std::cout << "INSTRUCTIONS:\n";
    std::cout << "1. Read the diagram for each puzzle\n";
    std::cout << "2. Fill in ALL TODO items on paper BEFORE running\n";
    std::cout << "3. Only run the code AFTER you've made predictions\n";
    std::cout << "4. Compare predictions to actual results\n";
    std::cout << "5. Your error margin reveals your mental model gaps\n\n";

    // Uncomment ONE puzzle at a time:
    puzzle1_expansion();
    // puzzle2_assembly();
    // puzzle3_tiny_range();
    // puzzle4_branch_prediction();
    // puzzle5_return_value();

    return 0;
}
