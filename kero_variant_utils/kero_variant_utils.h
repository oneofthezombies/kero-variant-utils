#ifndef KERO_VARIANT_UTILS_H_
#define KERO_VARIANT_UTILS_H_

#include <variant>

namespace kero {

template <typename... Handlers>
struct Visitor : Handlers... {
  using Handlers::operator()...;
};

template <typename... Handlers>
Visitor(Handlers...) -> Visitor<Handlers...>;

template <typename Visitor, typename T>
constexpr bool IsInvocableWith() {
  return std::is_invocable_v<Visitor, T> || std::is_invocable_v<Visitor, T &> ||
         std::is_invocable_v<Visitor, T &&>;
}

template <typename Variant, typename Visitor, std::size_t Index>
constexpr bool IsIndexInvocableWith() {
  using Alternative = std::variant_alternative_t<Index, Variant>;
  return IsInvocableWith<Visitor, Alternative>();
}

template <typename Variant, typename Visitor, std::size_t... Indices>
constexpr bool AreAllIndicesInvocable(std::index_sequence<Indices...>) {
  return (IsIndexInvocableWith<Variant, Visitor, Indices>() && ...);
}

template <typename Variant, typename Visitor>
constexpr bool IsExhaustiveVisitor() {
  constexpr auto indices =
      std::make_index_sequence<std::variant_size_v<Variant>>{};
  return AreAllIndicesInvocable<Variant, Visitor>(indices);
}

template <typename Variant, typename Visitor>
constexpr decltype(auto) Visit(Variant &&variant, Visitor &&visitor) {
  static_assert(IsExhaustiveVisitor<std::decay_t<Variant>, Visitor>(),
                "Visitor does not handle all alternatives in the variant!");
  return std::visit(std::forward<Visitor>(visitor),
                    std::forward<Variant>(variant));
}

template <typename Variant, typename... Handlers>
auto MakeVisitor(Handlers &&...handlers) {
  return Visitor{std::forward<Handlers>(handlers)...};
}

template <typename Variant, typename... Handlers>
constexpr decltype(auto) Visit(Variant &&variant, Handlers &&...handlers) {
  auto visitor =
      MakeVisitor<std::decay_t<Variant>>(std::forward<Handlers>(handlers)...);
  return Visit(std::forward<Variant>(variant), visitor);
}

}  // namespace kero

#endif  // KERO_VARIANT_UTILS_H_
