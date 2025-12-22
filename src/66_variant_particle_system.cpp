
#include <variant>
#include <vector>
#include <iostream>
#include <memory>
#include <chrono>
#include <random>
#include <algorithm>

// -----------------------------------------------------------------------------
// USER INSTRUCTIONS:
// 1. Read 'src/66_variant_particle_system.md' for memory layout derivation.
// 2. Implement the missing TODO blocks.
// 3. Compile with optimizations (-O2 or -O3) to see real differences.
// -----------------------------------------------------------------------------

// --- Types ---
struct Fire {
    float temp;
    float life;
    void update() { 
        temp *= 0.99f; 
        life -= 0.1f; 
    }
};

struct Smoke {
    float density;
    float life;
    void update() { 
        density *= 0.98f; 
        life -= 0.05f; 
    }
};

struct Water {
    float viscosity;
    float life;
    void update() { 
        viscosity *= 1.01f; 
        life -= 0.2f; 
    }
};

// --- Variant Alias ---
using ParticleVar = std::variant<Fire, Smoke, Water>;

// --- Virtual Base Interface ---
struct IParticle {
    virtual void update() = 0;
    virtual ~IParticle() = default;
};

struct VirtFire : IParticle {
    float temp, life;
    VirtFire(float t, float l) : temp(t), life(l) {}
    void update() override { temp *= 0.99f; life -= 0.1f; }
};

struct VirtSmoke : IParticle {
    float density, life;
    VirtSmoke(float d, float l) : density(d), life(l) {}
    void update() override { density *= 0.98f; life -= 0.05f; }
};

struct VirtWater : IParticle {
    float viscosity, life;
    VirtWater(float v, float l) : viscosity(v), life(l) {}
    void update() override { viscosity *= 1.01f; life -= 0.2f; }
};

// --- Benchmarking Utilities ---
using Clock = std::chrono::high_resolution_clock;

int main() {
    const size_t N = 1'000'000;
    std::cout << "Generating " << N << " particles...\n";

    // Random generator
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 2);

    // 1. Setup Variant System
    std::vector<ParticleVar> variants;
    variants.reserve(N);
    // TODO: Loop N times, use dist(rng) to push_back Fire, Smoke, or Water.
    // Use emplace_back for efficiency.
    // ...

    // 2. Setup Virtual System
    std::vector<std::unique_ptr<IParticle>> virtuals;
    virtuals.reserve(N);
    // TODO: Loop N times, use dist(rng) to make_unique VirtFire, VirtSmoke, etc.
    // ...

    std::cout << "Benchmarking Variant System...\n";
    auto start_var = Clock::now();
    
    // TODO: Iterate over 'variants' and call update() on each using std::visit.
    // Hint: std::visit([](auto& p){ p.update(); }, v);
    // for (auto& v : variants) { ... }
    
    auto end_var = Clock::now();
    std::chrono::duration<double> diff_var = end_var - start_var;
    std::cout << "Variant Time: " << diff_var.count() << " s\n";


    std::cout << "Benchmarking Virtual System...\n";
    auto start_virt = Clock::now();
    
    // TODO: Iterate over 'virtuals' and call update() on each.
    // for (auto& p : virtuals) { ... }
    
    auto end_virt = Clock::now();
    std::chrono::duration<double> diff_virt = end_virt - start_virt;
    std::cout << "Virtual Time: " << diff_virt.count() << " s\n";

    // Analysis
    std::cout << "Ratio (Virtual / Variant): " << (diff_virt.count() / diff_var.count()) << "x\n";

    // Verify Prediction from MD file
    // "Variant expected 2-3x speedup" -> Check if true.
    
    return 0;
}
