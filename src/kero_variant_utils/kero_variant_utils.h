#ifndef KERO_VARIANT_UTILS_H_
#define KERO_VARIANT_UTILS_H_

#include <variant>

namespace kero {

namespace variant_utils {

template <typename Visitor, typename T>
constexpr bool IsInvocable() {
  return std::is_invocable_v<Visitor, T> ||
         std::is_invocable_v<Visitor, const T> ||
         std::is_invocable_v<Visitor, T &> ||
         std::is_invocable_v<Visitor, const T &> ||
         std::is_invocable_v<Visitor, T &&> ||
         std::is_invocable_v<Visitor, const T &&>;
}

template <typename Visitor, typename Variant, std::size_t AlternativeIndex>
constexpr bool IsInvocableAlternativeAtIndex() {
  using Alternative =
      std::variant_alternative_t<AlternativeIndex, std::decay_t<Variant>>;
  return IsInvocable<Visitor, Alternative>();
}

template <typename Visitor, typename Variant, std::size_t... AlternativeIndex>
constexpr bool IsInvocableAllAlternatives(
    std::index_sequence<AlternativeIndex...>) {
  return (IsInvocableAlternativeAtIndex<Visitor, Variant, AlternativeIndex>() &&
          ...);
}

template <typename Visitor, typename Variant>
constexpr bool IsExhaustiveVisitor() {
  constexpr auto alternative_indices =
      std::make_index_sequence<std::variant_size_v<std::decay_t<Variant>>>{};
  return IsInvocableAllAlternatives<Visitor, Variant>(alternative_indices);
}

template <typename Visitor, typename Variant>
constexpr void AssertExhaustiveVisitor() {
  static_assert(IsExhaustiveVisitor<Visitor, Variant>(),
                "Visitor does not handle all alternatives in the variant!");
}

template <typename... Handlers>
struct Visitor : Handlers... {
  using Handlers::operator()...;
};

template <typename... Handlers>
Visitor(Handlers...) -> Visitor<Handlers...>;

template <typename... Handlers>
decltype(auto) MakeVisitor(Handlers &&...handlers) {
  return Visitor{std::forward<Handlers>(handlers)...};
}

}  // namespace variant_utils

template <typename Variant, typename Visitor>
constexpr decltype(auto) Visit(Variant &&variant, Visitor &&visitor) {
  kero::variant_utils::AssertExhaustiveVisitor<Visitor, Variant>();
  return std::visit(std::forward<Visitor>(visitor),
                    std::forward<Variant>(variant));
}

template <typename Variant, typename... Handlers>
constexpr decltype(auto) Visit(Variant &&variant, Handlers &&...handlers) {
  auto visitor =
      kero::variant_utils::MakeVisitor(std::forward<Handlers>(handlers)...);
  return Visit(std::forward<Variant>(variant), visitor);
}

}  // namespace kero

#endif  // KERO_VARIANT_UTILS_H_
