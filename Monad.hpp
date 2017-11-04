#pragma once

#include <cassert>
#include <functional>
#include <list>
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

template <template <typename> typename M, typename T, typename U>
M<U> operator>>(M<T> ignored_monad, M<U> other_monad) {
  std::function<M<U>(T)> func = [other_monad](T ignored_data) {
    (void)ignored_data;
    return other_monad;
  };
  return ignored_monad >>= func;
}

/*
  List Monad
 */

template <typename T>
std::list<T> operator>>=(const std::list<T> list,
                         const std::function<std::list<T>(T)> func) {
  std::list<T> new_list;
  for (auto it = list.begin(); it != list.end(); ++it) {
    new_list.splice(new_list.end(), func(*it));
  }
  return new_list;
}

template <typename T, typename U>
std::list<U> operator>>=(const std::list<T> list,
                         const std::function<std::list<U>(T)> func) {
  std::list<U> new_list;
  for (auto it = list.begin(); it != list.end(); ++it) {
    new_list.splice(new_list.end(), func(*it));
  }
  return new_list;
}

template <typename T> std::list<T> return_monad(T data) {
  return std::list{data};
}
