#include <Specs/BDD.h>
#include <Specs/Setup.h>

int main(int argc, char** argv) {
    Specs::CLI cli;
    Specs::Setup(cli);
    Specs::BDD(cli);

    it("Passing test", []() {});
    it("Failing test", []() { throw std::runtime_error("This test failed!"); });
    describe("This is a test group", []() {
        it("child Passing test", []() {});
        it("child Failing test", []() { throw std::runtime_error("child This test failed!"); });
        describe("This is a child child test group", []() {
            it("grandchild Passing test", []() {});
            it("grandchild Failing test", []() { throw std::runtime_error("grandchild This test failed!"); });
        });
    });

    cli.Run(argc, argv);
}
