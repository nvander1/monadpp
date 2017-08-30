#include "Monad.hpp"
#include "gtest/gtest.h"

const Monad<int> doubled(int);

const Monad<int> doubled(int x) { return Monad<int>{x * 2}; }

namespace {
class MonadTest : public ::testing::Test {};
}  // namespace

TEST_F(MonadTest, DoubledMonad) {
  constexpr int x = 5;
  const Monad<int> intmonad{x};
  EXPECT_EQ(5, intmonad);
  EXPECT_EQ((intmonad >>= doubled), 10);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
