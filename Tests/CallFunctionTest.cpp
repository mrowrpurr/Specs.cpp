#define SPEC_FILE CallFunctionTest

#include <Specs.h>

// 1. using header
#include <Specs/v3/SpecsApplication.h>

// 2. using module

Test("Call function in Specs.Application") {
    //
    auto functionResult = Specs::v3::SayHello();
}
