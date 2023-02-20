#include <Specs/CLI.h>
#include <Specs/ExceptionHandlers/FallbackExceptionHandler.h>

int main(int argc, char** argv) {
    Specs::CLI cli;

    // Get the application
    auto app = cli.GetApplication();

    // Get the registry for registering test cases
    auto registry = app->GetRegistry();

    // Add an exception handler
    app->AddExceptionHandler<Specs::ExceptionHandlers::FallbackExceptionHandler>();

    // Register some test cases (without DSL)
    registry->RegisterTestCase("Top-level test!", [](std::shared_ptr<Specs::SpecTestCaseParam>) {
        Print("YOU RAN THE EXAMPLE PASSING SPEC");
    });
    auto group = registry->RegisterTestGroup("THIS IS A GROUP OF TESTS");
    registry->RegisterTestCase("Test in group 1: ONE", group, [](std::shared_ptr<Specs::SpecTestCaseParam>) {
        Print("YOU RAN spec 1 in group 1");
    });
    registry->RegisterTestCase("Test in group 1: TWO", group, [](std::shared_ptr<Specs::SpecTestCaseParam>) {
        throw "This blow up!";
    });

    // Run!
    cli.Run(argc, argv);
}
