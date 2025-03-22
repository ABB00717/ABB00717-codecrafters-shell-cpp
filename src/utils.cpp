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