#pragma once

#include <functional>

// A generic monad that stores some data,
// and returns the result of applying a callable
// to bind.
template <typename T>
class Monad {
public:
    Monad(const T data) : data(data) {}

    template <typename F>
    const Monad<T> bind(const F &func) const {
      return func(this->data);
    }

    const T peek() const {
      return data;
    }

private:
    const T data;
};
