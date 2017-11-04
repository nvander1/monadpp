#ifndef MAYBE_MONAD_H_
#define MAYBE_MONAD_H_

#include <type_traits>

// data Maybe a = Just a | Nothing
class Maybe {};

// (>>=) :: Maybe a -> (a -> Maybe b) -> Maybe b

struct Nothing : public Maybe {
  // Nothing >>= _ = Nothing
  template <typename F>
  constexpr auto operator>>=(F &&) const {
    return Nothing{};
  }
};

template <typename A>
struct Just : public Maybe {
  constexpr Just(A val) : d_val(val) {}

  template <typename F>
  constexpr auto operator>>=(F &&func) const {
    return func(d_val);
  }
  const A d_val;
};

template <typename Base, typename... Rest>
inline constexpr bool base_of_all_v = (std::is_base_of_v<Base, Rest> && ...);

template <typename Lhs, typename Rhs,
          typename = std::enable_if_t<base_of_all_v<Maybe, Lhs, Rhs>>>
constexpr auto add(Lhs mx, Rhs my) {
  return mx >>= [=](const int x) constexpr {
    return my >>= [=](const int y) constexpr { return Just{x + y}; };
  };
}
#endif
