#include "SpecHelper.h"

Specs {
    test("ONE something not even in a group!", []() {});

    describe("ONE Some group of tests", []() {
        it("ONE should pass", []() {});
        it("ONE should fail", []() { throw "KABOOM!"; });
    });
}
