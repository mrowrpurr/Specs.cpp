# 📋 Shared Code Templates

[TOC]

Sometimes you may find yourself writing the same code in your `Setup` and/or `Teardown` for many test groups.

In these scenarios, it may be useful to create a shared code template.

# What is a template?

A template is a sharable group of:

- `Setup` code
- `Teardown` code
- `OneTimeSetup` code
- `OneTimeTeardown` code
- `Test` code
- and even nested group code
  - (_e.g. defined using `TestGroup`, `StartTestGroup`, or `Describe`_)

# Defining Templates

There are a few available syntax options for defining templates:

- `#define SPEC_TEMPLATE Template_Name` 
- `TestTemplate("Template Name")`/`EndTestTemplate()`
- `StartTestTemplate("Template Name")`/`EndTestTemplate()`

## #define SPEC_TEMPLATE Template_Name

This is a great option for defining a templates in their own isolated files (_and it's my personal favorite!_).

```cpp
#define SPEC_TEMPLATE My_Template_Name

// Important: the name of the template will be "My Template Name" (with spaces)

#include <Specs.h>

// Anything here will be a part of the template!
// 
// Setup, Teardown, Test, Groups, etc.
```

> Note: when using `#define SPEC_TEMPLATE`, the name of the spec template **has underscores removed**.

## TestTemplate() / EndTestTemplate()

`TestTemplate` allows you to define a template anywhere in your code.

```cpp
#define SPEC_FILE My_Spec_File

#include <Specs.h>

// ... (normal spec code can go here) ...

TestTemplate("My Template Name");

// Anything here will be a part of the template!
// 
// Setup, Teardown, Test, Groups, etc.

EndTestTemplate();

// ... (normal spec code can go here) ...
```

> Don't forget to call `EndTestTemplate()`!

## StartTestTemplate() / EndTestTemplate()

`StartTestTemplate` allows you to define a template anywhere in your code.

The difference is that it supports a nested `{ ... }` syntax.

```cpp
#define SPEC_FILE My_Spec_File

#include <Specs.h>

// ... (normal spec code can go here) ...

StartTestTemplate("My Template Name") {

    // Anything here will be a part of the template!
    // 
    // Setup, Teardown, Test, Groups, etc.

} EndTestTemplate();

// ... (normal spec code can go here) ...
```

> Don't forget to call `EndTestTemplate()`!

## Load your templates before your tests!

If you define your templates in `.cpp` files, you'll need to make sure they are loaded before your tests.

Otherwise, your tests won't be able to find them!

In your `xmake.lua` or `CMakeLists.txt` file, make sure your template files are loaded before your test files.

For example, you might want to separate your templates into a `Templates` directory.

> Note: you can safely define your templates in `.h` files as well. They will only be defined once.

# Using Templates

This is the easiest part of all!

Simply use the `UseTemplate("Template Name")` function to use a template.

```cpp
#define SPEC_GROUP My_Spec_Group

#include <Specs.h>

// Feel free to include you template files at the top level here:
UseTemplate("My Template Name");

// ...

StartTestGroup("Some group of tests") {

  // Or include your template within a nested group:
  UseTemplate("My Template Name");

} EndTestGroup();
```

## Lambda syntax

If you are using lambda syntax inside of a `Describe` block, use the `use_template("Template Name")` function instead.

```cpp
#define SPEC_GROUP My_Spec_Group

#include <Specs.h>

Describe("Some group of tests") {

  // Include your template within a nested group:
  use_template("My Template Name");

  describe("A nested group", []() {

    // Or include your template within a nested child groups:
    use_template("My Template Name");

  });

} EndTestGroup();
```
