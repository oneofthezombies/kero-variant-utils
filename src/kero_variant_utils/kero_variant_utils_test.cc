#include "kero_variant_utils/kero_variant_utils.h"

#include <gtest/gtest.h>

#include <variant>

namespace kero {

TEST(KeroVariantUtilsIsInvocable, StructVisitor) {
  struct MyVisitor {
    void operator()(int) {}
  };
  auto result = kero::variant_utils::IsInvocable<MyVisitor, int>();
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsIsInvocable, LambdaVisitor) {
  auto visitor = [](int) {};
  auto result = kero::variant_utils::IsInvocable<decltype(visitor), int>();
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsIsInvocableAlternativeAtIndex, StructVisitorVariantSize1) {
  struct MyVisitor {
    void operator()(int) {}
  };
  using MyVariant = std::variant<int>;
  auto result =
      kero::variant_utils::IsInvocableAlternativeAtIndex<MyVisitor, MyVariant,
                                                         0>();
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsIsInvocableAlternativeAtIndex, StructVisitorVariantSize2) {
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

TEST(KeroVariantUtilsIsInvocableAlternativeAtIndex,
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

TEST(KeroVariantUtilsIsInvocableAlternativeAtIndex, LambdaVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  auto visitor = [](int) {};
  auto result =
      kero::variant_utils::IsInvocableAlternativeAtIndex<decltype(visitor),
                                                         MyVariant, 0>();
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsIsInvocableAlternativeAtIndex, LambdaVisitorVariantSize2) {
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

TEST(KeroVariantUtilsIsInvocableAllAlternatives, StructVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  struct MyVisitor {
    void operator()(int) {}
  };
  auto result =
      kero::variant_utils::IsInvocableAllAlternatives<MyVisitor, MyVariant>(
          std::make_index_sequence<std::variant_size_v<MyVariant>>{});
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsIsInvocableAllAlternatives, StructVisitorVariantSize2) {
  using MyVariant = std::variant<int, std::string>;
  struct MyVisitor {
    void operator()(int) {}
  };
  auto result =
      kero::variant_utils::IsInvocableAllAlternatives<MyVisitor, MyVariant>(
          std::make_index_sequence<std::variant_size_v<MyVariant>>{});
  EXPECT_FALSE(result);
}

TEST(KeroVariantUtilsIsInvocableAllAlternatives,
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

TEST(KeroVariantUtilsIsInvocableAllAlternatives, LambdaVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  auto visitor = [](int) {};
  auto result =
      kero::variant_utils::IsInvocableAllAlternatives<decltype(visitor),
                                                      MyVariant>(
          std::make_index_sequence<std::variant_size_v<MyVariant>>{});
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsIsInvocableAllAlternatives, LambdaVisitorVariantSize2) {
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

TEST(KeroVariantUtilsMakeVisitor, VariantSize1) {
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

TEST(KeroVariantUtilsMakeVisitor, VariantSize2) {
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

TEST(KeroVariantUtilsVisit, StructVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  struct MyVisitor {
    bool operator()(int) { return true; }
  };
  MyVariant variant = 42;
  auto result = kero::Visit(variant, MyVisitor{});
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsVisit, StructVisitorVariantSize2) {
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

TEST(KeroVariantUtilsVisit, LambdaVisitorVariantSize1) {
  using MyVariant = std::variant<int>;
  MyVariant variant = 42;
  auto result = kero::Visit(variant, [](int) { return true; });
  EXPECT_TRUE(result);
}

TEST(KeroVariantUtilsVisit, LambdaVisitorVariantSize2) {
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
