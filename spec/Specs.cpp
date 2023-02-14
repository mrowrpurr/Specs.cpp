#include <Spec/Autorun.h>

using namespace Spec;

Describe("Any possible way of getting the test results!") {
    it("can get both failing and passing results from a test run", []() {
        // Arrange
        auto context  = SpecContext{};
        auto session  = SpecSession{context};
        auto reporter = std::make_shared<Reporters::SimpleReporter>();
        session.AddReporter(reporter);
        auto discovery = context.GetDiscovery();
        auto runner    = Runners::SimpleRunner{};
        auto promise   = std::promise<void>{};
        discovery.DiscoverTest("A passing test", []() {});
        discovery.DiscoverTest("A failing test", []() { throw "Failure!"; });

        // Negation Assertions
        // if (session.GetResults().size() > 0) throw "Expected no results, but there were some";

        // Act
        runner.RunSpecs(promise, session);

        // Assert
        // if (session.GetResults().size() == 0) throw "Expected results, but there were none <------";
    });
}
