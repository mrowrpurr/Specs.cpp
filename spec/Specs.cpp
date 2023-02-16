#include <Spec/Autorun.h>
#include <snowhouse/snowhouse.h>

using namespace Spec;
using namespace snowhouse;

Describe("Any possible way of getting the test results!") {
    it("can get both failing and passing results from a test run", []() {

        AssertThat("69", Equals("420"));

        // throw "Butts!";

        // Types::SpecApp testApp;
        // testApp.Discovery.DiscoverTest("This is a passing test", []() {});
        // testApp.Discovery.DiscoverTest("This is a failing test", []() { throw "Butts!"; });

        // AssertThat(testApp.Results.GetTotalTests(), Equals(2));
        // AssertThat(testApp.Results.GetTotalFailed(), Equals(1));
        // AssertThat(testApp.Results.GetTotalPassed(), Equals(1));

        // testApp.Run().get();

        // Assert that there are 2 Results!
        // Assert that the first Result is a success!
        // Assert that the second Result is a failure!
    });
}
