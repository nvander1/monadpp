#pragma once
#include "Monad.hpp"
#include "utility.hpp"
#include <experimental/fixed_capacity_vector>
#include <tuple>

namespace monad {
template <typename T, std::size_t N, typename F,
          typename = std::enable_if_t<std::is_invocable_v<F, T>>>
constexpr auto operator>>=(const std::array<T, N> &list, F &&fn) {
  return map_flatten(list, std::move(fn));
}

template <typename T, std::size_t N, typename F,
          typename = std::enable_if_t<std::is_invocable_v<F, T>>,
          typename R = std::invoke_result_t<F, T>>
constexpr auto operator>>=(
    const std::experimental::fixed_capacity_vector<T, N> &list, F &&fn) {
  using std::experimental::fixed_capacity_vector;
  using traits = VecTraits<R>;
  auto new_list =
      fixed_capacity_vector<typename traits::type, traits::capacity * N>{};
  for (const auto &e : list) {
    for (auto &&f : fn(e)) {
      new_list.emplace_back(std::move(f));
    }
  }
  return new_list;
}

template <typename T>
constexpr std::array<T, 1> return_monad(T data) {
  return {data};
}
}  // namespace monad
