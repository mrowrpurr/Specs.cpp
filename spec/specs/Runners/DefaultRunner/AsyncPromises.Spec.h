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
    // done()
    // done(true/false)
    // done("failure message")

    // And
    // done.background([](){
    // });

    // Oooooo me likey!
    // done.capture([&]() {
    //     // https://stackoverflow.com/a/25284064
    //     // promise.set_exception
    //     // try { promise.get() } catch { ... }
    // });

    Print("um, hello?????");

    // try {
    AssertThat("Something in the background thread", Equals("butts"));
    // } catch (...) {
    //     // set the test promise here to the current exception ptr
    // }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    Print("Done sleeping");
    done();
}

// TODO - accept AsyncSpec overload
void ThisThrowsAnException(AsyncSpec& spec) {
    //
    // spec.done("This is a failure message from the background thread");
    spec.done();
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

    it("catch exception in background thread", [](AsyncSpec& spec) {
        // TODO
        spec.background(ThisThrowsAnException);
    });
}

TODO("Async Setups and Teardowns");
