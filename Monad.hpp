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
  Monad<T> operator>>=(const F& func) const {
    return func(d_data);
  }

  operator T() const { return d_data; }

 private:
  const T d_data;
};
