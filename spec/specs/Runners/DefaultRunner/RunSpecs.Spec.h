#pragma once

#include <regex>

#include "SpecHelper.h"

Test("Run passing test") {
    auto app = Spec::Types::SpecApp::CreateDefault();
    app->Reporters.clear();
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
    auto app = Spec::Types::SpecApp::CreateDefault();
    app->Reporters.clear();
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
