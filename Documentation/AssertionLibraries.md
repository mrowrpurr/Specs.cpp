# ✔️ Assertion Libraries

[TOC]

Getting started with `Specs` is incredibly easy.

Especially if you manage your C++ dependencies using `xmake` or `vcpkg`

> See [Installing Specs](md__documentation_2_installing.html) to get started.

## Assertion Libraries

One core difference between `Specs` and other testing frameworks is that `Specs` does not provide any assertion functions or macros.

Instead, `Specs` is designed to work with any assertion library (_or any C++ exception_).

By default, any C++ exception thrown during a test will be caught and reported as a failure.

> If the exception is a `std::exception`, the `what()` will be displayed as a failure message.
>
> If the exception is a literal C-string, the string will be displayed as a failure message.

### snowhouse

[Snowhouse](https://github.com/banditcpp/snowhouse) is a lovely C++ assertion library.

It uses an `AssertThat()` style syntax, which is very readable.

```cpp
Test("Snowhouse example") {
    AssertThat(69, Equals(69));
}
```

Visit the Snowhouse GitHub page for more examples:
- https://github.com/banditcpp/snowhouse

### libassert

[libassert](https://github.com/jeremy-rifkin/libassert) ia another great C++ assertion library.

Marketed as "_The most over-engineered and overpowered C++ assertion library._", it provided a simple `assert` syntax.

```cpp
Test("libassert example") {
    assert(69 == 420);
}
```

Visit the libassert GitHub page for more examples:
- https://github.com/jeremy-rifkin/libassert
