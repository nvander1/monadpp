include(`Monad.m4')dnl
#pragma once

#include <type_traits>

include(`Monad.hpp')

namespace monad {

// data Maybe a = Just a | Nothing
// (>>=) :: Maybe a -> (a -> Maybe b) -> Maybe b

template <typename A>
struct Nothing {
  // Nothing >>= _ = Nothing
  template <typename F, typename = std::enable_if_t<std::is_invocable_v<F, A>>>
  constexpr auto operator>>=(F &&) const {
    return Nothing{};
  }
};

template <typename A>
struct Just {
  constexpr Just(A val) : d_val(val) {}

  template <typename F, typename = std::enable_if_t<std::is_invocable_v<F, A>>>
  constexpr auto operator>>=(F &&func) const {
    return func(d_val);
  }
  const A d_val;
};

is_monad_t(Maybe, Just, Nothing)

template <typename Lhs, typename Rhs,
          typename = std::enable_if_t<is_maybe_v<Lhs> && is_maybe_v<Rhs>>>
constexpr auto add(Lhs mx, Rhs my) {
  return mx >>= [=](const int x) constexpr {
    return my >>= [=](const int y) constexpr { return Just{x + y}; };
  };
}

}  // namespace monad
