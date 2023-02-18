#include "SpecHelper.h"

TestGroup("Setup and Teardown");

Setup { Print("This is the setup!"); }
Setup { Print("This is another setup!"); }

Teardown { Print("This is the teardown!"); }

Test("Something!") { Print("This is something!"); }
Test("Something else!") { Print("This is something else!"); }
