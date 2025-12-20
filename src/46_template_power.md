# 46 Template Power Function Derivation

## Input→Output
```
pow(2,3)     → 8          int base, int result
pow(2.5,2)   → 6.25       float base, float result
pow(-3,3)    → -27        negative base, odd exponent
pow(5,0)     → 1          any base, zero exponent
pow(0,5)    → 0          zero base
```

## Code Duplication Problem
```
+-------------------+    +-------------------+    +-------------------+
| pow_int           |    | pow_float         |    | pow_double        |
| int x, int n      |    | float x, int n    |    | double x, int n   |
| int result = 1    |    | float result = 1.0f|    | double result=1.0 |
| loop: result *= x |    | loop: result *= x |    | loop: result *= x |
+-------------------+    +-------------------+    +-------------------+
         ↓                        ↓                        ↓
    SAME LOGIC              SAME LOGIC              SAME LOGIC
    DIFFERENT TYPE          DIFFERENT TYPE          DIFFERENT TYPE
```

## Step-by-Step Hand Trace

01. pow(2,3): result=1 at iter₀, result*=x means result=result*x=1*2=2 at iter₁, result=2*2=4 at iter₂, result=4*2=8 at iter₃, n=3 iterations done, return 8; count iterations: {1,2,3}=3 loops, verify 2³=8 ✓
02. pow(2.5,2): result=1.0f at start (type=float matches x), iter₁: result=1.0*2.5=2.5, iter₂: result=2.5*2.5=6.25, n=2 iterations done, return 6.25; verify 2.5²=6.25 ✓, trap: if result=1 (int) instead of 1.0f → int*float→float but result slot is int → truncation at each step
03. pow(-3,3): result=1, iter₁: 1*(-3)=-3, iter₂: (-3)*(-3)=9, iter₃: 9*(-3)=-27, return -27; odd exponent → sign preserved, (-1)³=-1 ✓
04. pow(-3,2): result=1, iter₁: 1*(-3)=-3, iter₂: (-3)*(-3)=9, return 9; even exponent → sign lost, (-1)²=+1 ✓
05. pow(5,0): n=0 → loop executes 0 times → result=1 unchanged → return 1; x⁰=1 definition, verify 5⁰=1 ✓
06. pow(0,5): result=1, iter₁: 1*0=0, iter₂: 0*0=0, iter₃: 0*0=0, iter₄: 0*0=0, iter₅: 0*0=0 → return 0; verify 0⁵=0 ✓, trap: once result=0, all further multiplications stay 0
07. pow(0,0): n=0 → loop 0 times → result=1; mathematically undefined, code returns 1 ⚠, this is 0⁰ edge case
08. Without template: pow_int(int x,int n){int result=1; for(int i=0;i<n;++i)result*=x; return result;} works for int, need pow_float(float x,int n){float result=1.0f;...} for float, need pow_double(double x,int n){double result=1.0;...} for double → 3 copies of same logic
09. With template: template<typename T> T pow(T x, int n){T result=1; for(int i=0;i<n;++i)result*=x; return result;} → compiler generates pow<int>, pow<float>, pow<double> on demand, trap: result=1 literal → must be convertible to T, for int→1, for float→1.0f, for double→1.0
10. Template instantiation: pow<int>(2,3) → compiler substitutes T=int everywhere → generates int pow(int x, int n){int result=1;...}, this happens at compile-time not runtime, verify: sizeof(result)=sizeof(int)=4 for T=int, sizeof(result)=sizeof(double)=8 for T=double

## Memory Layout Comparison
```
Non-template (3 functions in binary):
     .text section
     +------------------+
0x1000 | pow_int code     | 48 bytes
     +------------------+
0x1030 | pow_float code   | 48 bytes
     +------------------+
0x1060 | pow_double code  | 48 bytes
     +------------------+

Template (3 instantiations = same 3 functions):
     .text section
     +------------------+
0x1000 | pow<int> code    | 48 bytes
     +------------------+
0x1030 | pow<float> code  | 48 bytes
     +------------------+
0x1060 | pow<double> code | 48 bytes
     +------------------+

∴ Template = compile-time code generation, not runtime polymorphism
∴ Binary size same, but source code single definition
```

