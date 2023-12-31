#define SPEC_FILE Basics_Can_Run_Tests_OK

#include "SpecHelper.h"  // IWYU pragma: keep

SpecGroups("Basics", "Can Run Tests OK");

Example("Run one failing test") {
    auto group = SpecGroup("My Group");
    auto test  = SpecTest(&group, "My Test", code_block([]() { throw "KABOOM"; }));
    group.add_test(&test);

    auto reporter  = TestFakeReporter();
    auto reporters = SpecReporterCollection();
    reporters.add("test", &reporter);

    auto callback = unique_function_pointer([&](ISpecSuiteRunResult* result) {
        AssertThat(result->failed(), Equals(1));
        auto testResult = reporter.test_result("My Group > My Test");
        AssertThat(testResult->message(), Equals("KABOOM"));
    });

    auto runner = SpecSerialRunner();
    runner.run(&group, &reporters, nullptr, callback.get());
}

Example("Run one passing test") {
    auto group = SpecGroup("My Group");
    auto test  = SpecTest(&group, "My Test", code_block([]() { /* nothing, passes */ }));
    group.add_test(&test);

    auto reporter  = TestFakeReporter();
    auto reporters = SpecReporterCollection();
    reporters.add("test", &reporter);

    auto callback = unique_function_pointer([&](ISpecSuiteRunResult* result) {
        AssertThat(result->passed(), Equals(1));
        auto testResult = reporter.test_result("My Group > My Test");
        AssertThat(testResult->message(), IsEmpty());
    });

    auto runner = SpecSerialRunner();
    runner.run(&group, &reporters, nullptr, callback.get());
}
