001. struct counter { int count{}; int operator()(int increment) { return count += increment; } };
002. sizeof(counter) = 4 bytes (int size) ✓
003. alignof(counter) = 4 bytes (int alignment) ✓
004. Frame pointer (rbp) established at 0x7ffc_c000 (typical Linux stack base) → Stack grows downward ✓
005. &myCounter = rbp - 0x10 = 0x7ffc_bff0 → 16-byte alignment padding before first local variable ✓
006. Memory state at 0x7ffc_bff0 before construction: uninitialized garbage = 0xcdcdcdcd (debug fill pattern) ✓
007. Construction: counter myCounter{10} → aggregate initialization → count = 10 → bytes {0x0a, 0x00, 0x00, 0x00} ✓
008. Store to memory: *(int*)0x7ffc_bff0 = 0x0a → 0x7ffc_bff0 = 0a 00 00 00 ✓
009. First call site: int tick = myCounter(1); → PC = 0x4000_10a0, SP = rbp - 0x20 = 0x7ffc_bfe0 ✓
010. Call instruction pushes return address 0x4000_10a5 onto stack at SP-8 → new SP = 0x7ffc_bfd8, *(uint64*)0x7ffc_bfd8 = 0x4000_10a5 ✓
011. 'this' pointer passed in rdi register: rdi = 0x7ffc_bff0 (address of myCounter) ✓
012. 'increment' argument passed in esi register: esi = 0x00000001 (value 1) ✓
013. Function prologue: push rbp → *(uint64*)0x7ffc_bfd0 = old_rbp, rbp = 0x7ffc_bfd8 ✓
014. Load count member: mov eax, [rdi] → eax = *(int*)0x7ffc_bff0 = 0x0000000a = 10 ✓
015. Add increment: add eax, esi → eax = 0x0000000a + 0x00000001 = 0x0000000b = 11 ✓
016. Store result: mov [rdi], eax → *(int*)0x7ffc_bff0 = 0x0b → memory becomes 0b 00 00 00 ✓
017. Return value in eax = 0x0000000b → tick = eax = 11 ✓
018. Function epilogue: pop rbp → rbp = old_rbp = 0x7ffc_c000, SP = 0x7ffc_bfe0 ✓
019. Return instruction: ret → PC = *(uint64*)0x7ffc_bfd8 = 0x4000_10a5, SP = 0x7ffc_bfe8 ✓
020. Verify: tick = 11, myCounter.count = 11, memory at 0x7ffc_bff0 = 0b 00 00 00 ✓
021. Second call: myCounter(1); → PC = 0x4000_10b0, same 'this' = 0x7ffc_bff0, increment = 1 ✓
022. Load: eax = *(int*)0x7ffc_bff0 = 0x0000000b = 11 ✓
023. Add: eax = 11 + 1 = 12 → 0x0000000c ✓
024. Store: *(int*)0x7ffc_bff0 = 0x0c → memory = 0c 00 00 00 ✓
025. Return: eax = 12 → count = 12 ✓
026. Verify: myCounter.count = 12, memory = 0c 00 00 00 ✓
027. Third call: myCounter(3); → increment = 3, load = 12, add = 12+3 = 15 → 0x0000000f, store = 0f, count = 15 ✓
028. Fourth call: myCounter(5); → increment = 5, load = 15, add = 15+5 = 20 → 0x00000014, store = 14, count = 20 ✓
029. Fifth call: myCounter(2); → increment = 2, load = 20, add = 20+2 = 22 → 0x00000016, store = 16, count = 22 ✓
030. Final state after 5 calls: memory at 0x7ffc_bff0 = 16 00 00 00, count = 22 ✓
031. Sum of increments applied: 1 + 1 + 3 + 5 + 2 = 12 ✓
032. Arithmetic verification: initial_count(10) + sum(12) = final_count(22) ✓
033. Edge case N=0 calls: count remains 10, memory unchanged = 0a 00 00 00 ✓
034. Edge case N=1 call with increment=100: load=10, add=110, store=6e, count=110 ✓
035. Edge case N=2 calls with increment=INT_MAX: load=2147483647, add=1 → 0x80000000 = -2147483648 (overflow) → implementation-defined wraparound ✗
036. Copy construction: counter copy = myCounter; → copy constructed at address &copy = rbp - 0x14 = 0x7ffc_bfec → memcpy(0x7ffc_bfec, 0x7ffc_bff0, 4) → copy.count = 22, memory at 0x7ffc_bfec = 16 00 00 00 ✓
037. Call on copy: copy(1); → load from 0x7ffc_bfec = 22, add=23, store=17 → copy.count=23, original myCounter.count remains 22 ✓
038. Move construction: counter moved = std::move(myCounter); → moved object at 0x7ffc_bff8 = 16 00 00 00, myCounter left in valid-but-unspecified state (often unchanged) ✓
039. Large scale: N=1000000 calls, increment=1 → total increment = 1000000, final count = 10 + 1000000 = 1000010 → 0x000f424a ✓
040. Time estimation: 1 call = 5 CPU cycles @ 3GHz = 1.67ns → 1000000 calls = 1.67ms ✓
041. Cache analysis: sizeof(counter)=4 bytes < cache line size 64 bytes → fits in one line, no false sharing ✓
042. Thread safety: thread1 calls myCounter(1), thread2 calls myCounter(1) simultaneously → both load 10, both write 11 → race condition → lost update ✗
043. Thread safety fix: mutex lock/unlock around count += increment → 20 cycles overhead → 1.67ns → 6.67ns per call ✓
044. Narrowing conversion: myCounter(1.9f) → 1.9f → 0x3ff33333 → truncated to int = 1 → silent data loss ✗
045. Explicit cast: myCounter(static_cast<int>(1.9f)) → cast rounds toward zero = 1 → explicit conversion required ✓
046. Lambda equivalent: auto lambda = [count=10](int inc) mutable { return count += inc; }; → lambda object size = 4 bytes at &lambda = rbp - 0x1c = 0x7ffc_bfe4 → memory initialization: *(int*)0x7ffc_bfe4 = 0a ✓
047. Lambda call: lambda(1); → this pointer is lambda capture pointer → load 10, add=11, store=0b → return=11 ✓
048. Lambda copy: auto lambda2 = lambda; → lambda2 at 0x7ffc_bfe8 = 0b 00 00 00 (independent copy) ✓
049. Functor vs function pointer: functor inlined → 5 cycles, function pointer indirect call ~15 cycles → 3× slower ✗
050. Member function pointer: &counter::operator() = 0x4000_10a0 → sizeof(ptr) = 16 bytes (this adjustment + function address) ✓
051. std::function overhead: std::function<int(int)> fn = myCounter; → fn object size = 32 bytes → heap allocation for type-erasure = 48 bytes at 0x5555_e000 → vtable pointer = 0x4000_2000 ✗
052. std::function call: fn(1) → virtual call via vtable → 15 cycles → indirect jump misprediction penalty = 20 cycles → total 35 cycles ✗
053. Inheritance: struct derived : counter { int extra; }; → sizeof(derived) = 8 bytes → offset(extra)=4 → alignment=4 ✓
054. Polymorphism: counter* p = new derived{10, 5}; → heap allocation @ 0x5555_f000 → layout: 0a 00 00 00 05 00 00 00 → p->operator()(1) → derived::operator()? No, base operator called → count=11, extra unchanged=5 ✓
055. Virtual operator() fix: virtual int operator()(int inc) { return count += inc; } → vtable pointer added → sizeof(counter) = 16 bytes (4 for count + 8 for vptr + 4 padding) → address calculation requires vptr dereference ✓
056. Destructor overhead: ~counter() = default → no action → sizeof unchanged → no cleanup needed for int member ✓
057. Static member: static counter global; → global stored in .bss at 0x601000 → zero-initialized at program start → memory = 00 00 00 00 ✓
058. Static lifetime: persists across function calls → reused state → thread-unsafe ✗
059. constexpr: constexpr counter c{10}; → compile-time constant → stored in .rodata at 0x402000 = 0a 00 00 00 → cannot call operator() (non-const) ✗
060. const operator(): int operator()(int inc) const { return count + inc; } → does not modify count → returns 22+1=23 but count stays 22 ✗
061. mutable int count; + const operator() → allows modification in const method → count changes despite const call → count becomes 23 ✓
062. Alignment: alignas(16) counter { int count; }; → sizeof=16, alignment=16 → address must be 0x...0, 0x...10, etc → SP adjusted to rbp-0x20 for alignment ✓
063. Packed: __attribute__((packed)) counter → sizeof=4, alignment=1 → may cause unaligned access faults on ARM → performance penalty = 10 cycles per access ✗
064. Bit-field: struct { int count:24; int flag:8; }; → sizeof=4 → count max value = 2^24-1 = 16777215 → overflow at 16777216 → wrap to 0 ✗
065. Operator precedence: myCounter(1) + 2 → (myCounter(1)) + 2 → 22+1=23 then 23+2=25 → 0x00000019 ✓
066. Chaining: myCounter(myCounter(1)) → inner returns 23, outer adds 23 → count becomes 22+23=45 → 0x0000002d ✓
067. Conversion operator: operator int() const { return count; } → allows int x = myCounter; → x = 22 ✓
068. Explicit conversion: explicit operator int() const → prevents implicit conversion → int x = myCounter; ✗ compilation error, requires static_cast<int>(myCounter) ✓
069. Overload: double operator()(double inc) { return count += (int)inc; } → myCounter(1.5) → inc=1.5 → cast to int=1 → count becomes 23 → returns 23.0 ✓
070. Template: template<typename T> T operator()(T inc) → generates int and double instantiations → code size increase = 2 × 50 bytes = 100 bytes ✓
071. SFINAE: template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>> T operator()(T inc) → only accepts integers → myCounter(1.5) ✗ compilation error ✓
072. Perfect forwarding: template<typename... Args> auto operator()(Args&&... args) { return (count += ... += args); } → fold expression → myCounter(1,2,3) ✗ requires fold expression syntax (count += ... + args) ✓
073. Variadic: int operator()(std::initializer_list<int> incs) → myCounter({1,2,3}) → sum = 1+2+3 = 6 → count becomes 22+6=28 → 0x0000001c ✓
074. Reset annoyance: no reset() member → must assign myCounter = counter{10}; → state lost → design flaw ✗
075. Failure prediction F1: Race condition on concurrent calls → expected: count = initial + sum(all increments), actual: count < expected due to lost updates → ✗
076. Failure prediction F2: Overflow with INT_MAX → expected: 2147483647 + 1 = 2147483648, actual: -2147483648 → wraparound → ✗
077. Failure prediction F3: Narrowing conversion from float → expected: 1.9f treated as 1.9, actual: truncated to 1 → silent data loss → ✗
078. Failure prediction F4: Missing include <iostream> → expected: compilation success, actual: error: 'cout' not declared → ✗
079. Failure prediction F5: Forgetting mutable in lambda → expected: lambda can modify capture, actual: compilation error: cannot modify const capture → ✗
080. Failure prediction F6: Using std::function for simple functor → expected: same performance, actual: 10× slowdown due to heap allocation and virtual call → ✗
081. Failure prediction F7: Assuming SSO for long string in counter name → expected: no heap allocation, actual: allocation when string > 15 chars → ✗
082. Failure prediction F8: Not marking operator() const when no modification → expected: works, actual: prevents const objects from being called → ✗
083. Failure prediction F9: Packing struct without understanding alignment → expected: smaller size, actual: unaligned access crash on ARM → ✗
084. Failure prediction F10: Using bit-field without range check → expected: values fit, actual: overflow at 2^24 → ✗
