# 📂 Project Layout

This is the recommended project layout for getting started with `Specs`.

```
📂 Specs
  📄 main.cpp
  📄 SpecHelper.h
  📄 FeatureOne.Spec.cpp
  📄 FeatureTwo.Spec.cpp
```

`main.cpp`

```cpp
// This file has the entrypoint for the Specs test runner
#include <Specs/Main.h>

// If you're using Snowhouse, add the following to configure its Specs adapter:
#include <Specs/Snowhouse/Setup.h>
```

`SpecHelper.cpp`

```cpp
// This file is intended to be a dumping ground for common code across all specs
#include <Specs.h>

// If you're using assertion library adapters, then include those adapters:
#include <Specs/Snowhouse.h>
#include <Specs/LibAssert.h>

// Add whatever other stuff you want to be available to all specs:
using namespace std;

void DoSomethingCommon() {
  // ...
}
```

`FeatureOne.Spec.cpp`

```cpp
// Define the name of this spec group
#define SPEC_GROUP Feature_One

// Simply include SpecHelper.h to get all the goodies needed for tests
#include "SpecHelper.h"

// Define your test stuff! Setups, Teardowns, and Tests!

Setup { /* ... */ }
Teardown { /* ... */ }

Test("Test One") {
  // ...
}
```
