#include <kero_variant_utils/kero_variant_utils.h>

#include <cassert>
#include <memory>
#include <variant>

struct MyValue {};
struct MyError {};
using MyResult = std::variant<MyValue, MyError>;
using NonCopyableVariant =
    std::variant<std::unique_ptr<MyValue>, std::unique_ptr<MyError>>;

int main() {
  // Visit with lambda
  {
    MyResult v = MyValue{};
    auto res = kero::Visit(
        v, [](MyValue) -> bool { return true; },
        [](MyError) -> bool { return false; });

    assert(res == true);
  }

  // Incomplete visitor (compile-time error)
  // "Visitor does not handle all alternatives in the variant!"
  {
    MyResult v = MyValue{};
    // auto res = kero::Visit(v, [](MyValue) -> bool { return true; });
  }

  // Visit with Custom Visitor struct
  {
    struct MyVisitor {
      bool operator()(MyValue) { return false; }
      bool operator()(MyError) { return true; }
    };
    MyResult v = MyError{};
    auto res = kero::Visit(v, MyVisitor{});

    assert(res == true);
  }

  // Visit with non-copyable r-value
  {
    NonCopyableVariant v{std::make_unique<MyValue>()};
    auto res = kero::Visit(
        std::move(v), [](std::unique_ptr<MyValue>) -> bool { return true; },
        [](std::unique_ptr<MyError>) -> bool { return false; });

    assert(res == true);
  }

  // Reference type to non-copyable r-value (compile-time error)
  {
    NonCopyableVariant v{std::make_unique<MyValue>()};
    // auto res = kero::Visit(
    //     std::move(v), [](std::unique_ptr<MyValue>&) -> bool { return true; },
    //     [](std::unique_ptr<MyError>&) -> bool { return false; });
  }

  return 0;
}
