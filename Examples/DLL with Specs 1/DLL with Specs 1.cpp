#include <Specs/DLL.h>
#include <Specs/Snowhouse.h>

Setup { _Log_("HELLO FROM SETUP 1"); }

Teardown {
    _Log_("HELLO FROM TEARDOWN 1");
    throw "FOO";
}

Test("Hello from a test") {
    _Log_("HELLO from a TEST!!");
    AssertThat(1, Equals(1));
}

Test("Hello from another test") {
    _Log_("HELLO from another TEST!!");
    AssertThat(1, Equals(69));
}

Test("Yet another") { throw "Throw a C string"; }
