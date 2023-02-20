#include <Specs/CLI.h>

int main(int argc, char** argv) {
    Specs::CLI cli;

    // Get the registry for registering test cases
    auto registry = cli.GetApplication()->GetRegistry();

    // Register some test cases (without DSL)
    registry->RegisterTestCase("Top-level test!", [](std::shared_ptr<Specs::SpecTestCaseParam>) {
        //
        Print("YOU RAN THE EXAMPLE PASSING SPEC");
    });
    auto group = registry->RegisterTestGroup("THIS IS A GROUP OF TESTS");
    registry->RegisterTestCase("Test in group: ONE", group);
    registry->RegisterTestCase("Test in group: TWO", group);

    // Run!
    cli.Run(argc, argv);
}
