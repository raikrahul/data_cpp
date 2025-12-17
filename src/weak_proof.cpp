#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

// Helper to print counts
// T is int
void print_counts(const std::string& label, std::shared_ptr<int>& sp,
                  std::vector<std::weak_ptr<int>>& weaks) {
    long strong = sp ? sp.use_count() : 0;

    // Calculate weak count manually from strong + weak_ptrs
    // Note: use_count() returns strong refs.
    // weak_ptr doesn't expose raw weak_count directly in standard API easily without locking

    std::cout << "\n[" << label << "]\n";
    std::cout << "Strong Count: " << strong << "\n";
    // We will verify if they lock
    int locked_count = 0;
    for (auto& w : weaks) {
        if (!w.expired()) locked_count++;
    }
    std::cout << "Alive Weak Ptrs (Lockable): " << locked_count << " / " << weaks.size() << "\n";
}

int main() {
    // ---------------------------------------------------------
    // STEP 1: Create Shared Pointer
    // ---------------------------------------------------------
    // Allocates Control Block (16 bytes) + int (4 bytes) = 20 bytes
    // strong = 1
    // weak   = 1 (impl detail: usually 1 "self-ref" if object alive)
    // ---------------------------------------------------------
    std::shared_ptr<int> sp = std::make_shared<int>(42);

    std::vector<std::weak_ptr<int>> weaks;

    // ---------------------------------------------------------
    // STEP 2: Create 10 Weak Pointers
    // ---------------------------------------------------------
    // Loop 0..9
    // Each iteration:
    //   weak_ptr copy from sp
    //   increments weak_count in control block
    //   strong_count UNCHANGED
    // ---------------------------------------------------------
    for (int i = 0; i < 10; ++i) {
        weaks.push_back(sp);
        // Calculation trace:
        // i=0: weak = 1 (base) + 1 = 2
        // i=1: weak = 2 + 1 = 3
        // ...
        // i=9: weak = 10 + 1 = 11
    }

    print_counts("Before Reset", sp, weaks);

    // ---------------------------------------------------------
    // STEP 3: Reset Shared Pointer
    // ---------------------------------------------------------
    // sp triggers _M_release()
    // 1. strong_count: 1 -> 0
    // 2. strong == 0? YES -> destroy int(42)
    // 3. _M_weak_release() (decrement "object-alive" ref)
    //    weak_count: 11 -> 10
    //
    // Result:
    //   Object: DEAD
    //   Control Block: ALIVE (weak_count = 10 > 0)
    // ---------------------------------------------------------
    sp.reset();

    // ---------------------------------------------------------
    // STEP 4: Check Weak Pointers
    // ---------------------------------------------------------
    // for each w in weaks:
    //   w.lock() -> checks strong_count
    //   strong_count is 0
    //   returns nullptr
    //   locked_count should be 0
    // ---------------------------------------------------------
    print_counts("After Reset", sp, weaks);

    // ---------------------------------------------------------
    // STEP 5: Manual Check of one weak pointer
    // ---------------------------------------------------------
    auto sp_lock = weaks[0].lock();
    if (sp_lock == nullptr) {
        std::cout << "Verification: lock() returned nullptr (Object Dead)\n";
    } else {
        std::cout << "Verification: lock() returned valid (Object Alive)\n";
    }

    return 0;
}
