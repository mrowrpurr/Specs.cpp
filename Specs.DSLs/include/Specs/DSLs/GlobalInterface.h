#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

namespace SpecsCpp::DSLs::GlobalInterface {
    /* Template */

    inline void register_template_fn(std::string_view templateName, FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().register_template(
            templateName, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* Group */

    inline void register_group_fn(std::string_view description, FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().register_group(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* Test */

    inline void register_spec_fn(std::string_view description, FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().register_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_spec_fn(
        std::string_view description, FunctionPointer<void(SpecDone)> body
    ) {
        GlobalSpecGroup::instance().register_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_spec_fn(std::string_view description, FunctionPointer<void(ISpec*)> body) {
        GlobalSpecGroup::instance().register_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_spec_fn(
        std::string_view description, FunctionPointer<void(ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().register_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_spec_fn(
        std::string_view description, FunctionPointer<void(ISpecGroup*)> body
    ) {
        GlobalSpecGroup::instance().register_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_spec_fn(
        std::string_view description, FunctionPointer<void(ISpecGroup*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().register_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* Setup */

    inline void register_setup_fn(FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().register_setup(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_setup_fn(FunctionPointer<void(SpecDone)> body) {
        GlobalSpecGroup::instance().register_setup(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_setup_fn(FunctionPointer<void(ISpecComponent*, ISpec*)> body) {
        GlobalSpecGroup::instance().register_setup(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_setup_fn(FunctionPointer<void(ISpecComponent*, ISpec*, SpecDone)> body) {
        GlobalSpecGroup::instance().register_setup(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_setup_fn(FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*)> body
    ) {
        GlobalSpecGroup::instance().register_setup(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void register_setup_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().register_setup(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* Teardown */

    inline void register_teardown_fn(FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().register_teardown(std::make_unique<SpecCodeBlock>(std::move(body
        )));
    }

    inline void register_teardown_fn(FunctionPointer<void(SpecDone)> body) {
        GlobalSpecGroup::instance().register_teardown(std::make_unique<SpecCodeBlock>(std::move(body
        )));
    }

    inline void register_teardown_fn(FunctionPointer<void(ISpecComponent*, ISpec*)> body) {
        GlobalSpecGroup::instance().register_teardown(std::make_unique<SpecCodeBlock>(std::move(body
        )));
    }

    inline void register_teardown_fn(FunctionPointer<void(ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().register_teardown(std::make_unique<SpecCodeBlock>(std::move(body
        )));
    }

    inline void register_teardown_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*)> body
    ) {
        GlobalSpecGroup::instance().register_teardown(std::make_unique<SpecCodeBlock>(std::move(body
        )));
    }

    inline void register_teardown_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().register_teardown(std::make_unique<SpecCodeBlock>(std::move(body
        )));
    }
}
