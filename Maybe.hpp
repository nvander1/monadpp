#pragma once

#include <type_traits>

#include "Monad.hpp"

namespace monad {

// data Maybe a = Just a | Nothing
// (>>=) :: Maybe a -> (a -> Maybe b) -> Maybe b

template <typename A>
struct Nothing {
  // Nothing >>= _ = Nothing
  template <typename F>
  constexpr auto operator>>=(F &&) const {
    return Nothing{};
  }
};

template <typename A>
struct Just {
  constexpr Just(A val) : d_val(val) {}

  template <typename F>
  constexpr auto operator>>=(F &&func) const {
    return func(d_val);
  }
  const A d_val;
};

template <typename Base, typename... Rest>
inline constexpr bool base_of_all_v = (std::is_base_of_v<Base, Rest> && ...);

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

template <
    typename Lhs, typename Rhs,
    typename = std::enable_if_t<is_maybe<Lhs>::value && is_maybe<Rhs>::value>>
constexpr auto add(Lhs mx, Rhs my) {
  return mx >>= [=](const int x) constexpr {
    return my >>= [=](const int y) constexpr { return Just{x + y}; };
  };
}

}  // namespace monad
