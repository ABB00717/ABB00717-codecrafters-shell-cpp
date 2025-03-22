#include <cstddef>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "../include/parser.h"

std::vector<std::string> parseInputs(const std::string& input) {
    std::stringstream ss(input);
    char c;
    std::vector<std::string> tokens;

    bool insideSingleQuotes = false;
    bool insideDoubleQuotes = false;
    bool escape = false;
    std::string currentToken;

    while (ss.get(c)) {
        if (escape) {
            escape = false;
            currentToken += c;
            continue;
        }
        if (c == '\\') {
            if (insideSingleQuotes) {
                currentToken += c;
            } else if (insideDoubleQuotes) {
                char next = ss.peek();
                if (next == '"' || next == '\\' || next == '$') {
                    escape = true;
                } else {
                    currentToken += c;
                }
            } else {
                escape = true;
            }
        } else if (c == '\'' && !insideDoubleQuotes) {
            insideSingleQuotes = !insideSingleQuotes;
        } else if (c == '"' && !insideSingleQuotes) {
            insideDoubleQuotes = !insideDoubleQuotes;
        } else if (std::isspace(c) && !insideSingleQuotes &&
                   !insideDoubleQuotes) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken += c;
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

std::vector<CommandNode*> parseCommands(const std::vector<std::string> &tokens) {
    std::vector<CommandNode*> commands;

    CommandNode* current = new CommandNode();

    for (size_t i = 0; i < tokens.size(); i++) {
        std::string tok = tokens[i];

        if (tok == "|") {

        } else if (tok == ">" || tok == "1>") {
            if (i + 1 < tokens.size()) {
                current->outputFile = tokens[++i];
                current->outputFd = STDOUT_FILENO;
                current->appendMode = false;
            }
        } else if (tok == "2>") {
            if (i + 1 < tokens.size()) {
                current->outputFile = tokens[++i];
                current->outputFd = STDERR_FILENO;
                current->appendMode = false;
            }
        } else if (tok == ">>" || tok == "1>>") {
            if (i + 1 < tokens.size()) {
                current->outputFile = tokens[++i];
                current->outputFd = STDOUT_FILENO;
                current->appendMode = true;
            }
        } else if (tok == "2>>") {
            if (i + 1 < tokens.size()) {
                current->outputFile = tokens[++i];
                current->outputFd = STDERR_FILENO;
                current->appendMode = true;
            }
        } else if (tok == "<") {
        } else {
            current->args.push_back(tok);
        }
    }

    commands.push_back(current);
    return commands;
}