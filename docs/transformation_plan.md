# WORKSHEET TRANSFORMATION PLAN: Rudin-Style Axiomatic Format

---

## TASK ANALYSIS: What Must Be Done

### FILES TO TRANSFORM (32 total)

```
docs/   → 19 files
src/    → 13 files
```

---

## QUESTIONS ABOUT THE TASK (Grilling)

### Q1: What is the atomic unit of a "step"?

- Current state: Steps contain English sentences mixed with code
- Required state: Step = ONE calculation OR ONE diagram OR ONE fill-in
- UNRESOLVED: How long is "one step"? 
  - Too short → fragmented, loses context
  - Too long → user skips to end
- PROPOSED: 1 step = 1 line that fits 120 characters on wide screen
- COUNTER-QUESTION: What if calculation requires 3 sub-steps? Inline or split?

### Q2: What constitutes "grounding every 5 steps"?

- PROPOSED FORMAT:
```
01. [calculation]
02. [calculation]  
03. [calculation]
04. [calculation]
05. [calculation]
---GROUND--- 
   Current state: a=7, b=5, tmp=5, 0x7FFDFFF8=07, 0x7FFDFFF4=05
   Next goal: Verify swap completed
---
06. [calculation]
```
- UNRESOLVED: Is "---GROUND---" too much English?
- ALTERNATIVE: Use only symbols: `■ STATE: a=7 b=5 ■ NEXT: verify ■`

### Q3: What symbols replace English?

| English | Symbol | Example |
|:--------|:-------|:--------|
| "therefore" | ∴ | a=5 ∴ *pa=5 |
| "implies" | → | N=0 → base case |
| "true/pass" | ✓ | 5==5 ✓ |
| "false/fail" | ✗ | 5==7 ✗ |
| "not" | ¬ | ¬(a==b) |
| "and" | ∧ | a>0 ∧ b>0 |
| "or" | ∨ | a==0 ∨ b==0 |
| "for all" | ∀ | ∀i∈[0,N) |
| "exists" | ∃ | ∃i: arr[i]==x |
| "element of" | ∈ | i∈{0,1,2} |
| "assignment" | ← | a ← 5 |
| "memory write" | → | 5 → 0x1000 |
| "dereference" | * | *0x1000 = 5 |

- UNRESOLVED: Is this enough? What other English words appear frequently?
- SCAN NEEDED: grep all .md files for common English verbs

### Q4: What is the structure of a transformed step?

```
CURRENT (English-heavy):
"First, we allocate memory for variable a. The address is calculated by..."

REQUIRED (Symbol-heavy):
01. a ← 5 → rsp-8 = 0x7FFDFFF8 → mem[0x7FFDFFF8] = 05 00 00 00 (little-endian, 4 bytes)
```

- PATTERN: `[line#]. [variable] ← [value] → [address calculation] → [memory write in hex]`
- UNRESOLVED: How to handle multi-variable operations?
- EXAMPLE: `*pa = *pb` requires: load pb → load *pb → load pa → store to *pa
- PROPOSED: Chain notation: `pb=0x7FFDFFE4 → *pb=0x7FFDFFF4 → **pb=7 → pa=0x7FFDFFEC → *pa=0x7FFDFFF8 → 7→*pa`

### Q5: What diagrams are required?

```
MEMORY DIAGRAM FORMAT:
┌────────────┬────────────┬────────────┐
│ 0x7FFDFFE0 │ 0x7FFDFFE4 │ 0x7FFDFFEC │
├────────────┼────────────┼────────────┤
│ tmp=5      │ pb→FFF4    │ pa→FFF8    │
└────────────┴────────────┴────────────┘
         ↓             ↓
┌────────────┬────────────┐
│ 0x7FFDFFF4 │ 0x7FFDFFF8 │
├────────────┼────────────┤
│ b=7        │ a=5        │
└────────────┴────────────┘
```

- UNRESOLVED: How often to draw? Every step? Every 5 steps?
- PROPOSED: Draw BEFORE any memory-modifying operation
- COUNTER-QUESTION: What about non-memory problems (pure algorithm)?

### Q6: What is the failure prediction format?

```
FAILURES (end of document):
F1. pa=nullptr → *pa=5 → SIGSEGV at 0x0 → ✗
F2. a=INT_MAX, b=1 → a+b=overflow → wrap to INT_MIN → ✗
F3. pa==pb (alias) → tmp=*pa, *pa=*pb (no-op), *pb=tmp → self-swap → ✓ but wasteful
```

- UNRESOLVED: How many failures per document? 
- PROPOSED: Minimum 5, maximum 10
- COUNTER-QUESTION: Should failures be numbered globally or per-section?

---

## FILE-BY-FILE TRANSFORMATION REQUIREMENTS

### GROUP A: Memory/Pointer Worksheets (HIGH PRIORITY)

| File | Current Lines | Key Problem | Transformation Needed |
|:-----|:--------------|:------------|:----------------------|
| 57_swap_evolution.md | 400+ | Mixed English/Symbols | Strip English, keep only address math |
| 36_smart_pointer_factory.md | 100+ | Control block layout | Draw RefCount diagrams every step |
| 37_struct_class_init.md | 50+ | Padding calculation | Force user to calculate sizeof by hand |
| 41_inheritance_virtual.md | 500+ | vtable dispatch | Draw vptr→vtable→function chain |

QUESTIONS FOR GROUP A:
- What is the minimum number of bytes user must calculate by hand?
- How to verify user actually did calculation (not skipped)?
- What if user gets wrong answer? Show correction or force retry?

### GROUP B: Algorithm Worksheets (MEDIUM PRIORITY)

