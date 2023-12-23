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

#### Setup

To setup the `Specs` adapter for `Snowhouse`, include `<Specs/Snowhouse/Main.h>` in your `main.cpp`

```cpp
// Include the primary specs main() entrypoint
#include <Specs/Main.h>

// Setup the Snowhouse adapter (only do this once per project)
#include <Specs/Snowhouse/Main.h>
```

#### Usage

Then, in each spec file, you may include `<Specs/Snowhouse.h>` as a shorthand for including the `snowhouse` headers.

```cpp
#include <Specs.h>
#include <Specs/Snowhouse.h>

Test("Snowhouse example") {
    AssertThat(69, Equals(420));
}
```

```
[FAILED] Snowhouse example

Expected: equal to 420
Actual: 69

[Basic.Test.cpp:10] AssertThat(69, Equals(420));

1 failed
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
