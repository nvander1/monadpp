---
revealOptions:
    controls: false
---

# Monads

William Jagels, Rushil Kumar,

Ethan Schoen, Nik Vanderhoof

---

## Overview

- Motivation
<!-- .element: class="fragment" -->
- Definition of monads
<!-- .element: class="fragment" -->
- Examples in Haskell
<!-- .element: class="fragment" -->
    - Maybe Monad
<!-- .element: class="fragment" -->
    - List Monad
<!-- .element: class="fragment" -->
    - Monadic "do notation"
<!-- .element: class="fragment" -->
    - IO Monad
<!-- .element: class="fragment" -->
    - State Monad
<!-- .element: class="fragment" -->
- Examples in C++
<!-- .element: class="fragment" -->
    - Maybe Monad
<!-- .element: class="fragment" -->
    - List Monad
<!-- .element: class="fragment" -->

---

## Method Chaining
```java
StringBuilder sb = new StringBuilder();

sb.append("hello").append(" ").append("world");
```
<!-- .element: class="fragment" -->

```java
public class StringBuilder {
    //...
    StringBuilder append(String str) {
        super.append(str);
        return this;
    }
}
```
<!-- .element: class="fragment" -->

```java
public class PureStringBuilder {
    //...
    PureStringBuilder append(String str) {
        PureStringBuilder result =
            new PureStringBuilder(this.toString() + str);
        return result;
    }
}
```
<!-- .element: class="fragment" -->

---

## What is a Monad, anyway?

---

### Informal Definition for Monad
- Enhanced type that is easily composable
<!-- .element: class="fragment" -->
- Function composition in "disguise"
<!-- .element: class="fragment" -->
- Modularity with type safety
<!-- .element: class="fragment" -->

---

### Formal Definition
- Type constructor
<!-- .element: class="fragment" -->
    - Defines how to obtain a monadic version of a type
<!-- .element: class="fragment" -->

- Unit function
<!-- .element: class="fragment" -->
    - Takes a value, constructs a monad to house the value
<!-- .element: class="fragment" -->

- Bind function
<!-- .element: class="fragment" -->
    - Extracts a value from a monad, transforms it, and builds a new monad housing the result
<!-- .element: class="fragment" -->

---

### Monad Haskell Definition

```haskell
class Monad m where
    -- the "unit" function
    return :: a -> m a

    -- the "bind" function
    (>>=) :: m a -> (a -> m b) -> m b

    -- the "then" function
    (>>) :: m a -> m b -> m b
    x >> y = x >>= \_ -> y

    fail :: String -> m a
    fail msg = error msg
```
<!-- .element: class="fragment" -->

---

### Monad Laws
```xml
f :: a -> m a
g :: a -> m a
```
<!-- .element: class="fragment" -->
###### Left Identity
<!-- .element: class="fragment" -->
<!-- haskell syntax won't highlight these correctly -->
```xml
return a  >>= f       == f a
```
<!-- .element: class="fragment" -->

###### Right Identity
<!-- .element: class="fragment" -->
```xml
m         >>= return  == m
```
<!-- .element: class="fragment" -->

###### Associativity
<!-- .element: class="fragment" -->
```xml
(m >>= f) >>= g       == m >>= (\ x -> f x >>= g)
```
<!-- .element: class="fragment" -->

---

## Example Monads in Haskell

---

### The Maybe Monad
#### Definition
```haskell
data Maybe t = Just t | Nothing
```
<!-- .element: class="fragment" -->

```haskell
instance Monad Maybe where
    return x = Just x
    Nothing >>= f = Nothing
    Just x >>= f  = f x
    fail _ = Nothing
```
<!-- .element: class="fragment" -->

---

#### Examples
```haskell
nothingMonadDo = do
  x <- Just 3
  y <- Just 10
  z <- Nothing
  return (x + y + z)
```
<!-- .element: class="fragment" -->

