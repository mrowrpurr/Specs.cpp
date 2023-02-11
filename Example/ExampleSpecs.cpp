#include <Spec.h>

using namespace Spec;

Specs {
    test("something not even in a group!", []() {});

    describe("Some group of tests", []() {
        it("should pass", []() {});
        it("should fail", []() { throw "KABOOM!"; });
    });
}
