# Kero Variant Utils

🐸 **Kero Variant Utils** is an ergonomic, header-only C++ library designed to simplify handling `std::variant` alternatives.  
It provides **compile-time validation** to ensure all alternatives are handled, making your code safer and more robust.

## Key Features

- **Ergonomic API**: Clean, expressive, and easy-to-use interface for handling variants.
- **Compile-Time Validation**: Guarantees that all `std::variant` alternatives are handled by your handlers during compilation.
- **Header-Only**: Easy to integrate into your project with no additional dependencies.
- **Wide Compiler and Standard Support**: Tested with C++17, C++20, and C++23 standards, and major compilers including GCC, Clang, and MSVC.

This library is perfect for scenarios where exhaustive handling of `std::variant` alternatives is critical for code correctness and maintainability.

## Examples

```cpp
#include <kero/variant_utils.h>

struct MyValue {};
struct MyError {};
using MyResult = std::variant<MyValue, MyError>;

// Visit with lambda
MyResult v = MyValue{};
auto res = kero::Visit(
    v, [](MyValue) -> bool { return true; },
    [](MyError) -> bool { return false; });

assert(res == true);

// Incomplete visitor (compile-time error)
// "Visitor does not handle all alternatives in the variant!"
MyResult v = MyValue{};
// auto res = kero::Visit(v, [](MyValue) -> bool { return true; });
```

## How to Include

### Using CMake FetchContent (recommended)

```cmake
# CMakeLists.txt
include(FetchContent)
FetchContent_Declare(
  kero_variant_utils
  GIT_REPOSITORY https://github.com/oneofthezombies/kero-variant-utils.git
  GIT_TAG v0.3.0)
FetchContent_MakeAvailable(kero_variant_utils)

target_link_libraries(<your_target> PRIVATE kero::variant_utils)
```

### Using Installable CMake Package

1. Download and install

```bash
curl -fsSL https://github.com/oneofthezombies/kero-variant-utils/archive/refs/tags/v0.3.0.tar.gz -o kero_variant_utils.tar.gz
mkdir -p kero_variant_utils
tar -C kero_variant_utils --strip-components=1 -xf kero_variant_utils.tar.gz
cmake -S kero_variant_utils -B kero_variant_utils/build
cmake --install kero_variant_utils/build
rm -rf kero_variant_utils.tar.gz kero_variant_utils
```

2. Use in your project

```cmake
# CMakeLists.txt
find_package(kero_variant_utils REQUIRED)

target_link_libraries(<your_target> PRIVATE kero::variant_utils)
```

### Manual Installation

1. Download

```bash
curl -fsSL https://github.com/oneofthezombies/kero-variant-utils/archive/refs/tags/v0.3.0.tar.gz -o kero_variant_utils.tar.gz
mkdir -p kero_variant_utils
tar -C kero_variant_utils --strip-components=1 -xf kero_variant_utils.tar.gz
```

2. Add include search path

```bash
clang -I<kero_variant_utils_path>
# or
g++ -I<kero_variant_utils_path>
```

## Compiler and Standard Support

The following versions have been fully tested:

| C++ Standard | GCC Version | Clang Version | MSVC Version |
| ------------ | ----------- | ------------- | ------------ |
| C++17        | 12.2.0      | 18.1.8        | 19.38.33134  |
| C++20        | 12.2.0      | 18.1.8        | 19.38.33134  |
| C++23        | 12.2.0      | 18.1.8        | 19.38.33134  |

## Contributing

### Git Commit Messages

- Use [Gitmoji](https://gitmoji.dev/) for commit messages, but write the emoji as a **code format** (e.g., `:bug:`) rather than the actual emoji.
- Leave a single space after the emoji code before writing the commit title.
- Example:

  ```bash
  git commit -m ":bug: Fix an issue with formatting"
  ```

- To make adding emoji codes easier, you can use the [Gitmoji CLI](https://github.com/carloscuesta/gitmoji-cli):
  ```bash
  gitmoji -c
  ```
