#include "Maybe.hpp"

int main() {
    constexpr auto const a = Just{5};
    constexpr auto const b = Nothing<int>{};
    constexpr auto const result = add(a, b);
}

// add :: Maybe Int -> Maybe Int -> Maybe Int
// add mx my =             -- Adds two values of type (Maybe Int), where each input value can be Nothing
//   mx   >>=   (\x ->         -- Extracts value x if mx is not Nothing
//     my   >>=   (\y ->       -- Extracts value y if my is not Nothing
//       return (x + y)))  -- Wraps value (x+y), returning the sum as a value of type (Maybe Int)
