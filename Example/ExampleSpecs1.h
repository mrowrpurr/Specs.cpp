#include <chrono>

// #include "SpecHelper.h"

// #include <Spec.h>

// describe("something") {
//     it("whatever") { ... }
// }

// describe<Dog>() {
//     subject { .name = "Rover" }
//     it("whatever", auto dog) {

//     }
// }

// it("foo", [](){});

// it("foo") {

// }

// Specs {
//     test("sync: should pass", []() { std::cout << "Run sync function" << std::endl; });

//     test("async PASS", [](std::promise<bool>& done) {
//         std::cout << "Run async function, waiting..." << std::endl;
//         std::this_thread::sleep_for(std::chrono::seconds(4));
//         std::cout << "Done waiting!" << std::endl;
//         done.set_value(true);
//     });

//     test("async FAIL", [](std::promise<bool>& done) {
//         std::cout << "Run async function, waiting..." << std::endl;
//         std::this_thread::sleep_for(std::chrono::seconds(4));
//         std::cout << "Done waiting!" << std::endl;
//         done.set_value(false);
//     });

//     test("async Unexpected Error", [](std::promise<bool>& done) {
//         std::cout << "Run async function, waiting..." << std::endl;
//         std::this_thread::sleep_for(std::chrono::seconds(10));
//         throw "Boooom!";
//     });

//     // test("foo bar", {"tag", "tag"});

//     // ONE WHICH NEVER throws OR satisfies the promise (setup a TIMEOUT)

//     // test("async", [](std::function<void()> done) { done(); });

//     // test("ONE something not even in a group!", []() {});

//     // describe("ONE Some group of tests", []() {
//     //     it("ONE should pass", []() {});
//     //     it("ONE should fail", []() { throw "KABOOM!"; });
//     // });
// }
