#pragma once

#define RunSpecsMain \
    int main() { Spec::Internal::SpecController::GetSingleton().RunSpecs(); }
