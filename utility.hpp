#pragma once
#include <array>
#include <tuple>

namespace monad {
namespace detail {
struct tuple_to_array_helper {
  template <typename... Ts>
  auto operator()(Ts... args) {
    return std::array<std::common_type_t<Ts...>, sizeof...(Ts)>{{args...}};
  }
};
}  // namespace detail

template <typename Base, typename... Rest>
inline constexpr bool base_of_all_v = (std::is_base_of_v<Base, Rest> && ...);

template <typename Tup>
auto tuple_to_array(Tup &&tup) {
  return std::apply(detail::tuple_to_array_helper{}, std::forward<Tup>(tup));
}

}  // namespace monad
