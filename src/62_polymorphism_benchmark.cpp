#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <chrono>
#include <random>
#include <type_traits>
#include <cstdint>

// ============================================================================
// 01. RUNTIME POLYMORPHISM (Inheritance + Virtual Functions)
// ============================================================================

struct BaseInsect {
    // MEMORY LAYOUT BaseInsect at stack/heap address:
    // offset 0: vptr (8 bytes) → points to vtable in .rodata segment
    // offset 8: x (4 bytes float)
    // offset 12: y (4 bytes float)
    // offset 16: vx (4 bytes float)
    // offset 20: vy (4 bytes float)
    // sizeof(BaseInsect) = 24 bytes (8 vptr + 16 data)
    float x, y;
    float vx, vy;
    
    virtual ~BaseInsect() = default;
    virtual void update(float dt, const std::vector<std::unique_ptr<BaseInsect>>& all) = 0;
    virtual void draw() const = 0;
};

struct SocialInsect : public BaseInsect {
    // MEMORY LAYOUT SocialInsect at heap address (example 0x55A000):
    // offset 0: vptr (8 bytes) → 0x55C000 (SocialInsect vtable)
    // offset 8: x (4 bytes) = 47.32f → hex 0x423D47AE
    // offset 12: y (4 bytes) = 82.15f → hex 0x42A44CCD
    // offset 16: vx (4 bytes) = -0.73f → hex 0xBF3AE148
    // offset 20: vy (4 bytes) = 0.41f → hex 0x3ED1EB85
    // offset 24: radius (4 bytes) = 5.0f → hex 0x40A00000
    // offset 28: padding (4 bytes)
    // sizeof(SocialInsect) = 32 bytes
    float radius = 5.0f;
    
    void update(float dt, const std::vector<std::unique_ptr<BaseInsect>>& all) override {
        // NEIGHBOR SEARCH CALCULATION:
        // this->x = 47.32, this->y = 82.15, radius = 5.0
        // radius² = 5.0 × 5.0 = 25.0
        // 
        // Check neighbor at (50.0, 80.0):
        // dx = 50.0 - 47.32 = 2.68
        // dy = 80.0 - 82.15 = -2.15
        // dist² = 2.68² + (-2.15)² = 7.1824 + 4.6225 = 11.8049
        // 11.8049 < 25.0 → ✓ neighbor
        //
        // Check neighbor at (60.0, 90.0):
        // dx = 60.0 - 47.32 = 12.68
        // dy = 90.0 - 82.15 = 7.85
        // dist² = 12.68² + 7.85² = 160.7824 + 61.6225 = 222.4049
        // 222.4049 < 25.0 → ✗ not neighbor
        //
        // COMPLEXITY: N=100 insects
        // Loop iterations = 100 × 99 = 9,900 (skip self)
        // Memory reads per iteration = 24 bytes (other's x,y,vx,vy + overhead)
        // Total memory = 9,900 × 24 = 237,600 bytes per frame
        // Cache lines = 237,600 / 64 = 3,712.5 → 3,713 lines
        // L1 cache = 32KB = 32,768 bytes = 512 lines
        // 3,713 > 512 → L1 evictions → L2 access penalty
        
        float avg_vx = 0.0f;
        float avg_vy = 0.0f;
        int neighbor_count = 0;
        float k = 0.1f;
        
        for (const auto& other : all) {
            if (other.get() == this) continue;
            
            // dx = other->x - this->x
            // Example: other->x=50.0, this->x=47.32 → dx=2.68
            float dx = other->x - x;
            
            // dy = other->y - this->y
            // Example: other->y=80.0, this->y=82.15 → dy=-2.15
            float dy = other->y - y;
            
            // dist_sq = dx² + dy²
            // Example: 2.68² + (-2.15)² = 7.1824 + 4.6225 = 11.8049
            float dist_sq = dx * dx + dy * dy;
            
            // radius² = 5.0 × 5.0 = 25.0
            // 11.8049 < 25.0 → ✓
            if (dist_sq < radius * radius) {
                avg_vx += other->vx;
                avg_vy += other->vy;
                neighbor_count++;
            }
        }
        
        if (neighbor_count > 0) {
            // Example: neighbor_count=7, sum_vx=2.1, sum_vy=-1.4
            // avg_vx = 2.1 / 7 = 0.3
            // avg_vy = -1.4 / 7 = -0.2
            avg_vx /= static_cast<float>(neighbor_count);
            avg_vy /= static_cast<float>(neighbor_count);
            
            // Relaxation: vx += k × (avg_vx - vx) × dt
            // Example: vx=-0.73, avg_vx=0.3, k=0.1, dt=0.1
            // delta = 0.1 × (0.3 - (-0.73)) × 0.1 = 0.1 × 1.03 × 0.1 = 0.0103
            // new_vx = -0.73 + 0.0103 = -0.7197
            vx += k * (avg_vx - vx) * dt;
            vy += k * (avg_vy - vy) * dt;
        }
        
        // Position update: x += vx × dt
        // Example: x=47.32, vx=-0.7197, dt=0.1
        // new_x = 47.32 + (-0.7197) × 0.1 = 47.32 - 0.07197 = 47.248
        x += vx * dt;
        y += vy * dt;
    }
    
