# ⬇️ Installing Specs

[TOC]

# xmake

## Basic Install

This is a barebones `Specs.cpp` installation with no assertion library integration.

With this setup, any `std::exception` (_or literal string_) thrown will be caught and displayed as a test failure message.

### xmake.lua

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("specs")

target("MySpecs")
    set_kind("binary")
    add_packages("specs")
    add_files("*.cpp")
```

## With Assertion Library Integration

We provide integrations for the `snowhouse` and `libassert` assertion libraries.

See [Create Custom Exception Handler](#create-custom-exception-handler) for more information on how to create your own custom exception handler.

### xmake.lua

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("specs")

-- For integration with snowhouse assertion library:
add_requires("vcpkg::snowhouse", "specs_snowhouse")

-- For integration with libassert assertion library:
add_requires("libassert_latest", { configs = { lowercase = true } })
add_requires("specs_libassert")

target("MySpecs")
    set_kind("binary")
    add_packages("specs")
    add_files("*.cpp")

    -- For integration with snowhouse assertion library:
    add_packages("vcpkg::snowhouse", "specs_snowhouse")

    -- For integration with libassert assertion library:
    add_packages("libassert_latest", "specs_libassert")
```

> _Note: as of 12/1/23 the `libassert` xmake package wasn't working for me, so I hosted `libassert_latest` on the `MrowrLib` xmake package registry which uses the latest version from GitHub and currently works for me._

For `snowhouse` or `libassert` integration, you need to "_bring your own_" version of the library. They are not automatic dependencies of the specs integration packages (_to not lock you into a specific version of these libraries_).

# vcpkg
