#pragma once

#include <function_pointer.h>

#include <cstdint>
#include <exception>  // <--- only for LOCAL Exception Handler implementation

namespace SpecsCpp {

    struct ISpec;
    struct ISpecGroup;
    struct ISpecComponent;

    struct ISpecKeyValue {
        virtual ~ISpecKeyValue()          = default;
        virtual const char* key() const   = 0;
        virtual const char* value() const = 0;
    };

    struct ISpecKeyValueCollection {
        using ForEachMetaDataFn = IFunctionPointer<void(ISpecKeyValue*)>;

        virtual ~ISpecKeyValueCollection()                             = default;
        virtual void        add(const char* key, const char* value)    = 0;
        virtual bool        has(const char* key) const                 = 0;
        virtual const char* get(const char* key) const                 = 0;
        virtual void        foreach_metadata(ForEachMetaDataFn*) const = 0;
    };

    enum class SpecComponentType {
        Group,
        Spec,
        Setup,
        Teardown,
    };

    struct ISpecComponent {
        virtual ~ISpecComponent()                                       = default;
        virtual ISpecGroup*              group() const                  = 0;
        virtual ISpecKeyValueCollection* meta_data() const              = 0;
        virtual SpecComponentType        type() const                   = 0;
        virtual bool                     skip() const                   = 0;
        virtual void                     mark_skipped(bool skip = true) = 0;
    };

    enum class RunResultStatus {
        Passed,
        Failed,
        NotRun,
        Timeout,
    };

    struct ISpecRunResult {
        virtual ~ISpecRunResult()                 = default;
        virtual ISpecComponent* component() const = 0;
        virtual ISpec*          spec() const      = 0;
        virtual RunResultStatus status() const    = 0;
        virtual const char*     message() const   = 0;
        virtual ISpecRunResult* copy() const      = 0;

        virtual const char* status_as_string() const {
            switch (status()) {
                case RunResultStatus::Passed:
                    return "Passed";
                case RunResultStatus::Failed:
                    return "Failed";
                case RunResultStatus::NotRun:
                    return "NotRun";
                case RunResultStatus::Timeout:
                    return "Timeout";
                default:
                    return "Unknown";
            }
        }
    };

    using ISpecRunResultCallbackFn = IFunctionPointer<void(ISpecRunResult*)>;

    struct ISpecCodeBlock {
        using SpecCodeBlockAsyncDoneFn = IFunctionPointer<void()>;
        using SpecCodeBlockBodyFn =
            IFunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>;

        virtual ~ISpecCodeBlock() = default;

        virtual bool is_async() const              = 0;
        virtual void mark_async(bool async = true) = 0;

        virtual std::uint32_t get_timeout_ms() const                   = 0;
        virtual void          set_timeout_ms(std::uint32_t timeout_ms) = 0;

        virtual SpecCodeBlockBodyFn* body() const                   = 0;
        virtual void                 set_body(SpecCodeBlockBodyFn*) = 0;

        virtual void run(ISpecComponent*, ISpec*, ISpecRunResultCallbackFn*) = 0;
    };

    struct ISpecHasCodeBlock {
        virtual ~ISpecHasCodeBlock()               = default;
        virtual ISpecCodeBlock* code_block() const = 0;
    };

    struct ISpecSetup : virtual public ISpecComponent, virtual public ISpecHasCodeBlock {
        virtual ~ISpecSetup() = default;
    };

    struct ISpecTeardown : virtual public ISpecComponent, virtual public ISpecHasCodeBlock {
        virtual ~ISpecTeardown() = default;
    };

    struct ISpecDocumented {
        virtual ~ISpecDocumented()                   = default;
        virtual const char* description() const      = 0;
        virtual const char* full_description() const = 0;
    };

    struct ISpecGroup : virtual public ISpecComponent, virtual public ISpecDocumented {
        using ForEachGroupFn    = IFunctionPointer<void(ISpecGroup*)>;
        using ForEachSpecFn     = IFunctionPointer<void(ISpec*)>;
        using ForEachSetupFn    = IFunctionPointer<void(ISpecSetup*)>;
        using ForEachTeardownFn = IFunctionPointer<void(ISpecTeardown*)>;

        virtual ~ISpecGroup()                                   = default;
        virtual void add_group(ISpecGroup*)                     = 0;
        virtual void add_spec(ISpec*)                           = 0;
        virtual void add_setup(ISpecSetup*)                     = 0;
        virtual void add_teardown(ISpecTeardown*)               = 0;
        virtual void foreach_group(ForEachGroupFn*) const       = 0;
        virtual void foreach_spec(ForEachSpecFn*) const         = 0;
        virtual void foreach_setup(ForEachSetupFn*) const       = 0;
        virtual void foreach_teardown(ForEachTeardownFn*) const = 0;
        virtual void merge(ISpecGroup*)                         = 0;
    };

    // TODO: add a built-in property for defining a test which should be SKIPPED (pending test)
    struct ISpec : virtual public ISpecComponent,
                   virtual public ISpecDocumented,
                   virtual public ISpecHasCodeBlock {
        virtual ~ISpec() = default;
    };

    // This cannot be implemented across DLL boundaries, it's only for LOCAL use witha LOCAL
    // ISpecEnvironment
    struct ILocalSpecExceptionHandler {
        struct IExceptionMessage {
            virtual const char* message() const = 0;
        };

