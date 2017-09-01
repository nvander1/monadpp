#include "Monad.hpp"
#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <functional>

const Monad<int> doubled(int);

const Monad<int> doubled(int x) { return Monad<int>{x * 2}; }

TEST(MonadTest, DoubledMonad) {
  constexpr int x = 5;
  const Monad<int> intmonad{x};
  EXPECT_EQ(5, intmonad);
  EXPECT_EQ((intmonad >>= doubled), 10);
}

Monad<std::string> int_to_string(int);
Monad<std::string> int_to_string(int x){
  return Monad<std::string>{std::to_string(x)};
}

TEST(MonadTest, IntToStringMonad) {
  constexpr int x = 15;
  const Monad<int> intmonad{x};
  std::function<Monad<std::string>(int)> func = int_to_string;
  std::string num_string = intmonad >>= func;
  EXPECT_EQ(15, intmonad);
  EXPECT_EQ(num_string, "15");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
