// 69_mystring_lesson.cpp
// MODERN C++20 STRING CLASS - BASED ON LIBSTDC++ std::basic_string
// NOTE: Uses std::allocator, NOT raw new/delete
// Reference: /usr/include/c++/14/bits/basic_string.h lines 86-800

#include <cstddef>
#include <cstring>
#include <memory>      // std::allocator, std::allocator_traits
#include <utility>     // std::move
#include <iostream>
#include <algorithm>   // std::copy

// ═══════════════════════════════════════════════════════════════════════════
// MEMORY LAYOUT (from libstdc++ basic_string.h lines 204-213)
// ═══════════════════════════════════════════════════════════════════════════
//
// sizeof(MyString) = 32 bytes on x86-64
//
// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Offset │ Field           │ Size   │ Description                          │
// ├────────┼─────────────────┼────────┼──────────────────────────────────────┤
// │ 0      │ m_data          │ 8      │ Pointer to char buffer (local or heap)│
// │ 8      │ m_size          │ 8      │ Current string length                │
// │ 16     │ union {         │ 16     │ Either:                              │
// │        │   m_local[16]   │        │   - SSO buffer (≤15 chars + '\0')    │
// │        │   m_capacity    │        │   - OR heap capacity (size_t)        │
// │        │ }               │        │                                      │
// └───────────────────────────────────────────────────────────────────────────┘
//
// SSO (Small String Optimization):
// - If m_size ≤ 15: m_data points to m_local[0], no heap allocation
// - If m_size > 15: m_data points to heap, m_capacity stored in union
//
// Example: "hello" (5 chars)
// ┌────────────────────────────────┐
// │ m_data = &m_local[0]           │  ← points to embedded buffer
// │ m_size = 5                     │
// │ m_local = "hello\0??????????"  │  ← 16 bytes, 6 used
// └────────────────────────────────┘
// NO HEAP ALLOCATION!

class MyString {
public:
    using allocator_type = std::allocator<char>;
    using alloc_traits = std::allocator_traits<allocator_type>;
    using size_type = std::size_t;
    using pointer = char*;
    using const_pointer = const char*;
    
private:
    // libstdc++ line 207: enum { _S_local_capacity = 15 / sizeof(_CharT) };
    static constexpr size_type S_local_capacity = 15;
    
    pointer m_data;           // Pointer to buffer (local or heap)
    size_type m_size;         // Current length (not including '\0')
    
    // libstdc++ lines 209-213: union for SSO
    union {
        char m_local_buf[S_local_capacity + 1];  // 16 bytes for SSO
        size_type m_allocated_capacity;          // Capacity when on heap
    };
    
    [[no_unique_address]] allocator_type m_alloc;  // C++20: zero-size if stateless
    
    // ═══════════════════════════════════════════════════════════════════════
    // HELPER: Check if using local buffer (SSO)
    // libstdc++ line 267-276: _M_is_local()
    // ═══════════════════════════════════════════════════════════════════════
    [[nodiscard]] constexpr bool is_local() const noexcept {
        return m_data == local_data();
    }
    
    [[nodiscard]] constexpr pointer local_data() noexcept {
        return m_local_buf;
    }
    
