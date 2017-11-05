# Monads

William Jagels, Rushil Kumar, Ethan Schoen, Nik Vandehroof

---

## Overview

- WHat is a Monad
- Maybe Monads
- 

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
    - Takes an underlying type, returns the type of a monad containing that type
- Unit function
    - Takes an underlying type, returns a monad containing that type
- Binding operation
    - Takes a monad and a function mapping the underlying type to another monadic type

---

## Monad Definition
```python
class Monad:
    def __init__(self, x):
        raise NotImplementedError

    def bind(self, f):
        raise NotImplementedError
```
<!-- .element: class="fragment" -->

```python
class SimpleMonad:
    def __init__(self, x):
        self.x = x

    def bind(self, f):
        return f(self.x)
```
<!-- .element: class="fragment" -->
