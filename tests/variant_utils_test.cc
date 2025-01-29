#include "kero/variant_utils.h"

#include <gtest/gtest.h>

#include <variant>

namespace kero {

TEST(VariantUtilsIsInvocable, StructVisitor) {
  struct MyVisitor {
    void operator()(int) {}
  };
  auto result = kero::variant_utils::IsInvocable<MyVisitor, int>();
  EXPECT_TRUE(result);
}

TEST(VariantUtilsIsInvocable, LambdaVisitor) {
  auto visitor = [](int) {};
  auto result = kero::variant_utils::IsInvocable<decltype(visitor), int>();
  EXPECT_TRUE(result);
}

TEST(VariantUtilsIsInvocableAlternativeAtIndex, StructVisitorVariantSize1) {
  struct MyVisitor {
    void operator()(int) {}
  };
  using MyVariant = std::variant<int>;
  auto result =
      kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                         0>();
  EXPECT_TRUE(result);
}

TEST(VariantUtilsIsInvocableAlternativeAtIndex, StructVisitorVariantSize2) {
  struct MyVisitor {
    void operator()(int) {}
  };
  using MyVariant = std::variant<int, std::string>;
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                           0>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                           1>();
    EXPECT_FALSE(result);
  }
}

TEST(VariantUtilsIsInvocableAlternativeAtIndex,
     OverloadedStructVisitorVariantSize2) {
  struct MyVisitor {
    void operator()(int) {}
    void operator()(std::string) {}
  };
  using MyVariant = std::variant<int, std::string>;
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                           0>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                           1>();
    EXPECT_TRUE(result);
  }
}

TEST(VariantUtilsIsInvocableAlternativeAtIndex, LambdaVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  auto visitor = [](int) {};
  auto result =
      kero::variant_utils::IsInvocableAlternativeAtIndex<decltype(visitor),
                                                         MyVariant, 0>();
  EXPECT_TRUE(result);
}

TEST(VariantUtilsIsInvocableAlternativeAtIndex, LambdaVisitorVariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  auto visitor = [](int) {};
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<decltype(visitor),
                                                           MyVariant, 0>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<decltype(visitor),
                                                           MyVariant, 1>();
    EXPECT_FALSE(result);
  }
}

TEST(VariantUtilsIsInvocableAllAlternatives, StructVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  struct MyVisitor {
    void operator()(int) {}
  };
  auto result =
      kero::variant_utils::IsInvocableAllAlternatives<MyVisitor, MyVariant>(
          std::make_index_sequence<std::variant_size_v<MyVariant>>{});
  EXPECT_TRUE(result);
}

TEST(VariantUtilsIsInvocableAllAlternatives, StructVisitorVariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  struct MyVisitor {
    void operator()(int) {}
  };
  auto result =
      kero::variant_utils::IsInvocableAllAlternatives<MyVisitor, MyVariant>(
          std::make_index_sequence<std::variant_size_v<MyVariant>>{});
  EXPECT_FALSE(result);
}

TEST(VariantUtilsIsInvocableAllAlternatives,
     OverloadedStructVisitorVariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  struct MyVisitor {
    void operator()(int) {}
    void operator()(std::string) {}
  };
  auto result =
      kero::variant_utils::IsInvocableAllAlternatives<MyVisitor, MyVariant>(
          std::make_index_sequence<std::variant_size_v<MyVariant>>{});
  EXPECT_TRUE(result);
}

TEST(VariantUtilsIsInvocableAllAlternatives, LambdaVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  auto visitor = [](int) {};
  auto result =
      kero::variant_utils::IsInvocableAllAlternatives<decltype(visitor),
                                                      MyVariant>(
          std::make_index_sequence<std::variant_size_v<MyVariant>>{});
  EXPECT_TRUE(result);
}

TEST(VariantUtilsIsInvocableAllAlternatives, LambdaVisitorVariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  auto visitor = [](int) {};
  {
    auto result =
        kero::variant_utils::IsInvocableAllAlternatives<decltype(visitor),
                                                        MyVariant>(
            std::make_index_sequence<std::variant_size_v<MyVariant>>{});
    EXPECT_FALSE(result);
  }
}

TEST(VariantUtilsMakeVisitor, VariantSize1) {
  using MyVariant = std::variant<int>;
  auto visitor = kero::variant_utils::MakeVisitor([](int) {});
  using MyVisitor = decltype(visitor);
  {
    auto result = kero::variant_utils::IsInvocable<MyVisitor, int>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                           0>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAllAlternatives<MyVisitor, MyVariant>(
            std::make_index_sequence<std::variant_size_v<MyVariant>>{});
    EXPECT_TRUE(result);
  }
}

TEST(VariantUtilsMakeVisitor, VariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  auto visitor =
      kero::variant_utils::MakeVisitor([](int) {}, [](std::string) {});
  using MyVisitor = decltype(visitor);
  {
    auto result = kero::variant_utils::IsInvocable<MyVisitor, int>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                           0>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                           1>();
    EXPECT_TRUE(result);
  }
  {
    auto result =
        kero::variant_utils::IsInvocableAllAlternatives<MyVisitor, MyVariant>(
            std::make_index_sequence<std::variant_size_v<MyVariant>>{});
    EXPECT_TRUE(result);
  }
}

TEST(VariantUtilsVisit, StructVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  struct MyVisitor {
    bool operator()(int) { return true; }
  };
  MyVariant variant = 42;
  auto result = kero::Visit(variant, MyVisitor{});
  EXPECT_TRUE(result);
}

TEST(VariantUtilsVisit, StructVisitorVariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  struct MyVisitor {
    int operator()(int) { return 1; }
    int operator()(std::string) { return 2; }
  };
  MyVariant variant = 42;
  {
    auto result = kero::Visit(variant, MyVisitor{});
    EXPECT_EQ(result, 1);
  }
  {
    MyVariant variant = "hello";
    auto result = kero::Visit(variant, MyVisitor{});
    EXPECT_EQ(result, 2);
  }
}

TEST(VariantUtilsVisit, LambdaVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  MyVariant variant = 42;
  auto result = kero::Visit(variant, [](int) { return true; });
  EXPECT_TRUE(result);
}

TEST(VariantUtilsVisit, LambdaVisitorVariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  MyVariant variant = 42;
  {
    auto result = kero::Visit(
        variant, [](int) { return 1; }, [](std::string) { return 2; });
    EXPECT_EQ(result, 1);
  }
  {
    MyVariant variant = "hello";
    auto result = kero::Visit(
        variant, [](int) { return 1; }, [](std::string) { return 2; });
    EXPECT_EQ(result, 2);
  }
}

}  // namespace kero