    [[nodiscard]] constexpr const_pointer local_data() const noexcept {
        return m_local_buf;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // HELPER: Allocate using std::allocator (NOT new!)
    // libstdc++ line 129-142: _S_allocate()
    // ═══════════════════════════════════════════════════════════════════════
    [[nodiscard]] pointer allocate(size_type n) {
        // std::allocator::allocate() calls ::operator new internally
        // But abstracts memory management correctly
        return alloc_traits::allocate(m_alloc, n);
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // HELPER: Deallocate using std::allocator (NOT delete!)
    // libstdc++ line 291-294: _M_destroy()
    // ═══════════════════════════════════════════════════════════════════════
    void deallocate(pointer p, size_type n) {
        alloc_traits::deallocate(m_alloc, p, n);
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // HELPER: Dispose of heap memory if not local
    // libstdc++ line 283-289: _M_dispose()
    // ═══════════════════════════════════════════════════════════════════════
    void dispose() {
        if (!is_local()) {
            deallocate(m_data, m_allocated_capacity + 1);
        }
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // HELPER: Set length and null-terminate
    // libstdc++ line 257-263: _M_set_length()
    // ═══════════════════════════════════════════════════════════════════════
    void set_length(size_type n) {
        m_size = n;
        m_data[n] = '\0';
    }
    
public:
    // ═══════════════════════════════════════════════════════════════════════
    // DEFAULT CONSTRUCTOR
    // libstdc++ line 526-533: basic_string()
    // Creates empty string using SSO (no heap allocation)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Memory state after:
    // m_data → m_local_buf (offset 16)
    // m_size = 0
    // m_local_buf[0] = '\0'
    //
    constexpr MyString() noexcept 
        : m_data(local_data()), m_size(0)
    {
        m_local_buf[0] = '\0';
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // C-STRING CONSTRUCTOR
    // libstdc++ line 646-655: basic_string(const _CharT* __s, ...)
    // ═══════════════════════════════════════════════════════════════════════
    //
    // Example: MyString s("hello");
    // strlen("hello") = 5 ≤ 15 → SSO
    // m_data → m_local_buf
    // memcpy("hello\0", 6 bytes)
    //
    // Example: MyString s("this is a longer string");
    // strlen(...) = 24 > 15 → heap allocation
    // m_data → heap (allocate 25 bytes via std::allocator)
    // m_allocated_capacity = 24
    //
    explicit MyString(const char* cstr) 
        : m_data(local_data()), m_size(0)
    {
        if (cstr == nullptr) {
            m_local_buf[0] = '\0';
            return;
        }
        
        const size_type len = std::strlen(cstr);
        
        if (len <= S_local_capacity) {
            // SSO: Use local buffer, no heap
            // m_data already points to m_local_buf from initializer
            std::memcpy(m_local_buf, cstr, len + 1);  // +1 for '\0'
        } else {
            // Heap: Allocate via std::allocator
            m_data = allocate(len + 1);
            m_allocated_capacity = len;
            std::memcpy(m_data, cstr, len + 1);
        }
        m_size = len;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // DESTRUCTOR
    // libstdc++ implicit + _M_dispose()
    // Only deallocates if NOT using SSO
    // ═══════════════════════════════════════════════════════════════════════
    ~MyString() {
        dispose();  // Only frees heap if !is_local()
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // COPY CONSTRUCTOR
    // libstdc++ line 551-558: basic_string(const basic_string& __str)
    // ═══════════════════════════════════════════════════════════════════════
    MyString(const MyString& other) 
        : m_data(local_data()), m_size(0)
    {
        if (other.m_size <= S_local_capacity) {
            // SSO: Copy to local buffer
            std::memcpy(m_local_buf, other.m_data, other.m_size + 1);
            m_data = local_data();
        } else {
            // Heap: Allocate and copy
            m_data = allocate(other.m_size + 1);
            m_allocated_capacity = other.m_size;
            std::memcpy(m_data, other.m_data, other.m_size + 1);
        }
        m_size = other.m_size;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // COPY ASSIGNMENT
    // libstdc++: operator=(const basic_string&)
    // Must handle: self-assign, dispose old, allocate new
    // ═══════════════════════════════════════════════════════════════════════
    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;  // Self-assign check
        
        // If new size fits in local, or current capacity is enough, reuse
        if (other.m_size <= S_local_capacity) {
            dispose();  // Free old heap if any
            std::memcpy(m_local_buf, other.m_data, other.m_size + 1);
            m_data = local_data();
            m_size = other.m_size;
        } else if (!is_local() && m_allocated_capacity >= other.m_size) {
            // Reuse existing heap buffer
            std::memcpy(m_data, other.m_data, other.m_size + 1);
            m_size = other.m_size;
        } else {
            // Need new allocation
            pointer new_data = allocate(other.m_size + 1);
            dispose();  // Free old
            m_data = new_data;
            m_allocated_capacity = other.m_size;
            std::memcpy(m_data, other.m_data, other.m_size + 1);
            m_size = other.m_size;
        }
        return *this;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // MOVE CONSTRUCTOR
    // libstdc++ line 681-703: basic_string(basic_string&& __str)
    // SSO: Must copy (can't steal local buffer)
    // Heap: Steal pointer (no allocation)
    // ═══════════════════════════════════════════════════════════════════════
    MyString(MyString&& other) noexcept 
        : m_data(local_data()), m_size(0)
    {
        if (other.is_local()) {
            // SSO: Can't steal, must copy local buffer
            std::memcpy(m_local_buf, other.m_local_buf, other.m_size + 1);
            m_data = local_data();
            m_size = other.m_size;
            // Leave other in valid state
            other.m_data = other.local_data();
            other.set_length(0);
        } else {
            // Heap: Steal pointer
            m_data = other.m_data;
            m_size = other.m_size;
            m_allocated_capacity = other.m_allocated_capacity;
            // Reset other to empty SSO state
            other.m_data = other.local_data();
            other.set_length(0);
        }
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // MOVE ASSIGNMENT
    // ═══════════════════════════════════════════════════════════════════════
    MyString& operator=(MyString&& other) noexcept {
        if (this == &other) return *this;
        
        dispose();  // Free current heap if any
        
        if (other.is_local()) {
            std::memcpy(m_local_buf, other.m_local_buf, other.m_size + 1);
            m_data = local_data();
            m_size = other.m_size;
        } else {
            m_data = other.m_data;
            m_size = other.m_size;
            m_allocated_capacity = other.m_allocated_capacity;
        }
        
        other.m_data = other.local_data();
        other.set_length(0);
        return *this;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // ACCESSORS
    // ═══════════════════════════════════════════════════════════════════════
    
    [[nodiscard]] constexpr char& operator[](size_type i) noexcept {
        return m_data[i];
    }
    
    [[nodiscard]] constexpr const char& operator[](size_type i) const noexcept {
        return m_data[i];
    }
    
    [[nodiscard]] constexpr size_type size() const noexcept { return m_size; }
    [[nodiscard]] constexpr size_type length() const noexcept { return m_size; }
    [[nodiscard]] constexpr bool empty() const noexcept { return m_size == 0; }
    [[nodiscard]] constexpr const char* c_str() const noexcept { return m_data; }
    [[nodiscard]] constexpr const char* data() const noexcept { return m_data; }
    
    [[nodiscard]] constexpr size_type capacity() const noexcept {
        return is_local() ? S_local_capacity : m_allocated_capacity;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // MODIFIERS
    // ═══════════════════════════════════════════════════════════════════════
    
    void clear() noexcept {
        set_length(0);
    }
    
    void reserve(size_type new_cap) {
        if (new_cap <= capacity()) return;  // Already have enough
        
        pointer new_data = allocate(new_cap + 1);
        std::memcpy(new_data, m_data, m_size + 1);
        dispose();
        m_data = new_data;
        m_allocated_capacity = new_cap;
    }
    
    MyString& append(const char* cstr) {
        if (cstr == nullptr) return *this;
        
        const size_type add_len = std::strlen(cstr);
        const size_type new_size = m_size + add_len;
        
        if (new_size > capacity()) {
            reserve(std::max(capacity() * 2, new_size));
        }
        
        std::memcpy(m_data + m_size, cstr, add_len + 1);
        m_size = new_size;
        return *this;
    }
    
    MyString& operator+=(const char* cstr) {
        return append(cstr);
    }
    
    MyString& operator+=(const MyString& other) {
        return append(other.c_str());
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // COMPARISON
    // ═══════════════════════════════════════════════════════════════════════
    
    [[nodiscard]] bool operator==(const MyString& other) const noexcept {
        if (m_size != other.m_size) return false;
        return std::memcmp(m_data, other.m_data, m_size) == 0;
    }
    
    [[nodiscard]] bool operator!=(const MyString& other) const noexcept {
        return !(*this == other);
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // OUTPUT
    // ═══════════════════════════════════════════════════════════════════════
    
    friend std::ostream& operator<<(std::ostream& os, const MyString& s) {
        return os << s.m_data;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// TESTS
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    std::cout << "=== SSO Test (short string) ===\n";
    MyString s1("hello");  // 5 chars ≤ 15 → SSO
    std::cout << "s1 = \"" << s1 << "\"\n";
    std::cout << "size = " << s1.size() << ", capacity = " << s1.capacity() << "\n";
    std::cout << "Expected: capacity = 15 (SSO)\n\n";
    
    std::cout << "=== Heap Test (long string) ===\n";
    MyString s2("this is a much longer string that exceeds SSO");  // > 15 → heap
    std::cout << "s2 = \"" << s2 << "\"\n";
    std::cout << "size = " << s2.size() << ", capacity = " << s2.capacity() << "\n";
    std::cout << "Expected: capacity = " << s2.size() << " (heap)\n\n";
    
    std::cout << "=== Copy Test ===\n";
    MyString s3 = s1;  // Copy ctor
    std::cout << "s3 (copy of s1) = \"" << s3 << "\"\n";
    
    std::cout << "\n=== Move Test ===\n";
    MyString s4 = std::move(s2);  // Move ctor
    std::cout << "s4 (moved from s2) = \"" << s4 << "\"\n";
    std::cout << "s2 (after move) size = " << s2.size() << "\n";
    
    std::cout << "\n=== Append Test ===\n";
    MyString s5("hi");
    std::cout << "Before: \"" << s5 << "\" (size=" << s5.size() << ", cap=" << s5.capacity() << ")\n";
    s5 += " there";
    std::cout << "After +=: \"" << s5 << "\" (size=" << s5.size() << ", cap=" << s5.capacity() << ")\n";
    s5 += " and more text to force reallocation beyond SSO";
    std::cout << "After long +=: \"" << s5 << "\" (size=" << s5.size() << ", cap=" << s5.capacity() << ")\n";
    
    std::cout << "\n=== sizeof Test ===\n";
    std::cout << "sizeof(MyString) = " << sizeof(MyString) << " bytes\n";
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << " bytes\n";
    
    return 0;
}
