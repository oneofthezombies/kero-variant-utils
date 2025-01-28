#include <kero_variant_utils/kero_variant_utils.h>

#include <iostream>
#include <string>
#include <variant>

int main() {
  {
    using MyVariant = std::variant<int, std::string>;

    // Test with int
    {
      MyVariant value = 42;
      kero::Visit(
          value, [](int x) { std::cout << "Int: " << x << '\n'; },
          [](const std::string& s) { std::cout << "String: " << s << '\n'; });
    }

    // Test with string
    {
      MyVariant value = "Hello, World!";
      kero::Visit(
          value, [](int x) { std::cout << "Int: " << x << '\n'; },
          [](const std::string& s) { std::cout << "String: " << s << '\n'; });
    }
  }

  {
    struct A {
      A() = default;
      ~A() = default;
      A(const A&) = delete;
      A& operator=(const A&) = delete;
      A(A&&) = default;
      A& operator=(A&&) = default;
    };

    struct B {
      B() = default;
      ~B() = default;
      B(const B&) = delete;
      B& operator=(const B&) = delete;
      B(B&&) = default;
      B& operator=(B&&) = default;
    };

    using MyVariant = std::variant<A, B>;

    MyVariant value{A{}};
    kero::Visit(
        std::move(value), [](A&&) { std::cout << "A\n"; },
        [](B&&) { std::cout << "B\n"; });
  }

  return 0;
}
