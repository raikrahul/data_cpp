# 61_constexpr_roundoff Error Report

## E1: "My constexpr is slowest"

YOUR CLAIM: "Mine is slowest despite being constexpr"

FACT:
```
constexpr_sin AT RUNTIME = 359 ns (slowest)
constexpr_sin AT COMPILE = 0.76 ns (fastest)
```

YOUR CONFUSION:
- constexpr FUNCTION ≠ always compile-time
- constexpr FUNCTION = CAN run at compile-time IF context demands
- `sink = constexpr_sin(pi_f)` = runtime call (no constexpr variable)
- `constexpr x = constexpr_sin(pi_f)` = compile-time call

QUESTION: Did you read what constexpr means?
ANSWER: constexpr = "able to run at compile time", not "always runs at compile time"

---

## E2: "Why loop 10M times for sin_of_pi?"

YOUR CLAIM: "Why am I doing this in a loop"

FACT:
```
1 load = 2 nanoseconds
chrono resolution = 1000 nanoseconds
1 load unmeasurable → 10M loads = 20ms (measurable)
```

YOUR CONFUSION:
- Benchmark needs amplification
- 1 operation too fast to measure
- N operations × N = measurable total time

QUESTION: How do you measure 2 nanoseconds with 1000ns clock?
ANSWER: You don't. You measure 20 million nanoseconds and divide by 10 million.

---

## E3: "I am not calling Taylor series in case of pi"

YOUR CLAIM: Correct.

```
Case 1: constexpr float sin_of_pi = constexpr_sin(pi_f);  ← Taylor at COMPILE TIME
        sink = sin_of_pi;                                   ← Load at runtime

Case 3: sink = constexpr_sin(pi_f);                        ← Taylor at RUNTIME
```

NOT CONFUSED HERE. Good.

---

## E4: "If no float immediate, what use is constexpr?"

YOUR CLAIM: "No float immediate → constexpr useless"

FACT:
```
Integer constexpr 49:  movl $49, %esi      ← Immediate in instruction
Float constexpr 3.14:  movss .LC0, %xmm0   ← Load from .rodata
```

YOUR CONFUSION:
- x86 SSE has NO float immediates
- Float MUST be loaded from memory
- BUT value is PRE-COMPUTED by compiler
- Constexpr saves COMPUTATION, not LOAD

QUESTION: What costs more: 1 load or 170 multiplications?
ANSWER: 170 multiplications = 359 ns. 1 load = 2 ns. Constexpr saves 357 ns.

---

## E5: "Cannot understand float template thing"

YOUR CLAIM: "Why enum class Angle?"

FACT:
```cpp
// C++17: ILLEGAL
template<float X>  // ERROR: float not allowed as template parameter
float sin();

// LEGAL
template<Angle A>  // Angle is enum = integer
float sin();
```

YOUR CONFUSION:
- Template parameters must be: types, integers, pointers, enums
- float NOT allowed until C++20
- Even in C++20, float comparison tricky (0.0f vs -0.0f)

QUESTION: What types can be template parameters?
```
template<typename T>    ← Type (int, float, MyClass)
template<int N>         ← Integer
template<auto X>        ← C++17: any allowed NTTP
template<Angle A>       ← Enum (converts to int)
template<float F>       ← C++20 ONLY
```

DIAGRAM:
```
C++17 NTTP (Non-Type Template Parameter):
┌─────────────────────────────────────────────┐
│ Allowed: int, char, bool, enum, pointer     │
│ Forbidden: float, double, class             │
└─────────────────────────────────────────────┘

C++20 NTTP:
┌─────────────────────────────────────────────┐
│ Allowed: int, char, bool, enum, pointer     │
│         + float, double (structural types)  │
│ Forbidden: non-structural class             │
└─────────────────────────────────────────────┘
```

WHY ENUM WORKS:
```
enum class Angle { ZERO=0, HALF_PI=1, PI=2 };

template<Angle::PI> → Compiler sees integer 2
template<Angle::HALF_PI> → Compiler sees integer 1

Each enum value = distinct integer = distinct specialization
```

---

## E6: "Round-off errors at runtime?"

YOUR CLAIM: (implicit) Round-off happens at runtime

FACT:
```
constexpr float x = constexpr_sin(pi);
              ↓
g++ computes Taylor series
g++ accumulates round-off errors
g++ stores 0xb2435010 in binary
              ↓
CPU at runtime: movss 0xb2435010, %xmm0
NO computation, NO new round-off
```

YOUR CONFUSION:
- Round-off happens WHERE computation happens
- Constexpr → computation in compiler → round-off in compiler
- Runtime → computation in CPU → round-off in CPU

---

## Summary

| Error | What You Said | Truth |
|-------|---------------|-------|
| E1 | "constexpr is slowest" | constexpr AT RUNTIME is slowest; AT COMPILE is fastest |
| E2 | "why loop" | Amplify nanosecond operation to measurable |
| E4 | "no float immediate = useless" | Saves computation, not load |
| E5 | "why enum" | float not allowed as template parameter in C++17 |
| E6 | "round-off at runtime" | Round-off at compile time for constexpr |

---

## Prevention Checklist

□ constexpr FUNCTION ≠ constexpr EXECUTION
□ constexpr VARIABLE forces compile-time evaluation
□ float template parameters: C++20 only
□ Enum = integer = valid template parameter
□ Round-off happens where computation happens
