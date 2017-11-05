#include "Monad.hpp"
#include "ListMonad.hpp"
#include "gtest/gtest.h"
#include <array>

using namespace monad;

TEST(list_monad, map) {
  constexpr std::array<int, 4> x = {1, 2, 3, 4};
  constexpr auto f = [](int a) { return a + 1; };
  constexpr std::array<int, 4> y = x >>= f;
  EXPECT_EQ(y[0], 2);
}

TEST(list_monad, map_flatten) {
  constexpr std::array<int, 4> x = {1, 2, 3, 4};
  constexpr auto f = [](int a) { return std::array<int, 2>{a, a + 1}; };
  constexpr std::array<int, 8> y = x >>= f;
  static_assert(std::get<0>(y) == 1);
  static_assert(std::get<1>(y) == 2);
  EXPECT_EQ(y[0], 1);
  EXPECT_EQ(y[1], 2);
}
