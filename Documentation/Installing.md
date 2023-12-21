# ⬇️ Installing Specs

[TOC]

`Specs` is very easy to install if you're using `xmake` or `vcpkg`.

> `Specs` has quite a few library dependencies which are available as `xmake` and `vcpkg` packages.
>
> Due to the dependencies, I do **not** recommend installing `Specs` manually.

# C++17

`Specs` requires `C++17` or higher.

> **Note:** if you are using `C++17`, you must add `fmt` as a dependency for string formatting.
> `C++20` is supported with no additional dependencies required.


> **Why not C++14?**
>
> `Specs` uses `string_view` and `structured bindings` which are C++17 features.

# xmake

The following is an `xmake.lua` example which sets up a `Specs` test suite:

```py
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("specs")

target("MyProject.Tests")
    set_kind("binary")
    add_packages("specs")
    add_files("*.cpp")
```

_That's it!_

If you want to verify that it works, create a `Test.cpp` with the following contents:

```cpp
#include <Specs.h>
#include <Specs/Main.h>

Test("Example test") { throw "Kaboom, this failed!"; }
```

Then run `xmake run MyProject.Tests` and you should see the following output:

```
[FAILED] Example test

Kaboom, this failed!

1 failed
```

# vcpkg


