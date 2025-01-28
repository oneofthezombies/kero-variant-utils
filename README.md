# Kero Variant Utils

**Kero Variant Utils** is an ergonomic, header-only C++ library designed to simplify handling `std::variant` alternatives. It provides **compile-time validation** to ensure all alternatives are handled, making your code safer and more robust.

## Key Features

- **Compile-Time Validation**: Guarantees that all `std::variant` alternatives are handled by your handlers during compilation.
- **Header-Only**: Easy to integrate into your project with no additional dependencies.
- **Wide Compiler and Standard Support**: Compatible with `C++17`, `C++20`, and `C++23`, and tested with major compilers including GCC, Clang, and MSVC.
- **Ergonomic API**: Clean, expressive, and easy-to-use interface for handling variants.

This library is perfect for scenarios where exhaustive handling of `std::variant` alternatives is critical for code correctness and maintainability.

## Examples

```cpp
#include <iostream>
#include <variant>
#include <string>

#include <kero_variant_utils/kero_variant_utils.h>

using MyVariant = std::variant<int, std::string>;

int main() {
  MyVariant v = 1;

  {
    // Using lambda
    kero::Visit(v,
        [](int i) { std::cout << "int: " << i << std::endl; },
        [](const std::string& s) { std::cout << "string: " << s << std::endl; });
  }

  {
    // Using struct
    struct MyVisitor {
      void operator()(int i) { std::cout << "int: " << i << std::endl; }
      void operator()(const std::string& s) { std::cout << "string: " << s << std::endl; }
    };
    kero::Visit(v, MyVisitor{});
  }

  return 0;
}
```

## Compiler Support

| C++ Standard | GCC Version    | Clang Version  | MSVC Version |
| ------------ | -------------- | -------------- | ------------ |
| C++17        | Not tested yet | Not tested yet | 19.38.33134  |
| C++20        | Not tested yet | Not tested yet | 19.38.33134  |
| C++23        | Not tested yet | Not tested yet | 19.38.33134  |

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
