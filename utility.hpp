#pragma once
#include <array>
#include <tuple>

namespace monad {
namespace detail {
struct tuple_to_array_helper {
  template <typename... Ts>
  constexpr auto operator()(Ts... args)
      -> std::array<std::common_type_t<Ts...>, sizeof...(Ts)> {
    return {{args...}};
  }
};

template <typename F>
struct map_helper {
  constexpr map_helper(F &&f) : fn{std::move(f)} {}
  template <typename... Ts>
  constexpr auto operator()(Ts... args)
      -> std::array<std::common_type_t<Ts...>, sizeof...(Ts)> {
    return {{fn(args)...}};
  }
  F fn;
};

template <typename F>
struct map_flatten_helper {
  constexpr map_flatten_helper(F &&f) : fn{std::move(f)} {}
  template <typename... Ts>
  constexpr auto operator()(Ts... args) {
    return std::tuple_cat(fn(args)...);
  }
  F fn;
};

}  // namespace detail

template <typename Base, typename... Rest>
inline constexpr bool base_of_all_v = (std::is_base_of_v<Base, Rest> && ...);

template <typename Tup>
constexpr auto tuple_to_array(Tup &&tup) {
  return std::apply(detail::tuple_to_array_helper{}, std::forward<Tup>(tup));
}

template <typename T, std::size_t N, typename F>
constexpr auto map(const std::array<T, N> &list, F &&fn) {
  detail::map_helper<F> helper{std::move(fn)};
  return std::apply(helper, list);
}

template <typename T, std::size_t N, typename F>
constexpr auto map_flatten(const std::array<T, N> &list, F &&fn) {
  detail::map_flatten_helper<F> helper{std::move_if_noexcept(fn)};
  return tuple_to_array(std::apply(helper, list));
}

}  // namespace monad
