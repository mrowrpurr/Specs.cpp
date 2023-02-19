#pragma once

#include "Spec/Types/SpecMain.h"

#define RunSpecsMain                                       \
    int main() {                                           \
        auto result = Spec::Types::SpecMain::RunDefault(); \
        Print("EXIT CODE: {}", result);                    \
        return result;                                     \
    }