        using LocalSpecExceptionFailureMessageCallbackFn =
            IFunctionPointer<void(IExceptionMessage*)>;

        virtual ~ILocalSpecExceptionHandler() = default;

        // This can only be implemented and run LOCALLY to the DLL that implements it
        // because these std:: types are not ABI compatible across DLL boundaries
        virtual bool handle_exception(
            std::exception_ptr*                         exception,
            LocalSpecExceptionFailureMessageCallbackFn* failureMessageCallback
        ) = 0;
    };

    using IExceptionHandler = ILocalSpecExceptionHandler;
    using IExceptionMessageCallbackFn =
        ILocalSpecExceptionHandler::LocalSpecExceptionFailureMessageCallbackFn;

    struct ILocalSpecExceptionHandlerCollection {
        using ForEachExceptionHandlerFn = IFunctionPointer<void(ILocalSpecExceptionHandler*)>;

        virtual ~ILocalSpecExceptionHandlerCollection()                          = default;
        virtual void register_exception_handler(ILocalSpecExceptionHandler*)     = 0;
        virtual void foreach_exception_handler(ForEachExceptionHandlerFn*) const = 0;
    };

    struct ISpecSuiteRunResult {
        virtual ~ISpecSuiteRunResult()          = default;
        virtual std::uint32_t passed() const    = 0;
        virtual std::uint32_t failed() const    = 0;
        virtual std::uint32_t not_run() const   = 0;
        virtual std::uint32_t timed_out() const = 0;
    };

    struct ISpecReporter {
        virtual ~ISpecReporter()                         = default;
        virtual void report_start()                      = 0;
        virtual void report_spec_begin(ISpec*)           = 0;
        virtual void report_setup(ISpecRunResult*)       = 0;
        virtual void report_spec(ISpecRunResult*)        = 0;
        virtual void report_teardown(ISpecRunResult*)    = 0;
        virtual void report_spec_result(ISpecRunResult*) = 0;
        virtual void report_suite(ISpecSuiteRunResult*)  = 0;
    };

    struct ISpecReporterCollection {
        using ForEachReporterFn = IFunctionPointer<void(ISpecReporter*)>;

        virtual ~ISpecReporterCollection()                                = default;
        virtual void           add(const char*, ISpecReporter*)           = 0;
        virtual bool           has(const char* name) const                = 0;
        virtual ISpecReporter* get(const char* name) const                = 0;
        virtual void           foreach_reporter(ForEachReporterFn*) const = 0;

        virtual void report_start()                      = 0;
        virtual void report_spec_begin(ISpec*)           = 0;
        virtual void report_setup(ISpecRunResult*)       = 0;
        virtual void report_spec(ISpecRunResult*)        = 0;
        virtual void report_teardown(ISpecRunResult*)    = 0;
        virtual void report_spec_result(ISpecRunResult*) = 0;
        virtual void report_suite(ISpecSuiteRunResult*)  = 0;
    };

    using ISpecSuiteRunResultCallbackFn = IFunctionPointer<void(ISpecSuiteRunResult*)>;

    struct ISpecRunner {
        // TODO: regex options too
        static auto constexpr DEFAULT_TIMEOUT_MS_OPTION_KEY             = "default_timeout_ms";
        static auto constexpr LIST_TEST_NAMES_OPTION_KEY                = "list";
        static auto constexpr DESCRIPTION_FILTER_OPTION_KEY             = "name";
        static auto constexpr SPEC_DESCRIPTION_FILTER_OPTION_KEY        = "spec";
        static auto constexpr GROUP_DESCRIPTION_FILTER_OPTION_KEY       = "group";
        static auto constexpr DESCRIPTION_REGEX_FILTER_OPTION_KEY       = "pattern";
        static auto constexpr SPEC_DESCRIPTION_REGEX_FILTER_OPTION_KEY  = "spec_patterm";
        static auto constexpr GROUP_DESCRIPTION_REGEX_FILTER_OPTION_KEY = "group_pattern";

        virtual ~ISpecRunner() = default;
        virtual void
        run(ISpecGroup*, ISpecReporterCollection*, ISpecKeyValueCollection* options,
            ISpecSuiteRunResultCallbackFn*) = 0;
    };

    struct ISpecRunnerCollection {
        using ForEachRunnerFn = IFunctionPointer<void(ISpecRunner*)>;

        virtual ~ISpecRunnerCollection()                            = default;
        virtual void         add(const char*, ISpecRunner*)         = 0;
        virtual bool         has(const char* name) const            = 0;
        virtual ISpecRunner* get(const char* name) const            = 0;
        virtual void         foreach_runner(ForEachRunnerFn*) const = 0;
    };

    struct ISpecEnvironment {
        virtual ~ISpecEnvironment()                                                    = default;
        virtual ISpecGroup*                           root_group() const               = 0;
        virtual ILocalSpecExceptionHandlerCollection* local_exception_handlers() const = 0;
        virtual ISpecRunnerCollection*                runners() const                  = 0;
        virtual ISpecReporterCollection*              reporters() const                = 0;
        virtual void
        run(ISpecRunner*, ISpecReporterCollection*, ISpecKeyValueCollection*,
            ISpecSuiteRunResultCallbackFn*) = 0;
    };
}
