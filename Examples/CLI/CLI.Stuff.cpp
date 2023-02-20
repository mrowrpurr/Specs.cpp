#include <Specs/CLI.h>

int main(int argc, char** argv) {
    Specs::CLI cli;
    auto       registry = cli.GetApplication()->GetRegistry();
    registry->RegisterTestCase("Top-level test!", [](std::shared_ptr<Specs::SpecTestCaseParam>) {
        //
        Print("YOU RAN THE EXAMPLE PASSING SPEC");
    });
    auto group = registry->RegisterTestGroup("THIS IS A GROUP OF TESTS");
    registry->RegisterTestCase("Test in group: ONE", group);
    registry->RegisterTestCase("Test in group: TWO", group);
    cli.Run(argc, argv);
}
