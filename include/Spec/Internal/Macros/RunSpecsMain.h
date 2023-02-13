#pragma once

#include "Spec/Internal/RunDefault.h"

#define RunSpecsMain                  \
    int main() {                      \
        Spec::Internal::RunDefault(); \
        return 0;                     \
    }
