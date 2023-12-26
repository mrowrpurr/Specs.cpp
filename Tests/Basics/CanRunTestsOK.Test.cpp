#define SPEC_FILE Basics_Can_Run_Tests_OK

#include "TestHelper.h"  // IWYU pragma: keep

TestGroup("Basics");
ChildTestGroup("Can Run Tests OK");

#define code_block(...) std::make_unique<SpecCodeBlock>(function_pointer(__VA_ARGS__))

AsyncTest("Run one failing test") {
    //
    auto group     = SpecGroup("My Group");
    auto test      = SpecTest(&group, "My Test", code_block([]() { throw "KABOOM"; }));
    auto reporter  = MockTestReporter();
    auto reporters = SpecReporterCollection();
    reporters.add("mock", &reporter);

    auto callback = unique_function_pointer([&](ISpecSuiteRunResult* result) {
        //
        // AssertThat(result->failed(), Equals(1));
        _Log_("CALLBACK called!");

        auto testResult = reporter.test_result("My Group > My Test");
        // AssertThat(testResult->message(), Equals("KABOOM???"));

        done();
    });

    auto runner = SpecSerialRunner();
    runner.run(&group, &reporters, nullptr, callback.get());
    _Log_("AFTER RUN");
}

// void run(
//     ISpecGroup* group, ISpecReporterCollection* reporters, ISpecRunOptions* options,
//     ISpecSuiteRunResultCallbackFn* callback