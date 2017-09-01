#pragma once

#include <cassert>
#include <functional>
#include <ostream>

// A generic monad that stores some data,
// and returns the result of applying a callable
// to bind.
template <typename T> class Monad {
public:
  constexpr Monad(T data) : d_data{std::move(data)} {}

  Monad<T> operator>>=(const std::function<Monad<T>(T)> func) const {
    return func(d_data);
  }

  template <typename U>
  Monad<U> operator>>=(const std::function<Monad<U>(T)> func) const {
    return func(d_data);
  }

  template <typename U> Monad<U> operator>>(Monad<U> other_monad) const {
    std::function<Monad<U>(T)> func = [other_monad](T ignored_data) {
      (void)ignored_data;
      return other_monad;
    };
    return *this >>= func;
  }

  T get_data() { return d_data; }

  operator T() const { return d_data; }

  bool operator==(const Monad<T> &other) const {
    return this->d_data == other.d_data;
  }

  bool operator!=(const Monad<T> &other) const {
    return this->d_data != other.d_data;
  }

private:
  const T d_data;
};
