#pragma once

#include <type_traits>

#include "Monad.hpp"

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

template <typename T>
struct is_maybe_helper : std::false_type {};

template <typename T>
struct is_maybe_helper<Nothing<T>> : std::true_type {};

template <typename T>
struct is_maybe_helper<Just<T>> : std::true_type {};

template <typename T>
struct is_maybe
    : is_maybe_helper<typename std::remove_reference_t<std::remove_cv_t<T>>> {};

template <typename T>
inline constexpr bool is_maybe_v = is_maybe<T>::value;

template <typename... Rest>
inline constexpr bool are_maybe_v = (is_maybe_v<Rest> && ...);

template <typename Lhs, typename Rhs,
          typename = std::enable_if_t<are_maybe_v<Lhs, Rhs>>>
constexpr auto add(const Lhs &mx, const Rhs &my) {
  return mx >>= [=](auto x) constexpr {
    return my >>= [=](auto y) constexpr { return Just{x + y}; };
  };
}

}  // namespace monad
