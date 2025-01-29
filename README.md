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

### Manual Installation

1. Clone the repository

```bash
git clone --branch v0.3.0 --depth 1 https://github.com/oneofthezombies/kero-variant-utils.git
```

2. Add to include search path

```bash
clang -I<kero_variant_utils_repo>
# or
g++ -I<kero_variant_utils_repo>
```

### CMake

#### Using FetchContent

```cmake
# in your CMakeLists.txt
include(FetchContent)
FetchContent_Declare(
  kero_variant_utils
  GIT_REPOSITORY https://github.com/oneofthezombies/kero-variant-utils.git
  GIT_TAG v0.3.0)
FetchContent_MakeAvailable(kero_variant_utils)

target_include_directories(<your_target> PRIVATE ${kero_variant_utils_SOURCE_DIR})
```

#### Using CMake Package

1. Checkout the repository

```bash
git clone --branch v0.3.0 --depth 1 https://github.com/oneofthezombies/kero-variant-utils.git
```

2. Build and install

```bash
cmake -B build
cmake --install build
```

3. Use in your project

```cmake
# in your CMakeLists.txt
find_package(kero_variant_utils REQUIRED)

target_include_directories(<your_target> PRIVATE ${kero_variant_utils_SOURCE_DIR})
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
