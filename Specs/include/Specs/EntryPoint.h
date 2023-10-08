#pragma once

#include "BDD.h"
#include "CLI.h"
#include "Setup.h"

#if __has_include(<snowhouse/snowhouse.h>)
    #include <snowhouse/snowhouse.h>
    //
    #include <Specs/ExceptionHandlers/SnowhouseExceptionHandler.h>
#endif

int main(int argc, char* argv[]) {
    Specs::CLI cli;
    Specs::Setup(cli);
    Specs::BDD(cli);

#if __has_include(<snowhouse/snowhouse.h>)
    cli.GetApplication()->AddExceptionHandler<Specs::ExceptionHandlers::SnowhouseExceptionHandler>();
#endif

    return 0;
}
