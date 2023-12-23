# ⬇️ Installing Specs

[TOC]

`Specs` is very easy to install if you're using `xmake` or `vcpkg`.

> `Specs` has quite a few library dependencies which are available as `xmake` and `vcpkg` packages.
>
> Due to the dependencies, I do **not** recommend installing `Specs` manually.

# C++17

`Specs` requires `C++17` or higher.

Using `C++20` works out-of-the-box without any additional dependencies.

If you are using `C++17`, you must add `fmt` as a dependency for string formatting.

> **Why not C++14?**
>
> `Specs` uses `string_view` and `structured bindings` which are C++17 features.

# xmake

The following is an `xmake.lua` example which sets up a `Specs` test suite:

```py
-- # C++17 is required (but requires adding the 'fmt' library if used)
-- # C++20 works out-of-the-box without any additional dependencies
set_languages("c++20")

-- # Add the MrowrLib xmake repository which provides the packages:
-- # specs, specs_snowhouse, specs_libassert, and libassert_latest
add_repositories("MrowrLib https://github.com/MrowrLib/Packages")

-- # Add dependency on 'specs'
add_requires("specs")

-- # Create an executable target which will execute your specs when run
target("MyTests")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("specs")
```

_That's it!_

## Verify

If you want to verify that it works, create a `Test.cpp` with the following contents:

```cpp
#include <Specs.h>
#include <Specs/Main.h>

Test("Example test") {
    throw "Kaboom, this failed!";
}
```

Then build and run your test target.

You should see the following output:

```
[FAILED] Example test

Kaboom, this failed!

1 failed
```

## Assertion Library Support

By default, `Specs` will catch any `std::exception` (_or literal string_) thrown and display it as a test failure message.

If you want to integrate with an assertion library, we provide integrations for the `snowhouse` and `libassert` assertion libraries.

## Snowhouse

If you want to install the the `Snowhouse` assertion library with `Specs` support:

```py
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("specs")

-- # Install snowhouse
-- # Here we use the official vcpkg package registry to install snowhouse
add_requires("vcpkg::snowhouse")

-- # Install the Spec adapter for snowhouse
add_requires("specs_snowhouse")

target("MyProject.Tests")
    set_kind("binary")
    add_packages("specs")
    add_files("*.cpp")

    -- # Add the snowhouse and specs_snowhouse packages to your target
    add_packages("vcpkg::snowhouse", "specs_snowhouse")
```

### Verify

If you want to verify that it works, create a `Test.cpp` with the following contents:

```cpp
#include <Specs/Main.h>            // Provides the main() function for running Specs tests
#include <Specs/Snowhouse/Setup.h> // Configures Specs snowhouse support
#include <Specs.h>                 // Provides the primary DSL functions/macros for writing Specs tests
#include <Specs/Snowhouse.h>       // Shorthand for including snowhouse headers/namespace

Test("Example Snowhouse test") {
    AssertThat(69, Equals(420));
}
```

Then build and run your test target.

You should see the following output:

```
[FAILED] Example Snowhouse test

Expected: equal to 420
Actual: 69

[Test.cpp:7] AssertThat(69, Equals(420));

1 failed
```

## libassert

If you want to install the the `libassert` assertion library with `Specs` support:

```py
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("specs")

-- # Install snowhouse
-- # Here we use the official xmake package registry to install libassert
-- # (Optional) we are using the 'lowercase' option which provides an 'assert()' macro rather than 'ASSERT()'
add_requires("libassert", { configs = { lowercase = true } })

-- # Install the Spec adapter for libassert
add_requires("specs_libassert")

target("MyProject.Tests")
    set_kind("binary")
    add_packages("specs")
    add_files("*.cpp")

    -- # Add the libassert and specs_libassert packages to your target
    add_packages("libassert", "specs_libassert")
```

> **Note:** at the time of writing, I was having trouble getting `libassert` to build from the official `xmake` registry.
>
> If you run into problems, feel free to use the latest version of `libassert` from the `MrowrLib` registry (using the `libassert_latest` package):
>
> ```py
> add_requires("libassert_latest", { configs = { lowercase = true } })
>
> -- # ...
> target("MyProject.Tests")
>     -- # ...
>     -- # Add the libassert and specs_libassert packages to your target
>     add_packages("libassert_latest", "specs_libassert")
> ```

### Verify

If you want to verify that it works, create a `Test.cpp` with the following contents:

```cpp
#include <Specs/Main.h>      // Provides the main() function for running Specs tests
#include <Specs.h>           // Provides the primary DSL functions/macros for writing Specs tests
#include <Specs/LibAssert.h> // Includes libassert support

Test("Example libassert test") {
    assert_that(69 == 420);
}
```

Then run `xmake run MyProject.Tests` and you should see the following output:

```
[FAILED] Example libassert test

Verification failed at Basic.Test.cpp:6: void __cdecl __globalMacroFunctions__function___SPEC_TEST__DefaultCompilationUnit_0(SpecsCpp::ISpec *):
    VERIFY(69 == 420);

1 failed
```

