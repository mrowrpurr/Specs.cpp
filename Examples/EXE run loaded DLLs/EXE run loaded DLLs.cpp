#include <Specs/ExceptionHandlers/CStringExceptionHandler.h>
#include <Specs/ExceptionHandlers/StdExceptionExceptionHandler.h>
#include <Specs/GlobalSpecEnvironment.h>
#include <Specs/LibraryLoader.h>
#include <Specs/SpecDebugReporter.h>
#include <Specs/SpecEnvironment.h>
#include <Specs/SpecReporterCollection.h>
#include <Specs/SpecSerialRunner.h>
#include <_Log_.h>

int         returnCode    = 0;
static auto specs         = SpecsCpp::SpecEnvironment();
static auto runner        = SpecsCpp::SpecSerialRunner();
static auto reporter      = SpecsCpp::SpecDebugReporter();
static auto reporters     = SpecsCpp::SpecReporterCollection();
static auto LibraryLoader = SpecsCpp::LibraryLoader(&specs);

void load_dll(std::string_view dllFilePath) {
    if (auto* group = LibraryLoader.load(dllFilePath)) {
        specs.root_group()->merge(group);
        _Log_("( Loaded library: {} )", dllFilePath);
    } else {
        _Log_("Failed to load library: {}", dllFilePath);
    }
}

void on_suite_run_result(SpecsCpp::ISpecSuiteRunResult* result) {
    _Log_(
        "passed={}, failed={}, not run={}, timed out={}", result->passed(), result->failed(),
        result->not_run(), result->timed_out()
    );
    if (result->failed() > 0) returnCode = 1;
}

static auto on_suite_run_result_fn = unique_function_pointer(on_suite_run_result);

int main() {
#ifdef _WIN32
    load_dll("Library with Specs 1.dll");
    load_dll("Library with Specs 2.dll");
#else
    load_dll("./libLibrary with Specs 1.so");  // TODO: check for dylib?
    load_dll("./libLibrary with Specs 2.so");
#endif

    reporters.add("debug", &reporter);
    runner.run(specs.root_group(), &reporters, nullptr, on_suite_run_result_fn.get());

    return returnCode;
}
