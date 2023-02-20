#include <Specs/CLI.h>

int main() {
    Specs::CLI cli;

    std::vector<std::string> arguments = {"specs.cpp", "--runner", "default", "--reporter", "debug"};
    std::vector<char*>       argv;
    for (const auto& arg : arguments) argv.push_back((char*)arg.data());
    argv.push_back(nullptr);

    if (cli.Parse(argv.size() - 1, argv.data()))
        Print("Parsed argument ok!");
    else
        Print("Parsing argument failed!");
}
