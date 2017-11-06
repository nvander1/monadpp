#include "ListMonad.hpp"
#include "Monad.hpp"
#include "gtest/gtest.h"
#include <array>
#include <experimental/fixed_capacity_vector>

using namespace monad;

TEST(list_monad, map_flatten) {  // NOLINT
  constexpr std::array x = {1, 2, 3, 4};
  constexpr auto f = [](int a) { return std::array<int, 2>{a, a + 1}; };
  constexpr std::array<int, 8> y = x >>= f;
  static_assert(std::get<0>(y) == 1);
  static_assert(std::get<1>(y) == 2);
  EXPECT_EQ(y[0], 1);
  EXPECT_EQ(y[1], 2);
}

TEST(list_monad, dynamic) {  // NOLINT
  using std::experimental::fixed_capacity_vector;
  constexpr fixed_capacity_vector<int, 4> vec = {1, 2, 3, 4};
  constexpr auto f = [](int a) -> fixed_capacity_vector<int, 2> {
    if (a % 2 == 0) return {{0, a}};
    return {{a}};
  };
  constexpr auto mapped = vec >>= f;
  constexpr auto expected = fixed_capacity_vector<int, 8>{{1, 0, 2, 3, 0, 4}};
  static_assert(mapped == expected);
}

TEST(list_monad, list_comp) {  // NOLINT
  using std::experimental::fixed_capacity_vector;
  constexpr fixed_capacity_vector<int, 4> vec = {1, 2, 3, 4};
  constexpr auto square = [](int a) { return return_vec_monad(a * a); };
  constexpr auto end = (vec >>= square) >>= square;
  static_assert(end.at(1) == 16);
}
