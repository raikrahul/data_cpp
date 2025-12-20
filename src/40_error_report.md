:01. TRAP ADDRESS. `&p1.name` = 0x7FFC1000. `&p2.name` = 0x7FFC1020. 0x7FFC1000 ≠ 0x7FFC1020. Address compare = false. Content same. :02. TRAP SSO. "Alice" len=5 < 15. Buffer inside string at +16. p1.name.c_str()=0x7FFC1010. p2.name.c_str()=0x7FFC1030. Pointer compare = false. :03. TRAP MEMCMP. `memcmp("Alice","AliceX",5)` → 5 bytes equal → 0 (WRONG). Sizes differ: 5 ≠ 6. :04. CORRECT. `p1.name == p2.name` → operator== → size check → byte compare → true. :05. TRAP EMPTY. `max_element(v.begin(), v.end())` where v.size()=0. end()=begin(). Dereference end() = UB. :06. EDGE N=0. Check `v.empty()` before algorithm. :07. F1. Missing `#include <vector>`. Used type without header. Compile error. :08. F2. Pointer compare instead of content. `&a==&b` vs `a==b`. :09. F3. c_str() returns buffer pointer. Different strings = different addresses. :10. F4. memcmp(a,b,min(len)) ignores longer string.
# Error Report: Session 2025-12-19


## Errors Made

### Error 1: Missing includes
- Line: 5-8 in 40_person_name_compare_worksheet.cpp
- What went wrong: Used std::vector, std::copy_if without #include <vector>, <algorithm>
- What should be: Always include headers before using types
- Why sloppy: Typed code without checking dependencies
- What missed: Compile step before running
- Prevent: Compile after every 10 lines added

### Error 2: Pointer comparison confusion
- What went wrong: Expected &p1.name == &p2.name to compare content
- What should be: &p1.name compares ADDRESSES, p1.name == p2.name compares CONTENT
- Why sloppy: Did not trace memory addresses by hand
- What missed: Different objects have different addresses
- Prevent: Draw memory diagram BEFORE writing comparison

### Error 3: c_str() pointer comparison
- What went wrong: Expected p1.name.c_str() == p2.name.c_str() to work
- What should be: c_str() returns buffer pointer, different buffers have different addresses
- Why sloppy: Assumed pointers to same content are equal
- What missed: SSO buffers are INSIDE each string object at different locations
- Prevent: Print addresses before comparing

### Error 4: memcmp without size check
- What went wrong: memcmp("Alice", "AliceX", 5) returns 0 (equal)
- What should be: Check size equality FIRST, then memcmp
- Why sloppy: Did not consider different-length strings
- What missed: memcmp stops at N bytes, ignores rest
- Prevent: Always compare .size() before byte comparison

### Error 5: copy_if vs views::filter confusion
- What went wrong: Did not understand copy_if copies bytes
- What should be: copy_if = O(N × sizeof(T)) bytes copied, views::filter = 0 bytes
- Why sloppy: Did not trace where data lives after operation
- What missed: &source[0] ≠ &result[0] proves copy
- Prevent: Print addresses before and after algorithm

### Error 6: Empty vector edge case
- What went wrong: max_element(v.begin(), v.end())->age crashes on empty vector
- What should be: Check v.empty() first, or use ranges::max with exception handling
- Why sloppy: Did not consider edge case N=0
- What missed: end() iterator cannot be dereferenced
- Prevent: Always test with empty input

### Error 7: SSO threshold assumption
- What went wrong: Assumed all strings on heap
- What should be: "Alice" (5 chars) < 15 → SSO active → buffer inside string object
- Why sloppy: Did not check string.capacity() vs length
- What missed: Short strings avoid heap allocation
- Prevent: Check capacity() and compare to SSO threshold (15 for libstdc++)

### Error 8: Index formula confusion
- What went wrong: k = i×nx + j vs k = i×ny + j
- What should be: nx = columns per row, k = i×nx + j where nx = number of columns
- Why sloppy: Did not define nx and ny clearly before formula
- What missed: Row-major order: skip i×(columns per row) + column offset
- Prevent: Write definition before formula

## Questions for Sloppy Brain

1. Did you compile after adding code? NO → compile every 10 lines
2. Did you print addresses before comparing? NO → print always
3. Did you test empty input? NO → test N=0 first
4. Did you draw memory layout? NO → draw before code
5. Did you check sizeof() and offsetof()? NO → check always
6. Did you trace bytes through algorithm? NO → trace step by step
7. Did you calculate by hand before running? NO → calculate first

## Pattern: Where Errors Cluster

- Header includes: 1 error
- Pointer vs content comparison: 3 errors
- Algorithm behavior: 2 errors
- Edge cases: 1 error
- Index arithmetic: 1 error

Total: 8 errors

## Prevention Checklist

- [ ] Include headers matching types used
- [ ] Print addresses before comparison
- [ ] Draw memory diagram with real addresses
- [ ] Test with empty container
- [ ] Check sizeof() matches expectation
- [ ] Trace algorithm step by step with addresses
- [ ] Calculate index formula by hand with example