```haskell
nothingMonadBind = Just 3 >>=
                   (\x -> Just 10 >>=
                     (\y -> Nothing >>=
                       (\z -> return (x + y + z))))
```
<!-- .element: class="fragment" -->

```haskell
*Main> nothingMonadDo
Nothing
```
<!-- .element: class="fragment" -->

---

#### Examples (Cont.)

```haskell
addIntoMaybe x y = Just $ x + y
```
<!-- .element: class="fragment" -->

```haskell
justMonadDo = do
  x <- Just 3
  y <- Just 10
  z <- addIntoMaybe x y
  return (x + y + z)
```
<!-- .element: class="fragment" -->

```haskell
*Main> justMonadDo
Just 26
```
<!-- .element: class="fragment" -->

---

### The List Monad
#### Definition
```haskell
instance Monad [] where
    return x = [x]
    xs >>= f = concat (map f xs)
    fail _ = []
```
<!-- .element: class="fragment" -->
```haskell
Prelude> concat [[1,2],[3,4]]
[1,2,3,4]
```
<!-- .element: class="fragment" -->

---

#### Examples
```haskell
oddEvenList :: (Integral a) => [a] -> [a]
oddEvenList list = do
  x <- list
  if odd x then [x, -x] else [x]
```
<!-- .element: class="fragment" -->

```haskell
oddEvenListBind :: (Integral a) => [a] -> [a]
oddEvenListBind list = list >>=
                       (\x -> if odd x
                              then [x, -x]
                              else [x])
```
<!-- .element: class="fragment" -->

```haskell
*Main> oddEvenList [1, 2, 4, 10]
[1,-1,2,4,10]
```
<!-- .element: class="fragment" -->

```haskell
doubleMonad :: [a] -> [a]
doubleMonad list = [-1, 2] >> list
```
<!-- .element: class="fragment" -->

```haskell
*Main> doubleMonad [1, 2, 4]
[1,2,4,1,2,4]
```
<!-- .element: class="fragment" -->

---

### Monadic "do notation"
#### *then* operator translation
```haskell
putStr "Hello," >>
putStr " " >>
putStr "World!" >>
putStr "\n"
```
<!-- .element: class="fragment" -->
```haskell
do
    putStr "Hello,"
    putStr " "
    putStr "World!"
    putStr "\n"
```
<!-- .element: class="fragment" -->

---

#### *bind* operator translation
```haskell
add :: Maybe Integer -> Maybe Integer -> Maybe Integer
```
<!-- .element: class="fragment" -->
```haskell
add mx my =
  mx >>= (\x ->
    my >>= (\y ->
      return (x+y)))
```
<!-- .element: class="fragment" -->
```haskell
add mx my = do
  x <- mx
  y <- my
  return (x + y)
```
<!-- .element: class="fragment" -->

---

### IO Monad

- expressions denote a value
<!-- .element: class="fragment" -->
- I/O commands perform some action
<!-- .element: class="fragment" -->

```haskell
getChar :: IO Char
```
<!-- .element: class="fragment" -->
```haskell
putChar :: Char -> IO ()
```
<!-- .element: class="fragment" -->
```haskell
putStrLn :: String -> IO ()
```
<!-- .element: class="fragment" -->

---

### Programs as IO Actions
```haskell
main :: IO ()
main = putStrLn "hello world";
```
<!-- .element: class="fragment" -->
```haskell
main :: IO ()
main = do
    putStrLn "Who are you?"
    name <- getLine
    putStrLn ("You are " ++ name ++ "!")
```
<!-- .element: class="fragment" -->
```haskell
main :: IO ()
main = putStrLn "Who are you?" >>
  getLine >>= (\name -> putStrLn ("You are ") ++ name ++ "!")
```
<!-- .element: class="fragment" -->

---

