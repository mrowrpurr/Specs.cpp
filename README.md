<img src="Resources/Images/Logo_400.png" align="right">

# Specs <!-- omit in toc -->

> **Beautiful C++ Test Framework**
>
> - _Syntax is simple and configurable_
> - _Supports asyncronous tests_
> - _Supports runnings tests from shared libraries_
> - _Supports any C++ assertion library_ (e.g. `snowhouse` or `libassert`)

---

# What?  <!-- omit in toc -->

C++ test framework with simple syntax which supports async tests.

```cpp
#define spec_name My_Tests

#include <Specs.h>

Setup { /* Setup Code */ }
Teardown { /* Teardown Code */ }

Test("Some thing") {
    assert(69 == 420);
    AssertThat(69, Equals(69));
}

TestAsync("Slow thing") {
    // Do something slow...
    done();
}
```

# Why?  <!-- omit in toc -->

1. I enjoy authoring testing frameworks.
2. I wanted very simple, readable syntax for tests.
3. I wanted to use existing assertion libraries.
4. I needed to write async tests.
5. I needed to be able to load and run tests from shared libraries.

> _I'm proud of the result and I hope you enjoy using it!_

# Table of Contents  <!-- omit in toc -->

- [Getting Started](#getting-started)
  - [Installation](#installation)
  - [Writing Tests](#writing-tests)
  - [Running Tests](#running-tests)

# Getting Started

This section documents how to quickly get started with `Specs`!

1. Installation
2. Writing Tests
3. Running Tests

## Installation

...

## Writing Tests

..

## Running Tests

