#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/dispatcher.h"

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;
    while (inputCommand(input)) {
        std::vector<std::string> tokens = parseInputs(input);
        std::vector<CommandNode*> commands = parseCommands(tokens);

        dispatchCommands(commands);
        for (auto command : commands)
            delete command;
    }
}
