#include <Specs/BDD.h>
#include <Specs/DSL/BDD.h>
#include <Specs/ExceptionHandlers/SnowhouseExceptionHandler.h>
#include <Specs/Setup.h>
#include <snowhouse/snowhouse.h>

// [ ] Hook up the exception catcher for runtime_error and all fallback errors
// [ ] Hook up the exception catcher for snowhouse
// [ ] Provide a helper for defining a main()
// [ ] Provide something you can call in your own main()
// [ ] DO NOT YET support FILTERS, we'll do that AFTER getting version 0.1 working (all the above)

using namespace snowhouse;

int main(int argc, char** argv) {
    Specs::CLI cli;
    Specs::Setup(cli);
    Specs::BDD(cli);

    cli.GetApplication()->AddExceptionHandler<Specs::ExceptionHandlers::SnowhouseExceptionHandler>();

    it("Passing test", []() {});
    it("Failing test", []() { throw std::runtime_error("This test failed!"); });
    describe("This is a test group", []() {
        it("child Passing test", []() {});
        it("child Failing test", []() { throw "Threw a string!"; });
        it("child Failing SNOWHOUSE test", []() { AssertThat(69, Equals(420)); });
        describe("This is a child child test group", []() {
            it("grandchild Passing test", []() {});
            it("grandchild Failing test", []() { throw std::runtime_error("grandchild This test failed!"); });
        });
    });

    cli.Run(argc, argv);
}
