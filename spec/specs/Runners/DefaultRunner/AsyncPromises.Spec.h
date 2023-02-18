#include <thread>

#include "SpecHelper.h"

TODO("SpecCallback with a boolean");
TODO("Top-level It() and Test() support");

xTest("I would like this to be an async test") {
    //
    //
    // done();
}

void RunMeOnAThread(SpecCallback done) {
    Print("um, hello?????");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Print("Done sleeping");
    // AssertThat("Something in the background thread", Equals("butts"));
    done();
}

Describe("Async tests") {
    it("simple done callback", [](SpecCallback done) {
        // Call done on a background thread (after a few seconds)
        std::thread t(RunMeOnAThread, done);
        t.detach();
    });

    it("timeout", [](SpecCallback done) {
        // Does nothing! Never calls done()
    });
}
