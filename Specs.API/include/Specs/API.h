#pragma once

#include <_Log_.h>
#include <function_pointer.h>
#include <void_pointer.h>

#include <cstdint>
#include <exception>
#include <type_traits>

namespace SpecsCpp {

    struct ISpec;
    struct ISpecGroup;
    struct ISpecComponent;

    // TODO: rename to make clear that it's a string pair (or update to not be a string value)
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

    struct ISpecVariableCollection {
        using ForEachVariableFn = IFunctionPointer<void(IVoidPointer*)>;

        virtual ~ISpecVariableCollection() = default;
        virtual void          set(const char* name, IVoidPointer*, bool destructable = true) = 0;
        virtual void          unset(const char* name)                                        = 0;
        virtual bool          is_destructable(const char* name) const                        = 0;
        virtual bool          exists(const char* name) const                                 = 0;
        virtual IVoidPointer* get(const char* name) const                                    = 0;
        virtual void          foreach_variable(ForEachVariableFn*) const                     = 0;
        virtual void          clear()                                                        = 0;
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

    struct ISpecHasVariables {
        virtual ~ISpecHasVariables()                       = default;
        virtual ISpecVariableCollection* variables() const = 0;

        // Variable helpers:

        ISpecVariableCollection* vars() const { return variables(); }

        bool has_var(const char* name) const { return variables()->exists(name); }

        IVoidPointer* var(const char* name) const {
            if (!variables()->exists(name)) {
                _Log_("Variable '{}' does not exist", name);
                return nullptr;
            }
            return variables()->get(name);
        }

        template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        T var(const char* name) const {
            return *var(name)->as<T>();
        }

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        T var(const char* name) const {
            auto ptr = var(name);
            if (!ptr) return nullptr;
            return static_cast<T>(ptr->void_ptr());
        }

        template <typename T>
        T* var(const char* name, T* value, bool destructable = true) {
            variables()->set(name, new VoidPointer<T>(value), destructable);
            return value;
        }

        template <typename T>
        void var(const char* name, T&& value, bool destructable = true) {
            variables()->set(name, new VoidPointer<T>(new T(std::forward<T>(value))), destructable);
        }

        const char* var_text(const char* name) {
            char* value = var(name)->as<char>();
            return value ? value : nullptr;
        }

        const char* var_text(const char* name, const char* value) {
            char* copy = new char[strlen(value) + 1];

#ifdef _WIN32
            strcpy_s(copy, strlen(value) + 1, value);
#else
            strcpy(copy, value);
#endif

            variables()->set(name, new VoidPointer<char>(copy));
            return var_text(name);
        }
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

    struct ISpecGroup : virtual public ISpecComponent,
                        virtual public ISpecDocumented,
                        virtual public ISpecHasVariables {
        using ForEachGroupFn    = IFunctionPointer<void(ISpecGroup*)>;
        using ForEachSpecFn     = IFunctionPointer<void(ISpec*)>;
        using ForEachSetupFn    = IFunctionPointer<void(ISpecSetup*)>;
        using ForEachTeardownFn = IFunctionPointer<void(ISpecTeardown*)>;

        virtual ~ISpecGroup()                                            = default;
        virtual void add_group(ISpecGroup*)                              = 0;
        virtual void add_spec(ISpec*)                                    = 0;
        virtual void add_setup(ISpecSetup*)                              = 0;
        virtual void add_teardown(ISpecTeardown*)                        = 0;
        virtual void add_one_time_setup(ISpecSetup*)                     = 0;
        virtual void add_one_time_teardown(ISpecTeardown*)               = 0;
        virtual void foreach_group(ForEachGroupFn*) const                = 0;
        virtual void foreach_spec(ForEachSpecFn*) const                  = 0;
        virtual void foreach_setup(ForEachSetupFn*) const                = 0;
        virtual void foreach_teardown(ForEachTeardownFn*) const          = 0;
        virtual void foreach_one_time_setup(ForEachSetupFn*) const       = 0;
        virtual void foreach_one_time_teardown(ForEachTeardownFn*) const = 0;
        virtual void merge(ISpecGroup*)                                  = 0;
    };

    struct ISpec : virtual public ISpecComponent,
                   virtual public ISpecDocumented,
                   virtual public ISpecHasCodeBlock,
                   virtual public ISpecHasVariables {
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
        virtual ~ISpecReporter()                                = default;
        virtual void report_start()                             = 0;
        virtual void report_suite_begin(unsigned int specCount) = 0;
        virtual void report_spec_begin(ISpec*)                  = 0;
        virtual void report_setup(ISpecRunResult*)              = 0;
        virtual void report_spec(ISpecRunResult*)               = 0;
        virtual void report_teardown(ISpecRunResult*)           = 0;
        virtual void report_spec_result(ISpecRunResult*)        = 0;
        virtual void report_suite_result(ISpecSuiteRunResult*)  = 0;
    };

    struct ISpecReporterCollection {
        using ForEachReporterFn = IFunctionPointer<void(ISpecReporter*)>;

        virtual ~ISpecReporterCollection()                                = default;
        virtual void           add(const char*, ISpecReporter*)           = 0;
        virtual bool           has(const char* name) const                = 0;
        virtual ISpecReporter* get(const char* name) const                = 0;
        virtual void           foreach_reporter(ForEachReporterFn*) const = 0;

        virtual void report_start()                            = 0;
        virtual void report_spec_begin(ISpec*)                 = 0;
        virtual void report_setup(ISpecRunResult*)             = 0;
        virtual void report_spec(ISpecRunResult*)              = 0;
        virtual void report_teardown(ISpecRunResult*)          = 0;
        virtual void report_spec_result(ISpecRunResult*)       = 0;
        virtual void report_suite_result(ISpecSuiteRunResult*) = 0;
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
