#pragma once

export module specs.interfaces;

export namespace SpecsCpp::v3 {
    struct IExampleInterface {
        virtual int GetNumber() = 0;
    };
}
