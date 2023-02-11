#include <Spec.h>

test("something") { AssertThat(69, Equals(420)); }

testAsync("something", done) {
    AssertThat(69, Equals(420));
    // some async shit
    done(true);
}

#include <Spec/Internal/SpecStorage.h>

void test_fn(const std::string& description, std::function<void()> body) {
    //
}

void TestFunction(const std::string& description, std::function<void()> body) {
    std::cout << std::format("You registered a test function: {}", description) << std::endl;
    // std::cout << "Calling the body..." << std::endl;
    // body();
}

void TestGroup(const std::string& description, std::function<void()> body) {
    std::cout << std::format("You registered a test group: {}", description) << std::endl;
    std::cout << "LET US NOW EVALUATE IT TO GET THE CHILD TESTS" << std::endl;
    std::cout << "Calling the body..." << std::endl;
    body();
}

///////////////////////////////////////////////////////////////

/**
 * Basic helpers
 */

// Helper macros
#define __SPEC_MACRO_CONCAT_(x, y) x##y
#define __SPEC_MACRO_CONCAT(x, y) __SPEC_MACRO_CONCAT_(x, y)

/**
 * "Function runner"
 */

//! Lazy way to run arbitrary function on startup by providing a function.
struct FunctionRunner {
    FunctionRunner(std::function<void()> fn) { fn(); }
};

// Create a "FunctionRunner" which takes a std::function which is run immediately at runtime
#define __SPEC_MACRO_FUNCTIONRUNNER(count) \
    FunctionRunner __SPEC_MACRO_CONCAT(__specGroupDefinition, count)

/**
 * _TEST outer MACRO STUFF
 */

#define __SPEC_MACRO_CALLBACKFN_NAME(count) __SPEC_MACRO_CONCAT(__spec_test_Callback, count)
#define __SPEC_MACRO_REGISTER_AND_DEFINE_CALLBACK(description, count)               \
    inline void __SPEC_MACRO_CALLBACKFN_NAME(count)();                              \
    __SPEC_MACRO_FUNCTIONRUNNER(count){[]() {                                       \
        TestFunction(description, []() { __SPEC_MACRO_CALLBACKFN_NAME(count)(); }); \
    }};                                                                             \
    inline void __SPEC_MACRO_CALLBACKFN_NAME(count)
#define _test(description)                                              \
    __SPEC_MACRO_REGISTER_AND_DEFINE_CALLBACK(description, __COUNTER__) \
    ()

/**
 * _DESCRIBE outer MACRO STUFF
 */

#define __SPEC_MACRO_desribeFN_NAME(count) __SPEC_MACRO_CONCAT(__spec_test_Callback, count)
#define __SPEC_MACRO_REGISTER_AND_DEFINE_desribe(description, count)                     \
    inline void __SPEC_MACRO_desribeFN_NAME(count)();                                    \
    __SPEC_MACRO_FUNCTIONRUNNER(count                                                    \
    ){[]() { TestGroup(description, []() { __SPEC_MACRO_desribeFN_NAME(count)(); }); }}; \
    inline void __SPEC_MACRO_desribeFN_NAME(count)
#define _describe(description) __SPEC_MACRO_REGISTER_AND_DEFINE_desribe(description, __COUNTER__)()

/** test() inner macro */

#define __SPEC_MACRO_innerTest_FN_NAME(count) __SPEC_MACRO_CONCAT(__spec_test_Callback, count)
#define __SPEC_MACRO_REGISTER_AND_DEFINE_innerTest_(description, count)                     \
    inline void __SPEC_MACRO_innerTest_FN_NAME(count)();                                    \
    __SPEC_MACRO_FUNCTIONRUNNER(count                                                       \
    ){[]() { TestGroup(description, []() { __SPEC_MACRO_innerTest_FN_NAME(count)(); }); }}; \
    inline void __SPEC_MACRO_innerTest_FN_NAME(count)
#define test(description) __SPEC_MACRO_REGISTER_AND_DEFINE_innerTest_(description, __COUNTER__)()

/** describe() inner macro */

/** EXAMPLE: */

#define test(description) if (description)

_describe("this is a describe block") {
    test("something") {
        // use dog
    }
}

_test("the macro test!") { std::cout << "THE MACRO DEFINED TEST RAN!" << std::endl; }

int main() {
    TestFunction("Defined in main()", []() {
        std::cout << "STDOUT from the test defined in main()" << std::endl;
    });
    //
    auto& storage = Spec::Internal::SpecStorage::GetSingleton();
}
