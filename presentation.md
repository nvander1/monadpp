---
revealOptions:
    transition: 'fade'
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

Note: The StringBuilder is a mutable object

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
