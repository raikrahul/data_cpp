# Problem 28: Ranges & Generate Derivation

## Pattern Recognition Shortcuts (From Transcript)

01. DETECT: "degenerate" → REPLACE: "generate" → WHY: Typo fixed.
02. DETECT: "arrange" → REPLACE: "range" → WHY: Compiler error fixed.
03. DETECT: "mass in twister" → REPLACE: "std::mt19937" → WHY: Gibberish fixed.
04. DETECT: "shown here" (no code) → ACTION: Write code below.

## RNG State Derivation (Seed = 1234)

05. Engine Start State: mt19937(1234).
06. Distribution: uniform_int_distribution(0, 9).
07. Range Check: 0 ≤ x ≤ 9. Span = 10.

08. Call 1: gen() state advance → dist(gen) → Value: ___.
09. Call 2: gen() state advance → dist(gen) → Value: ___.
10. Call 3: gen() state advance → dist(gen) → Value: ___.
11. Call 4: gen() state advance → dist(gen) → Value: ___.
12. Call 5: gen() state advance → dist(gen) → Value: ___.
13. Call 6: gen() state advance → dist(gen) → Value: ___.
14. Call 7: gen() state advance → dist(gen) → Value: ___.
15. Call 8: gen() state advance → dist(gen) → Value: ___.
16. Call 9: gen() state advance → dist(gen) → Value: ___.
17. Call 10: gen() state advance → dist(gen) → Value: ___.

## Generation Trace

18. v[0] Address: 0x3000. Write: Call 1 Result.
19. v[1] Address: 0x3004. Write: Call 2 Result.
20. ...
21. v[9] Address: 0x3024. Write: Call 10 Result.

## Shuffle Trace (Double Randomization?)

22. Input: v is already random (entropy ~33 bits).
23. Operation: std::ranges::shuffle(v, gen).
24. Logic: Fisher-Yates shuffle.
25. Swap 1: rand_index(9) ↔ v[9].
26. Swap 2: rand_index(8) ↔ v[8].
27. ...
28. Result: Permutation of random values.
29. Redundant? Yes/No: ____. (Does it add entropy?)

## Failure Prediction

F1. "rand int" syntax:
    Wrong: auto rand int = ...
    Right: auto rand_int = ...
    Fix: Use underscores.

F2. "shown here" missing:
    Wrong: Comment says "as shown" but code empty.
    Right: Explicitly write the lambda.

F3. Singular "element":
    Wrong: "generate random element"
    Right: "generate random elements"
