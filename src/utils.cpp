#include "../include/utils.h"
#include <cctype>
#include <cstdio>
#include <string>

bool inputCommand(std::string& input) {
    std::cout << "$ ";
    if (std::getline(std::cin, input))
        return true;

    return false;
}

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

std::string getPath(std::string command) {
    try {
        std::string path_env = std::getenv("PATH");

        std::stringstream ss(path_env);
        std::string path;

        while (std::getline(ss, path, ':')) {
            std::filesystem::path abs_path = path;
            abs_path /= command;
            if (std::filesystem::exists(abs_path)) {
                return abs_path.string();
            }
        }
    } catch (...) {
        return "";
    }

    return "";
}