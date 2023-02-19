#include <thread>

#include "SpecHelper.h"

TODO("SpecCallback with a boolean");
TODO("Top-level It() and Test() support");

xTest("I would like this to be an async test") {
    //
    //
    // done();
}

void RunMeOnAThread(SpecCallback done) {  // <--- SpecTest& instead of SpecCallback
    Print("Sleeping for 2 seconds");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Print("Done sleeping");
    done();
}

void BackgroundThreadFunction_UsingTryCatch(std::shared_ptr<AsyncSpec> spec) {
    spec->tryCatch([]() {
        //
        throw std::runtime_error("This is an exception from the background thread");
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

    it("catch exception in background thread (using tryCatch)", [](AsyncSpec& spec) {
        auto        specPtr = std::make_shared<AsyncSpec>(spec);
        std::thread t(BackgroundThreadFunction_UsingTryCatch, specPtr);
        t.detach();
    });

    xit("catch exception in background thread (using background)", [](AsyncSpec& spec) {

    });

    xit("SOME EXAMPLES!", [](AsyncSpec& spec) {
        spec.background([](SpecCallback done) {
            // you have to call done()
        });
        spec.background([](AsyncSpec& spec) {
            // you have to call spec.done()
        });
        spec.background([]() {
            // if no exception, test passes!
            // just try/catch
        });
    });
}

TODO("Async Setups and Teardowns");
