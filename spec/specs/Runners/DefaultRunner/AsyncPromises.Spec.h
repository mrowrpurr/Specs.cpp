#include <thread>

#include "SpecHelper.h"

TODO("SpecCallback with a boolean");
TODO("Top-level It() and Test() support");

xTest("I would like this to be an async test") {
    //
    //
    // done();
}

void RunMeOnAThread(SpecCallback done
) {  // <--- SpecTest& instead of SpecCallback
    Print("Sleeping for 2 seconds");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Print("Done sleeping");
    done();
}

void BackgroundThreadFunction_UsingTryCatch(std::shared_ptr<AsyncSpec> spec) {
    spec->tryCatch([]() {
        //
        throw std::runtime_error(
            "This is an exception from the background thread"
        );
    });
    spec->done();
}

Describe("Async tests") {
    xit("simple done callback", [](SpecCallback done) {
        // Call done on a background thread (after a few seconds)
        std::thread t(RunMeOnAThread, done);
        t.detach();
    });

    xit("timeout", [](SpecCallback done) {
        // Does nothing! Never calls done()
    });

    // xit("catch exception in background thread (using tryCatch)",
    //     [](AsyncSpec& spec) {
    //         auto        specPtr = std::make_shared<AsyncSpec>(spec);
    //         std::thread t(BackgroundThreadFunction_UsingTryCatch, specPtr);
    //         t.detach();
    //     });

    // xit("catch exception in background thread (using background)",
    //     [](AsyncSpec& spec) {

    //     });

    describe("spec.background", []() {
        it("background [](SpecCallback done)");
        it("background [](std::shared_ptr<AsyncSpec> spec)",
           [](std::shared_ptr<AsyncSpec> spec) {
               spec->background([](std::shared_ptr<AsyncSpec> s) {
                   throw "Kaboom from background!!!!";
                   //    s->done("Kaboom from background!");
               });
           });

        xit("background []()", [](AsyncSpec& spec) {
            spec.background([]() {
                throw std::runtime_error("Kaboom from background 333!");
            });
        });
    });
}

TODO("Async Setups and Teardowns");