#### Examples
```haskell
foo :: String
foo = "Hello"
```
<!-- .element: class="fragment" -->
```haskell
*Main> some_words = replicate 5 foo
```
<!-- .element: class="fragment" -->
```haskell
*Main> some_words
["Hello", "Hello", "Hello", "Hello", "Hello"]
```
<!-- .element: class="fragment" -->
```haskell
*Main> :t some_words
[String]
```
<!-- .element: class="fragment" -->
```haskell
*Main> different_words = replicate 5 getLine
*Main> :t different_words
[IO String]
```
<!-- .element: class="fragment" -->

---

#### Examples (Cont.)
```haskell
sequence :: Monad m => [m a] -> m [a]
```
<!-- .element: class="fragment" -->
```haskell
sequence [] = return []
```
<!-- .element: class="fragment" -->
```haskell
sequence (m:ms) = do
    x <- m
    xs = sequence ms
    return (x:xs)
```
<!-- .element: class="fragment" -->

---

#### Examples (Cont.)
```haskell
*Main> different_words = sequence $ replicate 3 getLine
```
<!-- .element: class="fragment" -->
```haskell
*Main> :t different_words
IO [String]
```
<!-- .element: class="fragment" -->
```haskell
*Main> different_words
hello

world
["hello", "", "world"]
```
<!-- .element: class="fragment" -->

---

### State Monad
```haskell
newtype State s a = State { runState :: s -> (a, s) }
```
- The state monad is actually just a wrapper for a stateful computation.
<!-- .element: class="fragment" -->

- Allows for solving stateful problems in a pure functional language.
<!-- .element: class="fragment" -->

- The stateful computation is the function s -> (a, s).
<!-- .element: class="fragment" -->

- The function takes an initial state "s", and returns a tuple of a result "a" and a new state "s".
<!-- .element: class="fragment" -->

---

#### Definition
```haskell
instance Monad (State s) where
    return x = State $ \s -> (x,s)
    (State h) >>= f = State $ \s -> let (a, newState) = h s
                                        (State g) = f a
                                    in  g newState
```
<!-- .element: class="fragment" -->

---

#### Examples
```haskell
removeMax :: (Num a, Eq a, Ord a) => State [a] a
removeMax = StateT $
            \list -> let maxNum = maximum list
                     in Identity (maxNum, delete maxNum list)
```
<!-- .element: class="fragment" -->

```haskell
removeMaxThreeTimes ::
  (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimes = do
  x <- removeMax
  y <- removeMax
  z <- removeMax
  return (x, y, z)
```
<!-- .element: class="fragment" -->

```haskell
removeMaxThreeTimesBind ::
  (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimesBind = removeMax >>=
                          (\x -> removeMax >>=
                            (\y -> removeMax >>=
                              (\z -> return ((x, y, z)))))
```
<!-- .element: class="fragment" -->

---

#### Examples (Cont.)

```haskell
*Main> runState removeMax  [1, 2, 10, 11]
(11,[1,2,10])
*Main> runState removeMaxThreeTimes   [1, 2, 10, 11]
((11,10,2),[1])
```
<!-- .element: class="fragment" -->

---

## Monads in C++17

---

### Goals
- Deduced types
- Similar to Haskell
- Constexpr
- User defined

---

### Generic Monads

---

#### Ignore Operator
```c++
template <typename T, typename U>
constexpr auto operator>>(const T &ignored_monad, const U &other_monad) {
  return ignored_monad >>= [other_monad](auto &&) { return other_monad; };
}
```

---

#### Bind Operator
```c++
template <typename M, typename F,
          typename = std::enable_if_t<
              std::is_invocable_v<F, decltype(std::declval<M>().data())>>>
constexpr auto operator>>=(const M &monad, F &&fn)
    -> std::invoke_result_t<F, decltype(monad.data())> {
  return fn(monad.data());
}
```

---

#### Like Curry?
```c++
template <typename F, typename A>
constexpr auto curry(F &&f, const A &a) {
  return [=](auto &&... rest) constexpr {
    return f(a, std::forward<decltype(rest)>(rest)...);
  };
}
```
Usage:
```c++
int sum(int a, int b, int c);

int a = curry(curry(curry(sum, 1), 2), 3)();
// a == 6
```

---

