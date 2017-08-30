#include "Monad.hpp"
#include "gtest/gtest.h"
#include <iostream>

const Monad<int> doubled(int);

const Monad<int> doubled(int x) {
  return Monad<int>{x * 2};
}

TEST(MonadTest, DoubledMonad) {
  constexpr int x = 5;
  const Monad<int> intmonad(x);
  EXPECT_EQ(intmonad.peek(), 5);
  EXPECT_EQ(intmonad.bind(doubled).peek(), 10);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
