#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

struct CommandNode {
    std::vector<std::string> args;
    std::string outputFile;
};

std::vector<std::string> parseInputs(const std::string& input);
std::vector<CommandNode*> parseCommands(const std::vector<std::string>& tokens);

#endif