| File | Current Lines | Key Problem | Transformation Needed |
|:-----|:--------------|:------------|:----------------------|
| 20_stl_algorithms_worksheet.md | 1000+ | for_each trace | Force iter₁, iter₂, iter₃ notation |
| 27_equal_mismatch_derivation.md | 500+ | Comparison chain | Draw p1↔p2 pointer pairs |
| 32_transform_reduce_derivation.md | 200+ | Reduction trace | Show accumulator at each step |

QUESTIONS FOR GROUP B:
- How to handle loops with 1000 iterations? Show first 5, last 2?
- What is "non-trivial" number of iterations to show?
- Should user derive loop invariant or just trace?

### GROUP C: Template Worksheets (MEDIUM PRIORITY)

| File | Current Lines | Key Problem | Transformation Needed |
|:-----|:--------------|:------------|:----------------------|
| 46_template_power.md | 125 | pow(2,10) trace | Force 10-step multiplication |
| 48_abbreviated_template.md | 270 | Type deduction | Draw T1=double, T2=float chains |
| 53_cpp_templates_worksheet.md | 51 | Multiple exercises | Split into atomic blocks |

QUESTIONS FOR GROUP C:
- Templates are compile-time. How to show "compile-time calculation"?
- Should user trace template instantiation depth?
- What is minimum instantiation count to show pattern?

### GROUP D: Error Reports (LOW PRIORITY - Already symbol-heavy)

| File | Current Lines | Key Problem | Transformation Needed |
|:-----|:--------------|:------------|:----------------------|
| 40_error_report.md | 93 | Already tabular | Add failure predictions |
| 44_mistakes_report.md | 25 | Already tabular | Minimal changes |
| session_errors.md | 49 | Already dense | Add grounding blocks |

---

## TRANSFORMATION ALGORITHM (per file)

```
INPUT: worksheet.md with mixed English/symbols
OUTPUT: worksheet_rudin.md with pure symbol notation

PASS 1: IDENTIFY STRUCTURE
  - Count sections (##)
  - Count code blocks (```)
  - Count English paragraphs
  - Count numerical examples

PASS 2: EXTRACT CALCULATIONS
  - Find all "calculate", "compute", "derive" sentences
  - Convert to: [line#]. [input] → [operation] → [output]

PASS 3: EXTRACT DIAGRAMS
  - Find all memory addresses
  - Build ASCII box diagram
  - Insert BEFORE each modification

PASS 4: ADD GROUNDING
  - Every 5 lines: insert STATE block
  - Format: ■ [var=val, var=val, ...] ■ NEXT: [goal] ■

PASS 5: COLLECT FAILURES
  - Find all "error", "fail", "crash" mentions
  - Move to FAILURES section at end
  - Format: F#. [condition] → [symptom] → [result] → ✓/✗

PASS 6: STRIP ENGLISH
  - Remove: "First", "Then", "Next", "Now", "Because", "Since"
  - Remove: "we", "you", "the", all pronouns
  - Remove: all adjectives, adverbs
  - Keep: numbers, symbols, arrows, addresses
```

---

## UNRESOLVED QUESTIONS (Require User Input)

1. **Scope**: Transform ALL 32 files or prioritize subset?
2. **Backup**: Keep original files as `*.md.bak` or overwrite?
3. **Verify**: After transformation, how to verify quality? Manual review?
4. **Length**: Is 1 step = 1 line too atomic? Allow 2-3 lines per step?
5. **Grounding frequency**: Every 5 steps or every 10 steps?
6. **Edge cases**: What if original file has NO calculations (pure text)?

---

## COUNTER-QUESTIONS ABOUT TASK ITSELF

### Why Rudin format?
- Rudin books are dense, axiomatic, no hand-holding
- Forces reader to DO each step or get lost
- No skipping possible - each line depends on previous
- COUNTER: Rudin has NO diagrams. User requested diagrams. Hybrid needed.

### Why "grounding every 5 steps"?
- Working memory limit: 7±2 items
- 5 steps = safe margin before overflow
- Ground = dump all state to paper → free working memory
- COUNTER: What if 5 steps is too frequent? 10 steps?

### Why "no solutions"?
- Solution = endpoint. User reads endpoint, skips derivation.
- No solution = must derive to proceed
- COUNTER: How does user know if derivation is correct without solution?
- ANSWER: Verification steps inline: `result = 8 = 2³ ✓`

### Why "failure predictions at end"?
- Failures = edge cases user will hit
- At end = user reads derivation first, then sees traps
- If at start, user skips derivation to read "what not to do"
- COUNTER: Some failures are CRITICAL. Should those be inline?

---

## NEXT STEPS (After User Confirms)

1. Select 1 file as prototype (recommend: 57_swap_evolution.md)
2. Transform prototype manually
3. User reviews prototype
4. If approved, transform remaining 31 files
5. Commit all with message: "Transform worksheets to Rudin format"

---

## ESTIMATED EFFORT

| Phase | Files | Time per file | Total |
|:------|:------|:--------------|:------|
| Group A (Memory) | 4 | 15 min | 1 hour |
| Group B (Algorithm) | 8 | 20 min | 2.5 hours |
| Group C (Template) | 6 | 10 min | 1 hour |
| Group D (Error) | 3 | 5 min | 15 min |
| Remaining | 11 | 10 min | 2 hours |
| **Total** | 32 | - | ~7 hours |

---

## WAITING FOR USER INPUT

1. Confirm scope (all 32 or subset)
2. Confirm grounding frequency (5 or 10)
3. Confirm prototype file selection
4. Confirm backup strategy
5. Confirm: Should code blocks remain or convert to ASCII?
