---
revealOptions:
    transition: 'fade'
---

# Monads

William Jagels, Rushil Kumar, Ethan Schoen, Nik Vandehroof

---

## Overview

Definition of monads
Uses of monads
Haskell examples
Compile-time C++ monads

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

## Formal Definition
- Type constructor
<!-- .element: class="fragment" -->
    - Defines how to obtain a monadic version of a type
<!-- .element: class="fragment" -->

- Unit function (or return function)
<!-- .element: class="fragment" -->
    - Takes a value, constructs a monad to house the value
<!-- .element: class="fragment" -->

- Bind function
<!-- .element: class="fragment" -->
    - Extracts a value from a monad, transforms it, and builds a new monad housing the result
<!-- .element: class="fragment" -->

---

## Monad Laws
###### Left Identity
<!-- .element: class="fragment" -->
```python
bind(unit(a), f) == f(a)```
<!-- .element: class="fragment" -->

###### Right Identity
<!-- .element: class="fragment" -->
```python
bind(m, unit) == m```
<!-- .element: class="fragment" -->

###### Associativity
<!-- .element: class="fragment" -->
```python
bind(bind(m, f), g) == bind(m, bind(lambda x: bind(f(x), g)))
```
<!-- .element: class="fragment" -->

---

## Monad Definition

```haskell
class Monad m where
    return :: a -> m a

    (>>=) :: m a -> (a -> m b) -> m b

    (>>) :: m a -> m b -> m b
    x >> y = x >>= \_ -> y

    fail :: String -> m a
    fail msg = error msg
```
<!-- .element: class="fragment" -->

---

## The Maybe Monad
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

## Maybe Monad Examples
```haskell
nothingMonadDo = do
  x <- Just 3
  y <- Just 10
  z <- Nothing
  return (x + y + z)
```
<!-- .element: class="fragment" -->

```haskell
nothingMonadBind = Just 3 >>= (\x -> Just 10 >>= (\y -> Nothing >>= (\z -> return (x + y + z))))
```
<!-- .element: class="fragment" -->

```haskell
*Main> nothingMonadDo
Nothing
```
<!-- .element: class="fragment" -->

```haskell
justMonadDo = do
  x <- Just 3
  y <- Just 10
  z <- Just 11
  return (x + y + z)
```
<!-- .element: class="fragment" -->

```haskell
*Main> justMonadDo
Just 24
```
<!-- .element: class="fragment" -->

---

## The List Monad
```haskell
instance Monad [] where
    return x = [x]
    xs >>= f = concat (map f xs)
    fail _ = []
```
<!-- .element: class="fragment" -->

---

## List Monad Examples
```haskell
oddEvenList :: (Integral a) => [a] -> [a]
oddEvenList list = do
  x <- list
  if odd x then [x, -x] else [x]
```
<!-- .element: class="fragment" -->

```haskell
oddEvenListBind :: (Integral a) => [a] -> [a]
oddEvenListBind list = list >>= (\x -> if odd x then [x, -x] else [x])
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

## State Monad
```haskell
newtype State s a = State { runState :: s -> (a, s) }
```
The state monad is actually just a wrapper for a stateful computation.
Allows for solving stateful problems in a pure functional language.
<!-- .element: class="fragment" -->

The stateful computation is the function s -> (a, s).
The function takes an initial state "s", and returns a tuple of a result "a" and a new state "s".
<!-- .element: class="fragment" -->

---

## State Monad Instance Definition
```haskell
instance Monad (State s) where
    return x = State $ \s -> (x,s)
    (State h) >>= f = State $ \s -> let (a, newState) = h s
                                        (State g) = f a
                                    in  g newState
```
<!-- .element: class="fragment" -->

---

## State Example
```haskell
removeMax :: (Num a, Eq a, Ord a) => State [a] a
removeMax = StateT $ \list -> let maxNum = maximum list in Identity (maxNum, delete maxNum list)

removeMaxThreeTimes :: (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimes = do
  x <- removeMax
  y <- removeMax
  z <- removeMax
  return (x, y, z)

removeMaxThreeTimesBind :: (Num a, Eq a, Ord a) => State [a] (a, a, a)
removeMaxThreeTimesBind = removeMax >>=
                          (\x -> removeMax >>=
                                 (\y -> removeMax >>=
                                        (\z -> return ((x, y, z)))))
```
<!-- .element: class="fragment" -->

```haskell
*Main> runState removeMax  [1, 2, 10, 11]
(11,[1,2,10])
*Main> runState removeMaxThreeTimes   [1, 2, 10, 11]
((11,10,2),[1])
```
<!-- .element: class="fragment" -->

---

- State Monad
- Printing
- File I/O
- Other messy or unpure actions
