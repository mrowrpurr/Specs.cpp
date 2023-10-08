// #include <Specs/EntryPoint.h>

#include <Specs/DSL/Components/Macros/CoreMacroFeatures.h>
#include <_Log_.h>

int main() {
    _Log_("testing...");
    _Log_("Counter: {}", __MetaMacro__Quote(__COUNTER__));
    _Log_("Counter: {}", __MetaMacro__Quote(__COUNTER__));
    int x = __MetaMacro__CountArgs(one, two, three, four, five);
    _Log_("CountArgs: {}", x);
    _Log_("Concat: {}", __MetaMacro__Quote(__MetaMacro__Concatenate(one, two, three, four, five, six, seven)));

    _Log_(
        "Concat with stuff: {}",
        __MetaMacro__Quote(__MetaMacro__Concatenate(one, two, __FILE__, __LINE__, __COUNTER__, __DATE__, __TIME__))
    );

    return 0;
}
