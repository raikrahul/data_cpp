# Large-Scale Project Proposal: Physics Simulation Engine

## Concept Mapping: Your Files → Project Components

```
┌─────────────────────────────────────────────────────────────────────────────────────────────────┐
│                           PHYSICS SIMULATION ENGINE                                              │
│                                                                                                  │
│  ┌─────────────────────┐    ┌─────────────────────┐    ┌─────────────────────┐                  │
│  │ ENTITY SYSTEM       │    │ PHYSICS ENGINE      │    │ RENDER/OUTPUT       │                  │
│  │                     │    │                     │    │                     │                  │
│  │ 55_template_dims    │───▶│ 56_n_dimensional    │───▶│ 22_simd_parallel    │                  │
│  │ 41_inheritance      │    │ 46_template_power   │    │ 32_transform_reduce │                  │
│  │ 36_smart_pointer    │    │ 54_recursive_asm    │    │ 24_reduce_demo      │                  │
│  └─────────────────────┘    └─────────────────────┘    └─────────────────────┘                  │
│           │                          │                          │                               │
│           ▼                          ▼                          ▼                               │
│  ┌─────────────────────┐    ┌─────────────────────┐    ┌─────────────────────┐                  │
│  │ MEMORY MANAGEMENT   │    │ ALGORITHM LAYER     │    │ CONTAINER LAYER     │                  │
│  │                     │    │                     │    │                     │                  │
│  │ sbrk_demo           │    │ 20_stl_algorithms   │    │ containers_worksheet│                  │
│  │ copy_vs_move        │    │ 21_for_each         │    │ 28_ranges_generate  │                  │
│  │ weak_proof          │    │ 27_equal_mismatch   │    │ 33_ranges_views     │                  │
│  │ why_care_about_move │    │ 29_ranges_find      │    │ 34_view_abstraction │                  │
│  └─────────────────────┘    └─────────────────────┘    └─────────────────────┘                  │
│           │                          │                          │                               │
│           ▼                          ▼                          ▼                               │
│  ┌─────────────────────┐    ┌─────────────────────┐    ┌─────────────────────┐                  │
│  │ TYPE SYSTEM         │    │ CALLABLE LAYER      │    │ COMPILE-TIME LAYER  │                  │
│  │                     │    │                     │    │                     │                  │
│  │ 39_auto_type        │    │ 38_functor_lambda   │    │ 48_abbreviated      │                  │
│  │ 50_duck_typing      │    │ 23_lambda_anatomy   │    │ 52_all_syntax       │                  │
│  │ 40_person_compare   │    │ 37_struct_class     │    │ 51_missing_size     │                  │
│  └─────────────────────┘    └─────────────────────┘    └─────────────────────┘                  │
└─────────────────────────────────────────────────────────────────────────────────────────────────┘
```

## Project: N-Dimensional Particle Physics Simulator

### Phase 1: Entity System (Uses: 55, 56, 41, 36)

```cpp
// Template-based N-dimensional particle
template<size_t N>
struct Particle {
    std::array<double, N> position{};      // 55_template_dimensions
    std::array<double, N> velocity{};      // 56_n_dimensional_logic
    std::array<double, N> acceleration{};
    double mass = 1.0;
    
    double lengthSquared() const {         // Loop over N dimensions
        double sum = 0;
        for (size_t i = 0; i < N; ++i) sum += position[i] * position[i];
        return sum;
    }
};

// Virtual dispatch for different particle types
struct ParticleBase { virtual void update(double dt) = 0; };  // 41_inheritance_virtual
struct ChargedParticle : ParticleBase { double charge; };
struct MassiveParticle : ParticleBase { double gravity_factor; };

// Smart pointer ownership
std::vector<std::unique_ptr<ParticleBase>> particles;         // 36_smart_pointer_factory
```

### Phase 2: Physics Engine (Uses: 46, 54, 32, 24)

```cpp
// Compile-time power function for force laws
template<int N>
constexpr double ipow(double x) {                              // 46_template_power
    if constexpr (N == 0) return 1.0;                          // 54_recursive_template
    else return x * ipow<N-1>(x);
}

// Gravity: F = G * m1 * m2 / r^2
double gravity_force(double m1, double m2, double r) {
    return 6.674e-11 * m1 * m2 / ipow<2>(r);
}

// Total energy calculation using reduce
double total_kinetic_energy(const auto& particles) {           // 32_transform_reduce
    return std::transform_reduce(
        particles.begin(), particles.end(),
        0.0,
        std::plus{},
        [](const auto& p) { return 0.5 * p.mass * p.velocity.lengthSquared(); }
    );
}
```

### Phase 3: Algorithm Layer (Uses: 20-31, Ranges)

```cpp
// Find particles in region using ranges
auto particles_in_box(auto& particles, auto min, auto max) {   // 29_ranges_find
    return particles | std::views::filter([&](const auto& p) {
        return p.position[0] >= min[0] && p.position[0] <= max[0];
    });
}

// Generate initial positions using iota + transform
void initialize_grid(auto& particles, size_t count) {          // 31_iota_transform
    std::ranges::generate(particles, [i=0]() mutable {
        Particle<3> p;
        p.position = {i % 10 * 1.0, (i / 10) % 10 * 1.0, i / 100 * 1.0};
        ++i;
        return p;
    });
}

// Collision detection using equal/mismatch patterns
bool check_collision(const auto& p1, const auto& p2) {         // 27_equal_mismatch
    double dist_sq = 0;
    for (size_t i = 0; i < 3; ++i) {
        double d = p1.position[i] - p2.position[i];
        dist_sq += d * d;
    }
    return dist_sq < (p1.radius + p2.radius) * (p1.radius + p2.radius);
}
```

