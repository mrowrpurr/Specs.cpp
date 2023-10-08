#pragma once

// TODO make this not a total hack - total hack is fine for
// right now because the API will be basically the same

//
#include "SpecHelper.h"
//

#include <functional>
#include <vector>

namespace Specs::HacksPendingSpecsCppLibraryCompletion {
    std::vector<std::function<void()>> SpecDefinitionBodies;

    CollectSpecDefinitionBody::CollectSpecDefinitionBody(std::function<void()> body) {
        SpecDefinitionBodies.push_back(body);
    }
}

#include <Specs/BDD.h>
#include <Specs/CLI.h>
#if __has_include(<snowhouse/snowhouse.h>)
    #include <Specs/ExceptionHandlers/SnowhouseExceptionHandler.h>
#endif
#include <Specs/Setup.h>

namespace Specs {
    int Run(int argc, char** argv) {
        Specs::CLI cli;
        Specs::Setup(cli);
        Specs::BDD(cli);

#if __has_include(<snowhouse/snowhouse.h>)
        cli.GetApplication()
            ->AddExceptionHandler<Specs::ExceptionHandlers::SnowhouseExceptionHandler>();
#endif

        for (auto& specDefinitionBody :
             HacksPendingSpecsCppLibraryCompletion::SpecDefinitionBodies) {
            specDefinitionBody();
        }

        return cli.Run(argc, argv);
    }
}