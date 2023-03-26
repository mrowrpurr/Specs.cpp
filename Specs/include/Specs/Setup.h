#pragma once

#include "CLI.h"
#include "ExceptionHandlers/FallbackExceptionHandler.h"
#include "Reporters/OneLineReporter.h"
#include "Runners/QueueRunner.h"

namespace Specs {

    void Setup(const CLI& cli) {
        auto app = cli.GetApplication();
        app->AddExceptionHandler<Specs::ExceptionHandlers::FallbackExceptionHandler>();
        app->AddReporter<Specs::Reporters::OneLineReporter>();
        app->SetRunner<Specs::Runners::QueueRunner>();
    }
}