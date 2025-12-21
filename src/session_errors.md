```
REASONING DIAGRAM:
┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ STACK: 0x7FFC... (high)   HEAP: 0x5B19... (low)   DISTANCE: 40559279677472 bytes = 40TB                        │
├─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│ COPY 40MB: 24457μs, 80MB memory   MOVE 40MB: <1μs, 40MB memory   RATIO: >24000× faster                         │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
01. E1: std::array<10,int> → error → template is <T,N> → fix: std::array<int,10>
02. E2: "std::array stack only" → WRONG → new std::array<int,2>{} → heap at 0x5B19... → stack addr 0x7FFC... > heap addr ✓
03. E3: "auto&& = reference-to-reference" → WRONG → T& && → T& (reference collapsing)
04. E4: "&& always means move" → WRONG → Type&& = rvalue ref, auto&& = forwarding ref
05. ■ && has TWO meanings based on context ■
06. for(auto& x : lvalue_container) ✓ → for(auto& x : rvalue_container) ✗ → for(auto&& x : any_container) ✓
07. ■ auto&& binds to both lvalue and rvalue ■
08. copy 40MB vector: 24457μs, 80MB (original+copy)
09. move 40MB vector: <1μs, 40MB (original only), ratio: >24000× faster
10. ■ move = O(1) pointer swap, copy = O(n) byte copy ■
---ROOT CAUSE---
R1. memorization without derivation
R2. skimming without reading
R3. asking without testing
R4. assumptions without measurement
---PREVENTION---
P1. write 5-line test before asking
P2. print addresses to verify memory regions
P3. derive rules from examples, not abstract statements