#### Let's Make a Monad
```c++
struct IntMonad {
  explicit constexpr IntMonad(int data) : data_{data} {}
  constexpr int data() const { return data_; }
  const int data_;
};
```
```c++
struct DoubleMonad {
  explicit constexpr DoubleMonad(double data) : data_{data} {}
  constexpr double data() const { return data_; }
  const double data_;
};
```

---

#### Use it
```c++
/*   fn ::   int    -> DoubleMonad */
/*   fn =       \x  ->                   ...  */
auto fn = [](int x) -> DoubleMonad {
  return DoubleMonad{static_cast<double>(x * x)};
};
constexpr IntMonad m1{5};
constexpr DoubleMonad r = m1 >>= fn;
/* r == 25.0 */
```

---

### List Monads

---

#### Bind Operator
```c++
namespace monad {
template <typename T, std::size_t N, typename F,
          typename = std::enable_if_t<std::is_invocable_v<F, T>>>
constexpr auto operator>>=(const std::array<T, N> &list, F &&fn) {
  return map_flatten(list, std::move(fn));
}
```

---

```c++
template <typename T, std::size_t N, typename F>
constexpr auto map_flatten(const std::array<T, N> &list, F &&fn) {
  detail::map_flatten_helper<F> helper{std::move_if_noexcept(fn)};
  return tuple_to_array(std::apply(helper, list));
}
```
```c++
template <typename F>
struct map_flatten_helper {
  constexpr map_flatten_helper(F f) : fn{std::move(f)} {}
  template <typename... Ts>
  constexpr auto operator()(Ts... args) {
    return std::tuple_cat(fn(args)...);
  }
  F fn;
};
```

---

#### Usage
```c++
constexpr std::array x = {1, 2, 3, 4};
constexpr auto f = [](int a) { return std::array<int, 2>{a, a + 1}; };
constexpr std::array<int, 8> y = x >>= f;
```
With less noise...
<!-- .element: class="fragment" -->
```c++
array{1, 2, 3, 4} >>= [](int a) { return array{a, a + 1}; };
```
<!-- .element: class="fragment" -->
Quiz: what is this?
<!-- .element: class="fragment" -->

---

But there's a catch...

---

```c++
[](int a) {
    if (a % 2)
      return std::array<int, 1>{a};
    return std::array<int, 2>{0, a};
};
```
Not allowed!

Quiz: why not?

---

### Dynamic Size
We can still do this at compile time!

Enter [P0843](https://gnzlbg.github.io/fixed_capacity_vector/)

---

#### Bind Operator
```c++
template <typename T, std::size_t N, typename F, /*constraints*/>
constexpr auto operator>>=(const std::fixed_capacity_vector<T, N> &list, F &&fn) {
  using std::fixed_capacity_vector;
  using R = std::invoke_result_t<F, T>;
  auto new_list =
      fixed_capacity_vector<typename R::value_type, R::capacity() * N>{};
  for (const auto &e : list) {
    for (auto &&f : fn(e)) {
      new_list.emplace_back(std::move(f));
    }
  }
  return new_list;
}
```

---

#### Usage
```c++
using std::fixed_capacity_vector;
constexpr fixed_capacity_vector<int, 4> vec = {1, 2, 3, 4};
constexpr auto f = [](int a) -> fixed_capacity_vector<int, 2> {
  if (a % 2) return {{a}};
  return {{0, a}};
};
constexpr auto mapped = vec >>= f;
constexpr auto expected = fixed_capacity_vector<int, 8>{{1, 0, 2, 3, 0, 4}};
static_assert(mapped == expected);
```
Notice, the end result only has 6/8 elements

---

#### What if I don't know how much room I need?
- Set it "big enough"
- Write operator>>= for std::{vector, list, forward_list, map, ...}

It's easier to write a bind operator in a non-constexpr context

#### Another Catch
operator>>= is right-associative in C++, this can't be changed

Solutions:
- Use another operator
- Make bind a function
- Parenthesis
