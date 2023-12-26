_Almost_ ready for release 🎉


## TODO

- [ ] Write Specs for Specs 👓
- [ ] Rename `GlobalSpecGroup` (_it's more than groups now_) and make it (and `GlobalInterface`) nice for external consumption from DSL-makers
  - [ ] Extract the concept of data for 'next' component or spec into a structure
- [ ] Parameterized tests
- [ ] Parallel test runner
- [ ] If possible, add support/adapter for `BOOST_TEST`
- [ ] If possible, add support/adapter for GoogleTest's `EXPECT_THAT` and/or `ASSERT_THAT`
- [ ] If possible, add support/adapter for Catch2 assertions
- [ ] CLI options to include/exclude by:
  - [ ] tag (text or regex)
  - [ ] test name (text or regex)
  - [ ] group name (text or regex)
  - [ ] full test name with groups (text or regex)
  - [ ] file name (text or regex) **if possible**
- [ ] CLI option to glob for `.dll/.so/.dylib` files
- [ ] Provide example of programmatically providing those ^ filters, but from a custom entry point
  - _e.g. How I will likely want to do for my Skyrim test runner_
- [ ] **Maybe** provide a `Given`, `When`, `Then` syntax
- [ ] Bundle up the syntax options into simpler `#include`'s
  - [ ] A bit simpler to BYO syntax selection
  - [ ] Provide RSpec-ish `BeforeEach`/`It`
- [ ] Finish docs :)

---

<img src="Resources/Images/Logo_400.png" align="right">

# Specs <!-- omit in toc -->

> **Beautiful C++ Test Framework**
>
> - _Syntax is simple and configurable_
> - _Supports Asynchronous tests_
> - _Supports runnings tests from shared libraries_
> - _Supports any C++ assertion library_ (e.g. `snowhouse` or `libassert`)

---

# What?  <!-- omit in toc -->

C++ test framework with simple syntax which supports async tests.

```cpp
#define SPEC_GROUP My_Tests

#include <Specs.h>

Setup { /* Setup Code */ }
Teardown { /* Teardown Code */ }

Test("Some thing") {
    assert_that(69 == 420);
    AssertThat(69, Equals(420));
}

TestAsync("Slow thing") {
    // Do something slow...
    done();
}
```

# Documentation

https://specs.tools

# LICENSE

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```