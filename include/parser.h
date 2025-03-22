#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <unistd.h> // for STDOUT_FILENO

struct CommandNode {
    std::vector<std::string> args;
    std::string outputFile;

    int outputFd = STDOUT_FILENO;
};

std::vector<std::string> parseInputs(const std::string& input);
std::vector<CommandNode*> parseCommands(const std::vector<std::string>& tokens);

#endif