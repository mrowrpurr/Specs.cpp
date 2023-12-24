#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

namespace SpecsCpp::DSLs::GlobalInterface {
    /* Template */

    inline void define_template_fn(std::string_view templateName, FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().define_template(
            templateName, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* Group */

    inline void define_group_fn(
        std::string_view description, FunctionPointer<void()> body, bool removeUnderscores = false
    ) {
        GlobalSpecGroup::instance().define_group(
            description, std::make_unique<SpecCodeBlock>(std::move(body)), removeUnderscores
        );
    }

    inline void define_group_fn(
        std::string_view description, FunctionPointer<void(ISpecGroup*)> body,
        bool removeUnderscores = false
    ) {
        GlobalSpecGroup::instance().define_group(
            description, std::make_unique<SpecCodeBlock>(std::move(body)), removeUnderscores
        );
    }

    /* Test */

    inline void define_test_fn(std::string_view description, FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_test_fn(std::string_view description, FunctionPointer<void(SpecDone)> body) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_test_fn(std::string_view description, FunctionPointer<void(ISpec*)> body) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_test_fn(
        std::string_view description, FunctionPointer<void(ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_test_fn(
        std::string_view description, FunctionPointer<void(ISpecGroup*)> body
    ) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_test_fn(
        std::string_view description, FunctionPointer<void(ISpecGroup*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_test_fn(
        std::string_view description, FunctionPointer<void(ISpecGroup*, ISpec*)> body
    ) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_test_fn(
        std::string_view description, FunctionPointer<void(ISpecGroup*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_spec(
            description, std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* Setup */

    inline void define_setup_fn(FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().define_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
    }

    inline void define_setup_fn(FunctionPointer<void(SpecDone)> body) {
        GlobalSpecGroup::instance().define_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
    }

    inline void define_setup_fn(FunctionPointer<void(ISpecComponent*, ISpec*)> body) {
        GlobalSpecGroup::instance().define_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
    }

    inline void define_setup_fn(FunctionPointer<void(ISpecComponent*, ISpec*, SpecDone)> body) {
        GlobalSpecGroup::instance().define_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
    }

    inline void define_setup_fn(FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*)> body) {
        GlobalSpecGroup::instance().define_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
    }

    inline void define_setup_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
    }

    /* Teardown */

    inline void define_teardown_fn(FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().define_teardown(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_teardown_fn(FunctionPointer<void(SpecDone)> body) {
        GlobalSpecGroup::instance().define_teardown(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_teardown_fn(FunctionPointer<void(ISpecComponent*, ISpec*)> body) {
        GlobalSpecGroup::instance().define_teardown(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_teardown_fn(FunctionPointer<void(ISpecComponent*, ISpec*, SpecDone)> body) {
        GlobalSpecGroup::instance().define_teardown(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_teardown_fn(FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*)> body
    ) {
        GlobalSpecGroup::instance().define_teardown(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_teardown_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_teardown(std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* One-time Setup */

    inline void define_one_time_setup_fn(FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().define_one_time_setup(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_setup_fn(FunctionPointer<void(SpecDone)> body) {
        GlobalSpecGroup::instance().define_one_time_setup(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_setup_fn(FunctionPointer<void(ISpecComponent*, ISpec*)> body) {
        GlobalSpecGroup::instance().define_one_time_setup(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_setup_fn(
        FunctionPointer<void(ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_one_time_setup(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_setup_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*)> body
    ) {
        GlobalSpecGroup::instance().define_one_time_setup(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_setup_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_one_time_setup(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    /* One-time Teardown */

    inline void define_one_time_teardown_fn(FunctionPointer<void()> body) {
        GlobalSpecGroup::instance().define_one_time_teardown(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_teardown_fn(FunctionPointer<void(SpecDone)> body) {
        GlobalSpecGroup::instance().define_one_time_teardown(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_teardown_fn(FunctionPointer<void(ISpecComponent*, ISpec*)> body) {
        GlobalSpecGroup::instance().define_one_time_teardown(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_teardown_fn(
        FunctionPointer<void(ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_one_time_teardown(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_teardown_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*)> body
    ) {
        GlobalSpecGroup::instance().define_one_time_teardown(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }

    inline void define_one_time_teardown_fn(
        FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*, SpecDone)> body
    ) {
        GlobalSpecGroup::instance().define_one_time_teardown(
            std::make_unique<SpecCodeBlock>(std::move(body))
        );
    }
}
