#pragma once

#include <_Log_.h>
#include <function_pointer.h>
#include <void_pointer.h>

#include <cstdint>
#include <exception>
#include <functional>
#include <type_traits>

namespace SpecsCpp {

    struct ISpec;
    struct ISpecGroup;
    struct ISpecComponent;

    enum class SpecDataValueType {
        Boolean,
        Integer,
        UnsignedInteger,
        Float,
        String,
        Pointer,
    };

    struct ISpecDataValue {
        virtual ~ISpecDataValue() = default;

        virtual SpecDataValueType type() const = 0;

        virtual const char* key() const      = 0;
        virtual void        key(const char*) = 0;

        virtual bool         bool_value() const               = 0;
        virtual void         bool_value(bool)                 = 0;
        virtual int          int_value() const                = 0;
        virtual void         int_value(int)                   = 0;
        virtual unsigned int unsigned_int_value() const       = 0;
        virtual void         unsigned_int_value(unsigned int) = 0;
        virtual double       float_value() const              = 0;
        virtual void         float_value(double)              = 0;
        virtual const char*  string_value() const             = 0;
        virtual void         string_value(const char*)        = 0;
        virtual void*        pointer_value() const            = 0;
        virtual void         pointer_value(void*)             = 0;
        virtual void         pointer_value(IVoidPointer*)     = 0;

        virtual const char* to_string() = 0;

        virtual bool is_bool() const         = 0;
        virtual bool is_int() const          = 0;
        virtual bool is_unsigned_int() const = 0;
        virtual bool is_float() const        = 0;
        virtual bool is_string() const       = 0;
        virtual bool is_pointer() const      = 0;
    };

    struct ISpecDataValueCollection {
        using ForEachSpecDataFn = IFunctionPointer<void(ISpecDataValue*)>;

        virtual ~ISpecDataValueCollection() = default;

        virtual void            add(ISpecDataValue*)        = 0;
        virtual bool            has(const char* name) const = 0;
        virtual ISpecDataValue* get(const char* name) const = 0;

        virtual bool get_bool(const char* name) const {
            if (!has(name)) return false;
            return get(name)->bool_value();
        }
        virtual int get_int(const char* name) const {
            if (!has(name)) return 0;
            return get(name)->int_value();
        }
        virtual unsigned int get_unsigned_int(const char* name) const {
            if (!has(name)) return 0;
            return get(name)->unsigned_int_value();
        }
        virtual double get_float(const char* name) const {
            if (!has(name)) return 0.0;
            return get(name)->float_value();
        }
        virtual const char* get_string(const char* name) const {
            if (!has(name)) return nullptr;
            return get(name)->string_value();
        }
        virtual void* get_pointer(const char* name) const {
            if (!has(name)) return nullptr;
            return get(name)->pointer_value();
        }

        virtual void foreach_value(ForEachSpecDataFn*) const = 0;
        virtual void merge(ISpecDataValueCollection*)        = 0;
        virtual void clear()                                 = 0;

        void foreach(std::function<void(ISpecDataValue*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_value(callback.get());
        }
    };

    struct ISpecTagCollection {
        using ForEachTagFn = IFunctionPointer<void(const char*)>;

        virtual ~ISpecTagCollection() = default;

        virtual void add(const char*)                 = 0;
        virtual bool has(const char*) const           = 0;
        virtual void foreach_tag(ForEachTagFn*) const = 0;
        virtual void merge(ISpecTagCollection*)       = 0;
        virtual void clear()                          = 0;

