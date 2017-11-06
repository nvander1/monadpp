#include "Maybe.hpp"

using namespace monad;

int main() {
  constexpr Just<int> const a = Just{5};
  constexpr Nothing<int> const b = Nothing<int>{};
  constexpr Nothing<int> const result = add(a, b);
  constexpr Nothing<int> const ignored_result = a >> b;
  constexpr Nothing<int> const another_result = a >>= [=](auto num) {
    constexpr Nothing<int> const temp_nothing{};
    return temp_nothing >>= [=](auto second_num) {
      return Just<int>{10};
    };
  };
}

// add :: Maybe Int -> Maybe Int -> Maybe Int
// add mx my =             -- Adds two values of type (Maybe Int), where each
// input value can be Nothing
//   mx   >>=   (\x ->         -- Extracts value x if mx is not Nothing
//     my   >>=   (\y ->       -- Extracts value y if my is not Nothing
//       return (x + y)))  -- Wraps value (x+y), returning the sum as a value of
//       type (Maybe Int)