> **Release Mode**
>
> Note: `libassert`'s `assert` macro does NOT throw exceptions in `release` mode.
> 
> This means that `Specs` will not be able to catch the assertion failure and report it as a test failure.
>
> To get around this:
> - you can use the `VERIFY` macro instead of `assert` (_which throws exceptions in `release` mode_)
> - (**recommended**) use the `assert_that` macro provided by `Specs` (_which is an alias for `VERIFY`_)
> ```

# vcpkg

> In this example, we use a `vcpkg.json` file to manage our `vcpkg` dependencies.
>
> See [vcpkg Manifest Mode](https://learn.microsoft.com/en-us/vcpkg/concepts/manifest-mode) for more information.

To install `Specs` using `vcpkg`, you will need to:

- Add `specs` as a dependency in your `vcpkg.json`
- Add the [`MrowrLib/Packages`](https://github.com/MrowrLib/Packages.git) registry to your `vcpkg-configuration.json`
- Link `specs::specs` in your test target in your `CMakelists.txt`

### vcpkg.json

Add `specs` as a dependency in your `vcpkg.json`:

```cpp
{
    "dependencies": [
        "specs"
    ]
}
```

## vcpkg-configuration.json

Add the [`MrowrLib/Packages`](https://github.com/MrowrLib/Packages.git) registry to your `vcpkg-configuration.json`, including a full list of all `Specs` dependencies from the registry:

```cpp
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "ff6867374598312866fecfc64736a334591ceace"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "384225d0aa7bf0d345cb7f9740b913baec675233",
            "packages": [
                "specs",
                "specs-snowhouse",
                "specs-libassert",
                "mrowr-function-pointer",
                "mrowr-global-macro-functions",
                "mrowr-collections",
                "mrowr-log",
                "mrowr-string-format",
                "mrowr-void-pointer"
            ]
        }
    ]
}
```

> **Note:** you will want to update the `baseline` values in [`vcpkg-configuration.json`](vcpkg-configuration.json) for:
> - the `default-registry` registry: this should be the latest commit SHA of [`microsoft/vcpkg`](https://github.com/microsoft/vcpkg/commits/master/)
> - the [`MrowrLib/Packages`](https://github.com/MrowrLib/Packages/commits/main/) registry: this should be the latest commit SHA of [`MrowrLib/Packages`](https://github.com/MrowrLib/Packages/commits/main/)

## CMakeLists.txt

```py
cmake_minimum_required(VERSION 3.21)

project(MyTests)

# Create an executable target which will execute your specs when run
add_executable(
    ${PROJECT_NAME}
    Test.cpp
)

# C++17 is required (but requires adding the 'fmt' library if used)
# C++20 works out-of-the-box without any additional dependencies
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20) 

# Add dependency on 'specs'
find_package(specs CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE specs::specs)
```

## Verify

If you want to verify that it works, create a `Test.cpp` with the following contents:

```cpp
#include <Specs.h>
#include <Specs/Main.h>

Test("Example test") {
    throw "Kaboom, this failed!";
}
```

Then run `xmake run MyProject.Tests` and you should see the following output:

```
[FAILED] Example test

Kaboom, this failed!

1 failed
```

## Assertion Library Support

By default, `Specs` will catch any `std::exception` (_or literal string_) thrown and display it as a test failure message.

If you want to integrate with an assertion library, we provide integrations for the `snowhouse` and `libassert` assertion libraries.

### Snowhouse

If you want to install the the `Snowhouse` assertion library with `Specs` support:

- Add `specs-snowhouse` to your `vcpkg.json`
- Link `specs::specs_snowhouse` in your test target in your `CMakelists.txt`

#### vcpkg.json

Here we add `snowhouse` from the official `vcpkg` registry, and `specs-snowhouse` from the `MrowrLib/Packages` registry:

```cpp
{
    "dependencies": [
        "specs",
        "snowhouse",
        "specs-snowhouse"
    ]
}
```

#### CMakeLists.txt

```py
cmake_minimum_required(VERSION 3.21)

project(MyTests)

# Create an executable target which will execute your specs when run
add_executable(
    ${PROJECT_NAME}
    Test.cpp
)

# C++17 is required (but requires adding the 'fmt' library if used)
# C++20 works out-of-the-box without any additional dependencies
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20) 

# Add dependency on 'specs'
find_package(specs CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE specs::specs)

# Snowhouse:
find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})

# Specs adapter for Snowhouse:
find_package(specs_snowhouse CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE specs::specs_snowhouse)
```

#### Verify

If you want to verify that it works, create a `Test.cpp` with the following contents:

```cpp
#include <Specs/Main.h>            // Provides the main() function for running Specs tests
#include <Specs/Snowhouse/Setup.h> // Configures Specs snowhouse support
#include <Specs.h>                 // Provides the primary DSL functions/macros for writing Specs tests
#include <Specs/Snowhouse.h>       // Shorthand for including snowhouse headers/namespace
 
Test("Example Snowhouse test") {
    AssertThat(69, Equals(420));
}
```

Then build and run your test target.

You should see the following output:

```
[FAILED] Example Snowhouse test

Expected: equal to 420
Actual: 69

[Test.cpp:7] AssertThat(69, Equals(420));

1 failed
```

### libassert

At the time of writing, I can't get the `vcpkg` version of `libassert` to build.

I couldn't get the instructions on the `libassert` GitHub page to work either.

For that reason, for now... you're on your own.

Here is the `libassert` README: https://github.com/jeremy-rifkin/libassert

Here is a recent bug report for the `vcpkg`: https://github.com/jeremy-rifkin/libassert/issues/75

> _Don't worry, I really like the elegance of `libassert` and I hope to get this working!_
