#pragma once

#include "SpecHelper.h"

Test("Run passing test") {
    auto app = Spec::Types::SpecApp::CreateDefault();
    app->Discovery.DiscoverTest("PassingTest", []() {
        // Nothing, so this passes.
    });
    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(0));

    app->RunAndWait();

    AssertThat(app->Results.GetTotalTests(), Equals<unsigned int>(1));
}
