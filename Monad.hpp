#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <ostream>

namespace monad {

template <typename T, typename U>
constexpr auto operator>>(T ignored_monad, U other_monad) {
  return ignored_monad >>= [=](const auto) { return other_monad; };
}

}  // namespace monad
