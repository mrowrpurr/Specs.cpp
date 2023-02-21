#include <Specs/CLI.h>
#include <Specs/DSL/Components/Functions/DefineTest.h>
#include <Specs/DSL/Components/Functions/DefineTestGroup.h>
#include <Specs/ExceptionHandlers/FallbackExceptionHandler.h>
#include <Specs/Reporters/OneLineReporter.h>
#include <Specs/Runners/QueueRunner.h>

constexpr auto DefineTest = [](auto&&... args) {
    Specs::DSL::Components::Functions::DefineTest(std::forward<decltype(args)>(args)...);
};

constexpr auto DefineTestGroup = [](auto&&... args) {
    Specs::DSL::Components::Functions::DefineTestGroup(std::forward<decltype(args)>(args)...);
};

int main(int argc, char** argv) {
    Specs::CLI cli;

    // Get the application
    auto app = cli.GetApplication();

    // Get the registry for registering test cases
    auto registry = app->GetRegistry();

    // Add an exception handler
    app->AddExceptionHandler<Specs::ExceptionHandlers::FallbackExceptionHandler>();

    // Add a reporter
    app->AddReporter<Specs::Reporters::OneLineReporter>();

    // Setup the runner
    app->SetRunner<Specs::Runners::QueueRunner>();

    // Set the global test group to this application's root test group
    Specs::SpecGlobalScope::Get().SetGlobalGroup(registry->GetRootTestGroup());

    // Change the "full description" separator for test descriptions
    Specs::SpecGlobalScope::Get().SetTestDescriptionSeparator(" > ");

    // Register test cases
    DefineTest("Passing test", [](auto) {});
    DefineTest("Failing test", [](auto) { throw std::runtime_error("This test failed!"); });
    DefineTestGroup("This is a test group", []() {
        DefineTest("child Passing test", [](auto) {});
        DefineTest("child Failing test", [](auto) { throw std::runtime_error("child This test failed!"); });
        DefineTestGroup("This is a child child test group", []() {
            DefineTest("grandchild Passing test", [](auto) {});
            DefineTest("grandchild Failing test", [](auto) {
                throw std::runtime_error("grandchild This test failed!");
            });
        });
    });

    // Run!
    cli.Run(argc, argv);
}
