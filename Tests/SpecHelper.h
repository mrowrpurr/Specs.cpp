#pragma once

#include <Specs.h>
#include <Specs/Snowhouse.h>
#include <Specs/SpecReporterCollection.h>
#include <Specs/SpecSerialRunner.h>
#include <Specs/TestHelpers/TestSpecOutput.h>
#include <Specs/TestHelpers/TestSpecReporter.h>


using namespace std;
using namespace SpecsCpp;
using namespace SpecsCpp::TestHelpers;

#define code_block(...) std::make_unique<SpecCodeBlock>(function_pointer(__VA_ARGS__))
