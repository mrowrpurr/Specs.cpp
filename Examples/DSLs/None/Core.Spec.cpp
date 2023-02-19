// #include <Specs/DSL/Components/Functions/DefineTest.h>
#include <Specs/Application.h>
#include <Specs/DSL/Components/Functions/Print.h>
#include <Specs/Reporters/DebugReporter.h>
#include <Specs/Runners/DefaultRunner.h>
#include <Specs/SpecTestCaseParam.h>

constexpr auto Print = [](auto&&... args) { Specs::DSL::Components::Functions::Print(args...); };

int main() {
    Specs::Application app;
    app.SetRunner<Specs::Runners::DefaultRunner>();
    app.AddReporter<Specs::Reporters::DebugReporter>();
    auto registry = app.GetRegistry();
    registry->RegisterTestCase("This is my test", [](std::shared_ptr<Specs::SpecTestCaseParam> param) {
        Print("This is from inside the test!");
    });
    return 0;
}