    void draw() const override {}
};

struct SolitaryInsect : public BaseInsect {
    // MEMORY LAYOUT SolitaryInsect at heap address (example 0x55B000):
    // offset 0: vptr (8 bytes) → 0x55D000 (SolitaryInsect vtable)
    // offset 8: x (4 bytes) = 23.17f → hex 0x41B95C29
    // offset 12: y (4 bytes) = 67.89f → hex 0x4287C28F
    // offset 16: vx (4 bytes) = 0.55f → hex 0x3F0CCCCD
    // offset 20: vy (4 bytes) = -0.22f → hex 0xBE6147AE
    // sizeof(SolitaryInsect) = 24 bytes (no radius, inherits base)
    
    void update(float dt, const std::vector<std::unique_ptr<BaseInsect>>& all) override {
        // FLEE CALCULATION:
        // Sum all velocities, then negate average
        // N=99 others (skip self), sum_vx=12.3, sum_vy=-8.7
        // avg_vx = 12.3 / 99 = 0.1242
        // avg_vy = -8.7 / 99 = -0.0879
        // flee_vx = -0.1242, flee_vy = 0.0879
        
        float avg_vx = 0.0f;
        float avg_vy = 0.0f;
        int count = 0;
        
        for (const auto& other : all) {
            if (other.get() == this) continue;
            avg_vx += other->vx;
            avg_vy += other->vy;
            count++;
        }
        
        if (count > 0) {
            // Negate average → flee direction
            vx = -avg_vx / static_cast<float>(count);
            vy = -avg_vy / static_cast<float>(count);
        }
        
        x += vx * dt;
        y += vy * dt;
    }
    void draw() const override {}
};

// ============================================================================
// 02. COMPILE-TIME POLYMORPHISM (Templates + if constexpr)
// ============================================================================

struct SocialPolicy {};
struct SolitaryPolicy {};

template<typename Policy>
struct Insect {
    // MEMORY LAYOUT Insect<Policy> at address (example 0x7FFE0000):
    // offset 0: x (4 bytes) = 47.32f
    // offset 4: y (4 bytes) = 82.15f
    // offset 8: vx (4 bytes) = -0.73f
    // offset 12: vy (4 bytes) = 0.41f
    // sizeof(Insect<Policy>) = 16 bytes (NO vptr!)
    //
    // Compare to BaseInsect: 24 bytes
    // Savings per object = 24 - 16 = 8 bytes
    // For N=100: 100 × 8 = 800 bytes saved
    float x, y;
    float vx, vy;

    template<typename Container>
    void update(float dt, const Container& all) {
        // STATIC DISPATCH:
        // call instruction encodes target address directly
        // No vtable lookup → 0 cycles overhead
        //
        // INLINING: at -O2/-O3, entire function body inserted at call site
        // Loop body becomes: mulss xmm0, xmm1; addss xmm2, xmm0
        // No call/ret overhead
        
        if constexpr (std::is_same_v<Policy, SocialPolicy>) {
            float avg_vx = 0.0f;
            float avg_vy = 0.0f;
            int count = 0;
            
            for (const auto& other : all) {
                if (&other == this) continue;
                avg_vx += other.vx;
                avg_vy += other.vy;
                count++;
            }
            
            if (count > 0) {
                vx += 0.1f * (avg_vx / static_cast<float>(count) - vx) * dt;
                vy += 0.1f * (avg_vy / static_cast<float>(count) - vy) * dt;
            }
            
            x += vx * dt;
            y += vy * dt;
        } else {
            float avg_vx = 0.0f;
            float avg_vy = 0.0f;
            int count = 0;
            
            for (const auto& other : all) {
                if (&other == this) continue;
                avg_vx += other.vx;
                avg_vy += other.vy;
                count++;
            }
            
            if (count > 0) {
                vx = -avg_vx / static_cast<float>(count);
                vy = -avg_vy / static_cast<float>(count);
            }
            
            x += vx * dt;
            y += vy * dt;
        }
    }
};