## Failure Prediction Table
```
| ID | Failure                                    | Symptom                        | Detection               |
|:---|:-------------------------------------------|:-------------------------------|:------------------------|
| F1 | pow_float uses result=1 not 1.0f           | int→float implicit, works      | Subtle: relies on conv  |
| F2 | Call pow(2.5, 3.0) with n as double        | n=3.0→3 truncation ⚠           | Compiler warning        |
| F3 | Forget template<typename T> keyword        | Compile error: T undefined     | Immediate               |
| F4 | Assume template runs at runtime            | No, compile-time substitution  | Conceptual              |
| F5 | pow(2, -3) with int n → negative loop      | n=-3, i<-3 false, result=1     | Wrong: 2⁻³=0.125 ✗      |
| F6 | Expect pow<int>(2.5,3)=15.625              | 2.5→2, 2³=8 ✗                  | Type mismatch           |
| F7 | Use T result=T(1) vs T result=1            | Both work, T(1) explicit       | Style                   |
```

## Numerical Punishment Block - Large Scale
```
pow(2,10): 1→2→4→8→16→32→64→128→256→512→1024 = 2¹⁰=1024 ✓
Iter trace: i=0:1*2=2, i=1:2*2=4, i=2:4*2=8, i=3:8*2=16, i=4:16*2=32, i=5:32*2=64, i=6:64*2=128, i=7:128*2=256, i=8:256*2=512, i=9:512*2=1024
Verify: 2¹⁰=1024 ✓

pow(1.1,10): 1.0→1.1→1.21→1.331→1.4641→1.61051→1.771561→1.9487171→2.14358881→2.357947691→2.5937424601
Iter: i=0:1.0*1.1=1.1, i=1:1.1*1.1=1.21, i=2:1.21*1.1=1.331, i=3:1.331*1.1=1.4641, i=4:1.4641*1.1=1.61051, i=5:1.61051*1.1=1.771561, i=6:1.771561*1.1=1.9487171, i=7:1.9487171*1.1=2.14358881, i=8:2.14358881*1.1=2.357947691, i=9:2.357947691*1.1=2.5937424601
Verify: 1.1¹⁰≈2.5937... ✓ (compound growth)

pow(0.5,4): 1.0→0.5→0.25→0.125→0.0625 = 0.5⁴=0.0625=1/16 ✓
Iter: i=0:1.0*0.5=0.5, i=1:0.5*0.5=0.25, i=2:0.25*0.5=0.125, i=3:0.125*0.5=0.0625
Verify: 0.5⁴=(1/2)⁴=1/16=0.0625 ✓
```

## Template Syntax Breakdown
```
template<typename T>    ← keyword template, parameter list<>, typename T declares type parameter
T                       ← return type = same as base type
pow(T x, int n)         ← function name, T x base, int n exponent (n NOT templated)
{
    T result = 1;       ← result type = T, initialized with 1 (converts to T)
    for(int i=0; i<n; ++i)  ← loop n times
        result *= x;    ← compound multiply: result = result * x
    return result;      ← return type T
}

Call: pow<int>(2,3)     ← explicit instantiation, T=int
Call: pow(2.5,3)        ← implicit deduction, x=2.5 is double, T=double
```

## TODO Blocks for cpp file
```
TODO BLOCK 1: Implement pow_int without template (duplicate code pattern)
TODO BLOCK 2: Implement pow_float without template (duplicate code pattern)
TODO BLOCK 3: Implement template pow<T> (single definition)
TODO BLOCK 4: Test explicit instantiation pow<int>(2,3)
TODO BLOCK 5: Test implicit deduction pow(2.5,3)
TODO BLOCK 6: Test edge cases pow(0,5), pow(5,0), pow(0,0)
TODO BLOCK 7: Test negative base pow(-3,3), pow(-3,2)
```

## Complexity
```
Time: O(n) → n multiplications
Space: O(1) → result, i, x, n only
Optimization: O(log n) via squaring: x^8 = ((x²)²)² = 3 multiplies not 8
```
