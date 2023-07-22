// #pragma once

#define __MetaMacro__Expand(...) __VA_ARGS__
#define __MetaMacro__Stringify(a) #a
#define __MetaMacro__Quote(a) __MetaMacro__Stringify(a)

#define __MetaMacro__CountArgs__Raw(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define __MetaMacro__CountArgs(...) \
    __MetaMacro__Expand(__MetaMacro__CountArgs__Raw(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define __MetaMacro__InvokeN__GetMacroName(macroName, count) macroName##count
#define __MetaMacro__InvokeN__InvokeMacro(macroName, count, ...) \
    __MetaMacro__Expand(__MetaMacro__InvokeN__GetMacroName(macroName, count)(__VA_ARGS__))

#define __MetaMacro__InvokeN(macroName, count, ...) __MetaMacro__InvokeN__InvokeMacro(macroName, count, __VA_ARGS__)

#define __MetaMacro__Concatenate_1(a) a
#define __MetaMacro__Concatenate_2(a, b) a##b
#define __MetaMacro__Concatenate_3(a, b, c) a##b##c
#define __MetaMacro__Concatenate_4(a, b, c, d) a##b##c##d
#define __MetaMacro__Concatenate_5(a, b, c, d, e) a##b##c##d##e
#define __MetaMacro__Concatenate_6(a, b, c, d, e, f) a##b##c##d##e##f
#define __MetaMacro__Concatenate_7(a, b, c, d, e, f, g) a##b##c##d##e##f##g
#define __MetaMacro__Concatenate(...) \
    __MetaMacro__InvokeN(__MetaMacro__Concatenate_, __MetaMacro__CountArgs(__VA_ARGS__), __VA_ARGS__)
