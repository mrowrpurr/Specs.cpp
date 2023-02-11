#include <Spec/Internal/SpecStorage.h>

//! Lazy way to run arbitrary function on startup by providing a function.
struct FunctionRunner {
    FunctionRunner(std::function<void()> fn) { fn(); }
};

// Helper macros
#define __SPEC_MACRO_CONCAT_(x, y) x##y
#define __SPEC_MACRO_CONCAT(x, y) __SPEC_MACRO_CONCAT_(x, y)

// Create a "FunctionRunner" which takes a std::function which is run immediately at runtime
#define __SPEC_MACRO_FUNCTIONRUNNER(count) \
    FunctionRunner __SPEC_MACRO_CONCAT(__specGroupDefinition, count)

// Setup for a callback function to be registered
#define __SPEC_MACRO_CALLBACKFN_NAME(count) \
    __SPEC_MACRO_CONCAT(__skyrimScriptingPluginCallback, count)

void TestFunction(const std::string& description, std::function<void()> body) {
    std::cout << std::format("You registered a test function: {}", description) << std::endl;
    // std::cout << "Calling the body..." << std::endl;
    // body();
}

#define __SPEC_MACRO_REGISTER_AND_DEFINE_CALLBACK(description, count)               \
    inline void __SPEC_MACRO_CALLBACKFN_NAME(count)();                              \
    __SPEC_MACRO_FUNCTIONRUNNER(count){[]() {                                       \
        TestFunction(description, []() { __SPEC_MACRO_CALLBACKFN_NAME(count)(); }); \
    }};                                                                             \
    inline void __SPEC_MACRO_CALLBACKFN_NAME(count)

#define test(description)                                               \
    __SPEC_MACRO_REGISTER_AND_DEFINE_CALLBACK(description, __COUNTER__) \
    ()

test("the macro test!") { std::cout << "THE MACRO DEFINED TEST RAN!" << std::endl; }

int main() {
    TestFunction("Defined in main()", []() {
        std::cout << "STDOUT from the test defined in main()" << std::endl;
    });
    //
    auto& storage = Spec::Internal::SpecStorage::GetSingleton();
}
