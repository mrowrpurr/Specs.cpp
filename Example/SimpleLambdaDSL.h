#include <Spec.h>

#include <format>
#include <iostream>

void Print(const std::string& text) { std::cout << text << std::endl; }

int main() {
    // Define straight up here in main, yp!
    Spec::Internal::_DefineSpecGroup_("Dog", []() {
        Spec::Internal::_DefineSpecTest_("barks", [](auto&) {
            Print("THIS IS THE BODY OF THE DOG TEST");
        });
        Spec::Internal::_DefineSpecGroup_("Certain type of dog", []() {
            Spec::Internal::_DefineSpecTest_("Does certain thing", [](auto&) {
                Print("THIS IS THE BODY OF THE CAT TEST");
            });
        });
    });

    // Run them straight up here in main, yo!
    Spec::Internal::SpecController::GetSingleton().RunSpecs();
}