### Phase 4: Memory & Performance (Uses: sbrk, move, SIMD)

```cpp
// Custom allocator for particles (sbrk_demo concept)
class ParticleAllocator {
    char* pool;
    size_t offset = 0;
public:
    void* allocate(size_t n) {
        void* ptr = pool + offset;
        offset += n;
        return ptr;
    }
};

// Move semantics for particle transfer (copy_vs_move, why_care_about_move)
void transfer_particle(std::vector<Particle<3>>& from, 
                       std::vector<Particle<3>>& to, size_t idx) {
    to.push_back(std::move(from[idx]));  // O(1) not O(sizeof)
}

// SIMD parallel update (22_simd_parallel_puzzle)
void update_positions_parallel(std::vector<Particle<3>>& particles, double dt) {
    std::for_each(std::execution::par_unseq,
        particles.begin(), particles.end(),
        [dt](auto& p) {
            for (size_t i = 0; i < 3; ++i) {
                p.velocity[i] += p.acceleration[i] * dt;
                p.position[i] += p.velocity[i] * dt;
            }
        });
}
```

### Phase 5: Type System & Duck Typing (Uses: 48, 50, 52)

```cpp
// Abbreviated template for any container (50_abbreviated_duck_typing)
auto count_stationary(const auto& particles) {
    int count = 0;
    for (size_t i = 0; i < particles.size(); ++i) {
        if (particles[i].velocity.lengthSquared() < 1e-10) ++count;
    }
    return count;
}

// Works with: vector<Particle<3>>, array<Particle<3>, 100>, custom container
// Requires: size(), operator[], element has velocity.lengthSquared()

// Compile-time error detection (51_missing_size_error)
struct BrokenContainer { int data[10]; };  // No size() → compile error
// count_stationary(BrokenContainer{});  // ERROR: no member 'size'
```

## Numerical Scale Targets

| Component | N=100 | N=10,000 | N=1,000,000 |
|:----------|:------|:---------|:------------|
| Particle Update | 0.1ms | 10ms | 100ms |
| Collision O(N²) | 10ms | 100s | impossible |
| Collision O(N log N) | 0.5ms | 50ms | 500ms |
| Memory (3D, double) | 7KB | 700KB | 70MB |
| SIMD Speedup | 2× | 4× | 8× (cache) |

## File-to-Feature Mapping

| File | Feature Used | Project Component |
|:-----|:-------------|:------------------|
| 20_stl_algorithms | std::for_each, count_if | Particle iteration |
| 21_for_each | Side-effect accumulation | Energy calculation |
| 22_simd_parallel | par_unseq execution | Parallel update |
| 23_lambda_anatomy | Capture mechanics | Force callbacks |
| 24_reduce_demo | Reduction patterns | Total energy |
| 27_equal_mismatch | Comparison algorithms | Collision detection |
| 28_ranges_generate | Initialization | Grid generation |
| 29_ranges_find | Spatial queries | Region filtering |
| 32_transform_reduce | Combined operations | Statistics |
| 33_ranges_views | Lazy evaluation | View pipelines |
| 36_smart_pointer | Ownership | Particle lifetime |
| 37_struct_class | Memory layout | Cache optimization |
| 38_functor_lambda | Callable objects | Force functions |
| 39_auto_type | Deduction rules | API design |
| 41_inheritance | Virtual dispatch | Particle types |
| 46_template_power | Compile-time math | Force laws |
| 48_abbreviated | Modern syntax | Clean API |
| 50_duck_typing | Container generics | Algorithm reuse |
| 54_recursive_asm | Constant folding | Optimization |
| 55_template_dims | N-dimensional | Flexible physics |
| 56_n_dimensional | Loop over N | Generic algorithms |
| sbrk_demo | Memory allocation | Custom allocator |
| copy_vs_move | Performance | Particle transfer |
| weak_proof | Lifetime management | Observer pattern |

## Build Incrementally

```
Phase 1: Single particle, 3D, no forces        → Files 55, 56
Phase 2: Add forces, energy calculation        → Files 46, 24, 32
Phase 3: Multiple particles, smart pointers    → Files 36, 41
Phase 4: Algorithms, ranges, views             → Files 20-31
Phase 5: SIMD, parallel execution              → File 22
Phase 6: Custom allocator, move optimization   → Files sbrk, move
Phase 7: Generalize to N dimensions            → Template everything
Phase 8: Benchmark 100 → 1M particles          → Profile and optimize
```

## Success Metrics

- [ ] 1000 3D particles update in <1ms
- [ ] Zero heap allocations in hot loop
- [ ] Compile-time error for bad container types
- [ ] Same algorithm works for 2D, 3D, 10D
- [ ] SIMD gives 4× speedup on update loop
- [ ] Move semantics gives 1000× speedup on particle transfer
- [ ] Views give 0 allocation for filtered iteration
