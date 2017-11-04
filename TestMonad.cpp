#include "Monad.hpp"
#include "gtest/gtest.h"

#include <functional>
#include <iostream>
#include <string>

const Monad<int> doubled(int);

const Monad<int> doubled(int x) { return Monad<int>{x * 2}; }

TEST(MonadTest, DoubledMonad) {
  constexpr int x = 5;
  const Monad<int> intmonad{x};
  EXPECT_EQ(5, intmonad);
  EXPECT_EQ((intmonad >>= doubled).get_data(), 10);
}

Monad<std::string> int_to_string(int);
Monad<std::string> int_to_string(int x) {
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

TEST(MonadTest, MonadIgnore) {
  constexpr int x = 15;
  const Monad<int> intmonad{x};
  std::string s{"Hello world"};
  const Monad<std::string> stringmonad{s};
  const Monad<std::string> stringmonad2 = intmonad >> stringmonad;
  EXPECT_EQ(stringmonad, stringmonad2);
}

TEST(ListTest, ListDouble) {
  std::list<int> list{1, 2, 4, 10};
  std::function<std::list<int>(int)> double_func = [](int num) {
    return return_monad(num * 2);
  };
  std::list<int> double_list = list >>= double_func;
  std::list<int> expected{2, 4, 8, 20};
  EXPECT_EQ(double_list, expected);
}

TEST(ListTest, ListIntToString) {
  std::list<int> list{1, 2, 4, 10};
  std::function<std::list<std::string>(int)> string_func = [](int num) {
    return return_monad(std::to_string(num));
  };
  std::list<std::string> string_list = list >>= string_func;
  std::list<std::string> expected{"1", "2", "4", "10"};
  EXPECT_EQ(string_list, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
