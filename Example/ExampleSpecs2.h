#include "SpecHelper.h"

Specs {
    test("TWO something not even in a group!", []() {});

    describe("TWO Some group of tests", []() {
        it("TWO should pass", []() {});
        it("TWO should fail", []() { throw "KABOOM!"; });
    });
}
