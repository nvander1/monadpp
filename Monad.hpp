#pragma once

#include <functional>
#include <ostream>

// A generic monad that stores some data,
// and returns the result of applying a callable
// to bind.
template <typename T>
class Monad {
 public:
  constexpr Monad(T data) : d_data{std::move(data)} {}

  template <typename F>
  const Monad<T> bind(const F& func) const {
    return func(d_data);
  }

  const T peek() const { return d_data; }

 private:
  const T d_data;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Monad<T>& monad) {
  os << monad.peek();
  return os;
}