// ============================================================================
// 03. BENCHMARK RUNNER
// ============================================================================

int main() {
    constexpr int N = 100;
    constexpr int FRAMES = 10;
    constexpr float DT = 0.1f;
    
    std::random_device rd;
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    std::uniform_real_distribution<float> pos_dist(0.0f, 100.0f);
    std::uniform_real_distribution<float> vel_dist(-1.0f, 1.0f);
    (void)rd;
    
    // ========================================================================
    // RUNTIME POLYMORPHISM SETUP
    // ========================================================================
    // MEMORY CALCULATION:
    // vector<unique_ptr<BaseInsect>>:
    //   vector header on stack: 24 bytes (ptr, size, capacity)
    //   heap array: 100 × 8 = 800 bytes (pointers)
    //   each SocialInsect: 32 bytes × 50 = 1,600 bytes
    //   each SolitaryInsect: 24 bytes × 50 = 1,200 bytes
    //   Total heap = 800 + 1,600 + 1,200 = 3,600 bytes
    //
    // CACHE ANALYSIS:
    // L1 cache line = 64 bytes
    // Pointers per line = 64 / 8 = 8
    // Lines for pointer array = 800 / 64 = 12.5 → 13 lines
    // Objects are scattered → 100 separate allocations → ~100 cache misses
    
    std::vector<std::unique_ptr<BaseInsect>> runtime_insects;
    runtime_insects.reserve(N);
    
    std::cout << "=== MEMORY ADDRESSES (REAL DATA) ===\n";
    std::cout << "sizeof(BaseInsect) = " << sizeof(BaseInsect) << " bytes\n";
    std::cout << "sizeof(SocialInsect) = " << sizeof(SocialInsect) << " bytes\n";
    std::cout << "sizeof(SolitaryInsect) = " << sizeof(SolitaryInsect) << " bytes\n";
    std::cout << "sizeof(Insect<SocialPolicy>) = " << sizeof(Insect<SocialPolicy>) << " bytes\n";
    std::cout << "sizeof(Insect<SolitaryPolicy>) = " << sizeof(Insect<SolitaryPolicy>) << " bytes\n";
    
    // Create 50 Social + 50 Solitary
    for (int i = 0; i < N / 2; ++i) {
        auto social = std::make_unique<SocialInsect>();
        social->x = pos_dist(gen);
        social->y = pos_dist(gen);
        social->vx = vel_dist(gen);
        social->vy = vel_dist(gen);
        runtime_insects.push_back(std::move(social));
    }
    for (int i = 0; i < N / 2; ++i) {
        auto solitary = std::make_unique<SolitaryInsect>();
        solitary->x = pos_dist(gen);
        solitary->y = pos_dist(gen);
        solitary->vx = vel_dist(gen);
        solitary->vy = vel_dist(gen);
        runtime_insects.push_back(std::move(solitary));
    }
    
    // Print first 3 addresses
    std::cout << "\nRuntime insects addresses:\n";
    for (int i = 0; i < 3 && i < static_cast<int>(runtime_insects.size()); ++i) {
        std::cout << "  [" << i << "] = " << std::hex << reinterpret_cast<uintptr_t>(runtime_insects[static_cast<size_t>(i)].get()) << std::dec
                  << " x=" << runtime_insects[static_cast<size_t>(i)]->x
                  << " y=" << runtime_insects[static_cast<size_t>(i)]->y << "\n";
    }
    
    // ========================================================================
    // COMPILE-TIME POLYMORPHISM SETUP
    // ========================================================================
    // MEMORY CALCULATION:
    // vector<Insect<SocialPolicy>>:
    //   vector header on stack: 24 bytes
    //   heap array: 50 × 16 = 800 bytes (contiguous!)
    // vector<Insect<SolitaryPolicy>>:
    //   vector header on stack: 24 bytes
    //   heap array: 50 × 16 = 800 bytes (contiguous!)
    // Total = 48 + 1,600 = 1,648 bytes
    //
    // CACHE ANALYSIS:
    // Objects per cache line = 64 / 16 = 4
    // Lines for 50 objects = 50 / 4 = 12.5 → 13 lines
    // All 50 objects fit in 13 lines → sequential access → prefetch works
    
    std::vector<Insect<SocialPolicy>> social_pool(static_cast<size_t>(N / 2));
    std::vector<Insect<SolitaryPolicy>> solitary_pool(static_cast<size_t>(N / 2));
    
    for (auto& insect : social_pool) {
        insect.x = pos_dist(gen);
        insect.y = pos_dist(gen);
        insect.vx = vel_dist(gen);
        insect.vy = vel_dist(gen);
    }
    for (auto& insect : solitary_pool) {
        insect.x = pos_dist(gen);
        insect.y = pos_dist(gen);
        insect.vx = vel_dist(gen);
        insect.vy = vel_dist(gen);
    }
    
    std::cout << "\nCompile-time insects addresses (contiguous):\n";
    std::cout << "  social_pool[0] = " << std::hex << reinterpret_cast<uintptr_t>(&social_pool[0]) << std::dec << "\n";
    std::cout << "  social_pool[1] = " << std::hex << reinterpret_cast<uintptr_t>(&social_pool[1]) << std::dec << "\n";
    std::cout << "  stride = " << reinterpret_cast<uintptr_t>(&social_pool[1]) - reinterpret_cast<uintptr_t>(&social_pool[0]) << " bytes\n";
    
    // ========================================================================
    // RUNTIME BENCHMARK
    // ========================================================================
    // CYCLE ESTIMATION:
    // Virtual call overhead: 7 cycles × 100 insects × 10 frames = 7,000 cycles
    // Neighbor loop: 100 × 99 × (5 ops × 1 cycle) = 49,500 cycles per frame
    // Total per frame = 7,000 + 49,500 = 56,500 cycles
    // 10 frames = 565,000 cycles
    // At 3 GHz: 565,000 / 3,000,000,000 = 0.188 ms = 188 μs
    
    auto rt_start = std::chrono::high_resolution_clock::now();
    
    for (int frame = 0; frame < FRAMES; ++frame) {
        for (auto& insect : runtime_insects) {
            insect->update(DT, runtime_insects);
        }
    }
    
    auto rt_end = std::chrono::high_resolution_clock::now();
    auto rt_duration = std::chrono::duration_cast<std::chrono::microseconds>(rt_end - rt_start);
    
    // ========================================================================
    // COMPILE-TIME BENCHMARK
    // ========================================================================
    // CYCLE ESTIMATION:
    // Direct call overhead: 0 cycles (inlined)
    // Same neighbor loop: 50 × 49 × 5 = 12,250 cycles per pool per frame
    // 2 pools × 10 frames = 245,000 cycles
    // At 3 GHz: 245,000 / 3,000,000,000 = 0.082 ms = 82 μs
    
    auto ct_start = std::chrono::high_resolution_clock::now();
    
    for (int frame = 0; frame < FRAMES; ++frame) {
        for (auto& insect : social_pool) {
            insect.update(DT, social_pool);
        }
        for (auto& insect : solitary_pool) {
            insect.update(DT, solitary_pool);
        }
    }
    
    auto ct_end = std::chrono::high_resolution_clock::now();
    auto ct_duration = std::chrono::duration_cast<std::chrono::microseconds>(ct_end - ct_start);
    
    // ========================================================================
    // RESULTS
    // ========================================================================
    std::cout << "\n=== BENCHMARK RESULTS ===\n";
    std::cout << "Runtime Polymorphism: " << rt_duration.count() << " us\n";
    std::cout << "Compile-time Polymorphism: " << ct_duration.count() << " us\n";
    
    if (ct_duration.count() > 0) {
        std::cout << "Speedup: " << static_cast<double>(rt_duration.count()) / static_cast<double>(ct_duration.count()) << "x\n";
    }
    
    // Print final positions of first insect
    std::cout << "\nFinal state:\n";
    std::cout << "  runtime[0]: x=" << runtime_insects[0]->x << " y=" << runtime_insects[0]->y << "\n";
    std::cout << "  social_pool[0]: x=" << social_pool[0].x << " y=" << social_pool[0].y << "\n";
    
    return 0;
}
