#pragma once

#include "SpecHelper.h"

Test("Run passing test") {
    auto app = SpecApp();

    app->Discovery.DiscoverTest("PassingTest", []() {
        // Nothing, so this passes.
    });

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(0));

    app->RunAndWait();

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(1));
    AssertThat(app->Results.GetTotalPassed(), Equals<unsigned int>(1));
    AssertThat(app->Results.GetTotalFailed(), Equals<unsigned int>(0));
}

Test("Run failing test") {
    auto app = SpecApp();

    app->Discovery.DiscoverTest("FailingTest", []() { AssertThat(69, Equals(420)); });

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(0));

    app->RunAndWait();

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(1));
    AssertThat(app->Results.GetTotalPassed(), Equals<unsigned int>(0));
    AssertThat(app->Results.GetTotalFailed(), Equals<unsigned int>(1));
    AssertThat(
        app->Results.GetRoot()->GetTests()[0]->GetFailureMessage(), MatchesRegex("Expected: equal to 420", "Actual: 69")
    );
}

Test("Using the DSL") {
    auto app = SpecApp([]() {
        describe("Group of tests", []() {
            it("should pass", []() { AssertThat(69, Equals(69)); });
            it("should fail", []() { AssertThat(69, Equals(420)); });
        });
    });
    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(0));

    app->RunAndWait();

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(2));
    AssertThat(app->Results.GetTotalPassed(), Equals<unsigned int>(1));
    AssertThat(app->Results.GetTotalFailed(), Equals<unsigned int>(1));
    AssertThat(
        app->Results.GetRoot()->GetTests()[1]->GetFailureMessage(), MatchesRegex("Expected: equal to 420", "Actual: 69")
    );
}
