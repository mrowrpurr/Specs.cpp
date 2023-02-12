#include <Spec.h>
#include <Spec/Main.h>

using namespace Spec;

Test("top-level test") { Print("Hi from top-level test!"); }

Describe("top-level-describe") {
    it("inside top-level describe", []() { Print("this is inside top level describe"); });
}

Specs {
    describe("Dog", []() {
        it("barks", []() { Print("THIS IS THE BODY OF THE DOG TEST"); });
        describe("Certain type of dog", []() {
            it("Does certain thing", []() { Print("THIS IS THE BODY OF THE CAT TEST"); });
        });
    });
}
