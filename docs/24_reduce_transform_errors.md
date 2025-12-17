# Implementation Mistakes Report

## Line-by-line Errors

### Error 1: Missing struct keyword
Line: User wrote `template<typename T> my_plus {`
Wrong: No `struct` keyword
Should be: `template<typename T> struct my_plus {`
Why sloppy: Skipped fundamental C++ syntax
What missed: Class/struct declaration requires keyword
How to prevent: Write complete declaration, not shorthand

### Error 2: Missing operator() name
Line: User wrote `T operator(T a, Tb) {`
Wrong: No parentheses after `operator`, undefined `Tb`
Should be: `T operator()(const T& a, const T& b) const {`
Why sloppy: Confused function call operator syntax
What missed: `operator()` requires two sets of parentheses, const references, const method
How to prevent: operator() = operator + () + (parameters)

### Error 3: Missing const qualifiers
Line: User wrote `T operator()(T a, T b) {`
Wrong: Pass by value, non-const method
Should be: `T operator()(const T& a, const T& b) const {`
Why sloppy: Ignored efficiency and const-correctness
What missed: References avoid copies, const allows temporary objects
How to prevent: Always use const T& for read-only parameters

### Error 4: Missing semicolon after struct
Line: User wrote `template<typename T> struct my_plus { ... }`
Wrong: No semicolon after closing brace
Should be: `template<typename T> struct my_plus { ... };`
Why sloppy: Forgot struct definition requires semicolon
What missed: Struct/class definitions end with };
How to prevent: Every struct/class definition ends with };

### Error 5: Void specialization confusion
Line: User wrote `template<> struct my_plus { operator()(const T& a, const T&b) {`
Wrong: No `<void>`, no template parameters for operator(), `T` undefined
Should be: `template<> struct my_plus<void> { template<typename T, typename U> auto operator()(T&& a, U&& b) const -> decltype(a+b) { return a+b; } };`
Why sloppy: Misunderstood specialization syntax and type deduction
What missed: Specialization needs `<void>`, operator() needs own template, no `T` available
How to prevent: Specialization = template<> struct Name<SpecificType>, operator() deduces types

### Error 6: Typo in type name
Line: User wrote `T operator(T a, Tb) {`
Wrong: `Tb` instead of `T b`
Should be: `const T& b`
Why sloppy: Typing error, no proofreading
What missed: Variable name separated from type by space
How to prevent: Read code before asking

### Error 7: Missing forward declaration
Line: User wrote `template<> struct my_plus<void> {` without primary template
Wrong: Specializing non-existent template
Should be: First `template<typename T = void> struct my_plus;` then specialization
Why sloppy: Assumed compiler knows what being specialized
What missed: Specialization requires primary template declaration
How to prevent: Declare primary template before specialization

### Error 8: Missing forwarding references
Line: User wrote void specialization without `T&&` and `U&&`
Wrong: Cannot handle lvalues and rvalues
Should be: `template<typename T, typename U> auto operator()(T&& a, U&& b) const`
Why sloppy: Ignored perfect forwarding requirements
What missed: Forwarding reference `T&&` binds to both lvalue and rvalue
How to prevent: Void specialization needs universal references for flexibility

### Error 9: Missing trailing return type
Line: User wrote `auto operator()(...) {`
Wrong: No `-> decltype(a+b)`
Should be: `auto operator()(T&& a, U&& b) const -> decltype(a+b) { return a+b; }`
Why sloppy: Assumed auto deduces correctly without hint
What missed: Trailing return type documents deduction, helps compiler
How to prevent: Use `-> decltype(expression)` for clarity

### Error 10: Confusion about iterator_traits
Line: User asked why line 238 needs long return type
Wrong: Thought return type optional
Should be: `typename std::iterator_traits<InputIt>::value_type` required
Why sloppy: Did not understand template type deduction rules
What missed: Without `T` parameter, must extract type from iterator
How to prevent: No parameter = must compute type explicitly

## Conceptual Errors

### Conceptual Error 1: Template specialization vs overloading
Wrong: Thought `my_reduce` has specializations
Should be: `my_reduce` has 3 overloads (function overloading), `my_plus` has specialization (template specialization)
Why sloppy: Confused function templates with class templates
What missed: Functions = overloading, Classes = specialization
How to prevent: Functions cannot be partially specialized, only overloaded

### Conceptual Error 2: Partial specialization with 1 parameter
Wrong: Asked about partial specialization for `my_plus<T>`
Should be: Partial specialization requires 2+ parameters
Why sloppy: Did not understand partial vs full specialization
What missed: Partial = some parameters fixed, some variable; requires 2+ total
How to prevent: 1 parameter = only full specialization possible

### Conceptual Error 3: Type deduction source
Wrong: Confused where `T` comes from in overload 2 vs 3
Should be: Overload 2 deduces `T` from `init` argument, overload 3 extracts from iterator
Why sloppy: Did not trace template parameter sources
What missed: Deduction = from arguments, Extraction = from type traits
How to prevent: Check function signature for `T` parameter presence

### Conceptual Error 4: Return type declaration vs type alias
Wrong: Asked why line 238 and 310 both use `iterator_traits`
Should be: Line 238 = return type (outside body), line 310 = type alias (inside body)
Why sloppy: Confused declaration with usage
What missed: Return type needed at declaration, type alias needed for `T{}`
How to prevent: Declaration = what function returns, Usage = what code uses

## Pattern Recognition Failures

### Failure 1: operator() syntax
Pattern: `operator()` = `operator` + `()` + `(parameters)`
Missed: Two sets of parentheses required
Evidence: Wrote `operator(T a, T b)` instead of `operator()(T a, T b)`

### Failure 2: Template specialization syntax
Pattern: `template<> struct Name<SpecificType>`
Missed: `<SpecificType>` after struct name
Evidence: Wrote `template<> struct my_plus` instead of `template<> struct my_plus<void>`

### Failure 3: Const correctness
Pattern: Read-only parameters = `const T&`, read-only methods = `const`
Missed: Both parameter and method const
Evidence: Wrote `T operator()(T a, T b)` instead of `T operator()(const T& a, const T& b) const`

### Failure 4: Type deduction requirements
Pattern: No parameter of type `T` → must compute `T` explicitly
Missed: `iterator_traits` needed when `T` not in parameters
Evidence: Asked why long return type needed in overload 3

## Attention to Detail Failures

### Detail 1: Semicolon after struct
Count: 1 missing semicolon
Impact: Compile error
Fix: Add `;` after `}`

### Detail 2: Typo `Tb` instead of `T b`
Count: 1 typo
Impact: Undefined type error
Fix: Proofread before submitting

### Detail 3: Missing `const` qualifiers
Count: 3 missing (2 parameters + 1 method)
Impact: Cannot use with temporaries, inefficient copies
Fix: Always write `const T&` for read-only

### Detail 4: Missing template parameters
Count: 1 missing `template<typename T, typename U>` for operator()
Impact: Cannot deduce types
Fix: operator() in void specialization needs own template

## Carelessness Score

Total errors: 14
Syntax errors: 6
Conceptual errors: 4
Pattern failures: 4
Detail failures: 4

Carelessness level: HIGH
Root cause: Incomplete understanding + rushed typing + no verification
Solution: Write complete syntax, verify each component, test before asking
