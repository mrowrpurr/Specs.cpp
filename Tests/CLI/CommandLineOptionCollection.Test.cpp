#define SPEC_FILE CLI_CommandLineOptionCollection

#include <Specs/SpecCommandLineOption.h>
#include <Specs/SpecCommandLineOptionCollection.h>

#include "SpecHelper.h"  // IWYU pragma: keep

SpecGroups("CLI", "CommandLineOptionCollection");

Example("Add an option to a collection") {
    SpecCommandLineOptionCollection collection;
    AssertThat(collection.count(), Equals(0));

    SpecCommandLineOption option("o,option", "A cool option");
    collection.add(&option, false);

    AssertThat(collection.count(), Equals(1));
    AssertThat(collection.get_at(0), Equals(&option));

    collection.clear();

    AssertThat(collection.count(), Equals(0));
}
