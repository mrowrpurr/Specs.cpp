#pragma once

#include <Spec/Types/ISpecExceptionHandler.h>
#include <Spec/Types/SpecExtensionsRegistry.h>
#include <snowhouse/snowhouse.h>

namespace Spec::Types::ExceptionHandlers {

    class SnowhouseExceptionHandler : public Types::ISpecExceptionHandler {
    public:
        static void Register() {
            Spec::Types::SpecExtensionsRegistry::GetRegistry().RegisterExceptionHandler<SnowhouseExceptionHandler>();
        }

        bool HandleException(std::exception_ptr exception, SpecTestResult& result) {
            try {
                std::rethrow_exception(exception);
            } catch (const snowhouse::AssertionException& e) {
                result.SetFailure(e.what(), e.file(), e.line());
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}