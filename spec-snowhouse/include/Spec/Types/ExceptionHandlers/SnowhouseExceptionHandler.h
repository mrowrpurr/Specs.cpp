#pragma once

#include <Spec/Types/ISpecExceptionHandler.h>
#include <Spec/Types/SpecExtensionsRegistry.h>
#include <snowhouse/snowhouse.h>

#include <format>
#include <iostream>

namespace Spec::Types::ExceptionHandlers {

    class SnowhouseExceptionHandler : public Types::ISpecExceptionHandler {
    public:
        static void Register() {
            Spec::Types::SpecExtensionsRegistry::GetRegistry().RegisterExceptionHandler<SnowhouseExceptionHandler>();
        }

        bool HandleException(std::exception_ptr exception) {
            Print("I AM SNOWHOUSE EXCEPTION HANDLER!");
            try {
                std::rethrow_exception(exception);
            } catch (const snowhouse::AssertionException& e) {
                std::cout << std::format("Snowhouse Exception: {} FILE:{} LINE:{}", e.what(), e.file(), e.line())
                          << std::endl;
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}