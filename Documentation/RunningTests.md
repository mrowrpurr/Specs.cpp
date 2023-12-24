# 🏃‍♀️ Running Tests

[TOC]

It's time to run your tests!

> _This assumes that you have completed the steps outlines in:_
> - ⬇️ _[Installing Specs](Installing.md)_
> - ✏️ _[Writing Tests](WritingTests.md)_
>
> You might also be interested in using the recommended 📂 [Project Layout](ProjectLayout.md).

# Specs executable project

You should already have a binary/executable target in your `xmake` or `CMake`/`vcpkg` project.

## &lt;Specs/Main.h&gt;

You should already have a `.cpp` file in your project which includes the `<Specs/Main.h>` header file.

> ℹ️ **Reminders**
>
> - The `<Specs/Main.h>` header file includes a `main()` function which runs your tests.
> - The `<Specs/Main.h>` header should only be included ONCE in your project.
>   - _e.g. you may want to have a `main.cpp` which includes `<Specs/Main.h>`_
>
> And if you're using `snowhouse`, the `<Specs/Snowhouse/Setup.h>` should also only be included ONCE in your project.

# Run executable project

Simpy run your project's executable target!

## Running tests

By default, the executable will run any tests defined in your executable's project.

If there are none, it will print `No tests found.` and print the command line options.

If tests are found, it will run them!

> Return Codes
> 
> - `1` response code will be returned if any tests fail
> - `0` response code will be returned if all tests pass OR if no tests were found

## Help documentation

To view a list of the currently supported command-line arguments, run your executable with the `/-h--help` option.

The following is an example of the help documentation:

```
Specs.cpp command line options
Usage:
  Specs.cpp [OPTION...]

  -n, --name arg           Filter name of test/group to run
  -s, --spec arg           Filter name of test to run
  -g, --group arg          Filter name of group to run
  -r, --pattern arg        Regex pattern filter of test/group to run
      --spec-pattern arg   Regex pattern filter of test to run
      --group-pattern arg  Regex pattern filter of group to run
  -l, --list               List all tests and groups
      --dll arg            Load tests from shared library (--dll,--so)
  -t, --timeout arg        Timeout in milliseconds for each test
  -h, --help               Print usage
```

> **Note:** the above might not be up-to-date. Run your executable with the `/-h--help` option to see the latest help documentation.

# Command-Line Options

To learn more about using command-line options, see ▶️ [Command-Line Interface](CLI.md).

# Test runners

By default, `Specs` uses a test runner which runs all tests in the order that they were defined.

To learn more about the available test runners (_or how to make your own_), see 🏎️ [Test Runners](TestRunners.md).

# Test reporters

By default, `Specs` uses a test reporter which prints test results to the console.

To learn more about the available test reporters (_or how to make your own_), see 📰 [Test Reporters](TestReporters.md).
