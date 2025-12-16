# lecpp - Learning C++

C++23 learning project with CMake and static analysis.

## Requirements

| Tool | Version |
|------|---------|
| CMake | ≥ 3.28 |
| GCC | ≥ 13 (C++23 support) |
| clang-tidy | ≥ 18 |
| clang-format | ≥ 18 |
| cppcheck | latest |

## Build

```bash
mkdir build && cd build
cmake ..
make
./main
```

## Static Analysis

```bash
# cppcheck
cppcheck --enable=all --std=c++23 src/

# clang-tidy
clang-tidy src/main.cpp -p build/

# clang-format (check)
clang-format --dry-run --Werror src/*.cpp
```

## Project Structure

```
lecpp/
├── CMakeLists.txt      # Build config (C++23, strict warnings)
├── .clang-tidy         # Static analysis rules
├── .clang-format       # Code formatting rules
├── .gitignore          # Git ignore patterns
├── README.md           # This file
└── src/
    └── main.cpp        # Programs
```

## License

MIT
