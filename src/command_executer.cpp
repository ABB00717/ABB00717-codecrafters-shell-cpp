#include "../include/command_executer.h"
#include <string>
#include <vector>

void executeCommand(const std::vector<std::string>& tokens) {
    if (tokens.empty())
        return;

    std::vector<std::string> cmdTokens;
        
    std::string command = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    if (command == "exit") {
        handleExit(args);
    } else if (command == "echo") {
        handleEcho(args);
    } else if (command == "type") {
        handleType(args);
    } else if (command == "pwd") {
        handlePwd();
    } else if (command == "cd") {
        handleCd(args);
    } else {
        std::string path = getPath(command);
        if (path.empty()) {
            commandNotFound(command);
            return;
        }

        // external exe
        handleExternalProgram(command, args);
    }
}
