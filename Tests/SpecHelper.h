#pragma once

#include <Specs.h>
#include <Specs/Snowhouse.h>
#include <Specs/SpecReporterCollection.h>
#include <Specs/SpecSerialRunner.h>
#include <Specs/TestHelpers/TestFakeReporter.h>

#include <fakeit/standalone/fakeit.hpp>

using namespace SpecsCpp;
using namespace SpecsCpp::TestHelpers;
using namespace fakeit;

#define code_block(...) std::make_unique<SpecCodeBlock>(function_pointer(__VA_ARGS__))
