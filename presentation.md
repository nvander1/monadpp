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

## State Monad
```haskell
newtype State s a = State { runState :: s -> (a, s) }
```
Really the State Monad acts like a container for the state and a function to the next state
<!-- .element: class="fragment" -->

Here s is that function and a is the current value
<!-- .element: class="fragment" -->

---

- State Monad
- Printing
- File I/O
- Other messy or unpure actions
