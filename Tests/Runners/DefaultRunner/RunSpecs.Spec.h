#include "SpecHelper.h"

TestGroup("Running Specs");

Test("passing test") {
    auto app = SpecApp([]() { it("should pass", []() { AssertThat(69, Equals(69)); }); });
    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(0));

    app->RunAndWait();

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(1));
    AssertThat(app->Results.GetTotalPassed(), Equals<unsigned int>(1));
    AssertThat(app->Results.GetTotalFailed(), Equals<unsigned int>(0));
}

Test("failing test") {
    auto app = SpecApp([]() { it("should fail", []() { AssertThat(69, Equals(420)); }); });
    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(0));

    app->RunAndWait();

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(1));
    AssertThat(app->Results.GetTotalPassed(), Equals<unsigned int>(0));
    AssertThat(app->Results.GetTotalFailed(), Equals<unsigned int>(1));
    AssertThat(
        app->Results.GetRoot()->GetTests()[0]->GetFailureMessage(), MatchesRegex("Expected: equal to 420", "Actual: 69")
    );
}

Test("multiple tests (passing and failing)") {
    auto app = SpecApp([]() {
        describe("IN THE DESC Group of tests", []() {
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
