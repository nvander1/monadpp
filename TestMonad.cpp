#include <iostream>

#include "Monad.hpp"

const Monad<int> doubled(int x) {
  const Monad<int> result(x * 2);
  return result;
}

int main() {
  const Monad<int> intmonad(5);
  std::cout << intmonad << std::endl;
  std::cout << intmonad.bind(doubled) << std::endl;
}
