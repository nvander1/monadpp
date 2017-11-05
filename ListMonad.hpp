#pragma once
#include "Monad.hpp"
#include "utility.hpp"
#include <tuple>

namespace monad {
// TODO: constrain this better
template <typename T, std::size_t N, typename F,
          typename = std::enable_if_t<!std::is_invocable_r_v<T, F, T>>>
constexpr auto operator>>=(const std::array<T, N> &list, F &&fn) {
  return map_flatten(list, std::move(fn));
}

template <typename T, std::size_t N, typename F,
          typename = std::enable_if_t<std::is_invocable_r_v<T, F, T>>>
constexpr std::array<T, N> operator>>=(const std::array<T, N> &list, F &&fn) {
  return map(list, std::move(fn));
}

template <typename T>
constexpr std::array<T, 1> return_monad(T data) {
  return {data};
}
}  // namespace monad
