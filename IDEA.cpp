// Can we provide 2x types of groups?
//
// 1. For those with RUNNABLE test bodies such as below
// 2. For those which provide LAMBDAS for test bodies

Describe("Something") {
    std::string ThisWouldBeSimplyAVariableInTheSameStackAsTheItBelow;

    setup {}
    teardown {}

    it("should do something") {
        // ...
        test["blah"] = "blah";
    }

    it("should do something else") {
        // ...
    }
}
