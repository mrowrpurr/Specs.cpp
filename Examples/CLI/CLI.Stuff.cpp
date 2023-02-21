#include <Specs/CLI.h>
#include <Specs/DSL/Components/Functions/DefineTest.h>
#include <Specs/ExceptionHandlers/FallbackExceptionHandler.h>
#include <Specs/Reporters/OneLineReporter.h>
#include <Specs/Runners/QueueRunner.h>

constexpr auto DefineTest = [](auto&&... args) {
    Specs::DSL::Components::Functions::DefineTest(std::forward<decltype(args)>(args)...);
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

    // Register test cases
    DefineTest("Passing test", [](auto) { std::cout << "Hello, world from the test!!" << std::endl; });
    DefineTest("Failing test", [](auto) { throw std::runtime_error("This test failed!"); });

    // Run!
    cli.Run(argc, argv);
}
