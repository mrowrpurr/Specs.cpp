#pragma once

// TODO: make this all nice, neat, and tidy - it's a quickly done mess right now (WIP)

#define __SpecsHack__CONCAT_HELPER(a, b) a##b
#define __SpecsHack__CONCAT(a, b) __SpecsHack__CONCAT_HELPER(a, b)
#ifndef __SpecsHack_UniqueCppFileValue
    #ifdef spec_name
        #define __SpecsHack_UniqueCppFileValue \
            __SpecsHack__CONCAT(__SpecsHack_VariableX_, spec_name)
    #else
        #define __SpecsHack_UniqueCppFileValue __SpecsHack_VariableX
    #endif
#endif

#include <Specs/DSL/BDD.h>

#if __has_include(<snowhouse/snowhouse.h>)
    #include <snowhouse/snowhouse.h>
using namespace snowhouse;
    #define Assert "Do not use Assert::That"
#endif

namespace Specs::HacksPendingSpecsCppLibraryCompletion {
    extern std::vector<std::function<void()>> SpecDefinitionBodies;

    struct CollectSpecDefinitionBody {
        CollectSpecDefinitionBody(std::function<void()> body);
    };
}

#define __SpecsHack_Macro_Concat_(x, y) x##y
#define __SpecsHack_Macro_Concat(x, y) __SpecsHack_Macro_Concat_(x, y)
#define __SpecsHack_Macro_Unique(token, count) \
    __SpecsHack_Macro_Concat(token, __SpecsHack_Macro_Concat(__SpecsHack_UniqueCppFileValue, count))

#define __SpecsHack_Macro_LambdaCollector(count)                            \
    Specs::HacksPendingSpecsCppLibraryCompletion::CollectSpecDefinitionBody \
    __SpecsHack_Macro_Concat(__SpecsHack_UniqueCppFileValue, count)

#define __SpecsHack_Macro_CollectSpecs(count)                     \
    inline void __SpecsHack_Macro_Unique(CollectSpecs, count)();  \
    __SpecsHack_Macro_LambdaCollector(count                       \
    ){[]() { __SpecsHack_Macro_Unique(CollectSpecs, count)(); }}; \
    inline void __SpecsHack_Macro_Unique(CollectSpecs, count)()

#define Tests __SpecsHack_Macro_CollectSpecs(__COUNTER__)

#define __SpecsHack_Macro_DefineDescribe(description, count)                                \
    inline void __SpecsHack_Macro_Unique(DefineDescribe, count)();                          \
    __SpecsHack_Macro_LambdaCollector(count){[]() {                                         \
        describe(description, []() { __SpecsHack_Macro_Unique(DefineDescribe, count)(); }); \
    }};                                                                                     \
    inline void __SpecsHack_Macro_Unique(DefineDescribe, count)()

#define Describe(description) __SpecsHack_Macro_DefineDescribe(description, __COUNTER__)