        void foreach(std::function<void(const char*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_tag(callback.get());
        }
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
        virtual void          set_destructable(const char* name, bool destructable = true)   = 0;
        virtual bool          exists(const char* name) const                                 = 0;
        virtual IVoidPointer* get(const char* name) const                                    = 0;
        virtual void          foreach_variable(ForEachVariableFn*) const                     = 0;
        virtual void          clear()                                                        = 0;

        void foreach(std::function<void(IVoidPointer*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_variable(callback.get());
        }
    };

    struct ISpecComponent {
        virtual ~ISpecComponent()                                        = default;
        virtual ISpecGroup*               group() const                  = 0;
        virtual void                      set_group(ISpecGroup* group)   = 0;
        virtual ISpecDataValueCollection* data() const                   = 0;
        virtual ISpecTagCollection*       tags() const                   = 0;
        virtual SpecComponentType         type() const                   = 0;
        virtual bool                      skip() const                   = 0;
        virtual void                      mark_skipped(bool skip = true) = 0;
    };

    enum class RunResultStatus {
        Passed,
        Failed,
        NotRun,
        Timeout,
    };

    // TODO: change the spec() proprety to test() instead please :)
    struct ISpecRunResult {
        virtual ~ISpecRunResult()                 = default;
        virtual ISpecComponent* component() const = 0;
        virtual ISpecGroup*     group() const     = 0;
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

        virtual void run(ISpecComponent*, ISpecGroup*, ISpec*, ISpecRunResultCallbackFn*) = 0;
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

        template <typename T>
        T var(const char* name) const {
            return var(name)->as<T>();
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

        template <typename T>
        T* managed_var(const char* name, T* value) {
            variables()->set(name, new VoidPointer<T>(value), true);
            return value;
        }

        template <typename T>
        void managed_var(const char* name, T&& value) {
            variables()->set(name, new VoidPointer<T>(new T(std::forward<T>(value))), true);
        }

        template <typename T>
        T* unmanaged_var(const char* name, T* value) {
            variables()->set(name, new VoidPointer<T>(value), false);
            return value;
        }

        template <typename T>
        void unmanaged_var(const char* name, T&& value) {
            variables()->set(name, new VoidPointer<T>(new T(std::forward<T>(value))), false);
        }

        const char* var_text(const char* name) {
            char* value = var(name)->as<char*>();
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
        virtual void add_test(ISpec*)                                    = 0;
        virtual void add_setup(ISpecSetup*)                              = 0;
        virtual void add_teardown(ISpecTeardown*)                        = 0;
        virtual void add_one_time_setup(ISpecSetup*)                     = 0;
        virtual void add_one_time_teardown(ISpecTeardown*)               = 0;
        virtual void foreach_group(ForEachGroupFn*) const                = 0;
        virtual void foreach_test(ForEachSpecFn*) const                  = 0;
        virtual void foreach_setup(ForEachSetupFn*) const                = 0;
        virtual void foreach_teardown(ForEachTeardownFn*) const          = 0;
        virtual void foreach_one_time_setup(ForEachSetupFn*) const       = 0;
        virtual void foreach_one_time_teardown(ForEachTeardownFn*) const = 0;
        virtual void merge(ISpecGroup*)                                  = 0;

        void foreach_group(std::function<void(ISpecGroup*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_group(callback.get());
        }
        void foreach_test(std::function<void(ISpec*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_test(callback.get());
        }
        void foreach_setup(std::function<void(ISpecSetup*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_setup(callback.get());
        }
        void foreach_teardown(std::function<void(ISpecTeardown*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_teardown(callback.get());
        }
        void foreach_one_time_setup(std::function<void(ISpecSetup*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_one_time_setup(callback.get());
        }
        void foreach_one_time_teardown(std::function<void(ISpecTeardown*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_one_time_teardown(callback.get());
        }
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

        void foreach(std::function<void(ILocalSpecExceptionHandler*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_exception_handler(callback.get());
        }
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
        virtual void report_test_begin(ISpecGroup*, ISpec*)     = 0;
        virtual void report_setup(ISpecRunResult*)              = 0;
        virtual void report_test(ISpecRunResult*)               = 0;
        virtual void report_teardown(ISpecRunResult*)           = 0;
        virtual void report_test_result(ISpecRunResult*)        = 0;
        virtual void report_suite_result(ISpecSuiteRunResult*)  = 0;
    };

    struct ISpecReporterCollection {
        using ForEachReporterFn = IFunctionPointer<void(const char*, ISpecReporter*)>;

        virtual ~ISpecReporterCollection()                                = default;
        virtual void           add(const char*, ISpecReporter*)           = 0;
        virtual bool           has(const char* name) const                = 0;
        virtual ISpecReporter* get(const char* name) const                = 0;
        virtual void           foreach_reporter(ForEachReporterFn*) const = 0;

        void foreach(std::function<void(const char*, ISpecReporter*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_reporter(callback.get());
        }

        virtual void report_start()                            = 0;
        virtual void report_test_begin(ISpecGroup*, ISpec*)    = 0;
        virtual void report_setup(ISpecRunResult*)             = 0;
        virtual void report_test(ISpecRunResult*)              = 0;
        virtual void report_teardown(ISpecRunResult*)          = 0;
        virtual void report_test_result(ISpecRunResult*)       = 0;
        virtual void report_suite_result(ISpecSuiteRunResult*) = 0;
    };

    struct ISpecRunTextOptionList {
        using ForEachOptionFn = IFunctionPointer<void(const char*)>;

        virtual ~ISpecRunTextOptionList() = default;
        virtual bool any() const          = 0;
        virtual void add(const char*)     = 0;
        virtual void clear()              = 0;

        virtual void foreach_option(ForEachOptionFn*) const = 0;

        void foreach(std::function<void(const char*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_option(callback.get());
        }
    };

    // TODO: nah, make this composable, I kind like how static it is, but F that...
    struct ISpecRunOptions {
        virtual ~ISpecRunOptions()                                         = default;
        virtual bool          list_only() const                            = 0;
        virtual void          list_only(bool list_only)                    = 0;
        virtual std::uint32_t default_timeout_ms() const                   = 0;
        virtual void          default_timeout_ms(std::uint32_t timeout_ms) = 0;
        // TODO: we should have EXCLUDE options as well for every INCLUDE opion we currently have:
        virtual ISpecRunTextOptionList*   name_matchers() const             = 0;
        virtual ISpecRunTextOptionList*   test_name_matchers() const        = 0;
        virtual ISpecRunTextOptionList*   group_name_matchers() const       = 0;
        virtual ISpecRunTextOptionList*   regex_name_matchers() const       = 0;
        virtual ISpecRunTextOptionList*   regex_test_name_matchers() const  = 0;
        virtual ISpecRunTextOptionList*   regex_group_name_matchers() const = 0;
        virtual ISpecRunTextOptionList*   include_tags() const              = 0;
        virtual ISpecRunTextOptionList*   exclude_tags() const              = 0;
        virtual ISpecDataValueCollection* data() const                      = 0;
    };

    // TODO: what is this doing all the way out here?
    using ISpecSuiteRunResultCallbackFn = IFunctionPointer<void(ISpecSuiteRunResult*)>;

    struct ISpecRunner {
        virtual ~ISpecRunner() = default;
        virtual void
        run(ISpecGroup*, ISpecReporterCollection*, ISpecRunOptions* options,
            ISpecSuiteRunResultCallbackFn*) = 0;
    };

    struct ISpecRunnerCollection {
        using ForEachRunnerFn = IFunctionPointer<void(const char*, ISpecRunner*)>;

        virtual ~ISpecRunnerCollection()                            = default;
        virtual void         add(const char*, ISpecRunner*)         = 0;
        virtual bool         has(const char* name) const            = 0;
        virtual ISpecRunner* get(const char* name) const            = 0;
        virtual void         foreach_runner(ForEachRunnerFn*) const = 0;

        void foreach_runner(std::function<void(const char*, ISpecRunner*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_runner(callback.get());
        }
    };

    struct ISpecEnvironment {
        virtual ~ISpecEnvironment()                                                    = default;
        virtual ISpecGroup*                           root_group() const               = 0;
        virtual ILocalSpecExceptionHandlerCollection* local_exception_handlers() const = 0;
        virtual ISpecRunnerCollection*                runners() const                  = 0;
        virtual ISpecReporterCollection*              reporters() const                = 0;
        virtual void
        run(ISpecRunner*, ISpecReporterCollection*, ISpecRunOptions*,
            ISpecSuiteRunResultCallbackFn*) = 0;
    };

    struct ISpecApplication;

    struct ISpecCommandLineOption {
        using OnCommandLineOptionFn =
            IFunctionPointer<void(ISpecCommandLineOption*, ISpecApplication*)>;

        virtual ~ISpecCommandLineOption()                                        = default;
        virtual const char*            flags() const                             = 0;
        virtual void                   set_flags(const char*)                    = 0;
        virtual const char*            description() const                       = 0;
        virtual void                   set_description(const char*)              = 0;
        virtual bool                   is_list() const                           = 0;
        virtual void                   mark_list(bool list = true)               = 0;
        virtual bool                   is_required() const                       = 0;
        virtual void                   mark_required(bool required = true)       = 0;
        virtual OnCommandLineOptionFn* option_callback() const                   = 0;
        virtual void on_option(OnCommandLineOptionFn*, bool destructable = true) = 0;
    };

    struct ISpecCommandLineOptionCollection {
        using ForEachOptionFn = IFunctionPointer<void(ISpecCommandLineOption*)>;

        virtual ~ISpecCommandLineOptionCollection()                                = default;
        virtual void add(ISpecCommandLineOption* option, bool destructable = true) = 0;
        virtual ISpecCommandLineOption* get_at(std::uint32_t index) const          = 0;
        virtual std::uint32_t           count() const                              = 0;
        virtual void                    clear()                                    = 0;
        virtual void                    foreach_option(ForEachOptionFn*) const     = 0;

        void foreach(std::function<void(ISpecCommandLineOption*)> fn) const {
            auto callback = unique_function_pointer(fn);
            this->foreach_option(callback.get());
        }
    };

    struct ISpecApplication {
        virtual ~ISpecApplication()                                           = default;
        virtual int                               main(int argc, char** argv) = 0;
        virtual ISpecCommandLineOptionCollection* options() const             = 0;
        virtual ISpecEnvironment*                 environment()               = 0;
    };
}
