#pragma once
#include "Monad.hpp"
#include "utility.hpp"
#include <tuple>

namespace monad {
template <typename T, std::size_t N, typename F,
          typename = std::enable_if_t<std::is_invocable_v<F, T>>>
constexpr auto operator>>=(const std::array<T, N> &list, F &&fn) {
  return map_flatten(list, std::move(fn));
}

template <typename T>
constexpr std::array<T, 1> return_monad(T data) {
  return {data};
}
}  // namespace monad
