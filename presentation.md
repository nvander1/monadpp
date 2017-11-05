# Monads

William Jagels, Rushil Kumar, Ethan Schoen, Nik Vandehroof

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
        PureStringBuilder result = new PureStringBuilder(this.toString() + str);
        return result;
    }
}
```
<!-- .element: class="fragment" -->
