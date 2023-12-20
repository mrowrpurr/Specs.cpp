#pragma once

#include <Specs/API.h>
#include <Specs/GlobalSpecCodeBlocks.h>
#include <Specs/GlobalSpecEnvironment.h>
#include <Specs/GlobalSpecGroup.h>
#include <_Log_.h>

#ifdef _WIN32
extern "C" __declspec(dllexport
) SpecsCpp::ISpecGroup* SpecsCpp_Load(SpecsCpp::ISpecEnvironment* globalSpecEnvironment) {
#else
extern "C" SpecsCpp::ISpecGroup* SpecsCpp_Load(SpecsCpp::ISpecEnvironment* globalSpecEnvironment) {
#endif
    try {
        SpecsCpp::global_spec_environment().set(globalSpecEnvironment);
        SpecsCpp::GlobalSpecCodeBlocks::instance().run_code_blocks();
    } catch (const std::exception& e) {
        _Log_("Failed to load global code blocks: {}", e.what());
        return nullptr;
    } catch (...) {
        _Log_("Failed to load global code blocks: unknown exception");
        return nullptr;
    }
    return SpecsCpp::GlobalSpecGroup::instance().root();
}
