#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <ostream>

namespace monad {

template <typename M, typename F,
          typename = std::enable_if_t<
              std::is_invocable_v<F, decltype(std::declval<M>().data())>>>
constexpr auto operator>>=(const M &monad, F &&fn)
    -> std::invoke_result_t<F, decltype(monad.data())> {
  return fn(monad.data());
}

template <typename T, typename U>
constexpr auto operator>>(const T &ignored_monad, const U &other_monad) {
  return ignored_monad >>= [other_monad](auto &&) { return other_monad; };
}

}  // namespace monad
